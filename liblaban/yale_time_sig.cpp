//
//  le_time_sig.cpp
//  ALE
//
//  Created by Robert Baron on 8/17/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#include "yale_time_sig.hpp"

yale_time_sig::yale_time_sig() { bpm=0; note_value=0; }

yale_time_sig::yale_time_sig(double beats, int nv)
    {
    set_bpm(beats);
    set_note_value(nv);
    }

yale_time_sig::~yale_time_sig() { }

void yale_time_sig::render() {};

void yale_time_sig::deserialize(ast_t *pt)
    {
    ast_t *st=NULL;
    parse_util pu;
    if(pu.get_type(pt)==TYPE_OBJECT)
        {
        st=pu.get_ValueFromKey(pt,"time_sig",10);
        }
    else if(pu.get_type(pt)==TYPE_KEYVALUE && pu.cmp_key(pt,"time_sig",10)==0)
        {
        st=pu.get_value(pt);
        }
    else if(pu.get_type(pt)==TYPE_ARRAY)
        {
        st=pt;
        }
    if(st && pu.get_type(st)==TYPE_ARRAY)
        {
        this->bpm=pu.get_double(pu.get_arrayValue(st,0));
        this->note_value=pu.get_double(pu.get_arrayValue(st,1));
        }
    }

char *yale_time_sig::serialize()
    {
    char *rv;
    rv=(char *)malloc(50); //should take less
    if(bpm==0 && note_value==0) snprintf(rv,50,"time_sig:null");
    else                        snprintf(rv,50,"time_sig:[%.4f,%d]",this->bpm, this->note_value);
    return rv;
    };

void yale_time_sig::set_bpm(double beats)
    {
    bpm=beats;
    }

void yale_time_sig::set_note_value(int nv)
    {
    note_value=nv;
    }

void yale_time_sig::set_time_sig(double beats, int nv)
    {
    set_bpm(beats);
    set_note_value(nv);
    }

void yale_time_sig::set_time_sig(yale_time_sig *ts)
    {
    if(ts)
        {
        set_bpm(ts->get_bpm());
        set_note_value(ts->get_note_value());
        }
    }

double yale_time_sig::get_bpm() { return this->bpm; }
int yale_time_sig::get_note_value() { return this->note_value; }

