//
// Created by Will nicht on 28.07.18.
//

#include "image_handle.h"

int main() {
    ip::image_handle handle;
    auto ok = handle.load_image("/tmp/demo.tiff");
    if(ok == ip::NO_ERROR) {
        handle.set_reductor(37);
        handle.reduce(true);
        handle.sharpen(true);
        // Lower Gamma make pic brighter
        handle.gamma_correct(0.4, true);
        // handle.blurGausian(true);
        // handle.blurBilateral(true);
        // handle.dft(true);
        handle.erosion(MORPH_ELLIPSE, true);
        handle.dilation(MORPH_CROSS, true);
    }
}