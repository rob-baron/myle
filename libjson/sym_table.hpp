//
//  sym_table.hpp
//  ALE
//
//  Created by Robert Baron on 10/11/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#ifndef sym_table_hpp
#define sym_table_hpp

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
}

#include <vector>
#include <list>

class type
    {
private:
    char *name;
    int  size;
    char master_type; //ie (a)rray, (o)bject, (s)tring, (i)nt, (d)ouble, (d)ate
    char sub_type;    //ie array of ...
    int link_count;
    std::list<type *> members;
public:
    type() { name=NULL; size=0; master_type=0; sub_type=0; link_count=1; }
    virtual ~type() { if(name) free(name); }
    void set_name(const char *n)
    {
    if(n)
        {
        size_t len=strlen(n);
        name=(char *)malloc(len+1);
        std:strcpy(name, n);
        }
    }
    void set_size(int s){size=s;}
    void set_master_type(char t){master_type=t;}
    void set_sub_type(char st){sub_type=st;}
    const char *get_name(){return name;}
    int get_size(){return size;}
    char get_master_type() {return master_type;}
    char get_sub_type() {return sub_type;}

    void inc_linkcnt() { link_count++; }
    void dec_linkcnt() { link_count--; }
    int get_linkcnt() { return link_count; }

    //does 2 things
    //    1) adds member if not found
    //    2) updates the type to the least restrictive type.
    void add_member(type *m)
    {
    std::list<type *>::const_iterator iter;
    iter = members.begin();
    while(iter != members.end() && strcmp((*iter)->get_name(),m->get_name())!=0) { ++iter; }
    if(iter!=members.end() && strcmp((*iter)->get_name(),m->get_name())==0)
        {
        //update (*iter) to least restrive type
        }
    else
        {
        members.push_front(m);
        }
    }
    //This is a loose comparison
    //  are the mutual fields inconsistent
    int cmp_types(type *t2)
    {
    //should sort the members for both
    return 0;
    }

    int merge_types(type *t2)
    {
    return 0;
    }

    int get_ctype(char *buf, int buf_size)
    {
    int cnt=0;
    switch(this->get_master_type())
        {
            case 's': cnt+=snprintf(buf+cnt,buf_size-cnt,"%s_t *",this->get_name());break;
            case 'c': cnt+=snprintf(buf+cnt,buf_size-cnt,"char *");break;
            case 'd': cnt+=snprintf(buf+cnt,buf_size-cnt,"double ");break;
            case 'i': cnt+=snprintf(buf+cnt,buf_size-cnt,"long ");break;
            default: break;
        }
    this->get_name();
    cnt+=snprintf(buf+cnt,buf_size-cnt,"%s",this->get_name());
    if(this->get_size()>1) { cnt+=snprintf(buf+cnt,buf_size-cnt,"[%d]",this->get_size()); }
    cnt+=snprintf(buf+cnt,buf_size-cnt,";\n");
    return cnt;
    }

    void get_cstruct(char *buf, int buf_size)
    {
    int cnt=0;
    type *m;
    cnt+=snprintf(buf,buf_size,"typedef struct {\n");
    std::list<type *>::const_iterator iter;
    iter = members.begin();
    while(iter != members.end())
        {
        m=(*iter);
        cnt+=m->get_ctype(buf+cnt,buf_size-cnt);
        ++iter;
        }
    snprintf(buf+cnt,buf_size-cnt,"} %s;",this->name);
    }
};

class sym_table
{
private:
    std::vector<std::list<type *> >  symbols;
    int table_size;

    long long hash_key(char *k)
    {
    int x;
    long long rv=0;
    if(k)
        {
        for(x=0; x<strlen(k) && x<10; x++)
            {
            rv=rv*10 % table_size;
            rv+=k[x];
            }
        }
    return rv;
    }
    type *lookup_list(char *key)
    {
    type *t=NULL;
    long long bin=hash_key(key);
    std::list<type *> *sym_list;
    sym_list=&(symbols[bin]);
    std::list<type *>::const_iterator iter;
    for (iter = sym_list->begin(); iter != sym_list->end(); ++iter)
        {
        if(strcmp((*iter)->get_name(),key)==0) t=*iter;
        }
    return t;
    }

public:
    sym_table() { table_size=1000; }
    ~sym_table() { /* delete all of the symbols in table */ }

    int add_update(type *t, char *key)
    {
    long long bin=hash_key(key);
    std::list<type *> *sym_list;
    std::list<type *>::const_iterator iter;
    sym_list=&(symbols[bin]);
    iter = sym_list->begin();
    while( iter != sym_list->end()){ ++iter;}
        {
        if(strcmp((*iter)->get_name(),key)==0) t=*iter;
        }
    if(strcmp((*iter)->get_name(),key)==0)
        {
        //check/update info
        }
    else
        {
        sym_list->push_back(t);
        }
    return 0;
    }
    int del_key(char *key)
    {
    type *t;
    long long bin=hash_key(key);
    std::list<type *> *sym_list;
    std::list<type *>::const_iterator iter;
    sym_list=&(symbols[bin]);
    iter = sym_list->begin();
    while(iter != sym_list->end() && strcmp((*iter)->get_name(),key)==0) { ++iter; }
    if(strcmp((*iter)->get_name(),key)==0)
        {
        t=*iter;
        t->dec_linkcnt();
        if(t->get_linkcnt()==0) { free(t); }

        }
    return 0;
    }
    int link(char *k1, char *k2)
    {
    type *t1=get(k1);
    type *t2=get(k2);
    if(t1 && t2)
        {
        //merge the types to t2 and update t2 to k1
        //increment count on t2, delete t1

        }
    return 0;
    }
    type *get(char *key)
    {
    return lookup_list(key);
    }
};

#endif /* sym_table_hpp */
