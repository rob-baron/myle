//
//  ale_measure.cpp
//  ALE
//
//  Created by Robert Baron on 9/7/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//

#include "yale_measure.hpp"


yale_measure_data::yale_measure_data()
    {
    size=10;

    time_sig.set_bpm(0.0);
    time_sig.set_note_value(0);
    }

yale_measure_data::~yale_measure_data(){}

bool yale_measure_data::is_time_sig_null()
    {
        if(time_sig.get_bpm()==0.0 && time_sig.get_note_value()==0)
            return true;
        return false;
    }

void yale_measure_data::set_size(double s) { size=s; }

void yale_measure_data::set_time_sig(yale_time_sig *ts)
    {
    if(ts==NULL)
        {
        time_sig.set_bpm(0.0);
        time_sig.set_note_value(0);
        }
    else
        {
        time_sig.set_bpm(ts->get_bpm());
        time_sig.set_note_value(ts->get_note_value());
        }
    }

void yale_measure_data::set_time_sig(double beat_count, int note_value)
    {
    time_sig.set_bpm(beat_count);
    time_sig.set_note_value(note_value);
    }

yale_time_sig *yale_measure_data::get_time_sig(yale_time_sig *ts)
    {
    yale_time_sig *ret_ts;

    if(ts==NULL) ret_ts=new yale_time_sig();
    else ret_ts=ts;

    ret_ts->set_bpm(time_sig.get_bpm());
    ret_ts->set_note_value(time_sig.get_note_value());

    return ret_ts;
    }

double yale_measure_data::get_size() { return size; }

void yale_measure_data::render() {}

char *yale_measure_data::serialize()
    {
    char *rv;
    rv=(char *)malloc(50); //should take less
    char *ts=time_sig.serialize();
    if(ts)
        {
        snprintf(rv,50,"measure:{%s,size:%.4f}",ts,size);
        free(ts);
        }
    else
        {
        snprintf(rv,50,"measure:{time_sig:nil,size:%.4f}",size);
        }
    return rv;
    //{measure:{time_sig:[4,4],size:10}}
    }

void yale_measure_data::deserialize(ast_t *pt)
    {
    ast_t *st=NULL;
    parse_util pu;
    if(pu.get_type(pt)==TYPE_OBJECT)
        {
        st=pu.get_ValueFromKey(pt,"measure",10);
        }
    else if(pu.get_type(pt)==TYPE_KEYVALUE && pu.cmp_key(pt,"measure",10)==0)
        {
        st=pu.get_value(pt);
        }
    // a measure is an object that contains a size and a time_sig
    if(st && pu.get_type(st)==TYPE_OBJECT)
        {
        //This passes more than is necessary, but time_sig will find the 'time_sig' kv pair
        this->time_sig.deserialize(st);
        this->size=pu.get_double(pu.get_ValueFromKey(st, "size", 5));
        }
    }

// Should make this a sparse array, but for now, keep it fully populated
yale_measure_metadata::yale_measure_metadata() {}

yale_measure_metadata::~yale_measure_metadata()
    {
    int x;
    for(x=0; x<measure_array.size(); x++ )
        {
        if(measure_array[x]!=NULL)
            {
            delete(measure_array[x]);
            measure_array[x]=NULL;
            }
        }
    }

void yale_measure_metadata::render(){}

size_t yale_measure_metadata::get_measure_count()
    {
    return measure_array.size();
    }

int yale_measure_metadata::get_ui_size(unsigned long measure_num)
    {
    if(measure_num<measure_array.size())
        {
        return measure_array[measure_num]->get_size();
        }
    return 0;
    }

size_t yale_measure_metadata::calc_beats()
    {
    int x;
    long current_bpm=0;
    size_t total_beats=0;
    size_t measure_num=measure_array.size();
    for(x=0; x<measure_num; x++)
        {
        long tmp_bpm=(measure_array[x])->get_time_sig()->get_bpm();
        if( tmp_bpm > 0 ) { current_bpm=tmp_bpm;  }
        total_beats += current_bpm;
        }
    return total_beats;
    }

