/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     ENDIF = 260,
     DECL = 261,
     ENDDECL = 262,
     BEG = 263,
     END = 264,
     WHILE = 265,
     DO = 266,
     ENDWHILE = 267,
     RETURN = 268,
     READ = 269,
     WRITE = 270,
     TYPE = 271,
     MAIN = 272,
     THEN = 273,
     NOT = 274,
     BOOLEAN = 275,
     AND = 276,
     OR = 277,
     INTEGER = 278,
     ID = 279,
     RELOP = 280,
     NUMBER = 281
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define ENDIF 260
#define DECL 261
#define ENDDECL 262
#define BEG 263
#define END 264
#define WHILE 265
#define DO 266
#define ENDWHILE 267
#define RETURN 268
#define READ 269
#define WRITE 270
#define TYPE 271
#define MAIN 272
#define THEN 273
#define NOT 274
#define BOOLEAN 275
#define AND 276
#define OR 277
#define INTEGER 278
#define ID 279
#define RELOP 280
#define NUMBER 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 33 "sil.y"

	struct Node *ptr;



/* Line 2068 of yacc.c  */
#line 108 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


