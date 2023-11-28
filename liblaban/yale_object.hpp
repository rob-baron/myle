//
//  le_object.hpp
//  ALE
//
//  Created by Robert Baron on 7/20/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#ifndef yale_object_hpp
#define yale_object_hpp

#include <stdio.h>
#include "../../libjson/parse_tree.hpp"

class yale_object
    {
public:
    yale_object();
    virtual ~yale_object();
    virtual void render()=0;
    //virtual void deserialize(char *data)=0;
    virtual void deserialize(ast_t *pt){}
    virtual char *serialize(){return NULL;}
    };

#endif /* yale_object_hpp */
