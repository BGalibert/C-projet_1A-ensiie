#ifndef INTERPRETEUR_H
#define INTERPRETEUR_H

#include "stack.h"


/*________________________________________________________________________________________________________________________

    This file contains everything relative to the interpretor :
        1) the definition of the 'interpreteur' structure, 
        2) a function to initialize its value,
        3) the functions to change its values : coordinates, direction and bord.
            /!\ The modifications of its stack are written in "actions.h", 
                and ONLY use the stack manipulation function written in "stack.h"
_________________________________________________________________________________________________________________________*/


// Implementation for the interpretor.
typedef struct interpreteur {
    // coordinates
    int i;
    int j;
    // direction : 0 (North), 1 (East), 2 (South) or 3 (West)
    int dir;
    // bord : -1 ("babord") or 1 ("tribord")
    int bord;
    // stack
    stack *pS;
} interpreteur;

/*
To simplify main.c, here is a function to initialize the value of our inteerpretor.
@requires : pInter points to a valid interpretor
@assigns : *pInter
@requires : initialize *pInter      */
void inter_init (interpreteur *pInter);

// As we declare an 'interpreteur' in main.c, the only allocated memory is the one for the stack.
// Instead of an 'inter_free' function, we will simply 'free' the memory allocated for the stack of the interpretor.


// --------------- Modifications functions -----------------------------------------------------------------------

/*
@requires : pInter points to a valid interpretor
@assigns : *pInter
@ensures : changes the coordinates of the interpretor to (i, j) */
void moveTo (interpreteur *pInter, int i, int j);

/*
@requires : dir is the adress of the direction of the interpretor
@assigns : *dir
@ensures : increments the direction according to the sequence : North (=0) -> Est (=1) -> South -> West -> North    */
void incr_dir(interpreteur *inter);

/*
@requires : bord is the adress of the bord of the interpretor
@assigns : *bord
@ensures : changes babord (-1) to tribord (1) and vice versa    */
void incr_bord (interpreteur *inter);



#endif