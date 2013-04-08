%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commons.h"

const int debug = 0;
int line = 1, sec = SEC_NONE, error_count = 0, globals_size = 0, label_count = 0;
char error_buffer[64];
datatype_t *decl_type = NULL, *param_type = NULL;
datatype_t int_type = { B_INT }, bool_type = { B_BOOL };
datatype_t *DT_INT = &int_type, *DT_BOOL = &bool_type;

struct symstack_n *symstk_top = NULL, *global_top, *cur_func_def = NULL;
struct ptlist_n *ftype_param_cur = NULL;

void globals_init();

int is_int(ast_nt *);
int is_bool(ast_nt *);
int is_type(ast_nt *n, datatype_t *i_b_type);
int is_op(int tag);
int is_arith_op(int tag);
int is_log_op(int tag);

datatype_t *new_arraytype(base_e type, long size);

datatype_t *new_functype(base_e rettype);
void func_calc_size();
void param_def_semantics(char passby);
void ftype_addparam(datatype_t *func, datatype_t *ptype, char passby);

datatype_t *get_base2_wrapped(datatype_t *type);
void free_datatype(datatype_t *type);
char *get_tag_str(ast_nt *n);
void free_tree(ast_nt *);
void st_calc_offsets(int g);
void print_symstack(symstack_nt *sym_cur);
void print_tree(ast_nt *, int);
void sim_start();
void sim_halt();
void sim_func(ast_nt *fbody);
void sim_stmt(ast_nt *expr_n, int base_reg);

%}

%token DECL ENDDECL BEG END RETURN READ WRITE IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token BIN_LOG_OP REL_OP ADDITIVE_OP MULTIVE_OP
%token DATATYPE NOT
%token IDENTIFIER B_LITERAL I_LITERAL

%%
program:
		decl_sec { globals_init(); st_calc_offsets(1); if (!debug) sim_start(); } function_def_coll
		{
		  if (error_count == 0) {
			if (debug) printf("--\nParsing successfully completed!\n");
			else sim_halt();
		  } else
			fprintf(stderr, "--\nParsing completed with %d error(s)!\n", error_count);
		}
		;
decl_sec:
		DECL { sec = SEC_DECL; } decl_stmt_coll ENDDECL					{ sec = SEC_NONE; }
		;
decl_stmt_coll:
		decl_stmt decl_stmt_coll
		|
		;
decl_stmt:
		DATATYPE var_def_seq ';'
		| function_head ';'
		;
var_def_seq:
		var_def ',' var_def_seq
		| var_def
		;
var_def:
		IDENTIFIER														{ symstk_top->type = decl_type; }
		| IDENTIFIER '[' I_LITERAL ']'									{ symstk_top->type = new_arraytype(decl_type->base, $3->extra.value); }
		;
		
		
function_head:
		DATATYPE IDENTIFIER '(' {
		  if (sec == SEC_DECL) { //during function declaration
			sec = SEC_FDECL;
			symstk_top->type = new_functype(decl_type->base);
		  } else { //during function definition //sec==SEC_NONE
			sec = SEC_DECL;
			ftype_param_cur = (cur_func_def) ? cur_func_def->type->ptlist : NULL;
		  }
		} function_params ')'
		{
		  if (sec == SEC_DECL) { //f-definition
			if (ftype_param_cur) {
			  if (cur_func_def)
				yyerror("Function declaration and definition does not match!");
			  yyerror("> Less number of parameters in definition!");
			  ftype_param_cur = NULL;
			  cur_func_def = NULL;
			}
			sec = SEC_NONE;
		  } else //(sec == SEC_FDECL) f-declaration
			sec = SEC_DECL;
		}
		;
function_params:
		typed_params_group_seq
		|
		;
typed_params_group_seq:
		typed_params_group ';' typed_params_group_seq
		| typed_params_group
		;
typed_params_group:
		DATATYPE typed_group_param_seq
		;
typed_group_param_seq:
		param_def ',' typed_group_param_seq
		| param_def
		;

	//passing reference / value
param_def:
		IDENTIFIER														{ param_def_semantics('v'); }
		| '&' IDENTIFIER												{ param_def_semantics('r'); }
		;
