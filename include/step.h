#ifndef STEP_H
#define STEP_H

#include "bloc.h"
#include "interpreteur.h"
#include "image.h"

/*______________________________________________________________________________________________________________________

    This file is where we define the crucial 'step' function, which links the others files all together,
    in order to execute a step of the execution of 'image.ppm'.
    Some of the following functions have 2 versions : 
        - one to simply execute the task,
        - a second to also print what it does, for the BONUS debugging environment.
    Here are :
        1) some functions to move the interpretor, to the right corner or across a passing bloc,
        2) functions to perform the right action,
        3) finally the 'step' function.
_______________________________________________________________________________________________________________________*/


/*
@requires : pInter and pBloc point respectively to a valid interpreteur and bloc_caract
@assigns : *pInter
@ensures : changes the coordinates of the interpretor to the one of the right corner of the bloc
            the interpretor is located on (depending on the direction and bord of the interpretor)  */
void moveToGoodExtrem (interpreteur *pInter, bloc_caract *pBloc);

/*
This function is highly similar to the previous 'moveToGoodExtrem' one.
It has been added in a second phase of development, when treating the debogging BONUS question.
Insteed of moving to the right corner, we store its coordinates in two referenced integer.
This will be usefull to print where the interpretor moved at every step.
It could have been done by replacing the 'moveToGoodCorner' function by moveTo(i, j) after 
having called this 'whichGoodExtrem' one, but as its complexity is of O(1), it is not too bad. 

@requires : pInter and pBloc point respectively to a valid interpreteur and bloc_caract
@assigns : *i, *j
@ensures : stored at i and j the coordinates of the right corner to go depending on the location of *pInter
            and the caracteristics of the bloc (*pBloc) it stays on     */

void whichGoodExtrem(interpreteur *pInter, bloc_caract *pBloc, int *i, int *j);

/*
Once placed at the right corner of the current bloc, 
in order to determine wether the next bloc is a coding, passing or blocking color,
we need the coordinates of the pixel next to the current one in the right direction.

@requires : pImg points to a valid image, pInter to a valid interpretor, iNext and jNext to two integers
@assigns : *iNext, *jNext
@ensures : stores in iNext and jNext the coordinates of the next pixel in the same direction as pInter->dir  */

void coordVoisin (image *pImg, interpreteur *pInter, int *iNext, int *jNext);


/*
Once we got the ID of the action to perform thanks to 'codeAction' defined in "couleur.h", 
we can perform it, by calling the corresponding function defined in "actions.h".
@requires : 'action' has been determined by 'codeAction', and pInter points to a valid interpreteur.
@assigns : nothing
@ensures : call the right action to perform.    */
void doRightAction (interpreteur *pInter, int action, int blocSize);

/*
This is the exact same function as 'doRightAction', but which prints the action it calls, for the BONUS debugging environment.
@requires : 'action' has been determined by 'codeAction', and pInter points to a valid interpreteur.
@assigns : nothing
@ensures : calls AND PRINTS the right action to perform.    */
void doRightAction_print (interpreteur *pInter, int action, int blocSize);

/*
Here is finally the function which gets the ID of the action to perform (thanks to 'codeAction' defined in "couleur.h"), 
and performs it (thanks to the previous 'doRightAction' function).
@requires : pImg and pInter point respectively to a valid image and interpreteur.
@assigns : nothing
@ensures : performs the right action, according to the current color and the "next" one    */
void act (image *pImg, interpreteur *pInter, int iNext, int jNext, int blocSize);

/*
Once again, exact same function as the previous 'act' one, but which prints the action it calls, 
for the BONUS debugging environment
@requires : pImg and pInter point respectively to a valid image and interpreteur.
@assigns : nothing
@ensures : performs AND PRINTS the right action, according to the current color and the "next" one    */
void act_print (image *pImg, interpreteur *pInter, int iNext, int jNext, int blocSize);


/*
When the "next" color is a passing one, we have to cross it in the same direction,
until we reach the border of this passing bloc.
This function stores at iNext and jNext the coordinates of the border at the other side of that passing bloc.

@requires : pImg points to a valid image, pInter to a valid interpretor, iNext and jNext to two integers,
            AND the interpretor has been placed on the new passing bloc.
@assigns : *iNext and *jNext
@ensures : stores at iNext and jNext the coordinates of the other side of the passing bloc  */
void moveUntilNewBloc (image *pImg, interpreteur *pInter, int *iNext, int *jNext);


/*
We now have everything we need to write the 'step' function, for the execution of 'image.ppm'.
Here's a detailed description of a step.

At the beginning of the step, the interpreter is placed on a given point of an initial bloc.
Depending on its direction and edge, place the interpreter on the correct corner (eg : East-"babord").
Look at the neighbor pixel.

    A) if it is a coding color :
        a) if you are on a coding color :
            Perform the correct action 
        b) if you are on a passing one :
            Do nothing.
        Either way, move to that next bloc. It will be the starting bloc for the next step.

    B) if it is a blocking color :
        a) if it is the first blocking neighbor you meet since you are on your current bloc :
            change the edge, and end the step. 
            You will start the new one with a new "right corner" to move to, as you changed the edge. 
        b) if it is the 8th blocking neighbor you meet from your current bloc :
            End the execution of 'image.ppm'. 
            As there are only 8 corners, that means there is nowhere to go to keep executing the programm.
        c) otherwise (ie it is your one of your 2nd to 7th blocking neighbor) :
            if you previously changed the edge, now change the direction,
            and on the contrary if you just changed the direction, change the edge.
            In this way you will successively try every possible corner.
        Thus, either you've reached 8 and you end the programm, 
        or you have got a non-blocking color and you continue on next step.
        
    C) if it is a passing color :
        Move the interpretor to that passing bloc, then
        Continue in the same direction until reaching a non-passing pixel.
        a) if it is a blocking pixel :
            End the step. The next step will start on that passing bloc you were trying to cross, as you just moved to it.
        b) if it is a coding one :
            Move to that pixel, but don't perform any action as you just crossed a passing bloc.

@requires : pImg and pInter point respectively to a valid image and interpretor
@assigns : pInter, countBloquantes
@ensures : performs a step of the execution of 'image.ppm', as described above.     */

void step (image *pImg, interpreteur *pInter, int *countBloquantes);


/*
This is the exact same function as 'step', but which prints the action it calls, for the BONUS debugging environment.
Only the differences are commented here.
@requires : pImg and pInter point respectively to a valid image and interpretor
@assigns : pInter, countBloquantes
@ensures : performs a step of the execution of 'image.ppm', as described above, and prints what it  */

void step_print (image *pImg, interpreteur *pInter, int *countBloquantes, int boolPrint);

#endif