#include <stdio.h>

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


int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int pixel_igual(Pixel p1, Pixel p2) {
    if (p1.r == p2.r &&
        p1.g == p2.g &&
        p1.b == p2.b)
        return 1;
    return 0;
}

// grey scale filter
Image grey_scale(Image img) {
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            int average = img.pixel[i][j][0] +
                          img.pixel[i][j][1] +
                          img.pixel[i][j][2];
            average /= 3;
            img.pixel[i][j][0] = average;
            img.pixel[i][j][1] = average;
            img.pixel[i][j][2] = average;
        }
    }

    return img;
}

// sepia filter
Image sepia(Image img){
    for (unsigned int x = 0; x < img.h; ++x) {
        for (unsigned int j = 0; j < img.w; ++j) {
            unsigned short int pixel[3];
            pixel[0] = img.pixel[x][j][0];
            pixel[1] = img.pixel[x][j][1];
            pixel[2] = img.pixel[x][j][2];

            int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
            int min_r = (255 >  p) ? p : 255;
            img.pixel[x][j][0] = min_r;

            p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
            min_r = (255 >  p) ? p : 255;
            img.pixel[x][j][1] = min_r;

            p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
            min_r = (255 >  p) ? p : 255;
            img.pixel[x][j][2] = min_r;
        }
    }

    return img;
}

// mirroring filter
Image mirroring(Image img){
    int horizontal = 0;
    scanf("%d", &horizontal);

    int w = img.w, h = img.h;

    if (horizontal == 1) w /= 2;
    else h /= 2;

    for (int i2 = 0; i2 < h; ++i2) {
        for (int j = 0; j < w; ++j) {
            int x = i2, y = j;

            if (horizontal == 1) y = img.w - 1 - j;
            else x = img.h - 1 - i2;

            Pixel aux1;
            aux1.r = img.pixel[i2][j][0];
            aux1.g = img.pixel[i2][j][1];
            aux1.b = img.pixel[i2][j][2];

            img.pixel[i2][j][0] = img.pixel[x][y][0];
            img.pixel[i2][j][1] = img.pixel[x][y][1];
            img.pixel[i2][j][2] = img.pixel[x][y][2];

            img.pixel[x][y][0] = aux1.r;
            img.pixel[x][y][1] = aux1.g;
            img.pixel[x][y][2] = aux1.b;
        }
    }

  return img;
}

// blur filter
Image blur(Image img, int T) {
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            Pixel average = {0, 0, 0};

            int min_h = (img.h - 1 > i + T/2) ? i + T/2 : img.h - 1;
            int min_w = (img.w - 1 > j + T/2) ? j + T/2 : img.w - 1;

            for(int x = (0 > i - T/2 ? 0 : i - T/2); x <= min_h; ++x) {
                for(int y = (0 > j - T/2 ? 0 : j - T/2); y <= min_w; ++y) {
                    average.r += img.pixel[x][y][0];
                    average.g += img.pixel[x][y][1];
                    average.b += img.pixel[x][y][2];
                }
            }

            average.r /= T * T;
            average.g /= T * T;
            average.b /= T * T;

            img.pixel[i][j][0] = average.r;
            img.pixel[i][j][1] = average.g;
            img.pixel[i][j][2] = average.b;
        }
    }

    return img;
}

// rotate 90 degrees right
Image rotation(Image img) {
    Image rotated;

    rotated.w = img.h;
    rotated.h = img.w;

    for (unsigned int i = 0, y = 0; i < rotated.h; ++i, ++y) {
        for (int j = rotated.w - 1, x = 0; j >= 0; --j, ++x) {
            rotated.pixel[i][j][0] = img.pixel[x][y][0];
            rotated.pixel[i][j][1] = img.pixel[x][y][1];
            rotated.pixel[i][j][2] = img.pixel[x][y][2];
        }
    }

    return rotated;
}

// negative filter
Image negative(Image img) {
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            img.pixel[i][j][0] = 255 - img.pixel[i][j][0];
            img.pixel[i][j][1] = 255 - img.pixel[i][j][1];
            img.pixel[i][j][2] = 255 - img.pixel[i][j][2];
        }
    }
    return img;
}

// crop image
Image crop_image(Image img, int x, int y, int w, int h) {
    Image croped;

    croped.w = w;
    croped.h = h;

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            croped.pixel[i][j][0] = img.pixel[i + y][j + x][0];
            croped.pixel[i][j][1] = img.pixel[i + y][j + x][1];
            croped.pixel[i][j][2] = img.pixel[i + y][j + x][2];
        }
    }

    return croped;
}


int main() {
    Image img;

    // read type of image
    char p3[4];
    scanf("%s", p3);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &img.w, &img.h, &max_color);

    // read all pixels of image
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            scanf("%hu %hu %hu", &img.pixel[i][j][0],
                                 &img.pixel[i][j][1],
                                 &img.pixel[i][j][2]);

        }
    }

    int n_options;
    scanf("%d", &n_options);

    for(int i = 0; i < n_options; ++i) {
        int options;
        scanf("%d", &options);

        switch(options) {
            case 1: { // grey scale filter
                img = grey_scale(img);
                break;
            }
            case 2: { // sepia filter
                img = sepia(img);
                break;
            }
            case 3: { // blur filter
                int size = 0;
                scanf("%d", &size);
                img = blur(img, size);
                break;
            }
            case 4: { // rotation filter
                int count = 0;
                scanf("%d", &count);
                count %= 4;
                for (int j = 0; j < count; ++j) {
                    img = rotation(img);
                }
                break;
            }
            case 5: { // mirroring filter
                img = mirroring(img);
                break;
            }
            case 6: { // negative filter
                img = negative(img);
                break;
            }
            case 7: { // crop image
                int x, y;
                scanf("%d %d", &x, &y);
                int w, h;
                scanf("%d %d", &w, &h);

                img = crop_image(img, x, y, w, h);
                break;
            }
        }

    }

    // print type of image
    printf("P3\n");

    // print width height and color of image
    printf("%u %u\n255\n", img.w, img.h);

    // print pixels of image
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            printf("%hu %hu %hu ", img.pixel[i][j][0],
                                   img.pixel[i][j][1],
                                   img.pixel[i][j][2]);

        }
        printf("\n");
    }
    return 0;
}
