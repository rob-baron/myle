//
//  test_measure.cpp
//  
//  Created by Robert Baron on 7/9/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//
//  These are some unit tests.

#include <gtest/gtest.h>

#include <libjson/sym_table.hpp>
#include <libjson/parse_tree.hpp>
#include <liblaban/yale_measure.hpp>

TEST(time_measure, GetterAndSetters)
    {
    yale_measure_data *measure_data=new yale_measure_data();
    measure_data->set_time_sig(2.5,4);
    measure_data->set_size(5.5);

    yale_time_sig tmp_ts;
    EXPECT_DOUBLE_EQ(measure_data->get_size(),5.5);
    EXPECT_DOUBLE_EQ(measure_data->get_time_sig(&tmp_ts)->get_bpm(),2.5);
    EXPECT_EQ(measure_data->get_time_sig(&tmp_ts)->get_note_value(),4);
    }

TEST(test_measure, SaveAndRetrieve)
    {
    yale_measure_data *measure_data=new yale_measure_data();
    measure_data->set_time_sig(2.5,4);
    measure_data->set_size(5.5);
    yale_measure_data *measure_data2=new yale_measure_data();

    char *measure_data_json = measure_data->serialize();
    char json[60];

    parse_util pu;
    yale_time_sig tmp_ts;
 
    snprintf(json,sizeof(json),"{%s}",measure_data_json);
    //printf("%s\n",json);
    ast_t *measure_data_pt = (ast_t *)pu.parse(json);
    //pu.dump_parse_tree("test_measure",(void*)measure_data_pt,0);
    measure_data2->deserialize(measure_data_pt);    
    
    EXPECT_DOUBLE_EQ(5.5,measure_data2->get_size());
    EXPECT_DOUBLE_EQ(2.5,measure_data2->get_time_sig(&tmp_ts)->get_bpm());
    EXPECT_EQ(measure_data2->get_time_sig(&tmp_ts)->get_note_value(),4);
    }

TEST(test_measure, null_timesig)
    {
    yale_measure_data *md=new yale_measure_data();
    EXPECT_TRUE(md->is_time_sig_null());
    md->set_time_sig(NULL);
    EXPECT_TRUE(md->is_time_sig_null());

    md->set_time_sig(2.5,5);
    EXPECT_FALSE(md->is_time_sig_null());
    yale_time_sig *ts=new yale_time_sig(4,5);
    md->set_time_sig(ts);
    EXPECT_FALSE(md->is_time_sig_null());
    delete ts;
    }

TEST(test_measure_metadata, zero_length_array)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    }

TEST(test_measure_metadata, insert_one_measure)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    yale_time_sig ts;
    ts.set_bpm(4);
    ts.set_note_value(4);
    mmd.insert_measure(&ts,1);
    EXPECT_TRUE(mmd.get_measure_count()==1);
    yale_time_sig ts2;
    mmd.get_time_sig(0,&ts2);

    double test=ts2.get_bpm();
    EXPECT_DOUBLE_EQ(ts2.get_bpm(),4.0);
    EXPECT_EQ(ts2.get_note_value(),4.0);
    }

TEST(test_measure_metadata, insert_ten_measures1)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    yale_time_sig ts;
    ts.set_bpm(4);
    ts.set_note_value(4);
    mmd.insert_measure(&ts,0,10);
    EXPECT_TRUE(mmd.get_measure_count()==10);
    yale_time_sig ts2;
    int x;
    for(x=0; x<10; x++)
        {
        mmd.get_time_sig(x,&ts2);

        double test=ts2.get_bpm();
        EXPECT_DOUBLE_EQ(ts2.get_bpm(),4.0);
        EXPECT_EQ(ts2.get_note_value(),4.0);
        }
    }

