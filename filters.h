#include <structs.h>

// sepia filter
Image grey_scale(Image img);
// sepia filter
Image sepia(Image img);
// mirroring filter
Image mirroring(Image img);
// blur filter
Image blur(Image img, int T);
// 90 degree to the right rotation
Image rotation(Image img);
// negative filter
Image negative(Image img);
// crop image filter
Image crop_image(Image img, int x, int y, int w, int h);
