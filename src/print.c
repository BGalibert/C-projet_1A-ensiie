#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "couleur.h"



/*____________________________________________________________________________________________________________________

    This file contains some printing functions used in the BONUS debugging environment,
    and a few auxiliary functions they require.
____________________________________________________________________________________________________________________*/



/*
@requires : dir is the integer 'dir' of the interpretor (so it equals 0, 1, 2 or 3)
@assigns : nothing
@ensures : returns the name of the direction corresponding to the given integer */
char* intToDir (int dir){
    if (dir == 0) {
        return "Nord";
    } else if (dir == 1) {
        return "Est";
    } else if (dir == 2) {
        return "Sud";
    } else {
        return "Ouest";
    }
}


/*
@requires : 'bord' is the 'bord' value of the interpretor (so it equals -1 or 1)
@assigns : nothing
@ensures : returns the name of the edge corresponding to the given integer  */
char* intToBord (int bord){
    if (bord == -1) {
        return "babord";
    } else {
        return "tribord";
    }
}


/*
@requires : 'color' is a coding color
@assigns : nothing
@ensures : prints the abreviated name of 'color', to build an image characters-representation   */
void printColor(pixel color) {
    // LIGHT
    if (isColoredBy(color, rclair)) {
        printf(" Rc");
    } else if (isColoredBy(color, jclair)) {
        printf(" Jc");
    } else if (isColoredBy(color, vclair)) {
        printf(" Vc");
    } else if (isColoredBy(color, cclair)) {
        printf(" Cc");
    } else if (isColoredBy(color, bclair)) {
        printf(" Bc");
    } else if (isColoredBy(color, mclair)) {
        printf(" Mc");
    }

    // NORMAL
    else if (isColoredBy(color, rouge)) {
        printf(" R ");
    } else if (isColoredBy(color, jaune)) {
        printf(" J ");
    } else if (isColoredBy(color, vert)) {
        printf(" V ");
    } else if (isColoredBy(color, cyan)) {
        printf(" C ");
    } else if (isColoredBy(color, bleu)) {
        printf(" B ");
    } else if (isColoredBy(color, magenta)) {
        printf(" M ");
    }

    // DARK
    else if (isColoredBy(color, rfonc)) {
        printf(" Rf");
    } else if (isColoredBy(color, jfonc)) {
        printf(" Jf");
    } else if (isColoredBy(color, vfonc)) {
        printf(" Vf");
    } else if (isColoredBy(color, cfonc)) {
        printf(" Cf");
    } else if (isColoredBy(color, bfonc)) {
        printf(" Bf");
    } else { // if (isColoredBy(color, mfonc))
        printf(" Mf");
    }
}


/*
Almost the same function, but for a totally different purpose : this time it is not for the image printing, 
but to print the color the interpretor is located on.
@requires : 'color' is a coding color
@assigns : nothing
@ensures : returns the full name of the given color     */
char* whichCoding(pixel color) {
    // LIGHT
    if (isColoredBy(color, rclair)) {
        return "rouge clair";
    } else if (isColoredBy(color, jclair)) {
        return "jaune clair";
    } else if (isColoredBy(color, vclair)) {
        return "vert clair";
    } else if (isColoredBy(color, cclair)) {
        return "cyan clair";
    } else if (isColoredBy(color, bclair)) {
        return "bleu clair";
    } else if (isColoredBy(color, mclair)) {
        return "magenta clair";
    }
    // NORMAL
    else if (isColoredBy(color, rouge)) {
        return "rouge";
    } else if (isColoredBy(color, jaune)) {
        return "jaune";
    } else if (isColoredBy(color, vert)) {
        return "vert";
    } else if (isColoredBy(color, cyan)) {
        return "cyan";
    } else if (isColoredBy(color, bleu)) {
        return "bleu";
    } else if (isColoredBy(color, magenta)) {
        return "magenta";
    }
    // DARK
    else if (isColoredBy(color, rfonc)) {
        return "rouge foncé";
    } else if (isColoredBy(color, jfonc)) {
        return "jaune foncé";
    } else if (isColoredBy(color, vfonc)) {
        return "vert foncé";
    } else if (isColoredBy(color, cfonc)) {
        return "cyan foncé";
    } else if (isColoredBy(color, bfonc)) {
        return "bleu foncé";
    } else { // if (isColoredBy(color, mfonc))
        return "magenta foncé";
    }
}


/*
The function to print the image with characters instead of litteral colors.
The 'boolPrint' boolean indicates if the image has to be printed or not
(as the function will be called wether the image fits into the user's screen or not).
'x' and 'y' are the coordinates of the interpretor, to print differently.
If they equal -1, the interpretor should not be localized on the printed image. 
@requires : boolPrint is a boolean, x and y either respect the shape of *pImg or equal -1, and pImg points to a valid image
@assigns : nothing
@ensures : prints the image if 'boolPrint' = 1 (else does nothing), 
           and visually differenciates the ('x', 'y') point   */

void print_image (int boolPrint, image *pImg, int x, int y) {
    // if the image should not be printed,
    if (!boolPrint) {
        // do nothing, and end the function
        return;
    }

    // ELSE (ie the image should be printed)
    printf("\n");

    // if the interpretor sould not appeared
    if (x == -1 || y == -1) {
        // for every row,
        for (int i = 0; i < pImg->h; i++) {
            // for every column,
            for (int j = 0; j < pImg->w; j++) {
                // if the pixel (i, j) is coding :
                if (isCoding(pImg->mat[i * pImg->w + j])) {
                    // print its abreviated color
                    printColor(pImg->mat[i * pImg->w + j]);
                // if passing
                } else if (isPassing(pImg->mat[i * pImg->w + j])) {
                    printf(" . ");
                // if blocking
                } else {
                    printf(" | ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    // if the interpretor should appear :
    else {
        // for every row,
        for (int i = 0; i < pImg->h; i++) {
            // for every column,
            for (int j = 0; j < pImg->w; j++) {
                // if the coordinates are the given ones,
                if (i == x && j == y) {
                    // print a special character : '@'
                    printf(" @ ");
                // else, do the same thing than before
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
    }
}


/*
Finally, here is a function to print some information about a given pixel : wheter it is coding and its brightness.
@requires : 'i' and 'j' respect the shape of *pImg
@assigns : nothing
@ensures : prints some piece of information of the (i, j) pixel         */
void print_pixel (image *pImg, int i, int j) {

    // printing RGB components
    printf("{%d, %d, %d}. ", pImg->mat[i * pImg->w + j][0], pImg->mat[i * pImg->w + j][1], pImg->mat[i * pImg->w + j][2]);

    // if the pixel is coding,
    if (isCoding(pImg->mat[i * pImg->w + j])) {
        // printing its coding color
        printf("Couleur codante (%s).\n", whichCoding(pImg->mat[i * pImg->w + j]));
        return;
    
    // if not (either passing or coding),
    } else {
        // get its brightness
        int bright = brightness(pImg->mat[i * pImg->w + j]);
        // prints it
        printf("Luminosité : %d. ", (int)bright);
        // prints wether it is passing or blocking
        if (isPassing(pImg->mat[i * pImg->w + j])) {
            printf("Couleur passante.\n");
        } else {
            printf("Couleur bloquante.\n");
        }
    }
}
