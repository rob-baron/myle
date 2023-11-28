/* lexer.l
**   A simple tokenizer used to tokenize non-standard JSON
**  
**   built with the following in xcode:
**      /usr/local/bin/flex --nowarn --outfile="$DERIVED_FILE_DIR/$INPUT_FILE_BASE".c --header-file="$DERIVED_FILE_DIR/$INPUT_FILE_BASE".h "$INPUT_FILE_DIR/$INPUT_FILE_BASE".l
**
**      /usr/local/bin/flex --nowarn --outfile=lexer.c --header-file=lexer.h lexer.l
*/

%{
    #include "parser.h"
    #include <string.h>
    typedef struct
    {
        char *buf;
        int size;
    } my_buf_info_t;
    int my_yy_scan_buffer(char *buffer, int size, void *lexer);
    int my_yy_input(char* buffer,int *numBytesRead,int maxBytesToRead, void *lexer);


    #undef YY_INPUT
    /* Had to add the scanner so that we can get the extra from the input */
    #define YY_INPUT(b,r,s) my_yy_input(b,&r,s, (void *)yyscanner)
%}

%option bison-locations
%option reentrant
%option bison-bridge
%option fast
%option noyywrap

UNICODE         \\u[0-9a-fA-F]{4}
UNESCAPED       [ !#-\[\]-~]
ESCAPED         \\["\\bfnrt/]
CHAR            {UNESCAPED}|{ESCAPED}|{UNICODE}

EXP             [e|E][+|-]?[0-9]+
FRACTION        [.][0-9]+
INTEGER         [-]?[0-9]+

%%

[ \r\n\v\t]                 { /* ignore */; }

[{]                         { /* printf(" '{' "); */ return TOK_LBRACE; }
[}]                         { /* printf(" '}' "); */ return TOK_RBRACE; }
\[                          { /* printf(" '[' "); */ return TOK_LARRAY; }
\]                          { /* printf(" ']' "); */ return TOK_RARRAY; }
[:]                         { /* printf(" ':' "); */ return TOK_COLON; }
[,]                         { /* printf(" ',' "); */ return TOK_COMMA; }

[+]                         { /* printf("  "); */ return TOK_ADD;}
[-]                         { /* printf("  "); */ return TOK_SUB;}
[*]                         { /* printf("  "); */ return TOK_MUL;}
[/]                         { /* printf("  "); */ return TOK_DIV;}
[\^]                        { /* printf("  "); */ return TOK_EXP;}
<<EOF>>                     { /* printf(" <EOF>"); */ return TOK_EOF; }

{INTEGER}                   {
                            yylval->d = (double *)malloc(sizeof(double));
                            *yylval->d = strtod(yytext,NULL);
                            /* printf(" '%f' ",*yylval->d); */
                            return TOK_DOUBLE;
                            }

{INTEGER}{FRACTION}{EXP}    |
{INTEGER}{FRACTION}         |
{INTEGER}{EXP}              {
                            yylval->d = (double *)malloc(sizeof(double));
                            *yylval->d = strtod(yytext,NULL);
                            /* printf(" '%f' ",*yylval->d); */
                            return TOK_DOUBLE;
                            }

true                        { /* printf(" 'T' "); */ return TOK_TRUE; }
false                       { /* printf(" 'F' "); */ return TOK_FALSE; }
null                        { /* printf(" 'n' ");  */return TOK_NULL; }

['][^']*['] |
["][^"]*["]                 {
                            yylval->str=(char *)malloc((yyleng+1)*sizeof(char));
                            strncpy(yylval->str,yytext+1,(yyleng));
                            (yylval->str)[yyleng-2]=0;
                            /* printf(" '%s' ",yylval->str); */
                            return TOK_CHAR;
                            }

[a-zA-Z][a-zA-z0-9.]*       {
                            yylval->str=(char *)malloc((yyleng+1)*sizeof(char));
                            strncpy(yylval->str,yytext,(yyleng+1));
                            /* printf(" '%s' ",yylval->str); */
                            return TOK_CHAR;
                            }

.                           {
                            yylval->str=(char *)malloc((yyleng+1)*sizeof(char));
                            strncpy(yylval->str,yytext,(yyleng+1));
                            /* printf(" '%s' other character ",yylval->str); */
                            return TOK_CHAR;
                            }

%%

int my_yy_scan_buffer(char *buffer, int size, void *lexer)
{
    if(buffer && lexer)
    {
        my_buf_info_t *buf_info;
        buf_info=(my_buf_info_t *)malloc(sizeof(my_buf_info_t));
        buf_info->buf=buffer;
        buf_info->size=size;
        yyset_extra(buf_info, (yyscan_t *)lexer);
    }
    return 0;
}

int my_yy_free_buffer(void *lexer)
{
    if(lexer)
    {
        my_buf_info_t *buf_info;
        if((buf_info=(my_buf_info_t *)yyget_extra((yyscan_t) lexer)))
        {
            free(buf_info);
            yyset_extra(NULL,(yyscan_t *)lexer);
        }
    }
    return 0;
}

/* here is a custom yy_input funtion */
int my_yy_input(char *buffer, int *numBytesRead, int maxBytesToRead, void *lexer)
{
    my_buf_info_t *buf_info;
    buf_info = (my_buf_info_t *)yyget_extra((yyscan_t)lexer);
    if(buf_info && buf_info->size>0)
    {
        *buffer=(buf_info->buf)[0];
        *numBytesRead=1;
        buf_info->buf++;
        buf_info->size--;
    }
    else
    {
        *numBytesRead=0;
        *buffer=0;
    }
    return 0;
}
