#include <stdio.h>
#include <stdlib.h>

#include "step.h"
#include "couleur.h"
#include "actions.h"
#include "bloc.h"
#include "print.h"

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
void moveToGoodExtrem (interpreteur *pInter, bloc_caract *pBloc) {
    // We move depending on the direction and bord, so we have to test them.
    // if direction = North
    if (pInter->dir == 0) { 
        // and bord = "babord",
        if (pInter->bord == -1) {
            // then go to the North-"babord" (Nb) coordinates
            moveTo(pInter, pBloc->Nb.i, pBloc->Nb.j);
        // but if bord = tribord,
        } else {
            // go to North-"tribord"
            moveTo(pInter, pBloc->Nt.i, pBloc->Nt.j);
        }
    // Same process with all 3 other directions.
    // East
    } else if (pInter->dir == 1) {
        if (pInter->bord == -1) {                   
            moveTo(pInter, pBloc->Eb.i, pBloc->Eb.j);
        } else {                             
            moveTo(pInter, pBloc->Et.i, pBloc->Et.j);
        }
    // South
    } else if (pInter->dir == 2) {            
        if (pInter->bord == -1) {                         
            moveTo(pInter, pBloc->Sb.i, pBloc->Sb.j);
        } else {                                 
            moveTo(pInter, pBloc->St.i, pBloc->St.j);
        }
    // West
    } else {                   
        if (pInter->bord == -1) {           
            moveTo(pInter, pBloc->Wb.i, pBloc->Wb.j);
        } else {                     
            moveTo(pInter, pBloc->Wt.i, pBloc->Wt.j);
        }
    }
}


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

void whichGoodExtrem(interpreteur *pInter, bloc_caract *pBloc, int *i, int *j) {
    // North
    if (pInter->dir == 0) {
        // babord
        if (pInter->bord == -1) { 
            *i = pBloc->Nb.i;
            *j = pBloc->Nb.j;
        // tribord
        } else {
            *i = pBloc->Nt.i;
            *j = pBloc->Nt.j;
        }
    // East
    } else if (pInter->dir == 1) { 
        if (pInter->bord == -1) { 
            *i = pBloc->Eb.i;
            *j = pBloc->Eb.j;
        } else {
            *i = pBloc->Et.i;
            *j = pBloc->Et.j;
        }
    // South
    } else if (pInter->dir == 2) {
        if (pInter->bord == -1) { 
            *i = pBloc->Sb.i;
            *j = pBloc->Sb.j;
        } else { 
            *i = pBloc->St.i;
            *j = pBloc->St.j;
        }
    // West
    } else {
        if (pInter->bord == -1) { 
            *i = pBloc->Wb.i;
            *j = pBloc->Wb.j;
        } else {
            *i = pBloc->Wt.i;
            *j = pBloc->Wt.j;
        }
    }
}


/*
Once placed at the right corner of the current bloc, 
in order to determine wether the next bloc is a coding, passing or blocking color,
we need the coordinates of the pixel next to the current one in the right direction.

@requires : pImg points to a valid image, pInter to a valid interpretor, iNext and jNext to two integers
@assigns : *iNext, *jNext
@ensures : stores in iNext and jNext the coordinates of the next pixel in the same direction as pInter->dir  */

void coordVoisin (image *pImg, interpreteur *pInter, int *iNext, int *jNext) {
    // Depending on the direction,
    switch (pInter->dir) {
        // North
        case 0:
            // the neighbor's I-coordinate is 1 substracted to the one of the current one.
            // We use the 'decr_i' function to take into account that the image is a torus.
            *iNext = decr_i(pImg, pInter->i);
            // the neighbor's J-coordinate is the same as to the current.
            *jNext = pInter->j;
            break;
        // East
        case 1:
            *iNext = pInter->i;
            *jNext = incr_j(pImg, pInter->j);
            break;
        // South
        case 2:
            *iNext = incr_i(pImg, pInter->i);
            *jNext = pInter->j;
            break;
        // West (as the only possible remaning given integer is 3, if pInter is a valid 'interpretur')
        default :
            *iNext = pInter->i;
            *jNext = decr_j(pImg, pInter->j);
            break;
    }
}



