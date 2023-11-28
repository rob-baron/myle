//
//  le_score.cpp
//  ALE
//
//  Created by Robert Baron on 7/9/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#include "yale_score.hpp"
#include "../../libjson/parse_tree.hpp"

yale_score::yale_score()
    {
    score_title=NULL;
    num_of_measures=0;
    width=0;
    length_of_measure=2.5; //in cn
    length_of_page=0.5;
    //width_of_column=0;
    }

yale_score::~yale_score()
    {
    if(score_title) { free(score_title); }
    }

void yale_score::render(){ }

void deserialize(ast_t *pt) {}

char *serialize(){ return NULL; }

void yale_score::add_title(char *title)
    {
    long len;
    len=strlen(title);
    if(title) { free(title); }
    score_title=(char *)malloc(sizeof(char) * (len + 1));
    strncpy(title,score_title,len);
    }

void yale_score::add_staff(ast_t *pt)
    {
    yale_staff *tmp_staff=new yale_staff();
    tmp_staff->deserialize(pt);
    staff.push_back(tmp_staff);
    }

void yale_score::add_staff()
    {
    yale_staff *tmp_staff = new yale_staff();
    staff.push_back(tmp_staff);
    }

void yale_score::add_measure()
    {

    }

//translates the x,y into a part/colum/beat
//ale_movement *find_movement(long x, long y)
//    {
//
//    }
