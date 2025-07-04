#include <stdio.h>
#include <stdlib.h>
#include "actions.h"


/*_______________________________________________________________________________________________________________________

        This file contains every action that can be called when transitionning from a coding color to another one,
        depending on the difference in color AND in brightness between the two.    
________________________________________________________________________________________________________________________*/


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : push the given size to the stack of inter    */
void empile (interpreteur *inter, int size) {
    stack_push(inter->pS, size);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove its top element from the stack of inter (but do nothing with it)*/
void depile (interpreteur *inter) {
    if (stack_size(inter->pS) < 1) {
        return;
    }
    stack_pop(inter->pS);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the two first element from inter and push their sum   */
void plus (interpreteur *inter) {
    if (stack_size(inter->pS) < 2) {
        return;
    }
    int premier = stack_pop(inter->pS);
    int second = stack_pop(inter->pS);
    stack_push(inter->pS, second + premier);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the two first elements from inter and push (second - first) */
void moins (interpreteur *inter) {
    if (stack_size(inter->pS) < 2) {
        return;
    }
    int premier = stack_pop(inter->pS);
    int second = stack_pop(inter->pS);
    stack_push(inter->pS, second - premier);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the two first elements from inter and push (second * first) */
void fois (interpreteur *inter) {
    if (stack_size(inter->pS) < 2) {
        return;
    }
    int premier = stack_pop(inter->pS);
    int second = stack_pop(inter->pS);
    stack_push(inter->pS, second * premier);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the two first elements from inter and push (second / first) */
void divise (interpreteur *inter) {
    if (stack_size(inter->pS) < 2) {
        return;
    }
    int premier = stack_pop(inter->pS);
    int second = stack_pop(inter->pS);
    stack_push(inter->pS, second / premier);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the two first elements from inter and push (second % first) */
void reste (interpreteur *inter) {
    if (stack_size(inter->pS) < 2) {
        return;
    }
    int premier = stack_pop(inter->pS);
    int second = stack_pop(inter->pS);
    stack_push(inter->pS, second % premier);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the top first element from inter and push 1 if it equals 0
                                                            0 if not  */
void non (interpreteur *inter) {
    if (stack_size(inter->pS) < 1) {
        return;
    }
    int n = stack_pop(inter->pS);
    stack_push(inter->pS, (n == 0) );
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the two first elements from inter and push    1 if second > first
                                                                0 if second <= first */
void plus_grand (interpreteur *inter) {
    if (stack_size(inter->pS) < 2) {
        return;
    }
    int premier = stack_pop(inter->pS);
    int second = stack_pop(inter->pS);
    stack_push(inter->pS, (second > premier) );    // bien que l'énoncé ne précise pas "strictement"
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the 'top' from inter, and increments its direction 'top' times */
void direction (interpreteur *inter) {
    if (stack_size(inter->pS) < 1) {
        return;
    }
    int n = stack_pop(inter->pS);
    // as the direction is a cycle of size 4, incrementing (n % 4) times is enough
    int r = n % 4;
    for (int i = 0; i < r; i++) {
        incr_dir(inter);
    }
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : remove the 'top' from inter, and switches its bord 'top' times */
void bord (interpreteur *inter) {
    if (stack_size(inter->pS) < 1) {
        return;
    }
    int n = stack_pop(inter->pS);
    // as the direction is a cycle of size 2, incrementing (n % 2) times is enough
    int r = n % 2;
    for (int i = 0; i < r; i++) {
        incr_bord(inter);
    }
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : adds a second time the 'top' element to the stack of inter */
void duplique (interpreteur *inter) {
    if (stack_size(inter->pS) < 1) {
        return;
    }
    int n = stack_pop(inter->pS);
    stack_push(inter->pS, n);
    stack_push(inter->pS, n);
}


// ---------------------------------------------- FUNCTION 'tourne' ------------------------------------------------

/*
Auxiliary recursive function for the rotation ('tourne') function
@requires : inter points to a valid interpretor, and its stack has a size >= 'prof'
@assigns : *inter
@ensures :  Performs the placing part of the rotation : 
            place 'elem' at the 'prof' place in the stack   
IDEA :  we dive until we reaching the 'prof' depth.
        When we reach it (when 'prof' equals 0), we can simply push 'elem'.
        Until then, we :    (i)   remove the current 'top' element (hence the depth 'prof - 1')
                            (ii)  call 'aux' with the depth 'prof - 1'
                            (iii) replace the 'top' element we removed in (i)  
        The recursion ends as the stack is not infinite     */
void aux (interpreteur *inter, int prof, int elem) {
    // we reached the required depth
    if (prof == 0) {
        stack_push(inter->pS, elem);
        return;
    // else, we dive 
    } else {
        // (i)
        int n = stack_pop(inter->pS);
        // (ii)
        aux(inter, prof - 1, elem);
        // (iii)
        stack_push(inter->pS, n);
        return;
    }
}

/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures :  rotates the stack of inter.
            Removes the first two elements : 'first' and 'second'
            (*) Replaces the new first element to the place indicated by 'second'
            Do the (*) process 'first' times in total   */
void tourne (interpreteur *inter) {
    // First, 2 elements are needed to determine how to rotate the stack and how many times, so
    // if there is less than 2 elements in the stack,
    if (stack_size(inter->pS) < 2) {
        // we do nothing and end the function
        return;
    }
    // else, we get these two elements :
    // first the number of times we have to rotate
    int nbFois = stack_pop(inter->pS);
    // secondly the depth.
    int profondeur = stack_pop(inter->pS); 
    // To perform the rotation, the stack needs at least 'profondeur' elements, so
    // if there is not enough elements,
    if (stack_size(inter->pS) < profondeur) {
        // we have to restore the stack as it was before entering the function, so
        // we replace the second element,
        stack_push(inter->pS, profondeur);
        // then the first one,
        stack_push(inter->pS, nbFois);
        // and we end the function, as there is nothing we can do
        return;
    }

    // Else (if we can actually rotate), 
    // 'nbFois' times,
    for (int count = 0; count < nbFois; count++) {
        // we perform the rotation
        aux(inter, profondeur - 1, stack_pop(inter->pS));
    }
}
// --------------------------------------------- END OF FUNCTION 'tourne' ----------------------------------------


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : gets an integer from the stdin and pushes it to the stack */
void in_nombre (interpreteur *inter) {
    int nUser;
    char buf[256];
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", &nUser);
    stack_push(inter->pS, nUser);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : gets a character from the stdin and pushes its ASCII code to the stack*/
void in_char (interpreteur *inter) {
    char cUser;
    char buf[2];
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%c", &cUser);
    stack_push(inter->pS, (int) cUser);
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the 'top' element from the stack and prints it on the stdout  */
void out_nombre (interpreteur *inter) {
    if (stack_size(inter->pS) < 1) {
        return;
    }
    printf("%d", stack_pop(inter->pS));
}


/*
@requires : inter points to a valid interpretor
@assigns : *inter
@ensures : removes the 'top' element from the stack and prints its ASCII code on the stdout     */
void out_char (interpreteur *inter) {
    if (stack_size(inter->pS) < 1) {
        return;
    }
    printf("%c", stack_pop(inter->pS));
}



