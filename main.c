
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} RGBPixel;



char intensity_to_ascii(uint8_t intensity) {
    char ascii_chars[] = "@#%xo;:,. ";
    int num_chars = sizeof(ascii_chars) - 1;
    int index = intensity * num_chars / 256;
     return ascii_chars[index];
}

void read_bmp(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    
    long bsize = ftell(file);

    fseek(file, 10, SEEK_SET);
    int offset; 
    fread(&offset, sizeof(int), 1, file);
    printf("offset %i\n",offset);
    fseek(file, 18, SEEK_SET);
    int width, height;
    fread(&width, sizeof(int), 1, file);
    fread(&height, sizeof(int), 1, file);
    
    
    fseek(file, offset, SEEK_SET); 
    size_t size = width * height;

    RGBPixel* pixels = (RGBPixel*)malloc(bsize* sizeof(RGBPixel));
    uint8_t* grayscale = (uint8_t*)malloc(bsize* sizeof(uint8_t));
    fread(pixels, sizeof(RGBPixel), bsize, file);


    for (int i = 0; i < bsize; i++) {
        grayscale[i] = 0.2126 * pixels[i].red +  0.7152 *pixels[i].green + 0.0722 * pixels[i].blue;
    }
         

    for(int y = height - 1; y > 0; --y)
    {
        for (int x = 0; x < width; ++x) 
	{
            printf("%c", intensity_to_ascii(grayscale[x + width * y] ));
        }
        printf("\n");
    }    

    free(pixels);
    free(grayscale);
    fclose(file);
}



int main() {
    const char* filename = "/mnt/c/Users/Poe/Downloads/bulm.bmp";
    read_bmp(filename);
    return 0;
}
