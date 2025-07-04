#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


typedef unsigned char pixel[3];

typedef struct image {
    int w;
    int h;
    pixel *mat;
} image;



do 

do {
    fgets(buffer, sizeof(buffer), file);
} while (buffer[0] == '#');


typedef struct interpreteur {
    int i;
    int j;
    int dir;
    int bord;
    stack *pS;
} interpreteur;


typedef struct stack {
    int top;
    int size;
    int *tab;
} stack;

void stack_init (stack *s);
void stack_free (stack *s);
int stack_size (stack *s);
stack* stack_empty(void);
int stack_isEmpty (stack *s);
void stack_resize(stack *s, int new_size);
void stack_push (stack *s, int elem);
int stack_pop (stack *s);
void stack_print (stack *s);



pixel rouge = {255, 0, 0};
pixel vert = {0, 255, 0};
pixel bleu = {0, 0, 255};



int diffColor (pixel arrivee, pixel depart){
    return (whichColor(arrivee) - whichColor(depart) + 6) % 6;
}



int codeAction (pixel colArriv, pixel colDepart) {
    return diffColor(colArriv, colDepart) * 10 + diffBright(colArriv, colDepart);
}


int incr_i(image *pImg, int i) {
    return (i + 1) % pImg->h;
}


if if (traites.tab[lin * traites.w + extrm.e] == 1 
        && isColoredBy(img->mat[lin * img->w + extrm.e], color) 
        && !isColoredBy(img->mat[lin * img->w + incr_j(img, extrm.e)], color))


int countBloquantes = 0;
while (countBloquantes < 8) {
    step(pImg, &inter, &countBloquantes);
}


void plus_grand (interpreteur *inter) {
    if (stack_size(inter->pS) < 2) {
        return;
    }
    int premier = stack_pop(inter->pS);
    int second = stack_pop(inter->pS);
    stack_push(inter->pS, (second > premier) ); 
}

stack_push(inter->pS, (second > premier) ); 


pixel rouge = {255, 0, 0};