int yale_measure_metadata::insert_measure( yale_time_sig *ts, int measure_number, int count )
    {
    //0 inserts at start
    size_t start_index, x;
    if( measure_number==0 || measure_array.size()==0 )
        {
        measure_array.insert(measure_array.begin(),count,NULL);
        start_index=0;
        }
    //-1 inserts at end
    else if(measure_number==-1 || measure_number>measure_array.size() )
        {
        start_index=measure_array.size();
        measure_array.insert(measure_array.end(),count,NULL);
        }
    else
        {
        start_index=measure_number;
        measure_array.insert(measure_array.begin()+measure_number,count,NULL);
        }
    for(x=0; x<count; x++)
        {
        measure_array[start_index+x]=new yale_measure_data();
        if(ts) (measure_array[start_index+x])->set_time_sig(ts);
        }
    return 0;
    }

yale_time_sig *yale_measure_metadata::get_time_sig(unsigned long measure_num, yale_time_sig *ts_buf)
    {
    if(measure_num>=0 && measure_num<measure_array.size())
        {
        int x;
        yale_time_sig ts,*tmp_ts;
        //for(x=measure_number; x>=0; x--)
        //    {
        //    // eventually only store the changes, but for now just keep the array of timesignitures
        //    if( (tmp_ts=measure_array[x]->get_time_sig()) )
        //        {
        //            if(ts.get_bpm() == tmp_ts->get_bpm() && ts.get_note_value() == tmp_ts->get_note_value())
        //                {
        //                //measure_array[x]->set_time_sig(NULL);
        //                }
        //        }
        //    }
        if(ts_buf)
            {
            ts_buf->set_time_sig(measure_array[measure_num]->get_time_sig());
            return ts_buf;
            }
        return measure_array[measure_num]->get_time_sig();
        }
    ts_buf->set_bpm(0);
    ts_buf->set_note_value(0);
    return NULL;
    }

void yale_measure_metadata::set_time_sig(unsigned long measure_num, double bpm, double note_value)
    {
    //find the time signature of the measure_num -1

    //if it is different change it
    //if it is changed to the time_sig from the measure before, null it.
    measure_num--;
    if(measure_num>0 && measure_num < measure_array.size())
        {
        (measure_array[measure_num])->set_time_sig(new yale_time_sig(bpm,note_value));
        }
    }

void yale_measure_metadata::deserialize(ast_t *pt)
    {
    ast_t *st=NULL;
    parse_util pu;
    if(pu.get_type(pt)==TYPE_OBJECT)
        {
        st=pu.get_ValueFromKey(pt,"measures",10);
        }
    else if(pu.get_type(pt)==TYPE_KEYVALUE && pu.cmp_key(pt,"measures",10)==0)
        {
        st=pu.get_value(pt);
        }
    //measures is an array that contains measure data for each measure (may be sparse)
    if(st && pu.get_type(st)==TYPE_ARRAY)
        {
        ast_t *measure_ast;
        int cnt=0;

        while( (measure_ast=pu.get_arrayValue(st,0)) )
            {
            yale_measure_data *md;
            md=new yale_measure_data();
            md->deserialize(measure_ast);
            measure_array[cnt]=md;
            }
        }
    }

char *yale_measure_metadata::serialize()
    {
    int x=0;
    std::vector<char *> measure_json;
    int size=0;

    std::vector<yale_measure_data *>::iterator measure_iter;
    for (measure_iter=measure_array.begin(); measure_iter != measure_array.end(); ++measure_iter)
        {
        measure_json[x]=(*measure_iter)->serialize();
        size+=strlen(measure_json[x])+1;
        x++;
        }
    size+=100;
    char *ret_val=(char *)malloc(sizeof(char) * (size+1));

    snprintf(ret_val,size,"measures:[");
    size-=10;
    for(x=0; x<measure_json.size(); x++)
        {
        if(measure_json[x])
            {
            snprintf(ret_val,size,"%s,",measure_json[x]);
            size-=strlen(measure_json[x]);
            free(measure_json[x]);
            measure_json[x]=NULL;
            }
        }
    snprintf(ret_val,size,"]");
    return ret_val;
    }
