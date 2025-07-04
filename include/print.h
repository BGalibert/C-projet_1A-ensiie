#ifndef PRINT_H
#define PRINT_H

#include "image.h"


/*____________________________________________________________________________________________________________________

    This file contains some printing functions used in the BONUS debugging environment,
    and a few auxiliary functions they require.
____________________________________________________________________________________________________________________*/



/*
@requires : dir is the integer 'dir' of the interpretor (so it equals 0, 1, 2 or 3)
@assigns : nothing
@ensures : returns the name of the direction corresponding to the given integer */
char* intToDir (int dir);

/*
@requires : 'bord' is the 'bord' value of the interpretor (so it equals -1 or 1)
@assigns : nothing
@ensures : returns the name of the edge corresponding to the given integer  */
char* intToBord (int bord);

/*
@requires : 'color' is a coding color
@assigns : nothing
@ensures : prints the abreviated name of 'color', to build an image characters-representation   */
void printColor(pixel color);

/*
Almost the same function, but for a totally different purpose : this time it is not for the image printing, 
but to print the color the interpretor is located on.
@requires : 'color' is a coding color
@assigns : nothing
@ensures : returns the full name of the given color     */
char* whichCoding(pixel color);


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

void print_image (int boolPrint, image *pImg, int x, int y);

/*
Finally, here is a function to print some information about a given pixel : wheter it is coding and its brightness.
@requires : 'i' and 'j' respect the shape of *pImg
@assigns : nothing
@ensures : prints some piece of information of the (i, j) pixel         */
void print_pixel (image *pImg, int i, int j);


#endif