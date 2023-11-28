//
//  test_time_sig.cpp
//  
//  Created by Robert Baron on 7/9/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//
//  These are some unit tests.

#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libjson/sym_table.hpp>
#include <libjson/parse_tree.hpp>
#include <liblaban/yale_time_sig.hpp>
#include <liblaban/yale_measure.hpp>
#include <liblaban/yale_column.hpp>

void direction_test(const char *direction, int d)
    {
    yale_dir_symbol ds;
    char buff[4];

    ds.set_direction(direction);
    ds.get_direction(buff,sizeof(buff));
    //printf("dir: %s %s %d\n", direction, buff, ds.get_dir());
    EXPECT_EQ(ds.get_dir(),d);
    EXPECT_EQ(strncmp(direction,buff,sizeof(buff)),0);
    }

TEST(test_direction, GetterAndSetters)
    {
    yale_dir_symbol ds;
    char buff[20];

    direction_test("lv",DIR_LEFT_PIVOT);
    direction_test("lf",DIR_LEFT_FORWARD);
    direction_test("dlf",DIR_DIAG_LEFT_FORWARD);
    direction_test("ls",DIR_LEFT_SIDE);
    direction_test("dlb",DIR_DIAG_LEFT_BACK);
    direction_test("lb",DIR_LEFT_BACK);

    direction_test("rv",DIR_RIGHT_PIVOT);
    direction_test("rf",DIR_RIGHT_FORWARD);
    direction_test("drf",DIR_DIAG_RIGHT_FORWARD);
    direction_test("rs",DIR_RIGHT_SIDE);
    direction_test("drb",DIR_DIAG_RIGHT_BACK);
    direction_test("rb",DIR_RIGHT_BACK);

    yale_body_symbol bs;
    }

TEST(yale_measure_data, GettersAndSetters)
    {
    yale_measure_data *d=new yale_measure_data();
    EXPECT_TRUE(d->is_time_sig_null());
    }

TEST(test_measure_data, insert_measure)
    {
    yale_measure_metadata measures;

    yale_time_sig *ts=new yale_time_sig(4.0,4);
    measures.insert_measure(ts,0,20);
    EXPECT_EQ(measures.get_measure_count(),20);
    EXPECT_EQ(measures.calc_beats(),80);
    }

TEST(test_column, GetterAndSetters)
    {
    yale_column *column=new yale_column();
    yale_dir_symbol *ds;

    column->set_symbol(new yale_dir_symbol(DIR_LEFT_FORWARD,1,3));
    yale_measure_metadata measures;
    //yale_measure_metadata *measures=new yale_measure_metadata;

    column->set_measure(&measures);
    measures.set_time_sig(0,2.5,4);
    //measures.set_size(5.5);
    
    //EXPECT_EQ(column_data->get_time_sig()->get_note_value(),4);
    //delete measures;
    delete column;
    }

TEST(test_column, SaveAndRetrieve)
    {
    yale_column column_data;
    yale_column column_data2;

    char *column_json = column_data.serialize();
    char json[60];

    parse_util pu;

    snprintf(json,sizeof(json),"{%s}",column_json);
    //printf("%s\n",json);
    ast_t *column_data_pt = (ast_t *)pu.parse(json);
    //pu.dump_parse_tree("test_measure",(void*)measure_data_pt,0);
    //column_data2->deserialize(column_data_pt);

    }
