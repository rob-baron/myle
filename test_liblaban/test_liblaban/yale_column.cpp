#include "yale_column.hpp"

yale_symbol::yale_symbol(){}
yale_symbol::~yale_symbol(){}
void yale_symbol::render() {}
double yale_symbol::get_start_beat() { return start_beat; }
double yale_symbol::get_end_beat() { return end_beat; }
void yale_symbol::set_start_beat(double beat) { start_beat=beat; }
void yale_symbol::set_end_beat(double beat) { end_beat=beat; }
void yale_symbol::set_beats(double start, double end)
    {
    start_beat=start;
    end_beat=end;
    }

yale_dir_symbol::yale_dir_symbol(){}
yale_dir_symbol::yale_dir_symbol(int ds, long start_beat, long end_beat)
    {
        set_direction(ds);
        set_beats(start_beat,end_beat);
    }
yale_dir_symbol::~yale_dir_symbol(){}
void yale_dir_symbol::render() {}
int yale_dir_symbol::get_dir() { return direction; }
void yale_dir_symbol::set_dir(int d) { direction=d; }
void yale_dir_symbol::get_direction(char *dir, int n)
    {
    switch(direction)
        {
            case  DIR_DIAG_RIGHT_FORWARD: //1
            strncpy(dir,"drf",n);
            break;
            case  DIR_LEFT_FORWARD: // 2
            strncpy(dir,"lf",n);
            break;
            case  DIR_RIGHT_FORWARD: // 3
            strncpy(dir,"rf",n);
            break;
            case  DIR_DIAG_LEFT_FORWARD: // 4
            strncpy(dir,"dlf",n);
            break;
            case  DIR_LEFT_SIDE: //5
            strncpy(dir,"ls",n);
            break;
            case  DIR_PLACE:  //6
            strncpy(dir,"p",n);
            break;
            case  DIR_RIGHT_SIDE: //7
            strncpy(dir,"rs",n);
            break;
            case  DIR_DIAG_LEFT_BACK: //8
            strncpy(dir,"dlb",n);
            break;
            case  DIR_LEFT_BACK: //9
            strncpy(dir,"lb",n);
            break;
            case DIR_RIGHT_BACK: //10
            strncpy(dir,"rb",n);
            break;
            case DIR_DIAG_RIGHT_BACK: //11
            strncpy(dir,"drb",n);
            break;
            case DIR_LEFT_PIVOT: //12
            strncpy(dir,"lv",n);
            break;
            case DIR_RIGHT_PIVOT: //13
            strncpy(dir,"rv",n);
            break;
            default:
            strncpy(dir,"",n);
            break;
        }
    }
void yale_dir_symbol::set_direction(const char *dir)
    {
    if( dir && dir[0] )
        {
        int x=0;
        int y=0;
        int pivot; //planing to use for pivots

        if(dir[0]=='p') direction=DIR_PLACE;
        if(dir[0]=='l' || dir[1]=='l') x=1;
        if(dir[0]=='r' || dir[1]=='r') x=-1;
        if(dir[1]=='v')
            {
            if(x==1) direction= DIR_LEFT_PIVOT;
            else if (x==-1) direction= DIR_RIGHT_PIVOT;
            }
        else
            {
            if(dir[1]=='f' || dir[2]=='f') y=1;
            if(dir[1]=='b' || dir[2]=='b') y=-1;
            if(dir[0]=='d')
                {
                if(x==1 && y==1) direction=DIR_DIAG_LEFT_FORWARD;
                if(x==-1 && y==1) direction=DIR_DIAG_RIGHT_FORWARD;
                if(x==1 && y==-1) direction=DIR_DIAG_LEFT_BACK;
                if(x==-1 && y==-1) direction=DIR_DIAG_RIGHT_BACK;
                }
            else if(x==1 && y==1) direction=DIR_LEFT_FORWARD;
            else if(x==1 && y==0) direction=DIR_LEFT_SIDE;
            else if(x==1 && y==-1) direction=DIR_LEFT_BACK;
            else if(x==-1 && y==1) direction=DIR_RIGHT_FORWARD;
            else if(x==-1 && y==0) direction=DIR_RIGHT_SIDE;
            else if(x==-1 && y==-1) direction=DIR_RIGHT_BACK;
            }
        }
    }

void yale_dir_symbol::set_direction( int dir ) { direction=dir; }
int yale_dir_symbol::get_direction() { return direction; }
void yale_dir_symbol::deserialize(ast_t *pt)
    {
    ast_t *st;
    parse_util pu;
    if(pu.get_type(pt)==TYPE_OBJECT)
        {
        st=pu.get_ValueFromKey(pt,"dir",10);
        if(pu.get_type(st)==TYPE_STRING)
            {
            char buf[5];
            pu.get_string(st,buf,sizeof(buf));
            set_direction(buf);
            }
        //st=pu.get_ValueFromKey(pt,"start",10);
        //st=pu.get_ValueFromKey(pt,"end",10);

        }
    }

char *yale_dir_symbol::serialize()
    {
    char *rv;
    rv=(char *)malloc(50); //should take less
    char d[4];
    get_direction(d,sizeof(d));
    snprintf(rv,50,"dir:{%s}",d);
    return rv;
    }


yale_body_symbol::yale_body_symbol(){}
yale_body_symbol::~yale_body_symbol(){}
void yale_body_symbol::render() {}
void yale_body_symbol::deserialize(ast_t *pt) {}
char *yale_body_symbol::serialize() {return NULL;}


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


yale_column::yale_column(){ }
yale_column::~yale_column(){}
void yale_column::render() {}

int yale_column::get_num() { return num; }
void yale_column::set_num(int n) { num=n; }
    //we have symbols that have a start and end
    //and symbols that have a start
void yale_column::set_symbol(yale_symbol *s)
    {
    long start=s->get_start_beat();
    long end=s->get_end_beat();
    std::list<yale_symbol *>::iterator iter=symbols.begin();
    //ensure symbol doesn't overlap another symbol
    while(iter != symbols.end() && end < (*iter)->get_start_beat() ) { ++iter; }
    if( iter==symbols.begin())
        {
        symbols.push_front(s);
        }
    if( iter == symbols.end() )
        {
        symbols.push_back(s);
        }
    else
        {
        //look at next symbol to ensure that there is no overlap
        std::list<yale_symbol *>::iterator iter2=iter;
        while(iter2 != symbols.begin() && start > (*iter2)->get_end_beat() ) {--iter;}
        this->symbols.insert(iter2,s);
        }
    }
    //set_measure(yale_measure *m) { measure=m; }

void yale_column::deserialize(ast_t *pt)
    {

    }

char *yale_column::serialize()
    {
    char *ret_val=NULL;
    size_t n=sizeof(char)*50+sizeof(char)*50*symbols.size();
    ret_val=(char *)malloc( n );
    if(symbols.size()==0) snprintf(ret_val,50,"column:{num:\"%d\",symbols:{}}",num);
    else
        {
        snprintf(ret_val,50,"column:\"%d\",symbols:{",num);
        std::list<yale_symbol *>::iterator iter;
        for(iter=symbols.begin(); iter!=symbols.end(); iter++)
            {
            strncat(ret_val,(*iter)->serialize(),n);
            }
        }
    return ret_val;
    }

