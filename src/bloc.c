#include <stdio.h>
#include <stdlib.h>

//#include "stack.h"
//#include "image.h"
#include "bloc.h"
#include "couleur.h"


/*________________________________________________________________________________________________________________________

    This file contains the functions used to get the caracteristics of the bloc 
    where the interpretor is located at a given step of the image.ppm execution.
    There are :
        1) a few utilitary functions
        2) a preliminary treatment function called 'traitement'.
        3) the function which transforms the traited information to a bloc_caracteristics.
        4) the 'getBloc' function which sums up everything.
_________________________________________________________________________________________________________________________*/



// 4 functions to move in every direction in the image, as the image is a torus -------------------------------------------

/*
@requires : pImg points to a valid image
@assigns : *pImg
@ensures : increments the int 'h' of *pImg, with the fact that (pImg->h - 1) + 1 = 0, as the image is a torus    */
int incr_i(image *pImg, int i) {
    return (i + 1) % pImg->h;
}

/*
@requires : pImg points to a valid image
@assigns : *pImg
@ensures : decrements the int 'h' of *pImg, with the fact that 0 - 1 = (pImg->h - 1), as the image is a torus    */
int decr_i(image *pImg, int i) {
    // we add (+ pImg->h) to the left member to avoid any negative result of the modulo
    return (i - 1 + pImg->h) % pImg->h;
}

/*
@requires : pImg points to a valid image
@assigns : *pImg
@ensures : increments the int 'w' of *pImg, with the fact that (pImg->w - 1) + 1 = 0, as the image is a torus    */
int incr_j(image *pImg, int j) {
    return (j + 1) % pImg->w;
}

/*
@requires : pImg points to a valid image
@assigns : *pImg
@ensures : decrements the int 'w' of *pImg, with the fact that 0 - 1 = (pImg->w - 1), as the image is a torus    */
int decr_j(image *pImg, int j) {
    // we add (+ pImg->w) to the left member to avoid any negative result of the modulo
    return (j - 1 + pImg->w) % pImg->w;
}
// ----------------------------------------------------------------------------------------------------------------------



/*
The following 'traitement' function requieres an array of the same shape as the image, 
filled with booleans indicating wether the pixel at (i, j) has already been treated or not.
To clarify the following functions, here is a function that returns a so-called 'traited' array.
The struct traited is defined in "bloc.h" as :

    typedef struct {
        int h;
        int w;
        int* tab;
    } traited;

@requires : pImg points to a valid image
@assigns : *traites, dynamically alocated 
@ensures : returns a struct traited array with the shape of *pImg   */

traited *imgToTraited(image *pImg) {
    traited *traites = (traited *)malloc(sizeof(traited));
    traites->h = pImg->h;
    traites->w = pImg->w;
    traites->tab = (int *)malloc(traites->h * traites->w * sizeof(int));
    return traites;
}


/*
When we arrive to a new bloc, we need to find the coordinates of the good corner to go.
As it is not longer to get all the corner than to get only one (both have a complexity in O(height * width) ),
we get all of them at once.
This function does the preliminary traitement of the bloc.
It starts at the initial coordinates, and goes recursively in all 4 directions 
to determine the borders of the bloc (by filling the 'traites' array).
It always ends as it is supposed that no image contains an infinite bloc.
For each new pixel reached, if it is beyond the pre-determined farest pixel of the bloc in a direction,
we update that new farest row/column reached (values stocked in the given struct extrem, defined in "bloc.h" as :

    typedef struct extrem {
        int size;
        int e, s, w, n;
    } extrem; )

@requires : pImg, traites and extrm point respectively to valid image, traited and extrem
@asigns : *extrm, *traites
@ensures : at the end of the recursion, '*traites' contains every coordinates of the pixels of the bloc,
                                        and 'extrm' contains    the farest pixel in each direction 
                                                                and the size of the bloc    */
void traitement(image *pImg, int i, int j, traited *traites, pixel color, extrem *extrm) {
    // we mark the pixel (i, j) as traited
    traites->tab[i * pImg->w + j] = 1;
    // if this new pixel is of the right color, it belongs to the bloc (as next to the bloc), so :
    if (isColoredBy(pImg->mat[i * pImg->w + j], color)) {
        // we increments the size of the bloc
        extrm->size++;
        // There are 2 conditions to update the farest pixel of the bloc in a given direction (here South) :
        //  (i)  be further south than the precedent candidate
        //  (ii) the next pixel to the south is a different color (otherwise it is not a border) 
        // If these 2 conditions are met,
        if (i > extrm->s && !isColoredBy(pImg->mat[incr_i(pImg, i) * pImg->w + j], color)) {
            // we update the South border candidate
            extrm->s = i;
        }
        // we do the same thing for the 3 other direction.
        // North
        if (i < extrm->n && !isColoredBy(pImg->mat[decr_i(pImg, i) * pImg->w + j], color)) {
            extrm->n = i;
        }
        // East
        if (j > extrm->e && !isColoredBy(pImg->mat[i * pImg->w + incr_j(pImg, j)], color)) {
            extrm->e = j;
        }
        // West
        if (j < extrm->w && !isColoredBy(pImg->mat[i * pImg->w + decr_j(pImg, j)], color)) {
            extrm->w = j;
        }

        // Once the current pixel treated, we treat its neighbors recursively
        // if the pixel to the south has not already be treated,
        if (traites->tab[incr_i(pImg, i) * traites->w + j] != 1) {
            // we treat it (recursively)
            traitement(pImg, incr_i(pImg, i), j, traites, color, extrm);
        }
        // We do the same thing for the 3 other direction.
        // North
        if (traites->tab[decr_i(pImg, i) * traites->w + j] != 1) {
            traitement(pImg, decr_i(pImg, i), j, traites, color, extrm);
        }
        // East
        if (traites->tab[i * traites->w + incr_j(pImg, j)] != 1) {
            traitement(pImg, i, incr_j(pImg, j), traites, color, extrm);
        }
        // West
        if (traites->tab[i * traites->w + decr_j(pImg, j)] != 1) {
            traitement(pImg, i, decr_j(pImg, j), traites, color, extrm);
        }
    }
}
// -----------------------------  end of the 'traitement' function -----------------------------------------


