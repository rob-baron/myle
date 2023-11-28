//
//  ale_measure.hpp
//  ALE
//
//  Created by Robert Baron on 9/7/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#ifndef __YALE_MEASURE_HPP__
#define __YALE_MEASURE_HPP__

#include <stdio.h>
#include <list>
#include "yale_object.hpp"
#include "yale_rect.hpp"
#include "yale_time_sig.hpp"

class yale_measure_data: public yale_object
    {
private:
    yale_time_sig time_sig;
    double size;
    //need to include the bar/double_bar at bottom and top.  bar would be the default.
public:
    yale_measure_data();
    virtual ~yale_measure_data();
    virtual bool is_time_sig_null();
    virtual void set_size(double s);
    virtual void set_time_sig(yale_time_sig *ts);
    virtual void set_time_sig(double beat_count, int note_value);
    virtual yale_time_sig *get_time_sig(yale_time_sig *ts=NULL);
    virtual double get_size();
    virtual void render();
    virtual char *serialize();
    virtual void deserialize(ast_t *pt) ;
    };

// Should make this a sparse array, but for now, keep it fully populated
class yale_measure_metadata: public yale_object
    {
private:
    std::vector<yale_measure_data *> measure_array;
    long total_beats;

public:
    yale_measure_metadata();
    virtual ~yale_measure_metadata();
    virtual void render();
    virtual size_t get_measure_count();
    virtual int get_ui_size(unsigned long measure_num);
    virtual size_t calc_beats();
    virtual int insert_measure( yale_time_sig *ts, int measure_number, int count=1 );
    virtual yale_time_sig *get_time_sig(unsigned long measure_num, yale_time_sig *ts_buf=NULL);
    virtual void set_time_sig(unsigned long measure_num, double bpm, double note_value);
    virtual void deserialize(ast_t *pt);
    virtual char *serialize();
    };
#endif /* __YALE_MEASURE_HPP__ */
