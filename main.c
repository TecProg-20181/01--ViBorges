#include <stdio.h>
#include <filters.h>

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

    // menu
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