/*
Once we got the ID of the action to perform thanks to 'codeAction' defined in "couleur.h", 
we can perform it, by calling the corresponding function defined in "actions.h".
@requires : 'action' has been determined by 'codeAction', and pInter points to a valid interpreteur.
@assigns : nothing
@ensures : call the right action to perform.    */
void doRightAction (interpreteur *pInter, int action, int blocSize) {
    switch (action) {
        case 1:
            empile(pInter, blocSize);
            break;
        case 2:
            depile(pInter);
            break;
        case 10:
            plus(pInter);
            break;
        case 11:
            moins(pInter);
            break;
        case 12:
            fois(pInter);
            break;
        case 20:
            divise(pInter);
            break;
        case 21:
            reste(pInter);
            break;
        case 22:
            non(pInter);
            break;
        case 30:
            plus_grand(pInter);
            break;
        case 31:
            direction(pInter);
            break;
        case 32:
            bord(pInter);
            break;
        case 40:
            duplique(pInter);
            break;
        case 41:
            tourne(pInter);
            break;
        case 42:
            in_nombre(pInter);
            break;
        case 50:
            in_char(pInter);
            break;
        case 51:
            out_nombre(pInter);
            break;
        case 52:
            out_char(pInter);
            break;
        // case 0 (ie same color, which is not possible as it would be considered as the same bloc)
        default :
            // do nothing
            break;
    }
}

/*
This is the exact same function as 'doRightAction', but which prints the action it calls, for the BONUS debugging environment.
@requires : 'action' has been determined by 'codeAction', and pInter points to a valid interpreteur.
@assigns : nothing
@ensures : calls AND PRINTS the right action to perform.    */
void doRightAction_print (interpreteur *pInter, int action, int blocSize) {
    printf("     ");
    switch (action) {
        case 1:
            printf("On effectue 'empile' : on ajoute %d au sommet de la pile\n", blocSize);
            empile(pInter, blocSize);
            break;
        case 2:
            depile(pInter);
            printf("On effectue 'depile' : on retire l'élément au sommet de la pile\n");
            break;
        case 10:
            plus(pInter);
            printf("On effectue 'plus' : on retire les deux premiers élément de la pile, et empile leur somme\n");
            break;
        case 11:
            moins(pInter);
            printf("On effectue 'moins' : on retire les deux premiers élément de la pile, et empile (second - premier)\n");
            break;
        case 12:
            fois(pInter);
            printf("On effectue 'moins' : on retire les deux premiers élément de la pile, et empile leur produit\n");
            break;
        case 20:
            divise(pInter);
            printf("On effectue 'divise' : on retire les deux premiers élément de la pile, et empile (second / premier)\n");
            break;
        case 21:
            reste(pInter);
            printf("On effectue 'reste' : on retire les deux premiers élément de la pile, et empile (second modulo [premier])\n");
            break;
        case 22:
            non(pInter);
            printf("On effectue 'non' : on retire l'élément 'top' de la pile, et empile le booléen (top == 0)\n");
            break;
        case 30:
            plus_grand(pInter);
            printf("On effectue 'plus_grand' : on retire les deux premiers élément de la pile, et empile le booléen (second > premier)\n");
            break;
        case 31:
            direction(pInter);
            printf("On effectue 'direction' : on retire l'élément 'top' de la pile, et incrémente 'top' fois la direction\n");
            break;
        case 32:
            bord(pInter);
            printf("On effectue 'bord' : on retire l'élément 'top' de la pile, et incrémente 'top' fois le bord\n");
            break;
        case 40:
            duplique(pInter);
            printf("On effectue 'duplique' : on duplique l'élément 'top' de la pile\n");
            break;
        case 41:
            tourne(pInter);
            printf("On effectue 'tourne'\n");
            break;
        case 42:
            printf("On effectue 'in_nombre' : on empile l'entier que l'utilisateur saisit en stdin\n");
            in_nombre(pInter);
            break;
        case 50:
            printf("On effectue 'in_nombre' : on empile l'entier que l'utilisateur saisit en stdin\n");
            in_char(pInter);
            break;
        case 51:
            printf("On effectue 'out_nombre' : on retire le 'top' de la pile, et l'affiche sur stdout :\n");
            out_nombre(pInter);
            break;
        case 52:
            printf("On effectue 'out_char' : on retire le 'top' de la pile, et affiche sur stdout le caractère dont il est le code ASCII :\n");
            out_char(pInter);
            break;
        // case 0 (ie same color, which is not possible as it would be considered as the same bloc)
        default :
            // do nothing
            break;
    }
}


/*
Here is finally the function which gets the ID of the action to perform (thanks to 'codeAction' defined in "couleur.h"), 
and performs it (thanks to the previous 'doRightAction' function).
@requires : pImg and pInter point respectively to a valid image and interpreteur.
@assigns : nothing
@ensures : performs the right action, according to the current color and the "next" one    */