/*
As declaring a new bloc_caract 'bloc' fills its coordinates with pre-existing values, 
they need to be initialized in order to be used.
To clarify the declaration of a new bloc in the 'extrmToBloc' function, here is a function that initializes them.

@requires : pBloc points to a valid bloc_caract, and pImg to a valid image
@assigns : *pBloc
@ensures :  initializes every coordinate of *pBloc, for it to be ready to be treated   */

void initBloc(bloc_caract *pBloc, image *pImg) {
    // the East-"babord" corner is the top-right one.
    // To find its right coordinates, we use in the 'traitement' function 
    // an algorythm to find     (i)  the eastern pixel of the bloc
    //                          (ii) the highest pixel in this East border
    // Thus the East-"babord" row has necessarily an index < pImg->h,
    // hence its initialization to pImg->h + 1 (just to be sure)
    pBloc->Eb.i = pImg->h +1;
    // For the same reason, the East-"babord" column has an index necessarily > 0, hence :
    pBloc->Eb.j = -1;
    // We apply the same reasonning for the 7 other extremae.
    // East-tribord
    pBloc->Et.i = -1;
    pBloc->Et.j = -1;
    // South
    pBloc->Sb.i = -1;
    pBloc->Sb.j = -1;
    pBloc->St.i = -1;
    pBloc->St.j = pImg->w +1;
    // West
    pBloc->Wb.i = -1;
    pBloc->Wb.j = pImg->w +1;
    pBloc->Wt.i = pImg->h +1;
    pBloc->Wt.j = pImg->w +1;
    // North
    pBloc->Nb.i = pImg->h +1;
    pBloc->Nb.j = pImg->w +1;
    pBloc->Nt.i = pImg->h +1;
    pBloc->Nt.j = -1;
}


/*
Now the preliminary traitement done (thanks to the 'traitement' function),
we can create our current struct bloc_caract, defined in "bloc.h" as

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

and where a point is also defined in "bloc.h" as :

    typedef struct point {
        int i;
        int j;
    } point;

The idea is, for each direction, to go all over the row/column indicated as a border, 
and to get the index of the first and last pixel.

@requires : img points to a valid image
@assigns : *pBloc (dynamically allocated)
@ensures : returns the bloc_caract of the current bloc  */

