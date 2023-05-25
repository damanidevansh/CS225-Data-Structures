#include "Image.h"

#pragma once

 class StickerSheet{
 public:

   Image** background;
   unsigned* arr_x;
   unsigned* arr_y;
   unsigned maxnum;
   unsigned stickernumber;
   Image bottom;

   StickerSheet(const Image &picture, unsigned max);
   ~StickerSheet();
   StickerSheet(const StickerSheet &other);
   const StickerSheet & operator=(const StickerSheet &other);
   void changeMaxStickers(unsigned max);
   int addSticker(Image &sticker, unsigned x, unsigned y);
   bool translate(unsigned index, unsigned x, unsigned y);
   void removeSticker(unsigned index);
   Image *getSticker(unsigned index) const;
   Image render() const;
   void copy(const StickerSheet & other);
   void clear();
 };