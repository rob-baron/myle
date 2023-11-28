//
//  json_tests.cpp
//  
//  Created by Robert Baron on 7/9/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//
//  These are some unit tests.

#include <gtest/gtest.h>

#include "../libjson/sym_table.hpp"
#include "../libjson/parse_tree.hpp"

TEST(json_test, EmptyCurlyBraces)
    {
    ast_t *pt;
    parse_util pu;
    //go through the basic productions
    pt=(ast_t *)pu.parse( "{ }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairNull )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ test:null }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_rvalue(pt);
    EXPECT_TRUE(pu.get_type(st)==TYPE_KEYVALUE);
    EXPECT_TRUE(pu.cmp_key(st,"test",5)==0);
    EXPECT_TRUE(pu.get_type(pu.get_value(st))==TYPE_NULL);
    
    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        EXPECT_TRUE(pu.get_type(st)==TYPE_NULL);
        }
    st=pu.get_ValueFromKey(pt, "dummy",6);
    EXPECT_FALSE(st);

    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairTrue )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ test:true }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        EXPECT_TRUE(pu.get_type(st)==TYPE_BOOL);
        EXPECT_TRUE(pu.get_bool(st));
        }
    st=pu.get_ValueFromKey(pt, "dummy",6);
    EXPECT_FALSE(st);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairFalse )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ test:false }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        EXPECT_TRUE(pu.get_type(st)==TYPE_BOOL);
        EXPECT_FALSE(pu.get_bool(st));
        }
    st=pu.get_ValueFromKey(pt, "dummy",6);
    EXPECT_FALSE(st);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairQuotedValue )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ test:'ABC' }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        EXPECT_TRUE(pu.get_type(st)==TYPE_STRING);

        char tmp_str[50];
        pu.get_string(st,&(tmp_str[0]), 50);
        //printf("tmp_str = %s\n",tmp_str);
        //exit(0);
        EXPECT_TRUE( strcmp(tmp_str,"ABC")==0 );
        }
    st=pu.get_ValueFromKey(pt, "dummy",6);
    EXPECT_FALSE(st);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairUnquotedStrValue )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ test:ABC }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        EXPECT_TRUE(pu.get_type(st)==TYPE_STRING);

        char tmp_str[50];
        pu.get_string(st,&(tmp_str[0]), 50);
        EXPECT_TRUE( strcmp(tmp_str,"ABC")==0 );
        }
    st=pu.get_ValueFromKey(pt, "dummy",6);
    EXPECT_FALSE(st);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairUnquotedIntValue )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ test:123 }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        //TYPE_DOUBLE is a basic number type.
        EXPECT_TRUE(pu.get_type(st)==TYPE_DOUBLE);
        EXPECT_DOUBLE_EQ(123,pu.get_double(st));
        }
    st=pu.get_ValueFromKey(pt, "dummy",6);
    EXPECT_FALSE(st);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairUnquotedDoubleValue )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ test:123.456 }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        //TYPE_DOUBLE is a basic number type.
        EXPECT_TRUE(pu.get_type(st)==TYPE_DOUBLE);
        EXPECT_DOUBLE_EQ(123.456,pu.get_double(st));
        }
    st=pu.get_ValueFromKey(pt, "dummy",6);
    EXPECT_FALSE(st);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairUnquotedDoubleUnquotedStrValue )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ test:123.456, test1:ABC }" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        //TYPE_DOUBLE is a basic number type.
        EXPECT_TRUE(pu.get_type(st)==TYPE_DOUBLE);
        EXPECT_DOUBLE_EQ(123.456,pu.get_double(st));
        }
    st=pu.get_ValueFromKey(pt, "test1", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        EXPECT_TRUE(pu.get_type(st)==TYPE_STRING);
        char tmp_str[50];
        pu.get_string(st,&(tmp_str[0]), 50);
        EXPECT_TRUE( strcmp(tmp_str,"ABC")==0 );
        }
    st=pu.get_ValueFromKey(pt, "dummy",6);
    EXPECT_FALSE(st);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKvPairArray )
    {
    ast_t *pt, *st;
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{test:[123.456,321]}" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    st=pu.get_ValueFromKey(pt, "test", 5);
    EXPECT_TRUE(st);
    if(st)
        {
        //TYPE_DOUBLE is a basic number type.
        EXPECT_TRUE(pu.get_type(st)==TYPE_ARRAY);
        ast_t *element=pu.get_arrayValue(st,0);
        EXPECT_DOUBLE_EQ(123.456,pu.get_double(element));
        EXPECT_DOUBLE_EQ(123.456,pu.get_double(pu.get_arrayValue(st,0)));

        element=pu.get_arrayValue(st,1);
        //EXPECT_DOUBLE_EQ(123.456,pu.get_double(element));
        //EXPECT_DOUBLE_EQ(123.456,pu.get_double(pu.get_arrayValue(st,1)));

        }
    //st=pu.get_ValueFromKey(pt, "test1", 5);
    //EXPECT_TRUE(st);
    //if(st)
    //    {
    //    EXPECT_TRUE(pu.get_type(st)==TYPE_STRING);
    //    char tmp_str[50];
    //    pu.get_string(st,&(tmp_str[0]), 50);
    //    EXPECT_TRUE( strcmp(tmp_str,"ABC")==0 );
    //    }
    //st=pu.get_ValueFromKey(pt, "dummy",6);
    //EXPECT_FALSE(st);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonEmptyArray )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[ ]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==0);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayNullValue )     
    {
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[ null ]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==1);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }
 
