#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

#include "image.h"

/*_________________________________________________________________________________________________________________________

    This file contains eveything relative to the gestion of the image (the printing part is written in "print.h") : 
        1) Definitions for pixels, and for the image structure
        2) A function 'ppmToImage' which opens the file.ppm whose name is given, and returns the array of 'pixel'
        3) A function that does the exact same thing for the JPEG images,
            and finaly a function to tests if the given file is in PPM or JPEG format, 
            to know which opening function to use.
___________________________________________________________________________________________________________________________*/


/*
Here are the 'pixel' and 'struct image' defined in "image.h" :

typedef unsigned char pixel[3];

typedef struct {
    int w;
    int h;
    pixel* tab;
} image;            */


/*
The function that allocates memory for an array of pixel, opens the given file and copies its pixels to the array.
@requires : 'filename' is the correct path to the image.ppm file
@assigns : dynamically allocates memory for the array of pixels
@ensures : returns a pointer to the pixels array created     */

image* ppmToImage(const char* filename) {

    // Opening the file in binary mode
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Variables declaration 
    char buffer[128];
    int width, height;

    // Verification of the 'P6' (binary) format.
    fgets(buffer, sizeof(buffer), file);
    if (strcmp(buffer, "P6\n")) {
        fprintf(stderr, "Le fichier n'est pas au format P6\n");
        exit(EXIT_FAILURE);
    }

    // Ignoring the eventual commentary lines (beginning with a '#') if there are some
    do {
        fgets(buffer, sizeof(buffer), file);
    } while (buffer[0] == '#');
    // this loop eventually ends as there cannot be an infinite amount of commentary lines

    // Getting the height and width of the image
    sscanf(buffer, "%d %d", &width, &height);

    // Declaration, memory allocation and initialization of our 'struct image'
    image* pImg = malloc(sizeof(image));
    pImg->w = width;
    pImg->h = height;
    pImg->mat = malloc(width * height * sizeof(pixel));

    // Ignoring the following line, which always indicates that the RGB components doesn't exceed 255
    fgets(buffer, sizeof(buffer), file);

    // Getting the values of the pixels
    fread(pImg->mat, sizeof(pixel), width * height, file);

    // Closing the file
    fclose(file);

    // Returning the pointer to the allocated struct image.
    return pImg;
}


/*
Same function that 'ppmToImage', but this time for files in JPEG format.
It allocates memory for an array of pixel, opens the given file and copies its pixels to the array.
@requires : 'filename' is the correct path to the image.jpeg file
@assigns : dynamically allocates memory for the array of pixels
@ensures : returns a pointer to the pixels array created     */

image* jpegToImage(const char *filename) {

    // Opening the file in binary mode
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening the file");
        exit(EXIT_FAILURE);
    }

    // Initialization of the required structures
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // Specify the source of the JPEG file
    jpeg_stdio_src(&cinfo, file);

    // Read the header of the JPEG file
    (void)jpeg_read_header(&cinfo, TRUE);

    // Start the decompression
    (void)jpeg_start_decompress(&cinfo);

    // Create an image structure
    image *img = (image *)malloc(sizeof(image));
    img->h = cinfo.output_height;
    img->w = cinfo.output_width;
    img->mat = (pixel *)malloc(img->h * img->w * sizeof(pixel));

    // Read the lines of the JPEG file
    while (cinfo.output_scanline < cinfo.output_height) {
        JSAMPLE *row_pointer[1];
        row_pointer[0] = (JSAMPLE *)(img->mat + cinfo.output_scanline * img->w);
        (void)jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish the decompression
    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    // Close the JPEG file
    fclose(file);

    return img;
}


/*
When given a file, we need to identify the format it is in, to call the right conversion function.
@requires : 'filename' is the correct path to the image.jpeg file
@assigns : nothing
@returns :  1 if the given file is in PPM format, 
            0 if it is in JPEG, 
            and -1 either the opening failed, or the image is not in format PPM nor JPEG    */

int ppmOrJpeg(const char *file_name) {

    // File opening in binary mode
    FILE *file = fopen(file_name, "rb");
    if (!file) {
        return -1;
    }

    // Headers file apparently generaly have a size of 4 bytes.
    unsigned char header[4]; 
    fread(header, sizeof(char), 4, file);
    fclose(file);

    // If the header corresponds to a PPM file one (ie it is "P6"), return 1
    if (header[0] == 'P' && header[1] == '6') {
        return 1;
    }

    // If the header corresponds to a PPM file one, return 0
    if (header[0] == 0xFF && header[1] == 0xD8 && header[2] == 0xFF && header[3] == 0xE0) {
        return 0;
    }

    // If neither of the PPM nor JPEG format has been recognized, return -1
    return -1;
}




