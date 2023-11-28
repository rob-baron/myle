//
//  le_time_sig.hpp
//  ALE
//
//  Created by Robert Baron on 8/17/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#ifndef le_time_sig_hpp
#define le_time_sig_hpp

#include <stdio.h>
#include "yale_object.hpp"

class yale_time_sig:public yale_object
    {
private:
    double bpm; // beats per measure, this can be 1  2  3  4  6  8    2 1/2
    int note_value;    //this can be 2  4  4  8  8  16   5
public:
    yale_time_sig();
    yale_time_sig(double beats, int nv);
    virtual ~yale_time_sig();
    virtual void render();
    virtual void deserialize(ast_t *pt);
    virtual char *serialize();
    void set_bpm(double beats);
    void set_note_value(int nv);
    void set_time_sig(double beats, int nv);
    void set_time_sig(yale_time_sig *ts);
    double get_bpm();
    int get_note_value();
    };

#endif /* le_time_sig_hpp */