function_def_coll:
		function_def function_def_coll
		|
		;
function_def:
		function_head '{' decl_sec
		{ 
		  if (cur_func_def) {
			func_calc_size();
			st_calc_offsets(0);
		  }
		}
		function_body '}'
		{
		  if (debug) {
			print_symstack(symstk_top);
			print_tree($5, 0);
		  } else if (error_count == 0)
			sim_func($5);
		  cur_func_def = NULL;
		  free_tree($5);
		  pop_locals();
		}
		;
function_body:
		BEG { sec = SEC_FBODY; } stmt_block RETURN general_expr ';' END
		{
		  sec = SEC_NONE;
		  $$ = create_node(T_FBODY, $3, NULL);
		  $3->next = create_node(T_FRET, $5, NULL);
		}
		;
stmt_block:
		general_stmt_seq												{ $$ = create_node(T_ST_BLOCK, $1, NULL); }
		;
general_stmt_seq:
		general_stmt general_stmt_seq									{ $$ = $1; $1->next = $2; }
		| general_stmt													{ $$ = $1; }
		;
general_stmt:
		IF general_expr THEN stmt_block ENDIF ';'						{ $$ = create_node(T_IF, $2, NULL); $2->next = $4; if (!is_bool($2)) yyerror("Bad if condition!"); }
		| IF general_expr THEN stmt_block ELSE stmt_block ENDIF ';'		{ $$ = create_node(T_IF, $2, NULL); $2->next = $4; $4->next = $6; if (!is_bool($2)) yyerror("Bad if condition!"); }
		| WHILE general_expr DO stmt_block ENDWHILE ';'					{ $$ = create_node(T_WHILE, $2, NULL); $2->next = $4; if (!is_bool($2)) yyerror("Bad while condition!"); }
		| WRITE '(' general_expr ')' ';'								{ $$ = create_node(T_WRITE, $3, NULL); }
		| READ '(' variable_rw ')' ';'									{ $$ = create_node(T_READ, $3, NULL); }
		| variable_rw '=' general_expr ';'								{ $$ = create_node('=', $1, NULL); $1->next = $3; if (!((is_bool($1) && is_bool($3)) || (is_int($1) && is_int($3)))) yyerror("Assignment failed!"); }
		;
general_expr:
		general_rel BIN_LOG_OP general_expr
		{
		  $$ = $2;
		  $$->fchild = $1;
		  $1->next = $3;
		  if (is_bool($1) && is_bool($3))
			$$->extra.type = DT_BOOL;
		}
		| NOT general_rel
		{
		  $$ = $1;
		  $$->fchild = $2;
		  if (is_bool($2))
			$$->extra.type = DT_BOOL;
		}
		| general_rel													{ $$ = $1; }
		;
general_rel:
		'(' general_expr ')'											{ $$ = $2; }
		| arith_expr REL_OP arith_expr
		{
		  $$ = $2;
		  $$->fchild = $1;
		  $1->next = $3;
		  if (is_int($1) && is_int($3))
			$$->extra.type = DT_BOOL;
		}
		| arith_expr													{ $$ = $1; }
		;
arith_expr:
		arith_term ADDITIVE_OP arith_expr
		{
		  $$ = $2;
		  $$->fchild = $1;
		  $1->next = $3;
		  if (is_int($1) && is_int($3))
			$$->extra.type = DT_INT;
		}
		| arith_term													{ $$ = $1; }
		;
arith_term:
		'(' arith_expr ')'												{ $$ = $2; }
		| factor MULTIVE_OP arith_term
		{
		  $$ = $2;
		  $$->fchild = $1;
		  $1->next = $3;
		  if (is_int($1) && is_int($3))
			$$->extra.type = DT_INT;
		}
		| ADDITIVE_OP arith_term
		{
		  $$ = $1;
		  $$->fchild = $2;
		  if (is_int($2))
			$$->extra.type = DT_INT;
		}
		| factor														{ $$ = $1; }
		;
