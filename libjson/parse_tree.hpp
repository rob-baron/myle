//
//  parse_tree.hpp
//  ALE
//
//  Created by Robert Baron on 10/10/18.
//  Copyright © 2018 Robert Baron. All rights reserved.

#ifndef parse_tree_hpp
#define parse_tree_hpp

#define BAD_TYPE     -2
#define SEPARATOR    -1
#define TYPE_UNK      0
#define TYPE_STRING   1
#define TYPE_INT      2
#define TYPE_DOUBLE   3
#define TYPE_BOOL     4
#define TYPE_NULL     5
#define TYPE_KEYVALUE 6
#define TYPE_OBJECT   7
#define TYPE_ARRAY    8

#include "sym_table.hpp"


extern "C"
    {
    typedef struct ast_s 
        {
        char op;
        struct ast_s *rvalue;
        struct ast_s *lvalue;
        struct ast_s *parent;
        } ast_t;
    };

class parse_util
    {
public:
    parse_util();
    virtual ~parse_util();
    char get_op(ast_t *pt);
    ast_t *get_rvalue(ast_t *pt);
    ast_t *get_lvalue(ast_t *pt);
    ast_t *get_parent(ast_t *pt);
    ast_t *set_op(ast_t *pt, char op);
    ast_t *set_rvalue(ast_t *pt, ast_t *rvalue);
    ast_t *set_lvalue(ast_t *pt, ast_t *lvalue);
    int cmp_parse_tree(ast_t *pt1, ast_t *pt2, double epsilon=0.001 );
    void free_parse_tree(void *pt);
    void dump_parse_tree(const char *msg, void *pt, int indent=0);
    void *parse(const char *str);
    int dump_json(void *pt, int indent=0);  //this does nothing
    int get_type(ast_t *pt);
    long get_int(ast_t *pt);
    long get_bool(ast_t *pt);
    long is_null(ast_t *pt);
    double get_double(ast_t *pt);
    int get_string(ast_t *pt, char *str, int len);
    int cmp_string(ast_t *pt, const char *str, int len);
    int get_key(ast_t *pt, char *str, int len);
    int cmp_key(ast_t *pt, const char *str, int len);
    ast_t *get_value(ast_t *pt);
    int get_arrayLength(ast_t *pt);
    ast_t *get_arrayValue(ast_t *pt, int x);
    ast_t *get_KeyValue(ast_t *pt, int x);
    ast_t *get_ValueFromKey(ast_t *pt, const char *key, int len);
    type *get_type(void *pt, char *name=NULL);
    int buildSymTable(sym_table *st, void *pt, char *name=NULL);
    int get_data(char *URL, char *data, char *headers);
    };

#endif /* parse_tree_hpp */
