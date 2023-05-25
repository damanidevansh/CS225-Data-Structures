#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "cs225/PNG.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

using namespace std;

using cs225::HSLAPixel;
using cs225::PNG;

namespace cs225 {

  void Image::lighten() {
    unsigned int imh = height();
    unsigned int imw = width();
    for (unsigned x = 0; x < imw; x++) {
      for (unsigned y = 0; y < imh; y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.l = pixel.l + 0.1;
          if (pixel.l > 1) {
            pixel.l = 1;
          }
          if (pixel.l < 0) {
            pixel.l = 0;
          }
      }
    }
  }
  void Image::lighten (double amount) {
    unsigned int imh = height();
    unsigned int imw = width();
    for (unsigned x = 0; x < imw; x++) {
      for (unsigned y = 0; y < imh; y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.l = pixel.l + amount;
          if (pixel.l > 1) {
            pixel.l = 1;
          }
          if (pixel.l < 0) {
            pixel.l = 0;
          }
      }
    }
  }
  void Image::darken () {
    unsigned int imh = height();
    unsigned int imw = width();
    for (unsigned x = 0; x < imw; x++) {
      for (unsigned y = 0; y < imh; y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.l = pixel.l - 0.1;
          if (pixel.l < 0) {
            pixel.l = 0;
          }
      }
    }
  }
  void Image::darken (double amount) {
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.l = pixel.l - amount;
          if (pixel.l < 0) {
            pixel.l = 0;
          }
      }
    }
  }

  void Image::saturate () {
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.s = pixel.s + 0.1;
          if (pixel.s > 1) {
            pixel.s = 1;
          }
      }
    }
  }
  void Image::saturate (double amount) {
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.s = pixel.s + amount;
          if (pixel.s > 1) {
            pixel.s = 1;
          }
      }
    }
  }
  void Image::desaturate () {
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.s = pixel.s - 0.1;
          if (pixel.s < 0) {
            pixel.s = 0;
          }
      }
    }
  }
  void Image::desaturate (double amount) {
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.s = pixel.s - amount;
          if (pixel.s < 0) {
            pixel.s = 0;
          }
      }
    }
  }
  void Image::grayscale () {
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.s = 0;
      }
    }
  }
  void Image::illinify () {
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& pixel = getPixel(x, y);
        if (113.5 < pixel.h && pixel.h < 293.5) {
          pixel.h = 216;
        }
        else {
          pixel.h = 11;
        }
      }
    }
  }
  void Image::rotateColor (double degrees) {
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& pixel = getPixel(x, y);
        pixel.h = pixel.h + degrees;
        while (pixel.h < 0) {
          pixel.h = pixel.h + 360;
        }
        while (pixel.h > 360) {
          pixel.h = pixel.h - 360;
        }
      }
    }
  }
  void Image::scale(double factor) {
    Image buffer = *this;

    resize((double)width() * factor, (double)height() * factor);
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        HSLAPixel& newPixel = getPixel (x, y);
        HSLAPixel& oldPixel = buffer.getPixel((double)x/factor, (double)y/factor);
        newPixel = oldPixel;
      }
    }
  }
  void Image::scale(unsigned w, unsigned h) {
    double wf = (double)w/(double) width();
    double hf = (double)h/(double) height();
    double factor = min(wf, hf);
    scale(factor);
  }
}