factor:
		variable_rw														{ $$ = $1; }
		| I_LITERAL														{ $$ = $1; }
		| B_LITERAL 													{ $$ = $1; }
		| IDENTIFIER '(' argument_list ')'
		{
		  datatype_t *t = NULL;
		  symstack_nt *sym = $1->extra.st_entry;
		  if (sym && sym->type)
			if (sym->type->base == B_FUNC) {
			  ast_nt *args_looper = $3;
			  struct ptlist_n *para_looper = sym->type->ptlist;
			  while (args_looper && para_looper) {
				if (!is_type(args_looper, para_looper->type))
				  break;
				if (para_looper->passby == 'r' && args_looper->tag != T_ID)
				  break; //pass-by-reference => id must be passed
				args_looper = args_looper->next;
				para_looper = para_looper->next;
			  }
			  if (args_looper || para_looper) {
				if (args_looper)
				  if (!para_looper)
					yyerror("More number of arguments passed to the function than expected!");
				  else if (is_op(args_looper->tag) || args_looper->tag == T_ID) {
					if (args_looper->extra.other) //other => type or st_entry
					  yyerror("Invalid type passed to the function!");
				  } else
					yyerror("Invalid type passed to the function!");
				else
				  yyerror("Less number of arguments passed to the function than expected!");
				t = NULL;
			  } else
				t = get_base2_wrapped(sym->type);
			} else {
			  sprintf(error_buffer, "'%s' is not a function...", sym->id);
			  yyerror(error_buffer);
			}
		  $$ = create_node(T_FCALL, $1, t);
		  $1->next = create_node(T_FARGS, $3, NULL);
		}
		;
argument_list:
		general_expr arg_list_long										{ $$ = $1; $1->next = $2; }
		|																{ $$ = 0; }
		;
arg_list_long:
		',' general_expr arg_list_long									{ $$ = $2; $2->next = $3; }
		|																{ $$ = 0; }
		;
variable_rw:
		IDENTIFIER														{ $$ = $1; }
		| IDENTIFIER '[' arith_expr ']'
		{
		  datatype_t *t = NULL;
		  struct symstack_n *sym = $1->extra.st_entry;
		  if (sym && sym->type)
			if (sym->type->base == B_ARRAY)
			  t = get_base2_wrapped(sym->type);
			else {
			  sprintf(error_buffer, "'%s' is not an array...", sym->id);
			  yyerror(error_buffer);
			}
		  $$ = create_node(T_ARR_DREF, $1, t); $1->next = $3;
		}
		;
%%
void yyerror(char *s) {
  fprintf(stderr, "*** Line %d: %s\n", line, s);
  error_count++;
}

int main(void) {
  new_symbol("main");
  symstk_top->type = new_functype(B_INT);
  yyparse();
  return 0;
}

void param_def_semantics(char passby) {
  if (sec == SEC_FDECL)
	ftype_addparam(symstk_top->type, param_type, passby);
  else { //Function definition
	int err = 0;
	symstk_top->type = decl_type;
	if (!ftype_param_cur)
	  err = 1;
	else {
	  if (ftype_param_cur->type != decl_type)
		err = 2;
	  else if (ftype_param_cur->passby != passby)
		err = 3;
	  ftype_param_cur = ftype_param_cur->next;
	}
	if (err && cur_func_def) {
	  yyerror("Function declaration and definition does not match!");
	  yyerror(err == 1 ? "> More number of parameters in definition!" : err == 2 ? "> Type mismatch!" : "> Pass-by mechanism mismatch!");
	  cur_func_def = NULL;
	}
  }
}

//symstk_top will point to the new symbol
void new_symbol(char *id) {
  struct symstack_n * new_sym;
  new_sym = malloc(sizeof(struct symstack_n));
  strncpy(new_sym->id, id, 32);
  new_sym->type = NULL;
  new_sym->offset = 0;
  new_sym->next = symstk_top;
  symstk_top = new_sym;
}
//linked list remeber :)




struct symstack_n *lookup_sym(char *id) {
  struct symstack_n * cur_sym = symstk_top;
  while (cur_sym) {
	if (strcmp(cur_sym->id, id) == 0)
	  return cur_sym;
	cur_sym = cur_sym->next;
  }
  return NULL;
}




