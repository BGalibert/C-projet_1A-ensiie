#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "image.h"
#include "bloc.h"
#include "couleur.h"
#include "interpreteur.h"
#include "actions.h"
#include "step.h"
#include "print.h"


/*
The functions BEFORE the 'main' one are used ONLY for the BONUS debugging environment.
To simplify a bit the 'main' function, here is a function which asks the user if they wants to perform
the next step of the programm (by entering 'n'), or if they want to quit it ('q'). 

But first, as the 'step' function can also ask the user some stdin ('in_nombre' or 'in_char' actions),
the input buffer needs to be cleared after each scanf, 
or 'in_nombre' or 'in_char' might get some value accidentally left in the buffer.

@requires : nothing
@assigns : nothing
@ensures : clear the input buffer to avoid any input problem during a step.      */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


/*
That being done, we can write our function to get the user's desire.
@requires : nothing
@assigns : nothing
@ensures : returns 'n' or 'q' according to the user's desire to continue the programm.      */

// 'userWidth' is only given for stdout presentation purpose.
char userNext(int userWidth) {

    // declaration of the character to be returned
    char charIn;

    // stdout presentation
    printf("\n\n");
    for (int i = 0; i < userWidth / 8; i++) {
        printf("-");
    }

    // asking the user for a character
    printf(">  Entrez 'n' pour passer à l'étape suivante, ou 'q' pour quitter. (n/q) : ");
    scanf(" %c", &charIn);
    // cleaning the input buffer
    clearInputBuffer();  

    // keep asking the user until we get either a 'n' or a 'q'
    while (charIn != 'n' && charIn != 'q') {
        printf("Caractère non reconnu. Entrez 'n' pour lancer l'étape suivante, 'q' pour quitter. (n/q) : ");
        scanf(" %c", &charIn);
        clearInputBuffer();  // Ajoutez cette ligne également ici.
        printf("\n");
    }

    // stdout presentation
    for (int i = 0; i < userWidth; i++) {
        printf("-");
    }
    printf("\n\n");

    // returning 'n' or 'q'
    return charIn;
}




/*____________________________________________________________________________________________________________________

                                                'MAIN' FUNCTION
____________________________________________________________________________________________________________________*/