void act (image *pImg, interpreteur *pInter, int iNext, int jNext, int blocSize) {
    // we get the ID of the right action to perform,
    int action = codeAction(pImg->mat[iNext * pImg->w + jNext], pImg->mat[pInter->i * pImg->w + pInter->j]);
    // and we perform it.
    doRightAction(pInter, action, blocSize);
}

/*
Once again, exact same function as the previous 'act' one, but which prints the action it calls, 
for the BONUS debugging environment
@requires : pImg and pInter point respectively to a valid image and interpreteur.
@assigns : nothing
@ensures : performs AND PRINTS the right action, according to the current color and the "next" one    */

void act_print (image *pImg, interpreteur *pInter, int iNext, int jNext, int blocSize) {
    int action = codeAction(pImg->mat[iNext * pImg->w + jNext], pImg->mat[pInter->i * pImg->w + pInter->j]);
    doRightAction_print(pInter, action, blocSize);
}


/*
When the "next" color is a passing one, we have to cross it in the same direction,
until we reach the border of this passing bloc.
This function stores at iNext and jNext the coordinates of the border at the other side of that passing bloc.

@requires : pImg points to a valid image, pInter to a valid interpretor, iNext and jNext to two integers,
            AND the interpretor has been placed on the new passing bloc.
@assigns : *iNext and *jNext
@ensures : stores at iNext and jNext the coordinates of the other side of the passing bloc  */

void moveUntilNewBloc (image *pImg, interpreteur *pInter, int *iNext, int *jNext) {
    // Initialization of the variables we will use to cross the passing bloc
    int iTmp = pInter->i;
    int jTmp = pInter->j;

    // It is to be noted that the eventuality that we reach another passing bloc of another passing color doesn't matter.
    // We would have to keep going in the same direction anyway.
    // Thus we can keep going as long as the color met is passing, without looking wich exact passing color it is.
    while (isPassing(pImg->mat[iTmp * pImg->w + jTmp]) ) {
        // The variable incrementation depends on the direction of the interpretor.
        switch (pInter->dir) {
            // North
            case 0:  
                iTmp = decr_i(pImg, iTmp);
                break;
            // East
            case 1: 
                jTmp = incr_j(pImg, jTmp);
                break;
            // South
            case 2: 
                iTmp = incr_i(pImg, iTmp);
                break;
            // West
            default: 
                jTmp = decr_j(pImg, jTmp);
                break;
        }
    }
    // We store the coordinates at the given adresses.
    *iNext = iTmp;
    *jNext = jTmp;
}




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

void step (image *pImg, interpreteur *pInter, int *countBloquantes) {

    // Get the coordinates of the right corner to go
    bloc_caract *pBloc = getBloc(pImg, pInter);

    // Move to that right corner
    moveToGoodExtrem(pInter, pBloc);

    // Get the coordinates of the pixel at the other side of the border
    int iNext, jNext;
    coordVoisin(pImg, pInter, &iNext, &jNext);

    // The subsequent actions depend on that neighbor pixel.

    // A) if that neighbor pixel is a CODING color : 
    if (isCoding(pImg->mat[iNext * pImg->w + jNext])) {
        // That means there is somewhere to go in order to keep executinf 'image.ppm', 
        // so we can put the counter of blocking neighbor to 0.
        (*countBloquantes) = 0;
        // a) if the current pixel is also a coding color :
        if (isCoding(pImg->mat[pInter->i * pImg->w + pInter->j])) {
            // perform the correct action
            act(pImg, pInter, iNext, jNext, pBloc->size);
        // b) if the current pixel is not coding (because it is passing) :
        } else {
            // do nothing
        }
        // Move to that next coding bloc.
        moveTo(pInter, iNext, jNext);
    // End the step
    }

    // B) if that neighbor pixel is BLOCKING :
    else if ( !isPassing(pImg->mat[iNext * pImg->w + jNext]) ) {   
        // The information about the value to be changed (direction or edge) is contained in the parity of *countBloquantes.
        // The fact that countBloquantes doesn't exceed 8 is tested when the function 'step' is called,
        // so no need to worry about it here.
        // If *countBloquantes is even :
        if ((*countBloquantes) % 2 == 0) {     
            // Change the edge
            incr_bord(pInter);   
        // If it is odd :                              
        } else {            
            // Increment the direction                                
            incr_dir(pInter);                                       
        }
        // Either way, increment the counter of blocking neighbors met from this current bloc.
        (*countBloquantes)++;
    // End the step
    }                                                           

    // C) if that neighbor pixel is PASSING :
    else {  
        // Move to that passing bloc, even if you need to move again latter if you reach a coding pixel.
        moveTo(pInter, iNext, jNext);
        // Get the coordinates of the border at the other side of that passing bloc
        moveUntilNewBloc(pImg, pInter, &iNext, &jNext);
        // b) if that next bloc is coding :
        if (isCoding(pImg->mat[iNext * pImg->w + jNext])) {
            // Move to it,
            moveTo(pInter, iNext, jNext);
            // but don't perform any action as you crossed a passing bloc.
        // a) if that next bloc is BLOCKING :
        } else {   
            // Do nothing. The next step will begin on this passing bloc you previously moved to.
        }
        // Reset the counter of blocking neighbors to 0, as we just crossed a passing bloc.
        (*countBloquantes) = 0;
    // End the step.
    }                                                       

} 
// End of the 'step' function
// -------------------------------------------------------------------------------------------------------------------------



