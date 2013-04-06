
void yyerror(char *);
#define SEC_NONE 0
#define SEC_DECL 1
#define SEC_FDECL 2
#define SEC_FBODY 3

typedef struct datatype datatype_t;

struct symstack_n {
  char id[32];
  datatype_t *type;
  int offset; //for variables
  struct symstack_n *next;
};

typedef struct symstack_n symstack_nt;

void new_symbol(char *id);
symstack_nt *lookup_sym(char *id);
void pop_locals();

struct ptlist_n {
  datatype_t * type; //DT_INT or DT_BOOL
  char passby; //'v': value, 'r': reference
  struct ptlist_n *next;
};

typedef enum { B_INT=1, B_BOOL, B_ARRAY, B_FUNC } base_e;

struct datatype {
  base_e base; //int, bool, array, func
  base_e base2; //int, bool; when base=(array: obvious, func: return type)
  int size; //for array size; for function, size of activation record
  struct ptlist_n * ptlist; //for func: type of parameters
};

typedef enum { T_IF=256, T_WHILE, T_WRITE, T_READ, T_ST_BLOCK, T_FBODY,
			   T_FRET, T_FCALL, T_FARGS, T_ARR_DREF, T_ID, T_BOOL_LIT, T_INT_LIT, 
			   T_NOT, T_AND, T_OR, T_REL_E, T_REL_NE, T_REL_LE, T_REL_GE } tag_e;

struct ast_n {
  int tag;
  struct ast_n *next;
  struct ast_n *fchild;
  union {
	symstack_nt *st_entry; //symbol table entry
	long value;
	datatype_t *type;
	void *other;
  } extra;
  /** extra will store:
   * when title is
   * 	ID  	: symstack_n pointer value
   * 	BOOL_LIT: corresponding value (0 or 1)
   * 	INT_LIT	: corresponding value (integer)
   * 	<op>	: corresponding DT_INT or DT_BOOL
   * 	<other>	: "void" or "error"?
   */
};

typedef struct ast_n ast_nt;

#define YYSTYPE ast_nt *

ast_nt *create_node(int tag, ast_nt *fchild, void *extra);
