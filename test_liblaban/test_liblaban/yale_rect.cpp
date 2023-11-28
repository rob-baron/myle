//
//  le_rect.cpp
//  ALE
//
//  Created by Robert Baron on 7/27/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#include "yale_rect.hpp"

yale_point::yale_point() {}
yale_point::yale_point(double i, double j) { }
yale_point::~yale_point() {}
void yale_point::set(double i, double j) { x=i; y=j; }
double yale_point::get_x() { return x; }
double yale_point::get_y() { return y; }

yale_rect::yale_rect() {ll=NULL; ur=NULL; }
yale_rect::~yale_rect()
    {
    if(ll) { delete ll; ll=NULL;}
    if(ur) { delete ur; ur=NULL; }
    }
void yale_rect::set(yale_point *ll_p, yale_point *ur_p)
    {
    if( ll_p && ur_p)
        {
        if(!ll) { ll=new yale_point(); }
        if(!ur) { ur=new yale_point(); }
        ll->set(ll_p->get_x(), ll_p->get_y());
        ur->set(ur_p->get_x(), ur_p->get_y());
        }
    }
bool yale_rect::is_in(yale_point *p)
    {
    if( ll && ur && p)
        {
        if(   ll->get_x() <= p->get_x() && p->get_x() <= ur->get_x()
           && ll->get_y() <= p->get_y() && p->get_y() <= ur->get_y() )
            {
            return true;
            }
        return false;
        }
    return false;
    }