void globals_init() {
  global_top = symstk_top;
  globals_size = 0;
  symstack_nt *cur = symstk_top;
  while (cur) {
  	if (cur->type->base != B_FUNC) {
	  if (cur->type->base == B_ARRAY)
		globals_size += cur->type->size;
	  else
		globals_size++;
	}
	cur = cur->next;
  }
}

void pop_locals() {
  struct symstack_n * cur_sym = symstk_top;
  struct symstack_n * next_sym;
  while (cur_sym != global_top) {
	next_sym = cur_sym->next;
	free_datatype(cur_sym->type); //this was actually not req. CF's mistake 

	free(cur_sym);

	cur_sym = next_sym;
  }
  symstk_top = cur_sym;
}

void st_calc_offsets(int g) {
  symstack_nt *cur;
  int offset = 0, size;
  if (g) {
  	size = globals_size;
	cur = global_top;
	while(cur) {
	  if (cur->type->base != B_FUNC) {
		if (cur->type->base == B_ARRAY)
		  offset += cur->type->size;
		else
		  offset++;
		cur->offset = size - offset;
	  }
	  cur = cur->next;
	}
  } else {
	cur = symstk_top;
	size = cur_func_def->type->size;
	while (cur != global_top) {
	  cur->offset = size - ++offset;
	  cur = cur->next;
	}
  }
}

datatype_t *new_arraytype(base_e type, long size) {
  datatype_t *newtype = malloc(sizeof(datatype_t));
  newtype->base = B_ARRAY;
  newtype->base2 = type;
  newtype->size = size;
  return newtype;
}


datatype_t *new_functype(base_e rettype)
 {
  datatype_t *newtype = malloc(sizeof(datatype_t));
  newtype->base = B_FUNC;
  newtype->base2 = rettype;
  newtype->size = 0;
  newtype->ptlist = NULL;
  return newtype;
}



void func_calc_size() {
  symstack_nt *localsym = symstk_top;
  int s = 0;
  while (localsym!=global_top) {
	s++;
	localsym = localsym->next;
  }
  cur_func_def->type->size = s+1; //additional space for return value
}



void ftype_addparam(datatype_t *func, datatype_t *ptype, char passby) {
  struct ptlist_n *newparam = malloc(sizeof(struct ptlist_n));
  newparam->type = ptype;
  newparam->passby = passby;
  newparam->next = NULL;
  if (func->ptlist) {
	struct ptlist_n *cur_p = func->ptlist;
	while (cur_p->next)
	  cur_p = cur_p->next;
	cur_p->next = newparam;
  } else
	func->ptlist = newparam;
}



void free_datatype(datatype_t *type) {
  if (type->base == B_FUNC) {
	struct ptlist_n * cur_pt = type->ptlist, * next_pt;
	while (cur_pt) {
	  next_pt = cur_pt->next;
	  free(cur_pt);
	  cur_pt = next_pt;
	}
  } else if (type->base == B_ARRAY)
  	free(type);
}

ast_nt *create_node(int tag, ast_nt *fchild, void *extra) {
  ast_nt *newnode = malloc(sizeof(ast_nt));
  newnode->tag = tag;
  newnode->fchild = fchild;
  newnode->next = NULL;
  newnode->extra.other = extra;
  return newnode;
}

void print_symstack(symstack_nt *sym_cur) {
  if (sym_cur) {
	print_symstack(sym_cur->next);
	printf("\n%s%s <%d,%d,%d> %d", (sym_cur==global_top?"_":" "), sym_cur->id, sym_cur->type->base, sym_cur->type->base2, sym_cur->type->size, sym_cur->offset);
  }
}

int is_type(ast_nt *n, datatype_t *i_b_type) {
  if (i_b_type == DT_INT)
	return is_int(n);
  else if (i_b_type == DT_BOOL)
	return is_bool(n);
  else
	return 0;
}

int is_int(ast_nt *n) {
  if (n->tag == T_INT_LIT)
	return 1;
  if (n->tag == T_ID)
	return (n->extra.st_entry && n->extra.st_entry->type == DT_INT);
  else if (n->tag == T_FCALL)
	return (n->extra.type == DT_INT);
  else if (is_arith_op(n->tag))
	return (n->extra.type ? 1 : 0);
  return 0;
}