/*
This is the exact same function as 'step', but which prints the action it calls, for the BONUS debugging environment.
Only the differences are commented here.
@requires : pImg and pInter point respectively to a valid image and interpretor
@assigns : pInter, countBloquantes
@ensures : performs a step of the execution of 'image.ppm', as described above, and prints what it  */

void step_print (image *pImg, interpreteur *pInter, int *countBloquantes, int boolPrint) {

    bloc_caract *pBloc = getBloc(pImg, pInter);

    moveToGoodExtrem(pInter, pBloc);

    // In order to print where we moved, we get the coordinates of that right corner :
    int iExtrm, jExtrm;
    whichGoodExtrem(pInter, pBloc, &iExtrm, &jExtrm);
    printf("     On bouge à la bonne extrémité du bloc, en (%d, %d)\n", iExtrm, jExtrm);
    print_image(boolPrint, pImg, iExtrm, jExtrm);

    int iNext, jNext;
    coordVoisin(pImg, pInter, &iNext, &jNext);

    printf("     Pixel voisin : (%d, %d) : ", iNext, jNext);
    print_pixel(pImg, iNext, jNext);

    // A) CODING
    if (isCoding(pImg->mat[iNext * pImg->w + jNext])) {
        if (isCoding(pImg->mat[pInter->i * pImg->w + pInter->j])) {
            printf("     Couleur actuelle ET suivante codantes\n");
            act_print(pImg, pInter, iNext, jNext, pBloc->size);
        } else {
            printf("     Couleur suivante codante, mais pas l'actuelle ( ");
            print_pixel(pImg, pInter->i, pInter->j);
            printf(" ).\n");
            // Do nothing.
        }
        moveTo(pInter, iNext, jNext);
        printf("     Puisque la couleur voisine est codante, on s'y rend. Arrivé en (%d, %d)\n", iNext, jNext);
        printf("     L'arrivée sur une couleur codante provoque la réinitialisation du compteur de bloquantes à 0.\n");
        (*countBloquantes) = 0;
    }

    // B) BLOCKING
    else if ( !isPassing(pImg->mat[iNext * pImg->w + jNext]) ) {   
        printf("     Couleur voisine bloquante. On incrémente donc le compteur de bloquantes successives.\n");
        if ((*countBloquantes) % 2 == 0) {   
            if ((*countBloquantes) == 0) {
                printf("     C'est la première voisine bloquante que l'on croise depuis ce bloc, donc on change le bord.\n");
            } else {
                printf("     C'est la direction qu'on a changé la dernière fois. On change donc le bord.\n");
            }        
            incr_bord(pInter);                                 
        } else {            
            printf("     C'est le bord qu'on a changé la dernière fois. On change donc la direction.\n");                                
            incr_dir(pInter);                                       
        }
        (*countBloquantes)++;
    }                                                           

    // C) PASSING
    else {  
        printf("     Couleur voisine passante. On s'y place, en (%d, %d) (quitte à re-bouger en cas de couleur codante de l'autre côté).\n", iNext, jNext);
        moveTo(pInter, iNext, jNext);
        moveUntilNewBloc(pImg, pInter, &iNext, &jNext);
        if (isCoding(pImg->mat[iNext * pImg->w + jNext])) {
            moveTo(pInter, iNext, jNext);
            printf("     La couleur de l'autre côté est codante. On s'y rend donc, en (%d, %d)\n", iNext, jNext);
        } else {
            // Do nothing
        }
    }                                                       
}
// end of the 'step_print' function
// ---------------------------------------------------------------------------------------------------------------------
