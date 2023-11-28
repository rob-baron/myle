#ifndef __YALE_COLUMN_HPP__
#define __YALE_COLUMN_HPP__

#include "yale_object.hpp"
#include "yale_measure.hpp"
#include "../../libjson/parse_tree.hpp"
#include <list>

class yale_symbol:public yale_object
    {
private:
    double start_beat;
    double end_beat;
    
public:
    yale_symbol();
    virtual ~yale_symbol();
    virtual void render();
    virtual double get_start_beat();
    virtual double get_end_beat();
    virtual void set_start_beat(double beat);
    virtual void set_end_beat(double beat);
    virtual void set_beats(double start, double end);
    };

// 
//                  lv dlf lf rf drf rv
//                      ls   p   rs
//                     dlb lb rb drb
// 
// { dir:{LF:[1,3] } }
// { dir:{type:LF, beats:[1,3], foot:{{p:0,f:h},{p:35,f:c},{p:70,f:b}} } }
#define DIR_DIAG_RIGHT_FORWARD 1
#define DIR_LEFT_FORWARD 2
#define DIR_RIGHT_FORWARD 3
#define DIR_DIAG_LEFT_FORWARD 4
#define DIR_LEFT_SIDE 5
#define DIR_PLACE 6
#define DIR_RIGHT_SIDE 7
#define DIR_DIAG_LEFT_BACK 8
#define DIR_LEFT_BACK 9
#define DIR_RIGHT_BACK 10
#define DIR_DIAG_RIGHT_BACK 11
#define DIR_LEFT_PIVOT 12
#define DIR_RIGHT_PIVOT 13

class yale_dir_symbol:public yale_symbol
    {
private:
    int direction;
    double length;
    double height;
    int body_part;  //this is the 
public:
    yale_dir_symbol();
    yale_dir_symbol(int ds, long start_beat, long end_beat);
    virtual ~yale_dir_symbol();
    virtual void render();
    virtual int get_dir();
    virtual void set_dir(int d);
    virtual void get_direction(char *dir, int n);
    virtual void set_direction(const char *dir);
    virtual void set_direction( int dir );
    virtual int get_direction();
    virtual void deserialize(ast_t *pt);
    virtual char *serialize();
    };

class yale_body_symbol:public yale_symbol
    {
private:
    
public:
    yale_body_symbol();
    virtual ~yale_body_symbol();
    virtual void render();
    virtual void deserialize(ast_t *pt);
    virtual char *serialize();
    };

//This is attached to a symbol representing a foot.
//class yale_foot_symbol:public yale_symbol
//    {
//private:
//    
////public:
//    yale_body_symbol(){ }
//    virtual ~yale_body_symbol(){}
//    virtual void render() {}
//    virtual void deserialize(ast_t *pt) {}
//    virtual char *serialize() {return NULL;}  
//    };


//a figure is a array of symbols on a set of columns

//a routine is a array of symbols and figures (starting beat to ending beat)

class yale_column: public yale_object
    {
private:
    int num; //the column number positive are left, negative are right
    std::list<yale_symbol *> symbols;
    yale_measure_metadata *measures;  //this is only an alias do not delete or free here!!!
public:
    yale_column();
    virtual ~yale_column();
    virtual void render();

    virtual int get_num();
    virtual void set_num(int n);
    //we have symbols that have a start and end
    //and symbols that have a start
    virtual void set_symbol(yale_symbol *s);
    virtual void set_measure(yale_measure_metadata *m) { measures=m; }

    virtual void deserialize(ast_t *pt);
    virtual char *serialize();
    };

#endif /* __YALE_COLUMN_HPP__ */