int is_bool(ast_nt *n) {
  if (n->tag == T_BOOL_LIT)
	return 1;
  struct symstack_n *sym;
  if (n->tag == T_ID)
	return  (n->extra.st_entry && n->extra.st_entry->type == DT_BOOL);
  else if (n->tag == T_FCALL)
	return (n->extra.type == DT_BOOL);
  else if (is_log_op(n->tag))
	return (n->extra.type ? 1 : 0);
  return 0;
}

int is_op(int tag) {
  return is_arith_op(tag) || is_log_op(tag);
}

int is_arith_op(int tag) {
  switch (tag) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	  return 1;
  }
  return 0;
}

int is_log_op(int tag) {
  switch (tag) {
	case T_NOT:
	case T_AND:
	case T_OR:
	case T_REL_E:
	case T_REL_NE:
	case T_REL_LE:
	case T_REL_GE:
	case '>':
	case '<':
	  return 1;
  }
  return 0;
}

datatype_t *get_base2_wrapped(datatype_t *type) {
  if (!type)
	return NULL;
  if (type->base == B_ARRAY || type->base == B_FUNC)
	return (type->base2 == B_INT) ? DT_INT : DT_BOOL;
  return NULL;
}

void free_tree(ast_nt *n) {
  ast_nt *child = n->fchild, *next;
  while (child) {
	next = child->next;
	free_tree(child);
	child = next;
  }
  free(n);
}

void sim_start() {
  printf("START\n");
  symstack_nt *main_sym;
  int n;
  printf("MOV R0, 0\n");
  printf("MOV R1, %d\n", globals_size);
  printf("ADD R0, R1\n");
  printf("MOV SP, R0\n");
  main_sym = symstk_top;
  while (main_sym->next)
	main_sym = main_sym->next;
  n = main_sym->type->size;
  printf("MOV R1, %d\n", n);
  printf("ADD R0, R1\n");
  printf("MOV SP, R0\n");
  printf("MOV R1, %d\n", n-1);
  printf("SUB R0, R1\n");
  printf("MOV BP, R0\n");
  printf("CALL main\n");
  //printf("MOV R0, [BP]\n"); //what main returns is not used!! So why move ??
  printf("JMP end\n");
}

void sim_halt() {
  printf("end:\nHALT\n");
}

void sim_func(ast_nt *fbody) {
  if (fbody->tag == T_FBODY) {
	printf("%s:\n", cur_func_def->id);
	sim_stmt(fbody->fchild, 0); //T_ST_BLOCK
	sim_stmt(fbody->fchild->next, 0); //T_FRET
  }
}

void sim_bin_op(ast_nt *astn1, ast_nt *astn2, int Ri, int Rj, char *op) {
  printf("PUSH R%d\n", Rj);
  sim_stmt(astn1, Ri);
  sim_stmt(astn2, Rj);
  printf("%s R%d, R%d\n", op, Ri, Rj);
  printf("POP R%d\n", Rj);
}

void sim_get_addr(ast_nt *astn, int Ri) { //TODO: Global variables, Array
  int Rj = (Ri+1)%8;
  //astn: Assumed to be T_ID now
  printf("MOV R%d, BP\n", Ri);
  printf("PUSH R%d\n", Rj);
  printf("MOV R%d, %d\n", Rj, astn->extra.st_entry->offset);
  printf("ADD R%d, R%d\n", Ri, Rj);
  printf("POP R%d\n", Rj);
}

