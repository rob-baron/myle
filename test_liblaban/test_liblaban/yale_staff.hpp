//
//  le_staff.hpp
//  ALE
//
//  Created by Robert Baron on 8/17/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#ifndef le_staff_hpp
#define le_staff_hpp

#include <stdio.h>
#include <vector>
#include "yale_object.hpp"
#include "yale_measure.hpp"
#include "yale_column.hpp"
#include "../../libjson/parse_tree.hpp"

class yale_staff:public yale_object
    {
private:
    yale_measure_metadata *measure;  // this is an alias to reference the score measure!!!
    std::vector<yale_column *> column;
public:
    yale_staff();
    yale_staff(yale_measure_metadata *m);
    virtual unsigned long get_measures();
    virtual void set_measures(unsigned long measure_cnt); //this is just for the interface
    virtual void render();
    virtual void deserialize(ast_t *pt);
    virtual char *serialize();
    };
#endif /* le_staff_hpp */
