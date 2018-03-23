#include <filters.h>
#include <stdio.h>

// grey scale filter
Image grey_scale(Image img) {
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            int average = img.pixel[i][j].r +
                          img.pixel[i][j].g +
                          img.pixel[i][j].b;
            average /= 3;
            img.pixel[i][j].r = average;
            img.pixel[i][j].g = average;
            img.pixel[i][j].b = average;
        }
    }

    return img;
}

// sepia filter
Image sepia(Image img){
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            Pixel pixel;
            pixel.r = img.pixel[i][j].r;
            pixel.g = img.pixel[i][j].g;
            pixel.b = img.pixel[i][j].b;

            int p =  pixel.r * .393 + pixel.g * .769 + pixel.b * .189;
            int min_r = (255 >  p) ? p : 255;
            img.pixel[i][j].r = min_r;

            p =  pixel.r * .349 + pixel.g * .686 + pixel.b * .168;
            min_r = (255 >  p) ? p : 255;
            img.pixel[i][j].g = min_r;

            p =  pixel.r * .272 + pixel.g * .534 + pixel.b * .131;
            min_r = (255 >  p) ? p : 255;
            img.pixel[i][j].b = min_r;
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
            aux1.r = img.pixel[i2][j].r;
            aux1.g = img.pixel[i2][j].g;
            aux1.b = img.pixel[i2][j].b;

            img.pixel[i2][j].r = img.pixel[x][y].r;
            img.pixel[i2][j].g = img.pixel[x][y].g;
            img.pixel[i2][j].b = img.pixel[x][y].b;

            img.pixel[x][y].r = aux1.r;
            img.pixel[x][y].g = aux1.g;
            img.pixel[x][y].b = aux1.b;
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
                    average.r += img.pixel[x][y].r;
                    average.g += img.pixel[x][y].g;
                    average.b += img.pixel[x][y].b;
                }
            }

            average.r /= T * T;
            average.g /= T * T;
            average.b /= T * T;

            img.pixel[i][j].r = average.r;
            img.pixel[i][j].g = average.g;
            img.pixel[i][j].b = average.b;
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
            rotated.pixel[i][j].r = img.pixel[x][y].r;
            rotated.pixel[i][j].g = img.pixel[x][y].g;
            rotated.pixel[i][j].b = img.pixel[x][y].b;
        }
    }

    return rotated;
}

// negative filter
Image negative(Image img) {
    for (unsigned int i = 0; i < img.h; ++i) {
        for (unsigned int j = 0; j < img.w; ++j) {
            img.pixel[i][j].r = 255 - img.pixel[i][j].r;
            img.pixel[i][j].g = 255 - img.pixel[i][j].g;
            img.pixel[i][j].b = 255 - img.pixel[i][j].b;
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
            croped.pixel[i][j].r = img.pixel[i + y][j + x].r;
            croped.pixel[i][j].g = img.pixel[i + y][j + x].g;
            croped.pixel[i][j].b = img.pixel[i + y][j + x].b;
        }
    }

    return croped;
}
