//
//  le_score.hpp
//  ALE
//
//  Created by Robert Baron on 7/9/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#ifndef le_score_hpp
#define le_score_hpp

#include <stdio.h>
#include <vector>
#include "yale_object.hpp"
#include "yale_staff.hpp"
#include "yale_time_sig.hpp"
#include "yale_measure.hpp"
#include "../../libjson/parse_tree.hpp"

//ale - a laban editor
//
// ale_score
//  -> has staffs
//     -> staff has measures and columes
//        -> columns have movements
//
// here:
//     x and y screen coordinates need to a measure number and/or a beat

class yale_score: public yale_object
    {
private:
    std::vector<yale_staff *> staff;
    yale_measure_metadata measure;  //this is where the measures are defined
    char *score_title;
    long num_of_measures;
    long width;
    double length_of_measure;
    double length_of_page;

public:
    yale_score();
    virtual ~yale_score();
    virtual void render();
    virtual void deserialize(ast_t *pt);
    virtual char *serialize();
    void add_title(char *title);
    void add_staff(ast_t *pt);
    void add_staff();
    void add_measure();
    //translates the x,y into a part/colum/beat
    };

#endif /* le_score_hpp */
