#include <stdio.h>
#include <stdlib.h>

#include "couleur.h"
//#include "image.h"

/*________________________________________________________________________________________________________________________

    This file contains everything relative to colors (which are nothing but pixels) :
        1) definitions of the 18 color-variables first declared in "couleur.h", line 21.
        2) 'isColoredBy', an usefull boolean function testing wether a given pixel is the given colored, line 56
        3) some functions to determine wether a given color is coding, passing or blocking, line 76
        4) we wrote some functions to give an integer ID to every action possible 
            when transitioning from one to another coding color during a step, line 144
_________________________________________________________________________________________________________________________*/



// Here are the 18 coding RGB-colors in Cornelis ----------------------------------------------------------------

// Normal colors

pixel rouge = {255, 0, 0};
pixel vert = {0, 255, 0};
pixel bleu = {0, 0, 255};

pixel jaune = {255, 255, 0};
pixel cyan = {0, 255, 255};
pixel magenta = {255, 0, 255};

// Light

pixel rclair = {255, 128, 128};
pixel vclair = {128, 255, 128};
pixel bclair = {128, 128, 255};

pixel jclair = {255, 255, 128};
pixel cclair = {128, 255, 255};
pixel mclair = {255, 128, 255};

// Dark

pixel rfonc = {128, 0, 0};
pixel vfonc = {0, 128, 0};
pixel bfonc = {0, 0, 128};

pixel jfonc = {128, 128, 0};
pixel cfonc = {0, 128, 128};
pixel mfonc = {128, 0, 128};

// ---------------------------------------------------------------------------------------------------------------


/*
An usefull function.
@requires : nothing
@assigns : nothing
@ensures : tests if the pixel is colored by the given color     */
int isColoredBy (pixel pt, pixel color) {
    // For all 3 RGB components,
    for (int i = 0; i < 3; i++) {
        // if the value differs from the one of the color,
        if (pt[i] != color[i]) {
            // the pixel is not colored by the given color
            return 0;
        }
    }
    // if we reach this point, the pixel is colored by the given color
    return 1;
}



// A few functions to determine wether a given color is coding, passing or blocking in Cornelis -------------------------------

/*
@requires : nothing
@assigns : nothing
@ensures : tests if the given color is one of the 18 coding ones    */
int isCoding (pixel color){
    // Insted of testing 18 if (color == rouge), we use the similarity between  all normal, 
    //                                                                          light and dark primary and secondary colors. 
    // Indeed, all 3 colors of each group (eg light primary) have the same sum of their RGB components
    // So we get this sum :
    int s = color[0] + color[1] + color[2];
    // and we test depending on the value of 's'.
// Light
    // All and only the 3 primary light colors (between the 18 coding) have a sum of 511
    if (s == 511) {
        // Of course, the sum is not enough, and we still have to test if the given color is actually one of the 3 possibles. 
        return ( isColoredBy(color, rclair) || isColoredBy(color, vclair) || isColoredBy(color, bclair) );    
    // Same idea that previously
    } else if (s == 638) {
        return ( isColoredBy(color, jclair) || isColoredBy(color, cclair) || isColoredBy(color, mclair) ); 
    } 
// Normal
    else if (s == 255) {
        return ( isColoredBy(color, rouge) || isColoredBy(color, vert) || isColoredBy(color, bleu) );
    } else if (s == 510) {
        return ( isColoredBy(color, jaune) || isColoredBy(color, cyan) || isColoredBy(color, magenta) );
    } 
// Dark
    else if (s == 128) {
            return ( isColoredBy(color, rfonc) || isColoredBy(color, vfonc) || isColoredBy(color, bfonc) );
    } else if (s == 256) {
            return ( isColoredBy(color, jfonc) || isColoredBy(color, cfonc) || isColoredBy(color, mfonc) );
    } else {
        return 0;
    }
}


