//
//  test_time_sig.cpp
//  
//  Created by Robert Baron on 7/9/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//
//  These are some unit tests.

#include <gtest/gtest.h>

#include <libjson/sym_table.hpp>
#include <libjson/parse_tree.hpp>
#include <liblaban/yale_time_sig.hpp>

TEST(time_sig_test, GetterAndSetters)
    {
    yale_time_sig time_sig;
    yale_time_sig *time_sig_p;

    time_sig_p=new yale_time_sig();
    time_sig.set_bpm(6);
    time_sig.set_note_value(8);

    time_sig_p->set_bpm(4);
    time_sig_p->set_note_value(4);

    EXPECT_DOUBLE_EQ(time_sig.get_bpm(),6.0);
    EXPECT_EQ(time_sig.get_note_value(),8);

    EXPECT_DOUBLE_EQ(time_sig_p->get_bpm(),4.0);
    EXPECT_EQ(time_sig_p->get_note_value(),4);

    delete time_sig_p;
    }

TEST(time_sig_test, SaveAndRetrieve)
    {
    yale_time_sig time_sig;
    yale_time_sig *time_sig_p;
    yale_time_sig time_sig2;
    yale_time_sig *time_sig_p2;

    time_sig_p=new yale_time_sig();
    time_sig_p2=new yale_time_sig();
    time_sig.set_bpm(6);
    time_sig.set_note_value(8);

    time_sig_p->set_bpm(4);
    time_sig_p->set_note_value(4);
   
    char *time_sig_json = time_sig.serialize();
    char *time_sig_p_json = time_sig_p->serialize();
    char json[60];
    parse_util pu;
 
    snprintf(json,sizeof(json),"{%s}",time_sig_json);
    ast_t *time_sig_pt = (ast_t *)pu.parse(json);
    snprintf(json,sizeof(json),"{%s}",time_sig_p_json);
    ast_t *time_sig_pt2 = (ast_t *)pu.parse(json);

    time_sig2.deserialize(time_sig_pt);
    time_sig_p2->deserialize(time_sig_pt2);

    EXPECT_DOUBLE_EQ(6.0,time_sig2.get_bpm());
    EXPECT_EQ(8,time_sig2.get_note_value());

    EXPECT_DOUBLE_EQ(4.0, time_sig_p2->get_bpm());
    EXPECT_EQ(4, time_sig_p2->get_note_value());

    time_sig_p->set_bpm(7);
    time_sig_p->set_note_value(3);
    time_sig_p2->set_time_sig(time_sig_p);

    EXPECT_EQ(7,time_sig_p2->get_bpm());
    EXPECT_EQ(3,time_sig_p2->get_note_value());

    delete time_sig_p;
    delete time_sig_p2;
    }
