void yyerror(char *);
//to identify section 
#define SEC_NONE 0
#define SEC_DECL 1
#define SEC_FDECL 2
#define SEC_FBODY 3

//datatype_t = "struct datatype"
typedef struct datatype datatype_t;

//enum ? to define a type 
typedef enum { B_INT=1, B_BOOL, B_ARRAY, B_FUNC } base_e;
//base_e is the type!

//to store a datatype 
struct datatype {
  base_e base; //int, bool, array, func
  base_e base2; //int, bool; when base=(array: obvious, func: return type)
  int size; //for array
  struct ptlist_n * ptlist; //for func: type of parameters
};



datatype_t *new_arraytype(base_e type, long size);
datatype_t *new_functype(base_e rettype);

//Parameter list 
struct ptlist_n {
  datatype_t * type; //int_type or bool_type
  char passby; //'v': value, 'r': reference
  struct ptlist_n *next;
};





//symbol stack node (symbol table )
// [  name datatype offset  ]

struct symstack_n {
  char id[32];
  datatype_t *type;
  int offset;
  struct symstack_n *next;
};

typedef struct symstack_n symstack_nt;
//Now you can use "symstack_nt" instead of  "struct symstack_n"

//adding new symbole to linked list structure of symbols 
void new_symbol(char *id);

struct symstack_n *lookup_sym(char *id);
//<type="struct symstack_n *"> <id = "lookup">(<params>);


void pop_locals();



void ftype_addparam(datatype_t *func, datatype_t *ptype, char passby);
void free_datatype(datatype_t *type);

typedef enum { T_IF=256, T_WHILE, T_WRITE, T_READ, T_ST_BLOCK, T_FBODY,
				 T_FRET, T_FCALL, T_FARGS, T_ARR_DREF, T_ID, T_BOOL_LIT, T_INT_LIT, 
				 T_NOT, T_AND, T_OR, T_REL_E, T_REL_NE, T_REL_LE, T_REL_GE } tag_e;


struct ast_n {
  int tag;
  struct ast_n *next;
  struct ast_n *fchild;
  union {
	struct symstack_n *st_entry; //symbol table entry //for ID: symstack_n pointer value
	long value; // for BOOL_LIT: corresponding value (0 or 1), INT_LIT: corresponding value (integer)
	datatype_t *type; //for <op>: corresponding int_type or bool_type
	void *other; //initialisation
  } extra;
};

typedef struct ast_n ast_nt;

#define YYSTYPE struct ast_n *

struct ast_n *create_node(int tag, struct ast_n *fchild, void *extra);
