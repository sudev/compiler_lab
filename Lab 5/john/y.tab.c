/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "sil.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commons.h"

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
void free_tree(ast_nt *);
void st_calc_offsets(int g);

void sim_start();
void sim_func(ast_nt *fbody);
void sim_stmt(ast_nt *expr_n, int base_reg);


/* Line 371 of yacc.c  */
#line 110 "y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DECL = 258,
     ENDDECL = 259,
     BEG = 260,
     END = 261,
     RETURN = 262,
     READ = 263,
     WRITE = 264,
     IF = 265,
     THEN = 266,
     ELSE = 267,
     ENDIF = 268,
     WHILE = 269,
     DO = 270,
     ENDWHILE = 271,
     BIN_LOG_OP = 272,
     REL_OP = 273,
     ADDITIVE_OP = 274,
     MULTIVE_OP = 275,
     DATATYPE = 276,
     NOT = 277,
     IDENTIFIER = 278,
     B_LITERAL = 279,
     I_LITERAL = 280
   };
#endif
/* Tokens.  */
#define DECL 258
#define ENDDECL 259
#define BEG 260
#define END 261
#define RETURN 262
#define READ 263
#define WRITE 264
#define IF 265
#define THEN 266
#define ELSE 267
#define ENDIF 268
#define WHILE 269
#define DO 270
#define ENDWHILE 271
#define BIN_LOG_OP 272
#define REL_OP 273
#define ADDITIVE_OP 274
#define MULTIVE_OP 275
#define DATATYPE 276
#define NOT 277
#define IDENTIFIER 278
#define B_LITERAL 279
#define I_LITERAL 280



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 226 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   117

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    32,     2,
      30,    31,     2,     2,    27,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
       2,    35,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    28,     2,    29,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    33,     2,    34,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     8,     9,    14,    17,    18,    22,
      25,    29,    31,    33,    38,    39,    46,    48,    49,    53,
      55,    58,    62,    64,    66,    69,    72,    73,    74,    81,
      82,    90,    92,    95,    97,   104,   113,   120,   126,   132,
     137,   141,   144,   146,   150,   154,   156,   160,   162,   166,
     170,   173,   175,   177,   179,   181,   186,   189,   190,   194,
     195,   197
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    -1,    39,    38,    52,    -1,    -1,     3,
      40,    41,     4,    -1,    42,    41,    -1,    -1,    21,    43,
      26,    -1,    45,    26,    -1,    44,    27,    43,    -1,    44,
      -1,    23,    -1,    23,    28,    25,    29,    -1,    -1,    21,
      23,    30,    46,    47,    31,    -1,    48,    -1,    -1,    49,
      26,    48,    -1,    49,    -1,    21,    50,    -1,    51,    27,
      50,    -1,    51,    -1,    23,    -1,    32,    23,    -1,    53,
      52,    -1,    -1,    -1,    45,    33,    39,    54,    55,    34,
      -1,    -1,     5,    56,    57,     7,    60,    26,     6,    -1,
      58,    -1,    59,    58,    -1,    59,    -1,    10,    60,    11,
      57,    13,    26,    -1,    10,    60,    11,    57,    12,    57,
      13,    26,    -1,    14,    60,    15,    57,    16,    26,    -1,
       9,    30,    60,    31,    26,    -1,     8,    30,    67,    31,
      26,    -1,    67,    35,    60,    26,    -1,    61,    17,    60,
      -1,    22,    61,    -1,    61,    -1,    30,    60,    31,    -1,
      62,    18,    62,    -1,    62,    -1,    63,    19,    62,    -1,
      63,    -1,    30,    62,    31,    -1,    64,    20,    63,    -1,
      19,    63,    -1,    64,    -1,    67,    -1,    25,    -1,    24,
      -1,    23,    30,    65,    31,    -1,    60,    66,    -1,    -1,
      27,    60,    66,    -1,    -1,    23,    -1,    23,    28,    62,
      29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    51,    51,    51,    60,    60,    63,    64,    67,    68,
      71,    72,    75,    76,    79,    79,   103,   104,   107,   108,
     111,   114,   115,   118,   119,   122,   123,   127,   126,   143,
     143,   151,   154,   155,   158,   159,   160,   161,   162,   163,
     166,   174,   181,   184,   185,   193,   196,   204,   207,   208,
     216,   223,   226,   227,   228,   229,   268,   269,   272,   273,
     276,   277
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DECL", "ENDDECL", "BEG", "END",
  "RETURN", "READ", "WRITE", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "ENDWHILE", "BIN_LOG_OP", "REL_OP", "ADDITIVE_OP", "MULTIVE_OP",
  "DATATYPE", "NOT", "IDENTIFIER", "B_LITERAL", "I_LITERAL", "';'", "','",
  "'['", "']'", "'('", "')'", "'&'", "'{'", "'}'", "'='", "$accept",
  "program", "$@1", "decl_sec", "$@2", "decl_stmt_coll", "decl_stmt",
  "var_def_seq", "var_def", "function_head", "$@3", "function_params",
  "typed_params_group_seq", "typed_params_group", "typed_group_param_seq",
  "param_def", "function_def_coll", "function_def", "$@4", "function_body",
  "$@5", "stmt_block", "general_stmt_seq", "general_stmt", "general_expr",
  "general_rel", "arith_expr", "arith_term", "factor", "argument_list",
  "arg_list_long", "variable_rw", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    59,    44,    91,    93,
      40,    41,    38,   123,   125,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    38,    37,    40,    39,    41,    41,    42,    42,
      43,    43,    44,    44,    46,    45,    47,    47,    48,    48,
      49,    50,    50,    51,    51,    52,    52,    54,    53,    56,
      55,    57,    58,    58,    59,    59,    59,    59,    59,    59,
      60,    60,    60,    61,    61,    61,    62,    62,    63,    63,
      63,    63,    64,    64,    64,    64,    65,    65,    66,    66,
      67,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     0,     4,     2,     0,     3,     2,
       3,     1,     1,     4,     0,     6,     1,     0,     3,     1,
       2,     3,     1,     1,     2,     2,     0,     0,     6,     0,
       7,     1,     2,     1,     6,     8,     6,     5,     5,     4,
       3,     2,     1,     3,     3,     1,     3,     1,     3,     3,
       2,     1,     1,     1,     1,     4,     2,     0,     3,     0,
       1,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     4,     0,     2,     7,     1,    26,     0,     0,     7,
       0,     0,     0,     3,    26,    12,     0,    11,     5,     6,
       9,     0,     0,    25,     0,    14,     8,     0,    27,     0,
      17,    12,    10,     0,    13,     0,     0,    16,    19,    29,
       0,    23,     0,    20,    22,    15,     0,     0,    28,    24,
       0,    18,     0,     0,     0,     0,    60,     0,    31,    33,
       0,    21,     0,     0,     0,     0,    60,    54,    53,     0,
       0,    42,    45,    47,    51,    52,     0,     0,     0,    32,
       0,     0,     0,     0,    50,    41,    57,     0,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,     0,    43,    48,     0,    40,    44,    46,    49,
       0,    61,     0,    39,    38,    37,     0,    56,    55,     0,
       0,     0,    30,    59,     0,    34,    36,    58,     0,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     6,     3,     4,     8,     9,    16,    17,    10,
      30,    36,    37,    38,    43,    44,    13,    14,    33,    40,
      47,    57,    58,    59,    70,    71,    72,    73,    74,   102,
     117,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -89
