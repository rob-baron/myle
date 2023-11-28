/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_DOUBLE = 258,
    TOK_INTEGER = 259,
    TOK_CHAR = 260,
    TOK_ADD = 261,
    TOK_SUB = 262,
    TOK_MUL = 263,
    TOK_DIV = 264,
    TOK_EXP = 265,
    TOK_NEG = 266,
    TOK_EOF = 267,
    TOK_RBRACE = 268,
    TOK_LBRACE = 269,
    TOK_RARRAY = 270,
    TOK_LARRAY = 271,
    TOK_COLON = 272,
    TOK_COMMA = 273,
    TOK_TRUE = 274,
    TOK_FALSE = 275,
    TOK_NULL = 276
  };
#endif
/* Tokens.  */
#define TOK_DOUBLE 258
#define TOK_INTEGER 259
#define TOK_CHAR 260
#define TOK_ADD 261
#define TOK_SUB 262
#define TOK_MUL 263
#define TOK_DIV 264
#define TOK_EXP 265
#define TOK_NEG 266
#define TOK_EOF 267
#define TOK_RBRACE 268
#define TOK_LBRACE 269
#define TOK_RARRAY 270
#define TOK_LARRAY 271
#define TOK_COLON 272
#define TOK_COMMA 273
#define TOK_TRUE 274
#define TOK_FALSE 275
#define TOK_NULL 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "parser.y" /* yacc.c:1919  */

    double *d;
    long long *i;
    char *str;
    void *ast;
    

#line 104 "parser.h" /* yacc.c:1919  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (void *scanner, void **parse_tree);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
