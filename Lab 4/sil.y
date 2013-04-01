%%
/**
//gloabl variables and function declarations 
//program start 
**/

program:  		    global_decls function_decls
			        ;


global_decl:		DECL global_coll ENDDECL
			        ;   


global_col:         global_var global_col 
                    |
                    ;


global var:         DATATYPE {assign type using a mid rule}


