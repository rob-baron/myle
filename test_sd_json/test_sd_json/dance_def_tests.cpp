//
//  dance_def_tests.cpp
//  
//  Created by Robert Baron on 7/9/18.
//  Copyright © 2018 Robert Baron. All rights reserved.
//
//  These are some unit tests.

#include <gtest/gtest.h>

#include "../../libjson/sym_table.hpp"
#include "../../libjson/parse_tree.hpp"

TEST(dance_def, JsonOneWaltzFigure )     
    {     
    void *rv;
    parse_util os;
    rv=os.parse(  "{"
                    "DanceDefinition:[{"
                        "name:waltz,"
                            "figures: [ "
                                "{name:'Prep Step', id:0,  level: [{ l: 0, s:S}], time:['SSSSSS','123456'], spos:, epos:LFP }"
                            "]"

                        "}]"
                    "}");
    //os.dump_parse_tree("versions",rv);
    os.free_parse_tree(rv);
    EXPECT_TRUE(true);
    }

TEST(dance_def, TestAll  )
    {
    void *rv;
    parse_util os;
    // position definitions
    // RFP  (green) (lead's Right foot going Forward, follows left foot going back in either closed or outside position)
    // RBP  (green stripe)(lead's Right foot going Backward
    // LFP  (red) (lead's Left foot Forward follows right foot going back
    // LBP  (red stripe)(lead's Left foot Backward, follows right foot going forward
    // PP   (Blue)(Promenade Position going forward?
    // HP   (Black)(lead's Heel pull Position follows Left foot to side - foxtrot )
    // TP   (-) (teleswivel position, follow's hip is prependicular and centered to leads hips
    // STD: S ISTD, D IDTA
    rv=os.parse(  
        "{"
        "DanceDefinition:" "["
             "{ "
              "name:waltz,"
#if 0
                "figures: [ "
                "{name:'Prep Step',                  id:0,  level:[{'l':0, std:S}], 'time':[['', '']], spos:NONE, epos:RFP },"
                //ISTD New Commer
                "{name:'Natural Turn',               id:1,  level:[{'l':1, std:S}],time:[['SSSSSS', '123456']],spos:RFP, epos:RFP },"
                "{name:'1-3 Natural Turn',           id:2,  level:[{'l':1, std:S}],time:[['SSSSSS', '123']],   spos:RFP, epos:LBP },"
                "{name:'4-6 Natural Turn',           id:3,  level:[{'l':1, std:S}],time:[['SSSSSS', '123']],   spos:LBP, epos:RFP },"
                "{name:'Reverse Turn',               id:4,  level:[{'l':1, std:S}],time:[['SSSSSS', '123456']],spos:LFP, epos:RFP },"
                "{name:'1-3 Reverse Turn',           id:5,  level:[{'l':1, std:S}],time:[['SSSSSS', '123']],   spos:LFP, epos:RBP },"
                "{name:'4-6 Reverse Turn',           id:6,  level:[{'l':1, std:S}],time:[['SSSSSS', '123']],   spos:RBP, epos:LFP },"
                "{name:'LF Change Step',             id:7,  level:[{'l':1, std:S}],time:[['SSS', '123']],      spos:LFP, epos:RFP },"
                "{name:'RF Change Step',             id:8,  level:[{'l':1, std:S}],time:[['SSS', '123']],      spos:RFP, epos:LFP },"
                "{name:'Natural Spin Turn',          id:9,  level:[{'l':1, std:S}],time:[['SSS', '123']],      spos:LFP, epos:RBP },"
                "{name:'Whisk',                      id:10, level:[{'l':1, std:S}],time:[['SSS', '123']],      spos:LFP, epos:PP  },"
                "{name:'Chasse From PP',             id:11, level:[{'l':1, std:S}],time:[['SS+S', '12&3']],    spos:PP,  epos:RFP },"
                //ISTD Bronze
                "{'name':'Closed Impetus',           id:12, level:[{'l':2, std:S}],time:[['SSS', '123']],      spos:LBP, epos:RBP },"
                "{'name':'Natural Hesitation',       id:13, level:[{'l':2, std:S}],time:[['SSS', '123']],      spos:RFP, epos:RFP },"
                "{'name':'Outside Change',           id:14, level:[{'l':2, std:S}],time:[['SSS', '123']],      spos:LBP, epos:RFP },"
                "{'name':'Outside Change to PP',     id:15, level:[{'l':2, std:S}],time:[['SSS', '123']],      spos:LBP, epos:PP  },"
                "{'name':'Reverse Corte',            id:16, level:[{'l':2, std:S}],time:[['SSS', '123']],      spos:RBP, epos:LBP },"
                "{'name':'Back Whisk',               id:17, level:[{'l':2, std:S}],time:[['SSS', '123']],      spos:LFP, epos:PP  },"
                "{'name':'Double Rev Spin',          id:18, level:[{'l':2, std:S},"
                                                                  "{'l':4, std:D}],time:[['SSS+', '123&']],    spos:LFP, epos:LFP },"
                "{'name':'Reverse Pivot',            id:19, level:[{'l':2, std:S}],time:[['+', '&']],          spos:RFP, epos:LFP },"
                "{'name':'Back Lock',                id:20, level:[{'l':2, std:S}],time:[['SS+S', '12&3']],    spos:LFP, epos:LFP },"
                "{'name':'Progressive Chasse To R',  id:21, level:[{'l':2, std:S}],time:[['SS+S', '12&3']],    spos:LFP, epos:RBP },"
                "{'name':'Syncopated Spin Turn Rev - Pivot',  id:21, level:[{'l':2, std:S}],time:[['S+SS', '1&23']],    spos:LBP, epos:LFP },"
                // ISTD Silver
                "{'name':'Weave From PP',            id:22, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:PP,  epos:RFP },"
                "{'name':'Weave From PP end in PP',  id:23, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:PP,  epos:PP  },"
                "{'name':'Closed Telemark',          id:24, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:LFP, epos:RFP },"
                "{'name':'Open Telemark',            id:25, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:FRP, epos:PP  },"
                "{'name':'Open Impetus',             id:26, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:LBP, epos:PP  },"
                "{'name':'Cross Hesitation',         id:27, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:PP,  epos:LFP },"
                "{'name':'Wing',                     id:28, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:PP,  epos:RFP },"
                "{'name':'Outside Spin',             id:29, level:[{'l':3, std:S},"
                                                                  "{'l':4, std:D}],time:[['SSS', '123']],      spos:LFP, epos:RFP },"
                "{'name':'Underturned Outside Spin', id:30, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:LFP, epos:RBP },"
                "{'name':'Turning Lock to L',        id:31, level:[{'l':3, std:S}],time:[['SS+S', '12&3']],    spos:RBP, epos:RFP },"
                "{'name':'Drag Hesitation',          id:32, level:[{'l':3, std:S}],time:[['SSS', '123']],      spos:LFP, epos:LBP },"
                // ISTD Gold
                "{'name':'Left Whisk From PP',       id:33, level:[{'l':4, std:S}],time:[['SSS', '123']],      spos:PP,  epos:LBP },"
                "{'name':'Left Whisk',               id:34, level:[{'l':4, std:S}],time:[['SSS', '123']],      spos:RBP, epos:LBP },"
                "{'name':'Left Whisk on 1st beat',   id:35, level:[{'l':4, std:S}],time:[['SSS', '123']],      spos:RFP, epos:LBP },"
                "{'name':'L Whisk with Twist Ending',id:36, level:[{'l':4, std:S}],time:[['SSSSSS', '123456']],spos:RBP, epos:PP    },"  //PP?
                "{'name':'Conra Check',              id:37, level:[{'l':4, std:S}],time:[['SSS', '123']],      spos:LFP, epos:RFP   },"
                "{'name':'Conra Check to PP',        id:38, level:[{'l':4, std:S}],time:[['SSS', '123']],      spos:LFP, epos:PP    },"
                "{'name':'Closed Wing',              id:39, level:[{'l':4, std:S}],time:[['SSS', '123']],      spos:RFP, epos:LFP   },"
                "{'name':'Turning Lock to R',        id:40, level:[{'l':4, std:S}],time:[['SSS', '12&3']],     spos:RBP, epos:PP   },"
                "{'name':'Overturn Turning Lock to R',id:41,level:[{'l':4, std:D}],time:[['SSS', '12&3']],   spos:RBP, epos:RFP   },"
                "{'name':'Fallaway Rev & slip pivot',id:42, level:[{'l':4, std:S}],time:[['S+SS', '1&23'],"
                                                                                       " ['SS+S', '12&3'],"
                                                                                       " ['SSS+', '123&'] ],    spos:RFP, epos:RFP   },"
                "{'name':'Hover Corte',              id:43, level:[{'l':4, std:S}],time:[['SSSSSS', '123456'],"
                                                                                       " ['SSS', '123']],       spos:RBP, epos:LBP   },"
                //open
                "{'name':'Overturned Outside Spin',  id:44, level:[{'l':5, std:O}],time:[['SSS', '123']],        spos:LFP, epos:RFP   },"
                "{'name':'Bombshell',                id:45, level:[{'l':5, std:O}],time:[['+SSS', '&123']],      spos:RFP, epos:RFP   },"
                "{'name':'Oversway',                 id:46, level:[{'l':5, std:O}],time:[['SSSSSS', '123456'],"
                                                                                       " ['SSS', '123']],        spos:RBP, epos:LBP    }," //or epos: PP
                "{'name':'Undersway',                id:47, level:[{'l':5, std:O}],time:[['SSSSSS', '123456'],"
                                                                                       " ['SSS', '123']],       spos:RBP, epos:LBP   },"
                "{'name':'LF Back Passing Changes',  id:48, level:[{'l':5, std:O}],time:[['SSS', '123']], spos:LBP, epos:RBP   },"
                "{'name':'RF Back Passing Changes',  id:49, level:[{'l':5, std:O}],time:[['SSS', '123']], spos:RBP, epos:LBP   },"
                "{'name':'Double Natural Spin',      id:50, level:[{'l':5, std:O}],time:[['SSS+', '123&']], spos:RFP, epos:RFP   },"
                "{'name':'Fallaway Natural Turn',    id:51, level:[{'l':5, std:O}],time:[['SSSSSS', '123456']], spos:PP, epos:RFP   },"
                "{'name':'Forward Locks',            id:52, level:[{'l':5, std:O}],time:[['SS+S', '12&3']], spos:RFP, epos:RFP   },"
                "{'name':'Open Nat Turn From PP',    id:53, level:[{'l':5, std:O}],time:[['SSS', '123']], spos:PP, epos:LBP   },"
                "{'name':'Quick Nat Spin Turn',      id:54, level:[{'l':5, std:O}],time:[['', '']], spos:, epos:   },"
                "{'name':'Quick Open Reverse',       id:55, level:[{'l':5, std:O}],time:[['', '']], spos:, epos:   },"
                "{'name':'Running Spin Turn',        id:56, level:[{'l':5, std:O}],time:[['', '']], spos:, epos:   },"
                "{'name':'Throwaway Oversway',       id:57, level:[{'l':5, std:O}],time:[['', '']], spos:, epos:   },"
                "{'name':'Hinge',                    id:58, level:[{'l':5, std:O}],time:[['', '']], spos:, epos:   },"
                "{'name':'Eros',                     id:59, level:[{'l':, std:O}],time:[['', '']], spos:, epos:   },"
                "{'name':'Left Side Lunge',          id:60, level:[{'l':, std:O}],time:[['', '']], spos:, epos:   },"
                "{'name':'Tumble Turn',              id:61, level:[{'l':5, std:O}],time:[['QQSS', '1&23'],"
                                                                                       " ['SQQS', '12&3']], spos:RBP, epos:   },"
                "{'name':'Big Top',                  id:62, level:[{'l':5, std:O}],time:[['S+SS', '1&23']], spos:, epos:RFP   },"
        //        "{'name':'',  id:,level:[{'l':, std:}],time:[['', '']], spos:, epos:   },"
        //        "{'name':'',  id:,level:[{'l':, std:}],time:[['', '']], spos:, epos:   },"
                "]"
#endif
            "},"
#if 0
            "{"
            "name:Foxtrot,"
#if 0
            "figures:["
                    "{name:'Prep Step',                  id:0,  level:[{'l':0, std:S}], 'time':[['', '']], spos:NONE, epos:RFP },"
                    //New Commer
                    "{'name':'Feather Step',              id:,level:[{'l':1, std:S}],time:[['SQQ', '']], spos:RFP, epos:LFP   },"
                    "{'name':'Three Step',                id:,level:[{'l':1, std:S}],time:[['SQQ', '']], spos:LFP, epos:RFP   },"
                    "{'name':'Natural Turn 1-6',          id:,level:[{'l':1, std:S}],time:[['SQQSSS', '']], spos:RFP, epos:RFP   },"
                    "{'name':'Natural Turn 1-3',          id:,level:[{'l':1, std:S}],time:[['SQQ', '']], spos:RFP, epos:LBP   },"
                    "{'name':'Natural Turn 1-5',          id:,level:[{'l':1, std:S}],time:[['SQQSS', '']], spos:RFP, epos:HPP },"
                    "{'name':'Reverse Turn 1-6',          id:,level:[{'l':1, std:S}],time:[['SQQSQQ', '']], spos:LFP, epos:LFP   },"
                    "{'name':'Reverse Turn - checked 1-4',id:,level:[{'l':1, std:S}],time:[['SQQ', '']], spos:LFP, epos:LFP   },"
                    "{'name':'Feather Finish',            id:,level:[{'l':1, std:S}],time:[['SQQ', '']], spos:RBP, epos:LFP   },"
                    "{'name':'Feather Finish - checked',  id:,level:[{'l':1, std:S}],time:[['SQQS', '']], spos:RBP, epos:LBP   },"
                    "{'name':'Closed Impetus',            id:,level:[{'l':1, std:S}],time:[['SQQ', '']], spos:LBP, epos:RBP   },"
                    //Bronze
                    "{'name':'Natural Weave',  id:,level:[{'l':2, std:}],time:[['SQQQQQQ', '']], spos:RFP, epos:LFP   },"
                    "{'name':'Change of Direction',  id:,level:[{'l':2, std:}],time:[['SSS', '']], spos:LFP, epos:RFP   },"
                    "{'name':'Change of Direction 1',  id:,level:[{'l':2, std:}],time:[['SS', '']], spos:LFP, epos:LFP   },"  //prepares for a hover feather
                    "{'name':'Change of Direction 2',  id:,level:[{'l':2, std:}],time:[['SSSS', '']], spos:, epos:   },"  //elongated 1 or 2
                    "{'name':'Basic Weave',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                    //Silver
                    "{'name':'Closed Telemark',  id:,level:[{'l':3, std:}],time:[['SQQ', '']], spos:RBP, epos:LFP   },"
                    "{'name':'Open Telemark',  id:,level:[{'l':3, std:}],time:[['SQQ', '']], spos:RBP, epos:PP   },"
                    "{'name':'Feather Ending',  id:,level:[{'l':3, std:}],time:[['SQQ', '']], spos:RFP, epos:LFP   },"
                    "{'name':'Feather Ending - Checked',  id:,level:[{'l':3, std:}],time:[['SQQ', '']], spos:RFP, epos:LBP   },"
                    "{'name':'Top Spin',  id:,level:[{'l':3, std:}],time:[['QQQQ', '']], spos:LBP, epos: LFP   },"
                    "{'name':'Top Spin - checked',  id:,level:[{'l':3, std:}],time:[['QQQQ', '']], spos:LBP, epos: LBP  },"
                    "{'name':'Hover Feather',  id:,level:[{'l':3, std:}],time:[['QQ', '']], spos:HP, epos:LFP   },"
                    "{'name':'Hover Feather - checked',  id:,level:[{'l':3, std:}],time:[['QQ', '']], spos:HP, epos:LBP   },"
                    "{'name':'Hover Telemark',  id:,level:[{'l':3, std:}],time:[['SQQ', '']], spos:LFP, epos:RFP   },"
                    "{'name':'Hover Telemark to PP',  id:,level:[{'l':3, std:}],time:[['SQQ', '']], spos:LFP, epos:PP   },"
                    "{'name':'Natural telemark',  id:,level:[{'l':3, std:}],time:[['SQQQQ', '']], spos:RFP, epos:LFP   },"
                    "{'name':'Hover Telemark-Hover Feather',  id:,level:[{'l':3, std:}],time:[['SSQQ', '']], spos:RFP, epos:LFP   },"
                    "{'name':'Hover Cross',  id:,level:[{'l':3, std:}],time:[['SQQQQQQ', '']], spos:RFP, epos:LFP   },"
                    "{'name':'Hover Cross from PP',  id:,level:[{'l':3, std:}],time:[['SQQQQQQ', '']], spos:PP, epos:LFP   },"
                    "{'name':'Outside Swivel',  id:,level:[{'l':3, std:}],time:[['S', '']], spos:RBP, epos:PP   },"
                    "{'name':'Open Impetus',  id:,level:[{'l':3, std:}],time:[['SQQ', '']], spos:LBP, epos:PP   },"
                    "{'name':'Weave from PP',  id:,level:[{'l':3, std:}],time:[['SQQQQQQ', '']], spos:PP, epos:LFP   },"
                    "{'name':'Weave from PP - checked',  id:,level:[{'l':3, std:}],time:[['SQQQQQQ', '']], spos:PP, epos:LBP   },"
                    "{'name':'Natural Weave from PP',  id:,level:[{'l':3, std:}],time:[['SQQQQQQ', '']], spos:PP, epos:RFP   },"
                    "{'name':'Natural Weave from PP - checked',  id:,level:[{'l':3, std:}],time:[['SQQQQQQ', '']], spos:PP, epos:RBP   },"
                    "{'name':'Natural Weave - checked',  id:,level:[{'l':3, std:S}],time:[['SQQQQQQ', '']], spos:RFP, epos:LBP   },"
                    "{'name':'Reverse Wave',  id:,level:[{'l':3, std:}],time:[['SQQSQQSSS', '']], spos:LFP, epos:RFP   },"
                    "{'name':'Reverse Wave 1-6',  id:,level:[{'l':3, std:}],time:[['SQQSQQ', '']], spos:LFP, epos:LFB   },"
                    "{'name':'Reverse Wave 1-8',  id:,level:[{'l':3, std:}],time:[['SQQSQQSS', '']], sposLFP:, epos:HPP   },"
                    //Gold
                    "{'name':'Natural Twist Turn',               id:,level:[{'l':4, std:}],time:[['SQ&QSQQ', '']], spos:RFP, epos:LFP   },"
                    "{'name':'Natural Twist Turn 1-6',           id:,level:[{'l':4, std:}],time:[['SQ&QQQ', '']], spos:RFP, epos:RBP   },"
                    "{'name':'Natural Twist Turn 1-5',           id:,level:[{'l':4, std:}],time:[['SQ&QQ', '']], spos:RFP, epos:HPP   },"
                    "{'name':'Natural Twist Turn to PP',         id:,level:[{'l':4, std:}],time:[['SQ&QQQ', '']], spos:RFP, epos:PP   },"
                    "{'name':'Natural Twist Turn Weave Ending',  id:,level:[{'l':4, std:}],time:[['SQ&SQ QQQQQQ', '']], spos:RFP, epos:LFP   },"
                    "{'name':'Curved Feather',                   id:,level:[{'l':4, std:}],time:[['SQQ', '']], spos:RFP, epos:LBP   },"
                    "{'name':'Curved Feather from PP',           id:,level:[{'l':4, std:}],time:[['SQQ', '']], spos:PP, epos:LBP   },"
                    "{'name':'Back Feather',                     id:,level:[{'l':4, std:}],time:[['SQQ', '']], spos:LFB, eposRBP:   },"
                    "{'name':'Natural Zig-Zag from PP',          id:,level:[{'l':4, std:}],time:[['SQQQQ', '']], spos:PP, epos:LFP   },"
                    "{'name':'Natural Zig-Zag from PP - checked',id:,level:[{'l':4, std:}],time:[['SQQQQ', '']], spos:PP, epos:LBP   },"
                    "{'name':'Fallaway Reverse and Slip Pivot',  id:,level:[{'l':4, std:}],time:[['SQQS', ''],"
                                                                                                "['SQQ&', ''],"
                                                                                                "['SQ&Q', ''],"
                                                                                                "['S&QQ', ''],"
                                                                                                "['QQQQ', '']], spos:LFP, epos:LFP   },"
                    //open timing SQQQ with the following S of the next figure converted to a Q
                    //    fallaway rev and slip pivot (SQQQ) Double Reverse Spin (QQ&Q)
                    "{'name':'Natural Hover Telemark',           id:,level:[{'l':4, std:}],time:[['SQQSQQ', '']], spos:RFP, epos:LBP   },"
                    "{'name':'Bounce Fallaway with Weave Ending',id:,level:[{'l':4, std:}],time:[['S&QQ QQQQ', '']], spos:LFP, epos:LFP   },"
                    "{'name':'Bounce Fallaway with Weave Ending - checked',id:,level:[{'l':4, std:}],time:[['S&QQ QQQQ', '']], spos:LFP, epos:LBP   },"
                    // bounce fallway ududdddd
        //        "{'name':'',  id:,level:[{'l':, std:}],time:[['', '']], spos:, epos:   },"
              "]"
#endif
            "},"
            "{"
            "name:Tango,"
#if 0
            "figures:["
                //New Commer
                "{'name':'LF Walk',  id:,level:[{'l':1, std:}],time:[['S', '']], spos:LFP, epos:RFP   },"
                "{'name':'RF Walk',  id:,level:[{'l':1, std:}],time:[['S', '']], spos:RFP, epos:LFP   },"
                "{'name':'LF Backward Walk',  id:,level:[{'l':5, std:}],time:[['', '']], spos:LFP, epos:LFP   },"
                "{'name':'RF Backward Walk',  id:,level:[{'l':5, std:}],time:[['&', '']], spos:LBP, epos:LBP   },"
                "{'name':'Open Finish',  id:,level:[{'l':1, std:}],time:[['S', '']], spos:PP, epos:PP   },"
                "{'name':'Open Finish',  id:,level:[{'l':1, std:}],time:[['S', '']], spos:PP, epos:PP   },"
                "{'name':'Open Finish',  id:,level:[{'l':1, std:}],time:[['S', '']], spos:PP, epos:PP   },"
                "{'name':'Progressive Side Step',  id:,level:[{'l':1, std:}],time:[['QQS', '']], spos:LFP, epos:RFP   },"
                "{'name':'Progressive Link',  id:,level:[{'l':1, std:}],time:[['QQ', '']], spos:LFP, epos:PP   },"
                "{'name':'Closed Promenade',  id:,level:[{'l':1, std:}],time:[['SQQS', '']], spos:PP, eposLFP:   },"
                "{'name':'Closed Promenade',  id:,level:[{'l':1, std:}],time:[['SQQS', '']], spos:PP, eposLBP:   },"
                "{'name':'Rock Turn',  id:,level:[{'l':1, std:}],time:[['SQQSQQS', '']], spos:RFP, epos:LFP   },"
                "{'name':'Rock Turn',  id:,level:[{'l':1, std:}],time:[['SQQSQQS', '']], spos:RFP, epos:LBP   },"
                "{'name':'Rock Turn 1-4',  id:,level:[{'l':1, std:}],time:[['SQQS', '']], spos:RFP, epos:RBP   },"
                "{'name':'Open Reverse Turn, Lady Outside',  id:,level:[{'l':1, std:}],time:[['QQSQQS', '']], spos:LFP, epos:LFP   },"
                "{'name':'Open Reverse Turn, Lady Outside',  id:,level:[{'l':1, std:}],time:[['QQSQQS', '']], spos:LFP, epos:LBP   },"
                "{'name':'Open Reverse Turn, Lady Outside 1-3',  id:,level:[{'l':5, std:}],time:[['QQS', '']], spos:LFP, epos:RBP   },"
                "{'name':'Back Corte',  id:,level:[{'l':1, std:}],time:[['SQQS', '']], spos:LBP, epos:LFP   },"
                "{'name':'Back Corte',  id:,level:[{'l':1, std:}],time:[['SQQS', '']], spos:LBP, epos:LBP   },"
                //Bronze
                "{'name':'Open Reverse Turn, Lady in Line',  id:,level:[{'l':2, std:}],time:[['QQSQQS', '']], spos:LFP, epos:LFP   },"
                "{'name':'Open Reverse Turn, Lady in Line',  id:,level:[{'l':2, std:}],time:[['QQSQQS', '']], spos:LFP, epos:LBP   },"
                "{'name':'Open Reverse Turn, Lady in Line 1-3',  id:,level:[{'l':2, std:}],time:[['QQS', '']], spos:LFP, epos:RBP   },"
                "{'name':'Progressive Side Step Reverse Turn',  id:,level:[{'l':2, std:}],time:[['QQSSQQSQQS', '']], spos:LFP, epos:LFP   },"
                "{'name':'Progressive Side Step Reverse Turn',  id:,level:[{'l':2, std:}],time:[['QQSSQQSQQS', '']], spos:LFP, epos:LBP   },"
                "{'name':'Progressive Side Step Reverse Turn 1-4',  id:,level:[{'l':2, std:}],time:[['QQSS', '']], spos:LFP, epos:LBP   },"
                "{'name':'Progressive Side Step Reverse Turn 1-7',  id:,level:[{'l':2, std:}],time:[['QQSSQQS', '']], spos:LFP, epos:RBP   },"
                "{'name':'Open Promenade',  id:,level:[{'l':2, std:}],time:[['SQQS', '']], spos:PP, epos:LFP   },"
                "{'name':'Open Promenade',  id:,level:[{'l':2, std:}],time:[['SQQS', '']], spos:PP, epos:LBP   },"
                "{'name':'Left Foot Rocks',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Right Foot Rocks',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Natural Twist Turn',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Natural Promenade Turn',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                //sliver
                "{'name':'Promenade Link',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Four Step',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Back Open Promenade',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Outside Swivel 1',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Outside Swivel 2',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Outside Swivel 3',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Outside Swivel 4',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Fallaway Promenade',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Four Step Change',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Brush Tap',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                //Gold
                "{'name':'Fallaway Four Step',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Oversway',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Basic Reverse Turn',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'The Chase',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Fallaway Reverse and Slip Pivot',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Five Step',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Contra Check',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
        //        "{'name':'',  id:,level:[{'l':, std:}],time:[['', '']], spos:, epos:   },"
              "]"
#endif
            "},"
            "{"
            "name:QuickStep,"
#if 0
            "figures:["
                "{name:'Prep Step',                  id:0,  level:[{'l':0, std:S}], 'time':[['', '']], spos:NONE, epos:RFP },"
                //Newcommer
                "{'name':'Quarter Turn to Right',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Natural Turn',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Natural Turn w/ Hesitation',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Natural Pivot Turn',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Natural Spin Turn',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Progressive Chasse',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Casse Reverse Turn',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Forward Lock',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'(Heel Pivot)Quarter Turn to Left',  id:,level:[{'l':1, std:}],time:[['', '']], spos:, epos:   },"
                //Bronze
                "{'name':'Closed Impetus',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Back Lock',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Reverse Pivot',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Progressive Chasse to Right',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Tipple Chasse to Right',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Natural Turn - Back Lock',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Double Reverse Spin',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'ZigZag-Back Lock-Running Finish',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Running Finish',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Cross Chasse',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Change of Direction',  id:,level:[{'l':2, std:}],time:[['', '']], spos:, epos:   },"
                //Silver
                "{'name':'Quick Open Reverse',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Fishtail',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Four Quick Run',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Running Right Turn',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'V6',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Closed Telemark',  id:,level:[{'l':3, std:}],time:[['', '']], spos:, epos:   },"
                //Gold
                "{'name':'Cross Swivel',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Six Quick Run',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Rumba Cross',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Tipsy to Right',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Tipsy to Left',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
                "{'name':'Hover Corte',  id:,level:[{'l':4, std:}],time:[['', '']], spos:, epos:   },"
        //        "{'name':'',  id:,level:[{'l':, std:}],time:[['', '']], spos:, epos:   },"
        //        "{'name':'',  id:,level:[{'l':, std:}],time:[['', '']], spos:, epos:   },"
              "]"
#endif
            "},"
            "{"
            "name:Viennese Waltz,"
#if 0
            "figures:["
                "{name:'Prep Step side to side',     id:0,  level:[{'l':0, std:S}], 'time':[['', '']], spos:NONE, epos:RFP },"
                "{name:'Prep Step back to front',    id:0,  level:[{'l':0, std:S}], 'time':[['', '']], spos:NONE, epos:RFP },"
        //        "{'name':'',  id:,level:[{'l':, std:}],time:[['', '']], spos:, epos:   },"
            "]"
#endif
            "},"
#endif
        "]"
        "}");
    os.dump_parse_tree("versions",rv);
    os.free_parse_tree(rv);
    EXPECT_TRUE(true);
    }


//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

