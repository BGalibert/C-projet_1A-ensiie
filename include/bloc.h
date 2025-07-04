#ifndef BLOC_H
#define BLOC_H

#include "image.h"
#include "interpreteur.h"


/*________________________________________________________________________________________________________________________

    This file contains the functions used to get the caracteristics of the bloc 
    where the interpretor is located at a given step of the image.ppm execution.
    There are :
        1) a few utilitary functions
        2) a preliminary treatment function called 'traitement'.
        3) the function which transforms the traited information to a bloc_caracteristics.
        4) the 'getBloc' function which sums up everything.
_________________________________________________________________________________________________________________________*/





// 4 functions to move in every direction in the image, as the image is a tore -------------------------------------------

/*
@requires : pImg points to a valid image
@assigns : *pImg
@ensures : increments the int 'h' of *pImg, with the fact that (pImg->h - 1) + 1 = 0, as the image is a tore    */
int incr_i(image *pImg, int i);

/*
@requires : pImg points to a valid image
@assigns : *pImg
@ensures : decrements the int 'h' of *pImg, with the fact that 0 - 1 = (pImg->h - 1), as the image is a tore    */
int decr_i(image *pImg, int i);

/*
@requires : pImg points to a valid image
@assigns : *pImg
@ensures : increments the int 'w' of *pImg, with the fact that (pImg->w - 1) + 1 = 0, as the image is a tore    */
int incr_j(image *pImg, int j);

/*
@requires : pImg points to a valid image
@assigns : *pImg
@ensures : decrements the int 'w' of *pImg, with the fact that 0 - 1 = (pImg->w - 1), as the image is a tore    */
int decr_j(image *pImg, int j);
// -------------------------------------------------------------------------------------------------------------------




/*
The following 'traitement' function requieres an array of the same shape as the image, 
filled with booleans indicating wether the pixel at (i, j) has already been treated or not.
To clarify the following functions, here is a function that returns a so-called 'traited' array.
The struct traited is defined as :
*/
typedef struct traited {
    int h;
    int w;
    int* tab;
} traited; 
/*
@requires : pImg points to a valid image
@assigns : *traites, dynamically alocated 
@ensures : returns a struct traited array with the shape of *pImg   */
traited *imgToTraited(image *pImg);


/*
When we arrive to a new bloc, we need to find the coordinates of the good corner to go.
As it is not longer to get all the corner than to get only one (both have a complexity in O(height * width) ),
we get all of them at once.
This function does the preliminary traitement of the bloc.
It starts at the initial coordinates, and goes recursively in all 4 directions 
to determine the borders of the bloc (by filling the 'traites' array).
For each new pixel reached, if it is beyond the pre-determined farest pixel of the bloc in a direction,
we update that new farest row/column reached (values stocked in the given struct extrem, defined as :
*/
typedef struct extrem {
    int size;
    int e, s, w, n;
} extrem;
/*
@requires : pImg, traites and extrm point respectively to valid image, traited and extrem
@asigns : *extrm, *traites
@ensures : at the end of the recursion, '*traites' contains every coordinates of the pixels of the bloc,
                                        and 'extrm' contains    the farest pixel in each direction 
                                                                and the size of the bloc    */
void traitement(image *pImg, int i, int j, traited *traites, pixel color, extrem *extrm);



// To simplify the manipulation of coordinates, we difine a point structure :
typedef struct point {
    int i;
    int j;
} point;


// And here is a structure to stock all the corner of a bloc at one same memory adress :
typedef struct caracetistics_of_the_bloc {
    int size;
    // extremite at the East
    point Eb;
    point Et;
    //----------------- South
    point Sb;
    point St;
    //----------------- West
    point Wb;
    point Wt;
    // ---------------- North
    point Nb;
    point Nt;
} bloc_caract;



/*
As declaring a new bloc_caract 'bloc' fills its coordinates with pre-existing values, 
they need to be initialized in order to be used.
To clarify the declaration of a new bloc in the 'extrmToBloc' function, here is a function that initializes them.
@requires : pBloc points to a valid bloc_caract, and pImg to a valid image
@assigns : *pBloc
@ensures :  initializes every coordinate of *pBloc, for it to be ready to be treated   */
void initBloc(bloc_caract *pBloc, image *pImg);


/*
Now the preliminary traitement done (thanks to the 'traitement' function),
we can create our current struct bloc_caract.
The idea is, for each direction, to go all over the row/column indicated as a border, 
and to get the index of the first and last pixel.
@requires : img points to a valid image
@assigns : *pBloc (dynamically allocated)
@ensures : returns the bloc_caract of the current bloc  */
bloc_caract *extremToBloc(image *img, traited traites, pixel color, extrem extrm);


/*
Finaly, the function that sums up everything :
which returns the bloc_caract from the image and the interpretor current location
@requires : pImg and pInter point respecively to a valid image and interpretor
@assigns : a bloc_caract dynamically allocated
@ensures : returns the caracteristics of the bloc where the interpretor is      */
bloc_caract *getBloc(image *pImg, interpreteur *pInter);




#endif