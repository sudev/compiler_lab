void yyerror(char *);

//Assigning a value for each of the section to identify them properly
#define Sec_Fdecl 2
#define Sec_Fbody 3
#define Sec_None 0
#define Sec_Decl 1

//shortening the datatype 
typedef struct datatype s_dt; //datatype structute of functions, variables, id's
typedef struct symbols_n s_st; //symbol table stack 
typedef struct ast_n s_astn; //abstract syntax tree 
typedef struct paralist_n s_pln; //parameter list 

//new symbol fuction 
void new_symbol(char *id);
//looks up symbols from the symbol table 
s_st *lookup_sym(char *id);
//pop local variables from the symbol stack after the function call 
void pop_locals();


// A symbol stack to hold all variables and id's
struct symbols_n {
    char iden[32];
    sd_t *type;
    int offset;
    struct symbols_n *next;
};

//base type enumeration 
typedef enum { B_INT=1, B_BOOL, B_ARRAY, B_FUNC } base_enum

//store datatype details 
struct datatype {
    base_enum base; 
    base_enum base2; //secondary type array base , function return type 
    int size; //for array size 
    struct paralist_n * ptlist; //parameter storing list used for functions 
};

struct paralist_n {
    s_dt * type; // type of the parameter 
    char passtype; // type of passing the parameters 
    struct paralist_n *next; //linked list strcut 
}


//enumerating and typedefing the variables for compiler 
typedef enum { T_IF=256, T_WHILE, T_WRITE, T_READ, T_ST_BLOCK, T_FBODY, T_FRET, T_FCALL, T_FRAGS, T_ARR_DREF, T_ID, T_BOOL_LIT, T_INT_LIT, T_NOT, T_AND, T_OR, T_REL_E, T_REL_NE, T_REL_LE, T_REL_GE } tag_e;


//AST ------------- 
struct ast_n {
    int tag; //
    struct ast_n *next; //next in the ast 
    struct ast_n *fchild; //first child 
    union {
        symbols_n *st_entry;
        long value;
        s_dt *type;
        void *other;    
    }extra;

};

//----------abstract syntax tree structure 


//create ast node function prototpye 
s_astn *create_node(int tag, s_astn *fchild, void *extra);





































