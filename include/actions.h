#ifndef ACTION_H
#define ACTION_H

#include "interpreteur.h"

/*_______________________________________________________________________________________________________________________

        This file contains every action that can be called when switching from a coding color to another one,
        depending on the difference in color AND in brightness between them two.    
________________________________________________________________________________________________________________________*/


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : pushes the given size to the stack of inter    */
void empile (interpreteur *inter, int size);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes its top element from the stack of inter (but does nothing with it)*/
void depile (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the two first element from inter and pushes their sum   */
void plus (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the two first elements from inter and pushes (second - first) */
void moins (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the two first elements from inter and pushes (second * first) */
void fois (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the two first elements from inter and pushes (second / first) */
void divise (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the two first elements from inter and push (second % first) */
void reste (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the top first element from inter and pushes  1 if it equals 0
                                                                0 if not  */
void non (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the two first elements from inter and pushes     1 if second > first
                                                                    0 if second <= first */
void plus_grand (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the 'top' from inter, and increments its direction 'top' times */
void direction (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the 'top' from inter, and switches its bord 'top' times */
void bord (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : adds a second time the 'top' element to the stack of inter */
void duplique (interpreteur *inter);


// ------------------------------------------- FUNCTION 'tourne' -----------------------------------------------

/*
Auxiliary recursive function for the rotation ('tourne') function
@requires : inter points to a valid interpretor, and its stack has a size >= 'prof'
@assigns : *inter
@ensures :  Performs the placing part of the rotation : 
            place 'elem' at the 'prof' place in the stack   
IDEA :  we dive until we reaching the 'prof' depth.
        When we reach it (when 'prof' equals 0), we can simply push 'elem'
        Until then, we :    (i)   remove the current 'top' element (hence the depth 'prof - 1')
                            (ii)  call 'aux' with the depth 'prof - 1'
                            (iii) replace the 'top' element we removed in (i)  */
void aux (interpreteur *inter, int prof, int elem);

/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures :  rotates the stack of inter.
            Removes the first two elements : 'first' and 'second'
            (*) Replaces the new first element to the place indicated by 'second'
            Do the (*) process 'first' times in total   */
void tourne (interpreteur *inter);

// --------------------------------------------- END OF FUNCTION 'tourne' ----------------------------------------



/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : gets an integer from the stdin and pushes it to the stack */
void in_nombre (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : gets a character from the stdin and pushes its ASCII code to the stack*/
void in_char (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the 'top' element from the stack and prints it on the stdout  */
void out_nombre (interpreteur *inter);


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the 'top' element from the stack and prints its ASCII code on the stdout     */
void out_char (interpreteur *inter);



#endif