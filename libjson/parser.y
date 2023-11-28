/* A re-entrant parser to parse JSON
**
** to build in XCode:
**     /usr/local/bin/bison --defines="$DERIVED_FILE_DIR/$INPUT_FILE_BASE".h -o "$DERIVED_FILE_DIR/$INPUT_FILE_BASE".c "$INPUT_FILE_DIR/$INPUT_FILE_BASE".y
**
**     /usr/local/bin/bison --defines=parser.h -o parser.c parser.y
*/
/* /usr/local/bin/bison --defines=parser.h -o parser.c parser.y */

%{
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    #define YYDEBUG 1
    #define YYINITDEPTH 1000

    typedef void * yyscan_t;
    typedef struct ast_s {
        char op;
        struct ast_s *rvalue;
        struct ast_s *lvalue;
        struct ast_s *parent;
        } ast_t;

    #include "parser.h"
    int yyerror (void *, void *, void *, const char *);
    ast_t *create_ast_node(char op, ast_t *lvalue, ast_t *rvalue);
%}

%define lr.type ielr
%define api.pure full
%locations
%union {
    double *d;
    long long *i;
    char *str;
    void *ast;
    }
%lex-param {void * scanner}
%parse-param {void *scanner} { void **parse_tree }
%error-verbose

%{
    #include "lexer.h"
    int yyerror (void *, void *, void *, const char *);
%}

%token<d> TOK_DOUBLE
%token<i> TOK_INTEGER
%token<str> TOK_CHAR
%token<str> TOK_ADD
%token<str> TOK_SUB
%token<str> TOK_MUL
%token<str> TOK_DIV
%token<str> TOK_EXP
%token<str> TOK_NEG
%token<str> TOK_EOF
%token<ast> TOK_RBRACE
%token<ast> TOK_LBRACE
%token<ast> TOK_RARRAY
%token<ast> TOK_LARRAY
%token<ast> TOK_COLON
%token<ast> TOK_COMMA
%token<ast> TOK_TRUE
%token<ast> TOK_FALSE
%token<ast> TOK_NULL

/* %type<d> exp */
%type<str> line
%type<ast> json
%type<ast> array
%type<ast> values
%type<ast> value
%type<ast> type
%type<ast> object
%type<ast> kv_pairs
%type<ast> key_value
%type<ast> string

%% /* Grammar rules and actions follow.  */

line:
'\n'            { /*ignore*/; }
| json TOK_EOF  { /* printf ("json found %X \n", (void *) $1); */  *parse_tree=$1; return 0; }
;

json:
type                { $$ = $1; /* printf("JSON found %Xp\n",(void *)$1); */ }
| %empty            { $$ = create_ast_node('n',NULL,NULL); /*printf("TOK_null\n");*/ /* printf(" empty JSON\n"); */ }
;

type:
array               { $$ = $1; /* printf("Array found\n"); */ }
| object           { $$ = $1;  /* printf("Object found\n"); */ }
;

array:
TOK_LARRAY TOK_RARRAY    { $$ = create_ast_node('a',NULL,NULL); /* printf("Empty Array\n"); */ /* empty array */ }
| TOK_LARRAY values TOK_RARRAY  {$$ = create_ast_node('a',NULL,(ast_t *)$2); /* printf("Array\n"); */ }  //$$ = process_array($2);
;

values:
value                      { $$ = $1; /* printf("value found\n"); */ }
| value TOK_COMMA values   { $$ = create_ast_node(',', (ast_t *)$1, (ast_t *)$3);  /* printf("values found\n"); */ }
;

object:
TOK_LBRACE TOK_RBRACE  { $$ = create_ast_node('o',NULL, NULL); /* printf("Empty Object\n"); */ /* empty object */ }
| TOK_LBRACE kv_pairs TOK_RBRACE   { $$ = create_ast_node('o',NULL,(ast_t *)$2); /* printf("Object\n"); */ }
;

    /* The key indicates the type of the data.
       the value can either be a
       char * (string)
       double * (double)
       integer * (_int64)
       bool (true/false)
       array *(list of values)
       obj *
    */

kv_pairs:
key_value  { $$ = $1; }
| key_value TOK_COMMA kv_pairs  { $$ = create_ast_node(',',(ast_t *)$1,(ast_t *)$3); /* printf("kv pairs found\n"); */ }
;

key_value:
string TOK_COLON value  { $$ = create_ast_node(':',(ast_t *)$1,(ast_t *)$3);  /* printf("key value pair found\n"); */ }
;

value:
string             { $$ = $1; }
| TOK_INTEGER      { $$ = create_ast_node('i',NULL,(ast_t *)$1); /* printf("TOK_INTEGER\n"); */ }
| TOK_DOUBLE       { $$ = create_ast_node('d',NULL,(ast_t *)$1); /* printf("TOK_double\n"); */ }
| TOK_TRUE         { $$ = create_ast_node('t',NULL,NULL); /* printf("TOK_true\n"); */ }
| TOK_FALSE        { $$ = create_ast_node('f',NULL,NULL); /* printf("TOK_false\n"); */ }
| TOK_NULL         { $$ = create_ast_node('n',NULL,NULL); /* printf("TOK_null\n"); */ }
| json             { $$ = $1; /* printf("json 2\n"); */ } 
;

string:
TOK_CHAR           {$$ = create_ast_node('c',NULL,(ast_t *)$1); /* printf("TOK_CHAR\n"); */ }


%%

int yyerror (void *yylloc, void *parser, void *out_struct, const char *msg)
{
    fprintf(stderr, "ERROR: %s\n",msg);
    return 1; 
}

ast_t *create_ast_node(char op, ast_t *lvalue, ast_t *rvalue)
{
    ast_t *ast=(ast_t *)malloc(sizeof(ast_t));
    if(ast!=NULL)
    {
        ast->op=op;
        ast->lvalue=lvalue;
        ast->rvalue=rvalue;
        ast->parent=NULL;
        switch(ast->op)
            {
        case 'a':
        case 'o': 
            if(ast->lvalue) { ast->lvalue->parent = (void *)ast; } 
            break;
        case ',':
            if(ast->lvalue) { ast->lvalue->parent = (void *)ast; } 
            if(ast->rvalue) { ast->rvalue->parent = (void *)ast; }
            break;
            }
        //printf(stderr,"%Xp -> op='%c' %Xp %Xp\n", (void *)ast, ast->op, (void *)(ast->rvalue), (void *)(ast->lvalue));
    }
    return ast;
}

