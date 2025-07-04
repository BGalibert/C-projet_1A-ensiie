#include <stdio.h>
#include <stdlib.h>

#include "interpreteur.h"


/*________________________________________________________________________________________________________________________

    This file contains everything relative to the interpretor :
        1) the definition of the 'interpreteur' structure, 
        2) a function to initialize its value,
        3) the functions to change its values : coordinates, direction and bord.
            /!\ The modifications of its stack are written in "actions.h", 
                and ONLY use the stack manipulation function written in "stack.h"
_________________________________________________________________________________________________________________________*/


/*
To simplify "main.c", here is a function to initialize the value of our inteerpretor.
@requires : pInter points to a valid interpretor
@assigns : *pInter
@requires : initialize *pInter      */
void inter_init (interpreteur *pInter) {
    pInter->i = 0;
    pInter->j = 0;
    pInter->dir = 1;
    pInter->bord = -1;
    pInter->pS = malloc(sizeof(stack));
    stack_init(pInter->pS);
}

// inter_free ?
// When declaring an 'interpreteur' in main.c, the only allocated memory is the one for the stack.
// Instead of an 'inter_free' function, we will simply 'free' the memory allocated for the stack of the interpretor.




// --------------------------------------- MODIFICATIONS of the INTERPRETOR -------------------------------------------------


/*
@requires : pInter points to a valid interpretor
@assigns : *pInter
@ensures : changes the coordinates of the interpretor to (i, j) */
void moveTo (interpreteur *pInter, int i, int j) {
    pInter->i = i;
    pInter->j = j;
}

/*
@requires : pInter points to a valid interpretor
@assigns : *pInter
@ensures : increments the direction according to the sequence : North (=0) -> Est (=1) -> South -> West -> North    */
void incr_dir(interpreteur *pInter) {
    pInter->dir = (pInter->dir + 1) % 4;
}


/*
@requires : pInter points to a valid interpretor
@assigns : *pInter
@ensures : changes babord (-1) to tribord (1) and vice versa    */
void incr_bord (interpreteur *pInter) {
    pInter->bord *= -1;
}