TEST(json_test, JsonArrayTrueValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[ true ]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==1);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayFalseValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[ false ]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==1);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayQuotedStrValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[ 'ABC' ]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==1);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayUnquotedStrValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[ ABC ]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==1);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayNumValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[ 123 ]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==1);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayDoubleValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[ 123.456 ]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==1);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayQuotedStringValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "['1']" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==1);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayStrStrValues )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "['1','2']" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==2);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayStrStrArrays )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[['1','2'],['3','4']]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayStrStrStrValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "['1','2','3']" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    //printf("array length: %d\n",pu.get_arrayLength(pt));
    st=pu.get_arrayValue(pt, 0);
    //printf("type: %c",pu.get_op(st));
    char tmp_str[50];
    pu.get_string(st,&(tmp_str[0]), 50);
    //EXPECT_TRUE(pu.get_arrayLength(pt)==3);
    //pu.dump_parse_tree("versions",pt);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayStrEmpty )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "['1',]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==2);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayStrStrEmpty )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "['1','2',]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==3);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayStrStrArraysEmpty )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "[['1','2',],['3','4'],]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonArrayStrStrStrEmpty )     
    {     
    ast_t *pt, *st;    
    parse_util pu;
    pt=(ast_t *)pu.parse(  "['1','2','3',]" );
    EXPECT_TRUE(pu.get_type(pt)==TYPE_ARRAY);
    EXPECT_TRUE(pu.get_arrayLength(pt)==4);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonStrValue )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{ 'name' }" );  // This should produce a syntax error
    //EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);
    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKeyValEmptyJson )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{key1:{}}");
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKeyValueArrayJsonKeyVal )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{key1:[{name:val1}]}");
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKeyValueArrayJsonKeyValkeyVal )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{key1:[{key1a:val1,key1b:[]}]}");
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, Json004_Test )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{level:[{n:0, s:S}]}");  //this needs to be fixed! the [{n:  somehow the n is being skipped.
    //EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);
    //printf("op=%c\n",pt->op);
    //pu.dump_parse_tree("versions",pt);
    //if(!pt) printf("pt==NULL\n");
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, JsonKeyValueArrayjsonKeyValueArrays )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{key1:[{key1a:[{key2a:'val2a',id:0}],level:[{n:0, s:S}]}]}");  //this needs to be fixed! the [{n:  somehow the n is being skipped.
    //EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);
    //printf("op=%c\n",pt->op);
    //pu.dump_parse_tree("versions",pt);
    //if(!pt) printf("pt==NULL\n");
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, Json001 )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{DanceDefinition:[{name:waltz,figures:[{name:'Prep Step',id:0}],level:[{l:0, s:S}]}]}");
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, Json002 )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{DanceDefinition:[{name:waltz,figures:[{name:'Prep Step',id:0}],level:[{'n':0, s:S}]}]}");  //but 'n' is not
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

TEST(json_test, Json003 )     
    {     
    ast_t *pt, *st;     
    parse_util pu;
    pt=(ast_t *)pu.parse(  "{DanceDefinition:[{name:waltz,figures:[{name:'Prep Step',id:0}],level:[{le:0, s:S}]}]}"); //and le is not
    EXPECT_TRUE(pu.get_type(pt)==TYPE_OBJECT);

    //pu.dump_parse_tree("versions",rv);
    pu.free_parse_tree(pt);
    EXPECT_TRUE(true);
    }

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

