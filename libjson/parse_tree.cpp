//
//  parse_tree.cpp
//  ALE
//
//  Created by Robert Baron on 10/10/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
extern "C"
    {
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <curl/curl.h>
    #include <string.h>
    #include "parser.h"
    #include "lexer.h"
    }

#include "parse_tree.hpp"


extern "C" int my_yy_scan_buffer(char *buffer, int size, void *lexer);


    parse_util::parse_util() {}
    parse_util::~parse_util() {}

    char parse_util::get_op(ast_t *pt) { if(pt) return pt->op; else return '\x0'; }
    ast_t *parse_util::get_rvalue(ast_t *pt) { if(pt) return pt->rvalue; else return NULL; }
    ast_t *parse_util::get_lvalue(ast_t *pt) { if(pt) return pt->lvalue; else return NULL; }

    ast_t *parse_util::get_parent(ast_t *pt) { if(pt) return pt->parent; else return NULL; }

    ast_t *parse_util::set_op(ast_t *pt, char op) 
        { 
        if(pt) pt->op=op; 
        return pt; 
        }

    ast_t *parse_util::set_rvalue(ast_t *pt, ast_t *rvalue)
        {
        if(pt) pt->rvalue = rvalue;
        return pt;
        }

    ast_t *parse_util::set_lvalue(ast_t *pt, ast_t *lvalue)
        {
        if(pt) pt->lvalue = lvalue;
        return pt;
        }

    int parse_util::cmp_parse_tree(ast_t *pt1, ast_t *pt2, double epsilon )
        {
        int rv; 
        if(pt1 && !pt2) return 1;
        else if(!pt1 && pt2) return -1;
        if(pt1->op != pt2->op) { return -1; }
        switch(pt1->op)
            {
        case ':':
        case ',':
            rv = cmp_parse_tree((ast_t *)(pt1->lvalue),(ast_t *)(pt2->lvalue));
            if(rv==0) rv=cmp_parse_tree((ast_t *)(pt1->lvalue),(ast_t *)(pt2->lvalue));
            return rv; 
            break;

        case 'o':
        case 'a': 
            return cmp_parse_tree((ast_t *)(pt1->lvalue),(ast_t *)(pt2->lvalue)); 
            break;

        case 'c':
            //fprintf(stderr,"%s", (char *)parse_tree->rvalue);
            return strcmp((char *)(pt1->rvalue),(char *)(pt2->rvalue));
            break;
        case 'i':
            //fprintf(stderr,"%lld", *((long long *)parse_tree->rvalue));
            if( *((long long*)(pt1->rvalue)) > *((long long *)(pt2->rvalue))) return 1;
            else if (*((long long*)(pt1->rvalue)) < *((long long *)(pt2->rvalue))) return -1;
            else return 0;
            break;
        case 'd':
            //fprintf(stderr,"%f", *((double *) parse_tree->rvalue));
            if( *((double *)(pt1->rvalue)) + epsilon > *((double*)(pt2->rvalue))) return 1;
            else if (*((double*)(pt1->rvalue))  - epsilon < *((double*)(pt2->rvalue))) return -1;
            else return 0;
            break;

        case 't':
        case 'f':
        case 'n':
            return 0;
            break;
            }
        return -1;
        }

    void parse_util::free_parse_tree(void *pt)
        {
        ast_t *parse_tree=(ast_t *)pt;
        if(parse_tree)
            {
            switch(parse_tree->op)
                {
            case ',':
            case 'a':
            case 'o':
            case ':':
                if(parse_tree->lvalue) { free_parse_tree(parse_tree->lvalue); parse_tree->lvalue=NULL; }
                if(parse_tree->rvalue) { free_parse_tree(parse_tree->rvalue); parse_tree->rvalue=NULL; }
                free(parse_tree);
                break;
            case 'c':
            case 'i':
            case 'd':
                if(parse_tree->rvalue) { free(parse_tree->rvalue); parse_tree->rvalue=NULL; }
                free(parse_tree);
                break;
            case 't':
            case 'f':
            case 'n':
                free(parse_tree);
                break;
            default:
                break;
                }
            }
        }

    void parse_util::dump_parse_tree(const char *msg, void *pt, int indent)
        {
        if(msg) { fprintf(stderr,"INFO: %s\n",msg); }
        ast_t *parse_tree=(ast_t *)pt;
        if(parse_tree)
            {
            if(indent>0) { for(int x=0; x<indent; x++) { fputc(' ',stderr); } }
            switch (parse_tree->op)
                {
            case ',':
                if(indent>0) { for(int x=0; x<indent; x++) { fputc(' ',stderr); } }
                dump_parse_tree(NULL,parse_tree->lvalue);
                fprintf(stderr,",\n");
                dump_parse_tree(NULL,parse_tree->rvalue,indent);
                if(((ast_t *)(parse_tree->rvalue))->op!=',') fprintf(stderr,"\n");
                break;
                //case 'o':
                //case 'a':
                //    dump_parse_tree(NULL,parse_tree->rvalue,indent+4); break;
            case 'a':
            case 'o':
                if(indent>0) { for(int x=0; x<indent; x++) { fputc(' ',stderr); } }
                if(parse_tree->op=='a') fprintf(stderr,"[");
                else fprintf(stderr,"{");
                if(parse_tree->rvalue)
                    {
                    switch(((ast_t *)(parse_tree->rvalue))->op)
                        {
                    case 'a':
                    case 'o':
                        dump_parse_tree(NULL,parse_tree->rvalue,indent+4);
                        break;
                    case ',':
                        dump_parse_tree(NULL,parse_tree->rvalue,indent+4);
                        break;
                    default:
                        dump_parse_tree(NULL,parse_tree->rvalue);
                        }
                    }
                if(parse_tree->op=='a') fprintf(stderr,"  ]\n");
                else fprintf(stderr,"}\n");
                break;
            //case 'j':
            //case 'o':
            //    fprintf(stderr,"%c {\n",parse_tree->op);
            //    dump_parse_tree(NULL,parse_tree->rvalue,indent+4);
            //    if(indent>0) { for(int x=0; x<indent; x++) { fputc(' ',stderr); } }
            //    fprintf(stderr,"  }\n",parse_tree->op);
            //    break;
            case ':':
                //fprintf(stderr,":",parse_tree->op, (char *)((parse_tree->rvalue)->lvalue));
                if(indent>0) { for(int x=0; x<indent; x++) { fputc(' ',stderr); } }
                dump_parse_tree(NULL,parse_tree->lvalue);
                fprintf(stderr,":");
                dump_parse_tree(NULL,parse_tree->rvalue);
                break;

            /* Thse are all leaves of the tree don't go down any father */
            case 'c':
                fprintf(stderr,"%s", (char *)parse_tree->rvalue);
                break;
            case 'i':
                fprintf(stderr,"%lld", *((long long *)parse_tree->rvalue));
                break;
            case 'd':
                fprintf(stderr,"%f", *((double *) parse_tree->rvalue));
                break;
            case 't':
                fprintf(stderr,"true");
                break;
            case 'f':
                fprintf(stderr,"false");
                break;
            case 'n':
                fprintf(stderr,"null");
                break;
            default:
                fprintf(stderr,"ERROR: unknown type %c",parse_tree->op);
                break;
                }
            }
        }

    //moved this here as it is generally useful
    void *parse_util::parse(const char *str)
        {
        void *parse_tree=NULL;
        char *in_str;
        
        int x=strlen(str);
        in_str=(char *)calloc(sizeof(char), x+3);
        
        strcpy(in_str,str);
        in_str[x+1]=0;
        
        yyscan_t lexer;
        if(yylex_init(&lexer)) { printf("Error: Cannot initialize lexer\n"); abort(); }
        my_yy_scan_buffer(in_str,x,lexer);

        //YYSTYPE yylval_param;
        //YYLTYPE yylloc_param;
        //To test just the scanner
        //while(yylex(&yylval_param, &yylloc_param ,lexer));

        yyparse(lexer, &parse_tree);
        yylex_destroy(lexer);
        //free(in_str2);
        return parse_tree;
        }

    int dump_json(void *pt, int indent=0)
        {
        //this is for test code
        return 0;
        }

    int parse_util::get_type(ast_t *pt)
        {
        if(pt)
            {
            switch(pt->op)
                {
            case 'o': return TYPE_OBJECT; break;
            case 'a': return TYPE_ARRAY; break;
            case ':': return TYPE_KEYVALUE; break;
            case 'c': return TYPE_STRING; break;
            case 'i': 
                if(pt->rvalue) return TYPE_INT; 
                break;
            case 'd': return TYPE_DOUBLE; break;
            case 't':
            case 'f': return TYPE_BOOL; break;
            case 'n': return TYPE_NULL; break;
            case ',': if(pt->lvalue && pt->rvalue) return SEPARATOR; break;
                }
            }
        return TYPE_UNK;
        }
    long parse_util::get_int(ast_t *pt)
        {
        if(get_type(pt)==TYPE_INT)
            {
            return *((long *)(pt->rvalue));
            }
        return 0;
        }
    long parse_util::get_bool(ast_t *pt)
        {
        if(get_type(pt)==TYPE_BOOL)
            {
            if(pt->op=='t') return 1;
            else if(pt->op=='f') return 0;
            }
        return 0;
        }
    long parse_util::is_null(ast_t *pt)
        {
        if(get_type(pt)==TYPE_NULL)
            {
            return 1;
            }
        return 0;
        }
    double parse_util::get_double(ast_t *pt)
        {
        if(get_type(pt)==TYPE_DOUBLE)
            {
            return *((double *)(pt->rvalue));
            }
        return 0.0;
        }
    int parse_util::get_string(ast_t *pt, char *str, int len)
        {
        if(get_type(pt)==TYPE_STRING)
            {
            int ret_val=0;
            str[0]='\x00';
            if(pt->rvalue)
                {
                strncpy(str,((const char *)(pt->rvalue)),len);
                return strlen((char *)(pt->rvalue));
                }
            return 1;
            }   
        return 0;
        }
    int parse_util::cmp_string(ast_t *pt, const char *str, int len)
        {
        if(get_type(pt)==TYPE_STRING)
            {
            return strncmp(str,(char *)(pt->rvalue),len);
            }
        return BAD_TYPE;
        }
    int parse_util::get_key(ast_t *pt, char *str, int len)
        {
        if(get_type(pt)==TYPE_KEYVALUE)
            {
            return get_string(get_lvalue(pt), str, len);
            }
        return BAD_TYPE;
        }
    int parse_util::cmp_key(ast_t *pt, const char *str, int len)
        {
        if(get_type(pt)==TYPE_KEYVALUE)
            {
            return cmp_string(get_lvalue(pt), str, len);
            }
        return BAD_TYPE;
        }
    //get_value From KeyValue
    ast_t *parse_util::get_value(ast_t *pt)
        {
        if(get_type(pt)==TYPE_KEYVALUE)
            {
            return pt->rvalue;
            }
        return NULL;
        }
    //Array functions
    //  These assume that the parse tree is like
    //        ','
    //     [0]    ','
    //         [1]   [2]
    //   more general would be also handle the following
    //           ','
    //         ','  [2]
    //       [0] [1]
    int parse_util::get_arrayLength(ast_t *pt)
        {
        ast_t *st;
        int cnt;
        if(get_type(pt)==TYPE_ARRAY)  
            {
            if(!pt->rvalue) { return 0; } //empty array
            else if(pt->rvalue && get_op(pt->rvalue)!=',')
                {
                return 1;
                }
            else if(pt->rvalue && get_op(pt->rvalue)==',')
                {
                st=pt->rvalue;
                cnt=0;
                while(get_op(st)==',' && st->rvalue)
                    {
                    cnt++;
                    if(st->rvalue ) { st=st->rvalue; }
                    }
                cnt++;
                return cnt;
                }
            }
        return -1;  
        }

    ast_t *parse_util::get_arrayValue(ast_t *pt, int x)
        {
        ast_t *st;
        int cnt;
        if(get_type(pt)==TYPE_ARRAY)  
            {
            if(!pt->rvalue) { return NULL; } //empty array
            else if(pt->rvalue && get_op(pt->rvalue)!=',' && x==0 )
                {
                return pt->rvalue;
                }
            else if(pt->rvalue && get_op(pt->rvalue)==',')
                {
                st=pt->rvalue;
                cnt=0;
                if(x==0) { return st->lvalue; }
                while(get_op(st)==',' && cnt<x )
                    {
                    if(st->rvalue) { cnt++; st=st->rvalue; }
                    }
                if(cnt==x)
                    {
                    if(get_op(st)!=',') { return st; }
                    return st->lvalue; 
                    }
                }
            }
        return NULL;  
        }

    //dictionary types
    ast_t *parse_util::get_KeyValue(ast_t *pt, int x)
        {
        ast_t *st;
        int cnt;
        if(get_type(pt)==TYPE_OBJECT)  
            {
            if(!pt->rvalue) { return NULL; } //empty array
            else if(pt->rvalue && get_op(pt->rvalue)!=',' && x==0 )
                {
                return pt->rvalue;
                }
            else if(pt->rvalue && get_op(pt->rvalue)==',')
                {
                st=pt->rvalue;
                cnt=0;
                if(x==0) { return st->lvalue; }
                while(get_op(st)==',' && cnt<x )
                    {
                    if(st->rvalue && get_op(st->rvalue)==',') { cnt++; st=st->rvalue; }
                    }
                if(cnt==x)
                    {
                    if(get_op(st)!=',') { return st; }
                    return st->lvalue; 
                    }
                }
            }    
        return NULL;    
        }

    ast_t *parse_util::get_ValueFromKey(ast_t *pt, const char *key, int len)
        {
        ast_t *st;
        int cnt;
        //switch (get_type(pt))
        //    {
        //case TYPE_KEYVALUE:
        //case TYPE_OBJECT:
        //    }
        if(get_type(pt)==TYPE_OBJECT)  
            {
            if(!pt->rvalue) { return NULL; } //empty array
            else if(pt->rvalue && get_type(pt->rvalue)==TYPE_KEYVALUE)
                {
                if(cmp_key(pt->rvalue, key, len)==0) 
                    { 
                    return get_value(pt->rvalue); 
                    }
                return NULL;
                }
            else if(pt->rvalue && get_op(pt->rvalue)==',')
                {
                st=pt->rvalue;
                cnt=0;
                while(st && get_op(st)==',' )
                    {
                    if(cmp_key(st->lvalue,key,len)==0) { return get_value(st->lvalue); }
                    st=st->rvalue;
                    }
                if(st && get_op(st)!=',') 
                    {
                    if(cmp_key(st,key,len)==0)  { return get_value(st); }
                    }
                }
            }
        return NULL;  
        }    

    /* from the symbol table, build the types
     *
     * not really necessary since we got the symbol table
     * so, for now, just use the parse tree.
     */
    type *parse_util::get_type(void *pt, char *name)
        {
        ast_t *parse_tree=(ast_t *)pt;
        ast_t *sub_tree;
        type *m=NULL,*t=NULL;
        char new_type=0x00;
        int arry_size=0;

        if(parse_tree->rvalue)
            {
            t=new type;
            if(name) t->set_name(name);
            //else t->set_name(parse_tree->key);
            t->set_size(1);
            t->set_master_type(((ast_t*)parse_tree->rvalue)->op);
            t->set_sub_type('\0');
            switch(t->get_master_type())
                {
                    case 'a':
                    //find size of array
                    new_type='c';
                    arry_size=0;
                    sub_tree=(ast_t*)(parse_tree->rvalue);
                    if(sub_tree->rvalue)
                        {
                        new_type=((ast_t*)(sub_tree->rvalue))->op;
                        arry_size=1;
                        while(sub_tree->lvalue)
                            {

                            //are types consistent
                            arry_size++;
                            sub_tree=(ast_t*)(sub_tree->rvalue);
                            }
                        }
                    if(new_type!=0x00)
                        t->set_master_type(new_type);
                    t->set_size(arry_size);
                    break;
                    case 'j':
                    case 'o':
                    sub_tree=(ast_t*)(parse_tree->rvalue);

                    while(sub_tree->lvalue)
                        {
                        m=new type;

                        t->add_member(m);
                        }
                    break;
                    case 'i':
                    case 'd':
                    case 'c':
                    /* we already got the type info -- do nothing */
                    break;
                }
            }
        else
            {
            //Give error message
            }
        return t;
        }

    /* This was an attempt at building the symbol table
     *
     * The symbol table isn't really needed (though it is a nice to have
     * to analyze the json types and convert between json to c structures
     *
     * for now, just use the parse tree.
     */
    int parse_util::buildSymTable(sym_table *st, void *pt, char *name)
        {
        ast_t *parse_tree=(ast_t *)pt;
        type *t;
        while(parse_tree)
            {
            switch (parse_tree->op)
                {
            case 'a':
                fprintf(stderr,"%c [\n",parse_tree->op);
                buildSymTable(st, parse_tree->rvalue);
                fprintf(stderr,"  ]\n");
                break;
            case 'j':
            case 'o':
                //This is the start of a new structure!!!
                fprintf(stderr,"%c {\n",parse_tree->op);
                buildSymTable(st, parse_tree->rvalue);
                fprintf(stderr,"  }\n");
                break;
            case ':':
                //key is a structure member
                //determine_type(parse_tree->rvalue);
                //fprintf(stderr,"%s",parse_tree->key);
                //t=get_type((void *)parse_tree);
                buildSymTable(st, parse_tree->rvalue);
                break;
            case 'c':
                fprintf(stderr,"%c %s \n",parse_tree->op, (char *)parse_tree->rvalue);
                break;
            case 'i':
                fprintf(stderr,"%c %lld \n",parse_tree->op, *((long long *)parse_tree->rvalue));
                break;
            case 'd':
                fprintf(stderr,"%c %f \n",parse_tree->op, *((double *) parse_tree->rvalue));
                break;
            case 'T':
                fprintf(stderr,"%c True \n",parse_tree->op);
                break;
            case 'F':
                fprintf(stderr,"%c False \n",parse_tree->op);
                break;
            case 'N':
                fprintf(stderr,"%c null \n",parse_tree->op);
                break;
            default:
                fprintf(stderr,"ERROR: unknown type %c\n",parse_tree->op);
                break;
                }
            parse_tree=(ast_t *)parse_tree->lvalue;
            }
        return 0;
        }

//    int parse_util::get_data(char *URL, char *data, char *headers)
//        {
//        CURL *curl;
//        CURLcode res;
//
//        /* In windows, this will init the winsock stuff */
//        curl_global_init(CURL_GLOBAL_ALL);
//
//        /* get a curl handle */
//        curl = curl_easy_init();
//        if(curl)
//            {
//            /* First set the URL that is about to receive our POST. This URL can
//             just as well be a https:// URL if that is what should receive the
//             data. */
//            curl_easy_setopt(curl, CURLOPT_URL, URL);
//            /* Now specify the POST data */
//            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
//
//            /* Perform the request, res will get the return code */
//            res = curl_easy_perform(curl);
//            /* Check for errors */
//            if(res != CURLE_OK)
//                fprintf(stderr, "curl_easy_perform() failed: %s\n",
//                        curl_easy_strerror(res));
//
//            /* always cleanup */
//            curl_easy_cleanup(curl);
//            }
//        curl_global_cleanup();
//        return 0;
//        }
