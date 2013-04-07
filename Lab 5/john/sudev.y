%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sudev.h>

int line = 1, sec = SEC_NONE, error_count = 0, globals_length = 0 label_count = 0;  
char error_buffer[64];


//some variables of the type datatype refer .h file for the function definition 
s_dt *decl_type NULL, *param_type = NULL;
s_dt int_type = { B_INT }, bool_type = { B_BOOL };
s_dt *DT_INT = &int_type, *DT_BOOL = &bool_type;

struct s_st *st_top = NULL, *global_top, *cur_fun_def = NULL;
struct paralist_n *fftype_param_cur = NULL;

void globals_init();

//functions over astn node structure 
//checks for if it is something of the sort that we  have in ast 
int is_int(s_astn *);
int is_bool(s_astn *);
int is_type(s_astn *n, s_dt *i_b_type);
int is_op(int tag);
int is_arith_op(int tag);
int is_log_op(int tag);
s_dt *new_arraytype(base_e type, long size);
s_dt *new_functype(base_e rettype);
void func_calc_size();
void param_def_sematics(char passby);
void ftype_addparam(s_dt *func,s_dt *ptype,char passby);

s_dt *get_base2_wrapped(s_dt *type);


%}
%token BEG END READ WIRTE IF THEN ELSE ENDIF RETURN DECL ENDDECL  
%%
program:        decl_sect  { globals_init(); st_calc_offset(1);} funtcion_stream
                {
                    if (error_count == 0)
                    {
                        sim_start();
                    /*start sim if there is no error in the program */
                    }
                    else 
                    {    fprintf(stderr, "Could not start sim since there are errors              in                          the in program &d\n", error_count);
                    }
                }
                ;

decl_state:     DECL {sec = SECL_DECL;} decl_stream ENDDECL
                ;

decl_stream:    decl_stmt decl_stream
               |
               ;
decl_stmt:       DATATYPE var_def_stream ';'
                | function_head ';'
                ;
var_def_stream:
                var_def ',' var_def_stream 
                | var_def
                ;
var_def:        IDENTIFIER  { st_top->type = decl_type }
                | IDENTIFIER '[' I_LITERAL ']'   { st_top->type = new_arraytype(decl_tpye_base, (long) $3->extra.value); } 
                ;
function_head:  
                DATATYPE IDENTIFIER '(' { 
                    if (sec == SEC_DECL ) {
                        sec = F_DECL;
                        st_top->type = new_functype(decl_type->base);
                        }
                    else {
                        sec = SEC_DECL;
                        ftype_param_cur = (cur_func_def) ? cur_func_def->type->ptlist : NULL ;
                        }
                    }
                    function_params ')'
                    {
                    if (sec == SEC_DECL) {
                        if (ftype_param_cur) {
                            if(cur_func_def)
                                yyerror("function definition param not match 1 ");
                            yyerror("No of parameter passed not matching ");
                            ftype_param_cur = NULL;
                            cur_func_def = NULL;
                        }
                    sec = SEC_NONE;
                         }
                    else{ // sec == SECFDECL function declaration sec 
                    sec = SEC_DECL;
                        }
                    }
                    ;
function_params:    params_stream_group
                    |
                    ;
params_stream_group: params_stream ';'params_stream_group
                    |params_stream
                    |
                    ;
params_stream:      DATATYPE param_var_seq 
                    ;
param_var_seq:      param_var ',' param_var_seq
                    | param_var
                    ;
param_var:          IDENTIFIER { } /* define the passing method here */
                    |'&' IDENTIFIER  { } /* define the passing method for this */
                    ;
function_stream:    function_def function_stream
                    |
                    ;
function_def:       function_head '{' decl_sec
                    {
                    
                    }
                    function_body '}'
                    {
                    
                    }
                    ;
function_body:      BEG {  } stmt_block RETURN general_expr ';' END
                    {
                        
                    }
                    ;

stmt_block:         state_stream { }
                    ;

state_stream:       statement state_stream { }
                    | statement { }
                    ;
statement:          IF gen_expr THEN stmt_block ELSE stmt_block ENDIF ';' {}
                    |IF gen_expr THEN stmt_block ENDIF ';' {}
                    | WRITE '('gen_expr ')' ';' {}
                    | WHILE gen_expr DO stmt_block ENDWHILE ';' {}
                    | READ '(' var_rw ')' ';' {}
                    | var_rw '=' gen_expr ';' {} 
                    ;
gen_expr:          gen_bra BIN_LOG_OP gen_expr
                     {  
                     }
                    | NOT gen_expr
                    {   }
                    | gen_bra {} 
                    ;
gen_bra:            '(' gen_expr ')'
                    | a_expr RELOP a_expr
                    { }
                    | a_expr
                    ;
a_expr:             a_bra ADDITIVE_OP a_expr
                    { } 
                    | a_bra { }
                    ;
a_bra:              '(' a_expr ')' { }
                    | factor MULTIVE_OP a_bra
                    { }
                    | ADDITIVE_OP a_bra
                    { }
                    | factor { }
                    ;
factor:             
                    var_rw
                    | I_LITERAL {}
                    | B_LITERAL {}
                    | IDENTIFIER '(' argument_list ')' { }
                    ;
argument_list:      gen_expr arg_long { } 
                    |
                    ;
arg_long:           ',' gen_expr arg_long { }
                    |
                    ;

var_rw:             IDENTIFIER      { }
                    | IDENTIFIER '[' a_expr ']'
                     {  }
                    ;



%%

void yyerror(char *s){
    fprintf(stderr, "Line Number : %d --- %s\n",line , s);
    error_count++;
}

int main(void) { 
    new_symbol(main);
    st_top->top->type = new_functye(B_INT):
    yyparse();
    return (0)
    };

                
}
void globals_init()
{
    globals_top = st_top;
    globals_length = 0;
    s_st *cur = symstack_top;
    while(cur)
        {
        if (cur->type->base != B_FUNC) 
        {
            if(cur->type->base == B_ARRAY)
              {
                globals_length += cur->type->size;
              }
            else 
              {
              globals_length += 1;        
              }
         }
        cur = cur->next;
        }
}

//adding a new array type into datatype structure 
s_dt *new_arraytype(base_e type, long size) {
    s_dt *newtype = malloc(sizeof(s_dt));
    newtype->base = B_ARRAY;
    newtype->base2 = rettype;
    newtype->size = size;
    }