void sim_stmt(ast_nt *expr_n, int base_reg) {
  if (!expr_n) return;
  int Ri, Rj, Rk, n;
  Ri = base_reg;
  Rj = (Ri+1)%8;
  Rk = (Ri+2)%8;
  ast_nt *astn1, *astn2;
  astn1 = expr_n->fchild;
  astn2 = (astn1) ? astn1->next : NULL;
  //printf("--%s\n", get_tag_str(expr_n));
  switch (expr_n->tag) {
	case T_IF:
	  n = label_count++;
	  sim_stmt(astn1, Ri);
	  printf("JZ R%d, ifnot%d\n", Ri, n);
	  sim_stmt(astn2, Ri);
	  printf("JMP endif%d\n", n);
	  printf("ifnot%d:\n", n);
	  sim_stmt(astn2->next, Ri);
	  printf("endif%d:\n", n);
	  break;
	case T_WHILE:
	  n = label_count++;
	  printf("while%d:\n", n);
	  sim_stmt(astn1, Ri);
	  printf("JZ R%d, endwhile%d\n", Ri, n);
	  sim_stmt(astn2, Ri);
	  printf("JMP while%d\n", n);
	  printf("endwhile%d:\n", n);
	  break;
	case T_WRITE:
	  sim_stmt(astn1, Ri);
	  printf("OUT R%d\n", Ri);
	  break;
	case T_READ:
	  printf("IN R%d\n", Ri);
	  printf("PUSH R%d\n", Rj);
	  sim_get_addr(astn1, Rj);
	  printf("MOV [R%d], R%d\n", Rj, Ri);
	  printf("POP R%d\n", Rj);
	  break;
	case T_ST_BLOCK:
	  while (astn1) {
		sim_stmt(astn1, base_reg);
		astn1 = astn1->next;
	  }
	  break;
	case T_FCALL:
	  //(expr_n->fchild->next) has tag (T_FARGS)
	  astn1 = expr_n->fchild->next->fchild; //fchild of T_FARGS
	  astn2 = expr_n->fchild; //T_ID of type function
	  n = astn2->extra.st_entry->type->size;
	  printf("MOV R%d, SP\n", Ri);
	  printf("PUSH R%d\n", Rj);
	  printf("MOV R%d, %d\n", Rj, n);
	  printf("ADD R%d, R%d\n", Ri, Rj);
	  printf("MOV SP, R%d\n", Ri);
	  printf("MOV R%d, %d\n", Rj, n-1);
	  printf("SUB R%d, R%d\n", Ri, Rj);

	  //Here: Ri will contain the BP (act. rec.) of the calling function, and SP will point to the end of act. rec.
	  printf("PUSH R%d\n", Rk);
	  int Rl = (Rk+1)%8, off = 1;
	  printf("PUSH R%d\n", Rl);
	  while(astn1) {
		sim_stmt(astn1, Rj); //Rj will contain the result of astn1
		printf("MOV R%d, R%d\n", Rk, Ri);
		printf("MOV R%d, %d\n", Rl, off++); //offset
		printf("ADD R%d, R%d\n", Rk, Rl);
		printf("MOV [R%d], R%d\n", Rk, Rj);
		astn1 = astn1->next;
	  }
	  printf("POP R%d\n", Rl);
	  printf("POP R%d\n", Rk);
	  printf("POP R%d\n", Rj);

	  printf("PUSH BP\n");
	  printf("MOV BP, R%d\n", Ri);
	  printf("CALL %s\n", astn2->extra.st_entry->id);
	  printf("POP BP\n");
	  
	  //Return the stack pointer
	  printf("MOV SP, R%d\n", Ri); //Pop off activation record except the return value
	  printf("POP R%d\n", Ri); //Move to Ri, the value returned by function
	  break;
	case T_FRET:
	  sim_stmt(astn1, Ri);
	  printf("MOV [BP], R%d\n", Ri);
	  printf("RET\n");
	  break;
	case T_ARR_DREF:
	  //return "array-elem";
	  break;
	case T_NOT:
	  printf("PUSH R%d\n", Rj);
	  sim_stmt(astn1, Rj);
	  printf("MOV R%d, 1\n", Ri);
	  printf("SUB R%d, R%d\n", Ri, Rj);
	  printf("POP R%d\n", Rj);
	  break;
	case T_AND:
	  n = label_count++;
	  printf("PUSH R%d\n", Rj);
	  sim_stmt(astn1, Ri);
	  printf("MOV R%d, 1\n", Rj);
	  printf("EQ R%d, R%d\n", Ri, Rj);
	  printf("JZ R%d, and%d\n", Ri, n);
	  sim_stmt(astn2, Rj);
	  printf("EQ R%d, R%d\n", Ri, Rj);
	  printf("and%d:\n", n);
	  printf("POP R%d\n", Rj);
	  break;
	case T_OR:
	  n = label_count++;
	  printf("PUSH R%d\n", Rj);
	  sim_stmt(astn1, Ri);
	  printf("MOV R%d, 1\n", Rj);
	  printf("EQ R%d, R%d\n", Ri, Rj);
	  printf("JNZ R%d, or%d\n", Ri, n);
	  sim_stmt(astn2, Rj);
	  printf("EQ R%d, R%d\n", Ri, Rj);
	  printf("or%d:\n", n);
	  printf("POP R%d\n", Rj);
	  break;
	case T_REL_E:
	  sim_bin_op(astn1, astn2, Ri, Rj, "EQ");
	  break;
	case T_REL_NE:
	  sim_bin_op(astn1, astn2, Ri, Rj, "NE");
	  break;
	case T_REL_LE:
	  sim_bin_op(astn1, astn2, Ri, Rj, "LE");
	  break;
	case T_REL_GE:
	  sim_bin_op(astn1, astn2, Ri, Rj, "GE");
	  break;
	case '>':
	  sim_bin_op(astn1, astn2, Ri, Rj, "GT");
	  break;
	case '<':
	  sim_bin_op(astn1, astn2, Ri, Rj, "LT");
	  break;
	case '+':
	  sim_bin_op(astn1, astn2, Ri, Rj, "ADD");
	  break;
	case '-':
	  sim_bin_op(astn1, astn2, Ri, Rj, "SUB");
	  break;
	case '*':
	  sim_bin_op(astn1, astn2, Ri, Rj, "MUL");
	  break;
	case '/':
	  sim_bin_op(astn1, astn2, Ri, Rj, "DIV");
	  break;
	case '%':
	  sim_bin_op(astn1, astn2, Ri, Rj, "MOD");
	  break;
	case '=':
	  printf("PUSH R%d\n", Rj);
	  sim_stmt(astn2, Rj);
	  sim_get_addr(astn1, Ri);
	  printf("MOV [R%d], R%d\n", Ri, Rj);
	  printf("POP R%d\n", Rj);
	  break;
	case T_ID:
	  astn1 = expr_n;
	  printf("PUSH R%d\n", Rj);
	  printf("PUSH R%d\n", Rk);
	  printf("MOV R%d, BP\n", Rj);
	  printf("MOV R%d, %d\n", Rk, astn1->extra.st_entry->offset);
	  printf("ADD R%d, R%d\n", Rj, Rk);
	  printf("MOV R%d, [R%d]\n", Ri, Rj);
	  printf("POP R%d\n", Rk);
	  printf("POP R%d\n", Rj);
	  break;
	case T_BOOL_LIT:
	case T_INT_LIT:
	  printf("MOV R%d, %ld\n", Ri, expr_n->extra.value);
	  break;
	default:
	  break;
  }
}

