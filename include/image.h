#ifndef IMAGE_H
#define IMAGE_H


/*_________________________________________________________________________________________________________________________

    This file contains eveything relative to the gestion of the image (the printing part is written in "print.h") : 
        1) Definitions for pixels, and for the image structure
        2) A function 'ppmToImage' which opens the file.ppm whose name is given, and returns the array of 'pixel'
        3) A function that does the exact same thing for the JPEG images,
            and finaly a function to tests if the given file is in PPM or JPEG format, 
            to know which opening function to use.
___________________________________________________________________________________________________________________________*/


/*
Implementation for pixels.
A pixel is an array of 3 integer between 0 and 255, which is exactly an unsigned char, so :       */
typedef unsigned char pixel[3];


/*
An image is nothing but an array of pixels. 
However, creating a structure for it was convinient as it allows to keep its height and width in a single memory adress.
We chose to use a 1-dimensional array, where the (i, j) pixel is accessed by img[i * width + j]
*/
typedef struct image {
    int w;
    int h;
    pixel *mat;
} image;


/*
The function that allocates memory for an array of pixel, opens the given file and copies its pixels to the array.
@requires : 'filename' is the correct path to the image.ppm file
@assigns : dynamically allocates memory for the array of pixels
@ensures : returns a pointer to the pixels array created     */
image* ppmToImage(const char* filename);

/*
Same function that 'ppmToImage', but this time for files in JPEG format.
It allocates memory for an array of pixel, opens the given file and copies its pixels to the array.
@requires : 'filename' is the correct path to the image.jpeg file
@assigns : dynamically allocates memory for the array of pixels
@ensures : returns a pointer to the pixels array created     */
image* jpegToImage(const char *filename);

/*
When given a file, we need to identify the format it is in, to call the right conversion function.
@requires : 'filename' is the correct path to the image.jpeg file
@assigns : nothing
@returns :  1 if the given file is in PPM format, 
            0 if it is in JPEG, 
            and -1 either the opening failed, or the image is not in format PPM nor JPEG    */
int ppmOrJpeg(const char *file_name);





#endif