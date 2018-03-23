typedef struct _pixel {
    unsigned short int r;
    unsigned short int g;
    unsigned short int b;
} Pixel;

typedef struct _image {
    // pixel[width][height]
    Pixel pixel[512][512];
    unsigned int w;
    unsigned int h;
} Image;