TEST(test_measure_metadata, insert_one_measure10_head_addition)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    yale_time_sig ts;
    ts.set_bpm(4);
    ts.set_note_value(4);
    int x;
    for(x=0; x<10; x++)
        {
        mmd.insert_measure(&ts,0,1);
        }

    EXPECT_TRUE(mmd.get_measure_count()==10);
    yale_time_sig ts2;

    for(x=0; x<10; x++)
        {
        mmd.get_time_sig(x,&ts2);

        double test=ts2.get_bpm();
        EXPECT_DOUBLE_EQ(ts2.get_bpm(),4.0);
        EXPECT_EQ(ts2.get_note_value(),4.0);
        }
    }

TEST(test_measure_metadata, insert_one_measures10_tail_addition)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    yale_time_sig ts;
    ts.set_bpm(4);
    ts.set_note_value(4);
    int x;
    for(x=0; x<10; x++)
        {
        mmd.insert_measure(&ts,x,1);
        }

    EXPECT_TRUE(mmd.get_measure_count()==10);
    yale_time_sig ts2;

    for(x=0; x<10; x++)
        {
        mmd.get_time_sig(x,&ts2);

        double test=ts2.get_bpm();
        EXPECT_DOUBLE_EQ(ts2.get_bpm(),4.0);
        EXPECT_EQ(ts2.get_note_value(),4.0);
        }
    }

TEST(test_measure_metadata, insert_one_measures10_mid_addition)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    yale_time_sig ts;
    ts.set_bpm(4);
    ts.set_note_value(4);
    mmd.insert_measure(&ts,0,2);
    int x;
    for(x=0; x<10; x++)
        {
        mmd.insert_measure(&ts,x+1,1);
        }

    EXPECT_TRUE(mmd.get_measure_count()==12);
    yale_time_sig ts2;

    for(x=0; x<12; x++)
        {
        mmd.get_time_sig(x,&ts2);

        double test=ts2.get_bpm();
        EXPECT_DOUBLE_EQ(ts2.get_bpm(),4.0);
        EXPECT_EQ(ts2.get_note_value(),4.0);
        }
    }

TEST(test_measure_metadata, insert_ten_measures10_head_addition)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    yale_time_sig ts;
    ts.set_bpm(4);
    ts.set_note_value(4);
    int x;
    for(x=0; x<10; x++)
        {
        mmd.insert_measure(&ts,0,10);
        }

    EXPECT_TRUE(mmd.get_measure_count()==100);
    yale_time_sig ts2;

    for(x=0; x<100; x++)
        {
        mmd.get_time_sig(x,&ts2);

        double test=ts2.get_bpm();
        EXPECT_DOUBLE_EQ(ts2.get_bpm(),4.0);
        EXPECT_EQ(ts2.get_note_value(),4.0);
        }
    }

TEST(test_measure_metadata, insert_ten_measures10_tail_addition)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    yale_time_sig ts;
    ts.set_bpm(4);
    ts.set_note_value(4);
    int x;
    for(x=0; x<10; x++)
        {
        mmd.insert_measure(&ts,x,10);
        }

    EXPECT_TRUE(mmd.get_measure_count()==100);
    yale_time_sig ts2;

    for(x=0; x<100; x++)
        {
        mmd.get_time_sig(x,&ts2);

        double test=ts2.get_bpm();
        EXPECT_DOUBLE_EQ(ts2.get_bpm(),4.0);
        EXPECT_EQ(ts2.get_note_value(),4.0);
        }
    }

TEST(test_measure_metadata, insert_ten_measures10_mid_addition)
    {
    yale_measure_metadata mmd;
    EXPECT_TRUE(mmd.get_measure_count()==0);
    yale_time_sig ts;
    ts.set_bpm(4);
    ts.set_note_value(4);
    mmd.insert_measure(&ts,0,2);
    int x;
    for(x=0; x<10; x++)
        {
        mmd.insert_measure(&ts,x+1,10);
        }

    EXPECT_TRUE(mmd.get_measure_count()==102);
    yale_time_sig ts2;

    for(x=0; x<102; x++)
        {
        mmd.get_time_sig(x,&ts2);

        double test=ts2.get_bpm();
        EXPECT_DOUBLE_EQ(ts2.get_bpm(),4.0);
        EXPECT_EQ(ts2.get_note_value(),4.0);
        }
    }
