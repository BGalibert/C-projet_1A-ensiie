#ifndef COULEUR_H
#define COULEUR_H

#include "image.h"

/*________________________________________________________________________________________________________________________

    This file contains everything relative to colors (which are nothing but pixels) :
        1) definitions of the 18 color-variables first declared in "couleur.h", line 21.
        2) 'isColoredBy', an usefull boolean function testing wether a given pixel is the given colored, line 56
        3) some functions to determine wether a given color is coding, passing or blocking, line 76
        4) we wrote some functions to give an integer ID to every action possible 
            when transitioning from one to another coding color during a step, line 144
_________________________________________________________________________________________________________________________*/


// -----------------------------------------------------------------------------------------------------------------------------
// Declarations of the 18 coding RGB-colors in Cornelis, as external variable to avoid multiple definitions,
// as it occured when including this file in others.        

// Normal colors

extern pixel rouge;
extern pixel vert;
extern pixel bleu;

extern pixel jaune;
extern pixel cyan;
extern pixel magenta;

// Light

extern pixel rclair;
extern pixel vclair;
extern pixel bclair;

extern pixel jclair;
extern pixel cclair;
extern pixel mclair;

// Dark

extern pixel rfonc;
extern pixel vfonc;
extern pixel bfonc;

extern pixel jfonc;
extern pixel cfonc;
extern pixel mfonc;

// ----------------------------------------------------------------------------------------------------------------------

/*
An usefull function.
@requires : nothing
@assigns : nothing
@ensures : tests if the pixel is colored by the given color     */
int isColoredBy (pixel pt, pixel color);

// ---------------------------------------------------------------------------------------------------------------------

// A few functions to determine wether a given color is coding, passing or blocking in Cornelis

/*
@requires : nothing
@assigns : nothing
@ensures : tests if the given color is one of the 18 coding ones    */
int isCoding (pixel color);


/*
A non-coding color is classified as either passing or blocking based on its brightness.
Here is the function that calulates it.
@requires : nothing
@assigns : nothing
@ensures : returns the brightness of the given color obtained with the RGB brightness formula   */
int brightness (pixel color);
/*
@requires : nothing
@assigns : nothing
@ensures :  tests if the given color is Passing (returns 1) or not.
            If we already know that the color is not coding, returning 0 means the color is blocking    */
int isPassing (pixel color);

//----------------------------------------------------------------------------------------------------------------------

/*
When transitioning from one to another coding color, we perform an action based on the difference
in color AND in brightness between both.
The idea is to give an ID to every possible action, and to write a function 'codeAction'
that returns the right ID when given the two colors.
There are   3 possibles brightness (light, normal and dark),
            and 6 different colors (red, ...).
Thus, we can generate a bijection by assigning to each possible difference :
    (difference_in_color) * 10 + difference_in_brightness
Here are the few functions used to write 'codeAction' 
*/


/*
First, a function that assigns an integer to each color (independently of its brightness)
@requires : 'color' is a coding color
@assigns :  nothing
@ensures :  returns the position of the normal version of 'color' in the cycle R->J->V->C->B->M->R->...
            eg :    rfonc -> rouge -> 0
                    magenta -> magenta -> 5   */
int whichColor (pixel color);
/*
Then, a function that assigns an integer to every difference in color (independently of the brightnesses)
@requires : 'arrivee' and 'depart' are both coding
@assigns : nothing
@ensures : returns the difference of color (arrivee) - (depart) in the cycle R->J->V->C->B->M->R->...   */
int diffColor (pixel arrivee, pixel depart);


/*
Secondly, a function that assigns an integer to each brightness (independently of its color).
@requires : 'color' is a coding color
@assigns : nothing
@ensures : returns the position of the color in the cycle Light -> Normal -> Dark -> Light ...  */
int whichBright (pixel color);
/*
Then, a function that assigns an integer to every difference in brightness (independently of the colors).
@requires : 'arrivee' and 'depart' are both coding
@assigns : nothing
@ensures : returns the difference of brightness (arrivee) - (depart) in the cycle Light -> Normal -> Dark -> Light ...   */
int diffBright (pixel arrivee, pixel depart);


/*
We can finally write the coding function, which returns the ID of the right action to perform
depending on the departure and arival colors.
@requires : nothing
@assigns : nothing
@ensures : returns an integer corresponding to an action to do, depending on the difference in color and brightness 
            between the colors colArriv and colDepart.
            Cf switch-case in function doRightAction to see the correspondance between integer => action  */
int codeAction (pixel colArriv, pixel colDepart);




#endif