int main (int argc, char **argv) {

    /*  The programm has to execute the image given when calling the executable.
        Thus we have to get the file name through the 'argc' array.
        Instead of asking the user if they wants to enter the BONUS debugging environment, 
        and for them to directly have the output of their image when they just wants the result,
        the debugging environment is launched when specified when calling the executable.

        Usage :  ./executable  <relative/path/to/image. ppm / jpeg > 
        or :     ./executable  <relative/path/to/image. ppm / jpeg > -debog
        Thus, either 2 or 3 arguments.                                                          */


    // Verification of the arguments count
    if (argc < 2 || argc > 3) {
        printf("Usage :  ./executable  <relative/path/to/image.ppm>  (-debog)\n");
        return 1;
    }

    // --------------------------------------------------------------------------------------
    // Getting the pixel array.

    // Get the file name for better visibility
    const char *file_name = argv[1];

    // Get wether it is a .ppm or a .jpeg image
    int isPPM = ppmOrJpeg(file_name);

    // Declaration of a struct image variable
    image *pImg;

    // If file_name is in PPM format :
    if (isPPM) {
        // get the pixels array thanks to the ppm conversion function.
        pImg = ppmToImage(file_name);
    // If it is in JPEG format :
    } else if (isPPM == 0) {
        // use instead the jpeg conversion one.
        pImg = jpegToImage(file_name);
    // Returns an error if file_name is neither one nor the other.
    } else {
        printf("Format d'image non reconnu.\n");
        return 1;
    }
    // Pixels array gotten ---------------------------------------------------------------
    

    // Initialization of the (although technically "an") interpretor
    interpreteur inter;
    inter_init(&inter);   


    /*
    "file_name" is executed thanks to a while loop.
    Its ending condition is that 8 blocking neighbors are met from a same bloc.
    As the behavior of the program is undifined if a bloc entirely crosses the image (thus being infinite 
        because of the torus topology), 
    it is supposed that no image given to the programm contains such an infinite bloc.
    However, the ending of the loop is not guaranted by the program.

    The rest of the 'main' function is devided into two possibilities :
        1) the programm has been called with the image as only argument,
            in which case we simply call the 'step' function until we somewhere meet 8 blocking neighbors.
        2) the "-debog" option has been specified, entering the BONUS debugging environment.
            The loop still works the same way, but it calls the 'step_print' function,
            and print a lot of information on the stdin.
    */

    // Case 1 : only the file_name has been given.
    if (argc == 2) {
        // Set a counter for blocking neighbors to 0,
        int countBloquantes = 0;
        // and while it doesn't reach 8 (which is supposed to eventually happen)
        while (countBloquantes < 8) {
            // do a step of the execution.
            step(pImg, &inter, &countBloquantes);
        }
    } 
    
    // Case 2 : a second argument has been given.
    else {
        // if this second argument is not "-debog",
        if (strcmp(argv[2], "-debog") != 0) {
            // print an usage error message,
            printf("Usage : ./executable <relative/path/to/image.ppm> -debog\n");
            // and exit with failure.
            return 1;
        }

        // -----------------------------------------------------------------------------------------------------------------|
        // If the second argument is "-debog", and we launch the BONUS DEBUGGING ENVIRONMENT.

        /* 
        When debugging, it can be helpful to literally "see" where the interpretor actually goes when it moves.
        But if the image is too wide, it cannot be correctly printed on the stdout.
        That is why we start by asking the user to give their screen width, 
        by printing a continuous line in the stdout. The last number they sees on their screen
        is the amount of characters that can fit on a line.
        */
        int userWidth;
        printf("\nBienvenue dans l'environnement de débogage !\n\n");
        printf("Pour savoir s'il est possible d'afficher entièrement l'image '%s' sur l'écran,\n", file_name);
        printf("veuillez indiquer le dernier nombre que vous voyez ENTIÈREMENT sur la première ligne :\n\n");
        printf("--------10--------20--------30--------40--------50--------60--------70--------80--------90-------100-------110-------120-------130-------140-------150-------160-------170-------180-------190-------200-------210-------220-------230-------240-------250-------260-------270-------280-------290------300\n\n");
        printf("Dernier nombre compris ENTIÈREMENT sur la ligne : ");
        scanf("%d", &userWidth);
        printf("\n\n");

        /*
        As the 'print_image' function requires 3 characters for each pixel, 
        we store in a boolean variable if the screen is wide enough to display the image.   */
        int boolPrint = (userWidth > 3 * pImg->w);

        // We inform the user wether the image will be printed in the stdout or not.
        if (!boolPrint) {
            printf("L'affichage de l'image nécessitant en largeur 3 emplacements de caractères par pixel,\n");
            printf("'%s', de dimension (%d x %d), est trop grande, et ne sera donc pas affichée sur l'écran.\n\n", file_name, pImg->h, pImg->w);
        } else {
            printf("L'écran est suffisamment large pour afficher %s.\n", file_name);
            printf("Les lettres correspondent aux couleurs, 'c' pour clair, 'f' pour foncé.\n");
            printf("' . ' représente une couleur passante, ' | ' une bloquante.\n");
        }


        // Initial image. Giving the function -1, -1 indicates there is no particular pixel to emphasize on. 
        print_image (boolPrint, pImg, -1, -1);

        
        /*
        We ask the user confirmation before performing the first step of the programm,
        by asking them to enter either 'n' for next, or 'q' for quit.
        As long as the user enters anything else, we keep asking them 'n' or 'q'.   
        The multiple printf are for visibility purpose.         */

        // character declaration
        char userBegin;

        // stdout presentation
        for (int i = 0; i < userWidth / 8; i++) {
            printf("-");
        }

        // asking for 'n' or 'q'
        printf(">  Entrez 'n' pour exécuter '%s', ou 'q' pour quitter. (n/q) : ", file_name);

        // getting their stdin
        scanf(" %c", &userBegin);

        printf("\n\n");

        // ask again until they answer either 'n' or 'q'
        while (userBegin != 'n' && userBegin != 'q') {
            printf("Caractère non reconnu. Entrez 'n' pour lancer l'étape suivante, 'q' pour quitter. (n/q) : ");
            scanf(" %c", &userBegin);
            printf("\n\n");
        } 

        // if they entered 'q',
        if (userBegin == 'q') {
            printf("\nArrêt du programme. Aucune étape réalisée.\n");
            // do nothing for the rest of the programm, as we don't enter the 'else' condition.
        }
        
        // if they entered 'n', we begin the execution of the image.
        else {

            // stdout presentation
            for (int i = 0; i < userWidth / 3; i++) {
                printf("-");
            }
            printf(" DÉBUT DE L'EXÉCUTION DE %s ", file_name);
            for (int i = 0; i < userWidth / 3; i++) {
                printf("-");
            }
            printf("\n\n");

            // printing of the initial state of the interpretor
            print_image (boolPrint, pImg, 0, 0);
            printf("  ETAT INITIAL.\n     Interpreteur en (0, 0).\n     direction : Est, à babord.\n\n");

            // declaration of the variables needed for the loop
            int countBloquantes = 0;
            int appelsStep = 1;
            char userContinue = userNext(userWidth);
        
            // whe perform the following step as long as we don't meet 8 blocking neighbor 
            // AND as long as the user doesn't ask for the programm to stop (by entering 'q')
            while (countBloquantes < 8 && userContinue == 'n') {
                // printing of 
                printf("  ÉTAPE %d.\n", appelsStep);
                print_image (boolPrint, pImg, inter.i, inter.j);
                printf("     Interpreteur en (%d, %d) : ", inter.i, inter.j);
                print_pixel(pImg, inter.i, inter.j);
                printf("     direction : %s, à %s.\n", intToDir(inter.dir), intToBord(inter.bord));
                printf("     Actuellement, le compteur de voisines bloquantes successives est à : %d\n", countBloquantes);
                printf("     État de la pile : ");
                stack_print(inter.pS);

                // performing the step, and printing what is done during it
                step_print(pImg, &inter, &countBloquantes, boolPrint);

                // printinf the final state of the interpretor
                printf("     Fin de l'étape: (%d, %d), dir = %s, bord = %s, compteur de bloquantes = %d\n", inter.i, inter.j, intToDir(inter.dir), intToBord(inter.bord), countBloquantes);
                
                // incrementing the steps count
                appelsStep++;

                // asking the user if they desire to continue the execution of the programm
                userContinue = userNext(userWidth);
            }

            // we quitted the while loop, so either we've reached 8 blocking neighbor, or the user asked for its end.

            // if we've reached 8 neighbors,
            if (countBloquantes == 8) {
                // we print the total amount of steps performed
                printf("\nArrêt du programme, puisque 8 couleurs bloquantes ont été rencontrées successivement.\n");
                printf("La lecture de  %s  a nécessité  %d  étapes.\n", file_name, appelsStep);
                printf("\n");
            }
            // if the end has been asked by the user,
            else {
                // we remind them during wich step they stopped the programm.
                printf("Arrêt du programme demandé, lors du  %de  appel.\n", appelsStep);
            }
        }
    }


    // Last but not least : MEMORY DEALLOCATION :

    // memory allocated for the stack of the interpretor,
    free(inter.pS);

    // and for the pixels array.
    free(pImg->mat);
    free(pImg);
    
    // successfully exit the 'main' function
    return 0;
}