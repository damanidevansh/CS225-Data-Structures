#pragma once

#include <string>
#include <iostream>

#include "cs225/PNG.h"

using namespace cs225;

namespace cs225{
  class Image:public PNG{
  public:
    void lighten();
    void lighten(double amount);
    void darken();
    void darken(double amount);
    void saturate(double amount);
    void saturate();
    void desaturate();
    void desaturate(double amount);
    void grayscale();
    void rotateColor(double degrees);
    void illinify();
    void scale(double factor);
    void scale(unsigned w, unsigned h);
  };
}
