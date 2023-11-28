//
//  le_rect.hpp
//  ALE
//
//  Created by Robert Baron on 7/27/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#ifndef le_rect_hpp
#define le_rect_hpp

#include <stdio.h>

class yale_point
    {
private:
    double x;
    double y;
public:
    yale_point();
    yale_point(double i, double j);
    virtual ~yale_point();
    void set(double i, double j);
    double get_x();
    double get_y();
    };

class yale_rect
    {
private:
    yale_point *ll;
    yale_point *ur;
public:
    yale_rect();
    virtual ~yale_rect();
    void set(yale_point *ll_p, yale_point *ur_p);
    bool is_in(yale_point *p);
    };

#endif /* le_rect_hpp */
