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
                | IDENTIFIER { st_top->type = new_arraytype(decl_tpye_base, (long) $3->extra.value); } 
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
function_params:    typed_params_group_seq
                    |
                    ;


           

%%

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