bloc_caract *extremToBloc(image *img, traited traites, pixel color, extrem extrm) {
    // Memory allocation
    bloc_caract *pBloc = malloc(sizeof(bloc_caract));
    // initialization of the coordinates
    initBloc(pBloc, img);
    // the easy part : the bloc size is the one got by 'extrm' 
    pBloc->size = extrm.size;

    // declaration of the variables used for all 4 directions.
    // lin and col will be the index used to go over the rows/columns
    // min and max will respectively stock the coordinate of the first and last pixel of each border
    int min, max, lin, col;

// EAST. 
    // The columned is fixed to the extrm.e value (=> col = extrm.e)
    // We go all over the 'extrem.e' column (=> lin variable)
    lin = 0;
    // Necessarily, min < img->h, so we initialize min to that value
    min = img->h;
    // Again, max >= 0
    max = 0;
    // The first pixel of the East border is the first pixel which meets 3 conditions :
    //      (i)   it is the right color
    //      (ii)  it has been traited (it could be another bloc of the same color, located before on that column)
    //      (iii) the pixel further to the East is another color (otherwise it is not on the East border)
    // After beeing traited by the 'traitement' function, at least one pixel of the 'extrem.e' column
    // simultaneously meets these 3 conditions, hence the ending of the loop.
    // Thus, while these 3 conditions are not simultaneously met,
    while (!(traites.tab[lin * traites.w + extrm.e] == 1 && isColoredBy(img->mat[lin * img->w + extrm.e], color) && !isColoredBy(img->mat[lin * img->w + incr_j(img, extrm.e)], color))) {
        // we keep going over the column.
        lin++;
    }
    // The loop ended at the first corresponding pixel, so 'lin' is the 'min' we were looking for.
    min = lin;
    // To find the last corresponding pixel, we keep going until the end of the column,
    for (lin = lin; lin < img->h; lin++) {
        // and if the pixel we are looking at simultaneously meets the 3 conditions,
        if (traites.tab[lin * traites.w + extrm.e] == 1 && isColoredBy(img->mat[lin * img->w + extrm.e], color) && !isColoredBy(img->mat[lin * img->w + incr_j(img, extrm.e)], color)) {
            // we update our 'max' value
            max = lin;
        }
    }
    // We have now our 4 East coordinates, so we assigns our *pBloc :
    // East-"babord"
    pBloc->Eb.i = min;
    pBloc->Eb.j = extrm.e;
    // East-tribord
    pBloc->Et.i = max;
    pBloc->Et.j = extrm.e;


// We now repeat the same exact process for the 3 other directions.
    
// WEST. col = extrm.w fixed, lin variable
    lin = 0;
    // min < img->h
    min = img->h;
    // max >= 0
    max = 0;
    // Research of the min
    while (!( traites.tab[lin * traites.w + extrm.w] == 1 && isColoredBy(img->mat[lin * img->w + extrm.w], color) && !isColoredBy(img->mat[lin * img->w + decr_j(img, extrm.w)], color))) {
        lin++;
    }
    min = lin;
    // Research of the max
    for (lin = lin; lin < img->h; lin++) {
        if (traites.tab[lin * traites.w + extrm.w] == 1 && isColoredBy(img->mat[lin * img->w + extrm.w], color) && !isColoredBy(img->mat[lin * img->w + decr_j(img, extrm.w)], color)) {
            max = lin;
        }
    }
    // Assignement
    // This time, 'max' is the index of the West-"babord" and not "tribord", as West is a 180° rotation from East
    pBloc->Wb.i = max;
    pBloc->Wb.j = extrm.w;
    // West-tribord
    pBloc->Wt.i = min;
    pBloc->Wt.j = extrm.w;

// NORTH. lin = extrm.n fixed, col variable
    col = 0;
    // min < img->w
    min = img->w;
    // max >= 0
    max = 0;
    // Research of the min
    while (!( traites.tab[extrm.n * traites.w + col] == 1 && isColoredBy(img->mat[extrm.n * img->w + col], color) && !isColoredBy(img->mat[decr_i(img, extrm.n) * img->w + col], color))) {
        col++;
    }
    min = col;
    // Research of the max
    for (col = col; col < img->w; col++) {
        if (traites.tab[extrm.n * traites.w + col] == 1 && isColoredBy(img->mat[extrm.n * img->w + col], color) && !isColoredBy(img->mat[decr_i(img, extrm.n) * img->w + col], color)) {
            max = col;
        }
    }
    // Assignement
    pBloc->Nb.i = extrm.n;
    pBloc->Nb.j = min;
    pBloc->Nt.i = extrm.n;
    pBloc->Nt.j = max;

// SOUTH. lin = extrm.s fixed, col variable
    col = 0;
    // min < img->w
    min = img->w;
    // max >= 0
    max = 0;
    // Research of the min
    while (!( traites.tab[extrm.s * traites.w + col] == 1 && isColoredBy(img->mat[extrm.s * img->w + col], color) && !isColoredBy(img->mat[incr_i(img, extrm.s) * img->w + col], color))) {
        col++;
    }
    min = col;
    //Research of the max
    for (col = col; col < img->w; col++) {
        if (traites.tab[extrm.s * traites.w + col] == 1 && isColoredBy(img->mat[extrm.s * img->w + col], color) && !isColoredBy(img->mat[incr_i(img, extrm.s) * img->w + col], color)) {
            max = col;
        }
    }
    // Assignement
    pBloc->Sb.i = extrm.s;
    pBloc->Sb.j = max;
    pBloc->St.i = extrm.s;
    pBloc->St.j = min;

    return pBloc;
}
// end of the 'extremToBloc' function -------------------------------------------------------------------------------------



/*
Finaly, the function that sums up everything :
which returns the bloc_caract from the image and the interpretor current location

@requires : pImg and pInter point respecively to a valid image and interpretor
@assigns : a bloc_caract dynamically allocated
@ensures : returns the caracteristics of the bloc where the interpretor is      */
bloc_caract *getBloc(image *pImg, interpreteur *pInter) {
    // Declaration of a stuct extrem
    extrem extrm;
    // Initilization of its values
    extrm.size = 0;
    extrm.e = 0;
    extrm.s = 0;
    extrm.w = pImg->w - 1;
    extrm.n = pImg->h - 1;
    // Creation for a traited array with the shape of *pImg
    traited *pTraites = imgToTraited(pImg);
    // Does the preliminary treatment
    traitement(pImg, pInter->i, pInter->j, pTraites, pImg->mat[pInter->i * pImg->w + pInter->j], &extrm);
    // returns the bloc_caract from the gotten extrem
    bloc_caract *pBloc = extremToBloc(pImg, *pTraites, pImg->mat[pInter->i * pImg->w + pInter->j], extrm);
    free(pTraites->tab);
    //free(pTraites);
    return pBloc;
}