/*
A non-coding color is classified as either passing or blocking based on its brightness.
Here is the function that calulates it.
@requires : nothing
@assigns : nothing
@ensures : returns the brightness of the given color obtained with the RGB brightness formula   */
int brightness (pixel color) {
    double bright = 0.202 * color[0] + 0.707 * color[1] + 0.071 * color[2];
    return (int) bright;
}


/*
@requires : nothing
@assigns : nothing
@ensures :  tests if the given color is Passing (returns 1) or not.
            If we already know that the color is not coding, returning 0 means the color is blocking    */
int isPassing (pixel color){
    // If the color is coding,
    if (isCoding(color)) {
        // it is not passing
        return 0;
    }
    // else, we get its brightness,
    int bright = brightness (color);
    // and test it
    return bright >= 128;
}
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
int whichColor (pixel color) {
    // we don't distinguish between light, dark and normal here
    if (isColoredBy(color, rclair) || isColoredBy(color, rouge) || isColoredBy(color, rfonc)) {
        return 0;
    } else if (isColoredBy(color, jclair) || isColoredBy(color, jaune) || isColoredBy(color, jfonc)) {
        return 1;
    } else if (isColoredBy(color, vclair) || isColoredBy(color, vert) || isColoredBy(color, vfonc)) {
        return 2;
    } else if (isColoredBy(color, cclair) || isColoredBy(color, cyan) || isColoredBy(color, cfonc)) {
        return 3;
    } else if (isColoredBy(color, bclair) || isColoredBy(color, bleu) || isColoredBy(color, bfonc)) {
        return 4;
    } else {
        return 5;
    }
}


/*
Then, a function that assigns an integer to every difference in color (independently of the brightnesses)
@requires : 'arrivee' and 'depart' are both coding
@assigns : nothing
@ensures : returns the difference of color (arrivee) - (depart) in the cycle R->J->V->C->B->M->R->...   */
int diffColor (pixel arrivee, pixel depart){
    // once again, we add +6 to the left member to avoid any negative result of the modulo
    return (whichColor(arrivee) - whichColor(depart) + 6) % 6;
}


/*
Secondly, a function that assigns an integer to each brightness (independently of its color).
@requires : 'color' is a coding color
@assigns : nothing
@ensures : returns the position of the color in the cycle Light -> Normal -> Dark -> Light ...  */
int whichBright (pixel color) {
    // Light
    if (isColoredBy(color, rclair) || isColoredBy(color, jclair) || isColoredBy(color, vclair) || isColoredBy(color, cclair) || isColoredBy(color, bclair) || isColoredBy(color, mclair)) {
        return 0;
    // Normal
    } else if (isColoredBy(color, rouge) || isColoredBy(color, jaune) || isColoredBy(color, vert) || isColoredBy(color, cyan) || isColoredBy(color, bleu) || isColoredBy(color, magenta)) {
        return 1;
    // Dark
    } else {
        return 2;
    }
}


/*
Then, a function that assigns an integer to every difference in brightness (independently of the colors).
@requires : 'arrivee' and 'depart' are both coding
@assigns : nothing
@ensures : returns the difference of brightness (arrivee) - (depart) in the cycle Light -> Normal -> Dark -> Light ...   */
int diffBright (pixel arrivee, pixel depart){
    // +3 to the left member to avoir any negative answer of the modulo
    return (whichBright(arrivee) - whichBright(depart) + 3) % 3;
}


/*
We can finally write the coding function, which returns the ID of the right action to perform
depending on the departure and arival colors.
@requires : nothing
@assigns : nothing
@ensures : returns an integer corresponding to an action to do, depending on the difference in color and brightness 
            between the colors colArriv and colDepart.
            Cf switch-case in function doRightAction to see the correspondance between integer => action  */
int codeAction (pixel colArriv, pixel colDepart) {
    return diffColor(colArriv, colDepart) * 10 + diffBright(colArriv, colDepart);
}