static const yytype_int8 yypact[] =
{
      20,   -89,    28,   -89,     9,   -89,    13,    15,    32,     9,
      29,    18,    19,   -89,    13,   -10,    35,    33,   -89,   -89,
     -89,    16,    20,   -89,    40,   -89,   -89,    31,   -89,    41,
      48,    46,   -89,    66,   -89,   -18,    44,   -89,    50,   -89,
      45,   -89,    54,   -89,    51,   -89,    48,    -1,   -89,   -89,
     -18,   -89,    52,    53,    26,    26,    56,    73,   -89,    -1,
      55,   -89,    58,    26,    34,    43,    -4,   -89,   -89,    26,
      74,    69,    70,    68,    71,   -89,    77,    34,    26,   -89,
      26,    62,    63,    34,   -89,   -89,    26,    64,   -14,    -1,
      26,    34,    34,    34,    -1,    60,    72,    75,    76,    78,
      65,    79,    80,   -89,   -89,    27,   -89,   -89,   -89,   -89,
      81,   -89,    93,   -89,   -89,   -89,    26,   -89,   -89,    -1,
      82,    83,   -89,    79,    87,   -89,   -89,   -89,    84,   -89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -89,   -89,   -89,    85,   -89,    94,   -89,    86,   -89,     5,
     -89,   -89,    59,   -89,    67,   -89,    98,   -89,   -89,   -89,
     -89,   -88,    57,   -89,   -53,    49,   -48,   -61,   -89,   -89,
      -8,   -47
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      60,   105,    76,    84,    91,    41,   110,    52,    53,    54,
      82,    12,    60,    55,    42,    81,    87,   104,    24,    12,
      25,    88,    56,     1,    77,    96,    86,    97,     5,    95,
       7,   124,   109,   101,    11,   100,    18,   106,    15,   119,
     120,    21,    60,   107,   108,    64,    25,    60,    65,    66,
      67,    68,    22,    64,    31,    20,    69,    66,    67,    68,
      27,    26,    64,   123,    83,    29,    66,    67,    68,    35,
      34,    39,    60,    69,    24,    45,    46,    49,    50,    48,
      78,    56,    62,    63,    77,    89,    90,    92,    91,   111,
      80,    93,    94,    98,    99,   103,   104,   121,   112,   122,
     128,   113,   114,    19,   115,    51,   116,    28,   125,   126,
     129,   118,    23,    32,    85,   127,    79,    61
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-89)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
      47,    89,    55,    64,    18,    23,    94,     8,     9,    10,
      63,     6,    59,    14,    32,    62,    69,    31,    28,    14,
      30,    69,    23,     3,    28,    78,    30,    80,     0,    77,
      21,   119,    93,    86,    21,    83,     4,    90,    23,    12,
      13,    23,    89,    91,    92,    19,    30,    94,    22,    23,
      24,    25,    33,    19,    23,    26,    30,    23,    24,    25,
      27,    26,    19,   116,    30,    25,    23,    24,    25,    21,
      29,     5,   119,    30,    28,    31,    26,    23,    27,    34,
       7,    23,    30,    30,    28,    11,    17,    19,    18,    29,
      35,    20,    15,    31,    31,    31,    31,    16,    26,     6,
      13,    26,    26,     9,    26,    46,    27,    22,    26,    26,
      26,    31,    14,    27,    65,   123,    59,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    37,    39,    40,     0,    38,    21,    41,    42,
      45,    21,    45,    52,    53,    23,    43,    44,     4,    41,
      26,    23,    33,    52,    28,    30,    26,    27,    39,    25,
      46,    23,    43,    54,    29,    21,    47,    48,    49,     5,
      55,    23,    32,    50,    51,    31,    26,    56,    34,    23,
      27,    48,     8,     9,    10,    14,    23,    57,    58,    59,
      67,    50,    30,    30,    19,    22,    23,    24,    25,    30,
      60,    61,    62,    63,    64,    67,    60,    28,     7,    58,
      35,    67,    60,    30,    63,    61,    30,    60,    62,    11,
      17,    18,    19,    20,    15,    62,    60,    60,    31,    31,
      62,    60,    65,    31,    31,    57,    60,    62,    62,    63,
      57,    29,    26,    26,    26,    26,    27,    66,    31,    12,
      13,    16,     6,    60,    57,    26,    26,    66,    13,    26
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 51 "sil.y"
    { globals_init(); st_calc_offsets(1); }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 52 "sil.y"
    {
		  if (error_count == 0)
			sim_start();
		  else
			fprintf(stderr, "--\nParsing completed with %d error(s)!\n", error_count);
		}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 60 "sil.y"
    { sec = SEC_DECL; }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 60 "sil.y"
    { sec = SEC_NONE; }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 75 "sil.y"
    { symstk_top->type = decl_type; }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 76 "sil.y"
    { symstk_top->type = new_arraytype(decl_type->base, (long) (yyvsp[(3) - (4)])->extra.value); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 79 "sil.y"
    {
		  if (sec == SEC_DECL) { //during function declaration
			sec = SEC_FDECL;
			symstk_top->type = new_functype(decl_type->base);
		  } else { //during function definition
			sec = SEC_DECL;
			ftype_param_cur = (cur_func_def) ? cur_func_def->type->ptlist : NULL;
		  }
		}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 88 "sil.y"
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
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 118 "sil.y"
    { param_def_semantics('v'); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 119 "sil.y"
    { param_def_semantics('r'); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 127 "sil.y"
    { 
		  if (cur_func_def) {
			func_calc_size();
			st_calc_offsets(0);
		  }
		}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 134 "sil.y"
    {
		  if (error_count == 0)
			sim_func((yyvsp[(5) - (6)]));
		  cur_func_def = NULL;
		  free_tree((yyvsp[(5) - (6)]));
		  pop_locals();
		}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 143 "sil.y"
    { sec = SEC_FBODY; }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 144 "sil.y"
    {
		  sec = SEC_NONE;
		  (yyval) = create_node(T_FBODY, (yyvsp[(3) - (7)]), NULL);
		  (yyvsp[(3) - (7)])->next = create_node(T_FRET, (yyvsp[(5) - (7)]), NULL);
		}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 151 "sil.y"
    { (yyval) = create_node(T_ST_BLOCK, (yyvsp[(1) - (1)]), NULL); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 154 "sil.y"
    { (yyval) = (yyvsp[(1) - (2)]); (yyvsp[(1) - (2)])->next = (yyvsp[(2) - (2)]); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 155 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 158 "sil.y"
    { (yyval) = create_node(T_IF, (yyvsp[(2) - (6)]), NULL); (yyvsp[(2) - (6)])->next = (yyvsp[(4) - (6)]); if (!is_bool((yyvsp[(2) - (6)]))) yyerror("Bad if condition!"); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 159 "sil.y"
    { (yyval) = create_node(T_IF, (yyvsp[(2) - (8)]), NULL); (yyvsp[(2) - (8)])->next = (yyvsp[(4) - (8)]); (yyvsp[(4) - (8)])->next = (yyvsp[(6) - (8)]); if (!is_bool((yyvsp[(2) - (8)]))) yyerror("Bad if condition!"); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 160 "sil.y"
    { (yyval) = create_node(T_WHILE, (yyvsp[(2) - (6)]), NULL); (yyvsp[(2) - (6)])->next = (yyvsp[(4) - (6)]); if (!is_bool((yyvsp[(2) - (6)]))) yyerror("Bad while condition!"); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 161 "sil.y"
    { (yyval) = create_node(T_WRITE, (yyvsp[(3) - (5)]), NULL); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 162 "sil.y"
    { (yyval) = create_node(T_READ, (yyvsp[(3) - (5)]), NULL); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 163 "sil.y"
    { (yyval) = create_node('=', (yyvsp[(1) - (4)]), NULL); (yyvsp[(1) - (4)])->next = (yyvsp[(3) - (4)]); if (!((is_bool((yyvsp[(1) - (4)])) && is_bool((yyvsp[(3) - (4)]))) || (is_int((yyvsp[(1) - (4)])) && is_int((yyvsp[(3) - (4)]))))) yyerror("Assignment failed!"); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 167 "sil.y"
    {
		  (yyval) = (yyvsp[(2) - (3)]);
		  (yyval)->fchild = (yyvsp[(1) - (3)]);
		  (yyvsp[(1) - (3)])->next = (yyvsp[(3) - (3)]);
		  if (is_bool((yyvsp[(1) - (3)])) && is_bool((yyvsp[(3) - (3)])))
			(yyval)->extra.type = DT_BOOL;
		}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 175 "sil.y"
    {
		  (yyval) = (yyvsp[(1) - (2)]);
		  (yyval)->fchild = (yyvsp[(2) - (2)]);
		  if (is_bool((yyvsp[(2) - (2)])))
			(yyval)->extra.type = DT_BOOL;
		}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 181 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 184 "sil.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 186 "sil.y"
    {
		  (yyval) = (yyvsp[(2) - (3)]);
		  (yyval)->fchild = (yyvsp[(1) - (3)]);
		  (yyvsp[(1) - (3)])->next = (yyvsp[(3) - (3)]);
		  if (is_int((yyvsp[(1) - (3)])) && is_int((yyvsp[(3) - (3)])))
			(yyval)->extra.type = DT_BOOL;
		}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 193 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 197 "sil.y"
    {
		  (yyval) = (yyvsp[(2) - (3)]);
		  (yyval)->fchild = (yyvsp[(1) - (3)]);
		  (yyvsp[(1) - (3)])->next = (yyvsp[(3) - (3)]);
		  if (is_int((yyvsp[(1) - (3)])) && is_int((yyvsp[(3) - (3)])))
			(yyval)->extra.type = DT_INT;
		}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 204 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 207 "sil.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 209 "sil.y"
    {
		  (yyval) = (yyvsp[(2) - (3)]);
		  (yyval)->fchild = (yyvsp[(1) - (3)]);
		  (yyvsp[(1) - (3)])->next = (yyvsp[(3) - (3)]);
		  if (is_int((yyvsp[(1) - (3)])) && is_int((yyvsp[(3) - (3)])))
			(yyval)->extra.type = DT_INT;
		}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 217 "sil.y"
    {
		  (yyval) = (yyvsp[(1) - (2)]);
		  (yyval)->fchild = (yyvsp[(2) - (2)]);
		  if (is_int((yyvsp[(2) - (2)])))
			(yyval)->extra.type = DT_INT;
		}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 223 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 226 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 227 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 228 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 230 "sil.y"
    {
		  datatype_t *t = NULL;
		  symstack_nt *sym = (yyvsp[(1) - (4)])->extra.st_entry;
		  if (sym && sym->type)
			if (sym->type->base == B_FUNC) {
			  ast_nt *args_looper = (yyvsp[(3) - (4)]);
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
		  (yyval) = create_node(T_FCALL, (yyvsp[(1) - (4)]), t);
		  (yyvsp[(1) - (4)])->next = create_node(T_FARGS, (yyvsp[(3) - (4)]), NULL);
		}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 268 "sil.y"
    { (yyval) = (yyvsp[(1) - (2)]); (yyvsp[(1) - (2)])->next = (yyvsp[(2) - (2)]); }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 269 "sil.y"
    { (yyval) = 0; }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 272 "sil.y"
    { (yyval) = (yyvsp[(2) - (3)]); (yyvsp[(2) - (3)])->next = (yyvsp[(3) - (3)]); }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 273 "sil.y"
    { (yyval) = 0; }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 276 "sil.y"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 278 "sil.y"
    {
		  datatype_t *t = NULL;
		  struct symstack_n *sym = (yyvsp[(1) - (4)])->extra.st_entry;
		  if (sym && sym->type)
			if (sym->type->base == B_ARRAY)
			  t = get_base2_wrapped(sym->type);
			else {
			  sprintf(error_buffer, "'%s' is not an array...", sym->id);
			  yyerror(error_buffer);
			}
		  (yyval) = create_node(T_ARR_DREF, (yyvsp[(1) - (4)]), t); (yyvsp[(1) - (4)])->next = (yyvsp[(3) - (4)]);
		}
    break;


/* Line 1792 of yacc.c  */
#line 1915 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 291 "sil.y"

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

//symstk_top will contain the new symbol
void new_symbol(char *id) {
  struct symstack_n * new_sym;
  new_sym = malloc(sizeof(struct symstack_n));
  strncpy(new_sym->id, id, 32);
  new_sym->type = NULL;
  new_sym->offset = 0;
  new_sym->next = symstk_top;
  symstk_top = new_sym;
}

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
  struct symstack_n * cur_sym = symstk_top, * next_sym;
  while (cur_sym != global_top) {
	next_sym = cur_sym->next;
	free_datatype(cur_sym->type);
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
}

datatype_t *new_functype(base_e rettype) {
  datatype_t *newtype = malloc(sizeof(datatype_t));
  newtype->base = B_FUNC;
  newtype->base2 = rettype;
  newtype->size = 0;
  newtype->ptlist = NULL;
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
  else if (n->tag == T_FCALL || n->tag == T_ARR_DREF)
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
  else if (n->tag == T_FCALL || n->tag == T_ARR_DREF)
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
  printf("MOV R0, %d\n", globals_size);
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
  printf("MOV R0, [BP]\nOUT R0\n");
  printf("die:\nHALT\n");
  printf("error:\nMOV R0, -1\nOUT R0\nJMP die\n");
}

void sim_func(ast_nt *fbody) {
  if (fbody->tag == T_FBODY) {
	printf("%s:\n", cur_func_def->id);
	sim_stmt(fbody->fchild, 0); //T_ST_BLOCK; may modify R0
	sim_stmt(fbody->fchild->next, 0); //T_FRET; may modify R0
  }
}

void sim_bin_op(ast_nt *astn1, ast_nt *astn2, int Ri, int Rj, char *op) {
  printf("PUSH R%d\n", Rj);
  sim_stmt(astn1, Ri);
  sim_stmt(astn2, Rj);
  printf("%s R%d, R%d\n", op, Ri, Rj);
  printf("POP R%d\n", Rj);
}

int sim_is_local(ast_nt *astn) {
  if (!astn) return 0;
  symstack_nt *cur = astn->extra.st_entry;
  while (cur->next) {
	if (cur->next == global_top)
	  return 1;
	cur = cur->next;
  }
  return 0;
}

void sim_get_addr(ast_nt *astn, int Ri, int Rj) {
  if (!astn) return;
  if (astn->tag == T_ID) {
	if (sim_is_local(astn)) {
	  printf("MOV R%d, BP\n", Ri);
	  printf("PUSH R%d\n", Rj);
	  printf("MOV R%d, %d\n", Rj, astn->extra.st_entry->offset);
	  printf("ADD R%d, R%d\n", Ri, Rj);
	  printf("POP R%d\n", Rj);
	} else
	  printf("MOV R%d, %d\n", Ri, astn->extra.st_entry->offset);
  } else if (astn->tag == T_ARR_DREF) {
	symstack_nt *sym = astn->fchild->extra.st_entry;
	printf("MOV R%d, %d\n", Ri, sym->type->size);
	printf("PUSH R%d\n", Rj);
	sim_stmt(astn->fchild->next, Rj);
	printf("LE R%d, R%d\n", Ri, Rj);
	printf("JNZ R%d, error\n", Ri); //array index out of bounds
	printf("MOV R%d, %d\n", Ri, sym->offset);
	printf("ADD R%d, R%d\n", Ri, Rj);
	printf("POP R%d\n", Rj);
  }
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
	  sim_get_addr(astn1, Rj, Rk);
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

	  printf("MOV R%d, 0\n", Ri);
	  printf("PUSH R%d\n", Ri); //activation record starts here: first word reserved for storing return value
	  printf("MOV R%d, SP\n", Ri); //Ri will contain the start point of activation record
	  int i;
	  for (i=1; i<n; i++) {
		if (astn1) {
		  sim_stmt(astn1, Rj); //Rj will contain the result of astn1
		  printf("PUSH R%d\n", Rj); //Push the result into the act. rec.
		  astn1 = astn1->next;
		} else
		  printf("PUSH R%d\n", Ri); //Reserve space for local variables in the act. rec.
	  }
	  printf("PUSH BP\n");
	  printf("MOV BP, R%d\n", Ri);
	  printf("PUSH R0\n"); //a function will only modify R0
	  printf("CALL %s\n", astn2->extra.st_entry->id);
	  printf("POP R0\n");
	  printf("POP BP\n");
	  
	  //Return the stack pointer
	  printf("MOV SP, R%d\n", Ri); //Pop off activation record except the return value
	  printf("POP R%d\n", Ri); //Move to Ri, the value returned by function
	  break;
	case T_FRET:
	  sim_stmt(astn1, Ri);
	  printf("MOV [BP], R%d\n", Ri);
	  printf("RET\n\n");
	  break;
	case T_NOT:
	  printf("PUSH R%d\n", Rj);
	  sim_stmt(astn1, Rj);
	  printf("MOV R%d, 0\n", Ri);
	  printf("EQ R%d, R%d\n", Ri, Rj); //0=0 => 1; 1=0 => 0
	  printf("POP R%d\n", Rj);
	  break;
	case T_AND:
	  n = label_count++;
	  sim_stmt(astn1, Ri);
	  printf("JZ R%d, and%d\n", Ri, n);
	  sim_stmt(astn2, Ri);
	  printf("and%d:\n", n);
	  break;
	case T_OR:
	  n = label_count++;
	  sim_stmt(astn1, Ri);
	  printf("JNZ R%d, or%d\n", Ri, n);
	  sim_stmt(astn2, Ri);
	  printf("or%d:\n", n);
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
	  sim_get_addr(astn1, Ri, Rj);
	  printf("MOV [R%d], R%d\n", Ri, Rj);
	  printf("POP R%d\n", Rj);
	  break;
	case T_ARR_DREF:
	case T_ID:
	  printf("PUSH R%d\n", Rj);
	  sim_get_addr(expr_n, Rj, Rk);
	  printf("MOV R%d, [R%d]\n", Ri, Rj);
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
