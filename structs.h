typedef struct _pixel {
    unsigned short int r;
    unsigned short int g;
    unsigned short int b;
} Pixel;

typedef struct _image {
    // 0 -> r
    // 1 -> g
    // 2 -> b
    // pixel[width][height][rgb]
    unsigned short int pixel[512][512][3];
    unsigned int w;
    unsigned int h;
} Image;