/*
void print_image2 (image *pImg) {
    for (int i = 0; i < pImg->h; i++) {
        for (int j = 0; j < pImg->w; j++) {
            if (isCoding(pImg->mat[i * pImg->w + j])) {
                if (isColoredBy(pImg->mat[i * pImg->w + j], rclair) || isColoredBy(pImg->mat[i * pImg->w + j], rouge) || isColoredBy(pImg->mat[i * pImg->w + j], rfonc)){
                    printf("R");
                } else if (isColoredBy(pImg->mat[i * pImg->w + j], jclair) || isColoredBy(pImg->mat[i * pImg->w + j], jaune) || isColoredBy(pImg->mat[i * pImg->w + j], jfonc)){
                    printf("J");
                } else if (isColoredBy(pImg->mat[i * pImg->w + j], vclair) || isColoredBy(pImg->mat[i * pImg->w + j], vert) || isColoredBy(pImg->mat[i * pImg->w + j], vfonc)){
                    printf("V");
                } else if (isColoredBy(pImg->mat[i * pImg->w + j], cclair) || isColoredBy(pImg->mat[i * pImg->w + j], cyan) || isColoredBy(pImg->mat[i * pImg->w + j], cfonc)){
                    printf("C");
                } else if (isColoredBy(pImg->mat[i * pImg->w + j], bclair) || isColoredBy(pImg->mat[i * pImg->w + j], bleu) || isColoredBy(pImg->mat[i * pImg->w + j], bfonc)){
                    printf("B");
                } else {
                    printf("M");
                }
            } else if (isPassing(pImg->mat[i * pImg->w + j])) {
                printf(".");
            } else {
                printf("|");
            }
        }
        printf("\n");
    }
    printf("\n");
}
*/


/*
void print_image3(int boolPrint, image *pImg, int x, int y) {
    if (!boolPrint) {
        return;
    }
    printf("\n");
    if (x == -1 || y == -1) {
        for (int i = 0; i < pImg->h; i++) {
            for (int j = 0; j < pImg->w; j++) {
                if (isCoding(pImg->mat[i * pImg->w + j])) {
                    printColor(pImg->mat[i * pImg->w + j]);
                } else if (isPassing(pImg->mat[i * pImg->w + j])) {
                    printf(" . ");
                } else {
                    printf(" | ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    else {
        for (int i = 0; i < pImg->h; i++) {
            for (int j = 0; j < pImg->w; j++) {
                if (i == x && j == y) {
                    printf(" @ ");
                } else {
                    if (isCoding(pImg->mat[i * pImg->w + j])) {
                        printColor(pImg->mat[i * pImg->w + j]);
                    } else if (isPassing(pImg->mat[i * pImg->w + j])) {
                        printf(" . ");
                    } else {
                        printf(" | ");
                    }
                }
            }
            printf("\n");
        }
        printf("\n");
        //printf("\npixel @(%d, %d) : ", x, y);
        //print_pixel(pImg, x, y);
    }
}

void print_pixel (image *pImg, int i, int j) {
    printf("{%d, %d, %d}. ", pImg->mat[i * pImg->w + j][0], pImg->mat[i * pImg->w + j][1], pImg->mat[i * pImg->w + j][2]);
    if (isCoding(pImg->mat[i * pImg->w + j])) {
        printf("Couleur codante (%s).\n", whichCoding(pImg->mat[i * pImg->w + j]));
        return;
    } else {
        double bright = 0.202*pImg->mat[i * pImg->w + j][0] + 0.707*pImg->mat[i * pImg->w + j][1] + 0.071*pImg->mat[i * pImg->w + j][2];
        printf("Luminosité : %d. ", (int)bright);
        if (isPassing(pImg->mat[i * pImg->w + j])) {
            printf("Couleur passante.\n");
        } else {
            printf("Couleur bloquante.\n");
        }
    }
}
*/