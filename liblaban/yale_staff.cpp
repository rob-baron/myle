//
//  le_staff.cpp
//  ALE
//
//  Created by Robert Baron on 8/17/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#include "yale_staff.hpp"

yale_staff::yale_staff() {measure=NULL;}
yale_staff::yale_staff(yale_measure_metadata *m)
    {
    measure=m;
    }
unsigned long yale_staff::get_measures() { return measure->get_measure_count(); }
void yale_staff::set_measures(unsigned long measure_cnt) { return; }  //this is just for the interface
void yale_staff::render() {}
void yale_staff::deserialize(ast_t *pt) {}
char *yale_staff::serialize() { return NULL; }

