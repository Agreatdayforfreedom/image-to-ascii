
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} RGBPixel;



char intensity_to_ascii(uint8_t intensity) {
    char ascii_chars[] = "..,:;ox%#@";
    int num_chars = sizeof(ascii_chars) - 1;
    int index = intensity * num_chars / 256;
    // return ascii_chars[index];
    if(intensity < 25) {
        return ascii_chars[9];
    } else if (intensity < 50) {
        return ascii_chars[8];
    }else if (intensity < 75) {
        return ascii_chars[7];
    } else if (intensity < 100) {
        return ascii_chars[6];
    } else if (intensity < 125) {
        return ascii_chars[5];
    }else if (intensity < 150) {
        return ascii_chars[4];
    }else if (intensity < 175) {
        return ascii_chars[3];
    }else if (intensity < 200) {
        return ascii_chars[2];
    }else if (intensity < 250) {
        return ascii_chars[1];
    } else {
        return ascii_chars[0];
    }
}


void read_bmp(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }


    fseek(file, 18, SEEK_SET);
    int width, height;
    fread(&width, sizeof(int), 1, file);
    fread(&height, sizeof(int), 1, file);
    printf("w: %i, h: %i", width, height);

    fseek(file, 10, SEEK_CUR); 

    RGBPixel* pixels = (RGBPixel*)malloc(width * height * sizeof(RGBPixel));
    int8_t* grayscale = (uint8_t*)malloc(width * height * sizeof(uint8_t));
    fread(pixels, sizeof(RGBPixel), width * height, file);


    for (int i = 0; i < width * height; i++) {
        grayscale[i] = 0.2126 * pixels[i].red +  0.7152 *pixels[i].green + 0.0722 * pixels[i].blue;
    }
    // printf("Pixel 0: R=%d, G=%d, B=%d\n", pixels[10].red, pixels[10].green, pixels[10].blue);
    //     printf("%i\n",grayscale[10]);
    // for (int i = 0; i < width * height; i++) {
    //     printf("%i\n",grayscale[i]);
    // }
         

    for(int y = height; y > 0; y-=2)
    {
        for (int x = width; x > 0; x-=2)
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