void print_tree(ast_nt *n, int depth) {
  ast_nt *child = n->fchild;
  int i;
  printf("\n");
  for (i=0; i<depth; i++)
	printf(" ");
  printf("(%s", get_tag_str(n));
  while (child) {
	print_tree(child, depth+1);
	child = child->next;
  }
  printf(")"); fflush(stdout);
  if (!depth) printf("\n");
}

char *get_tag_str(ast_nt *n) {
  switch (n->tag) {
	case T_IF:
	  return "if";
	case T_WHILE:
	  return "while";
	case T_WRITE:
	  return "write";
	case T_READ:
	  return "read";
	case T_ST_BLOCK:
	  return "block";
	case T_FBODY:
	  return "func";
	case T_FRET:
	  return "return";
	case T_FCALL:
	  return "call";
	case T_FARGS:
	  return "args";
	case T_ARR_DREF:
	  return "array-elem";
	case T_NOT:
	  return "not";
	case T_AND:
	  return "and";
	case T_OR:
	  return "or";
	case T_REL_E:
	  return "==";
	case T_REL_NE:
	  return "!=";
	case T_REL_LE:
	  return "<=";
	case T_REL_GE:
	  return ">=";
	case '>':
	case '<':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	  return (char[]) {(char) n->tag, '\0'};
	case T_ID:
	  return n->extra.st_entry->id;
	case T_BOOL_LIT:
	  return (n->extra.value ? "TRUE" : "FALSE");
	case T_INT_LIT:
	  return "INT";
  }
  return "X";
}
