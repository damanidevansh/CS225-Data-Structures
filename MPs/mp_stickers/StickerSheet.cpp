#include "Image.h"
#include "StickerSheet.h"

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  maxnum= max;
  bottom = picture;
  background = new Image* [max];
  arr_x = new unsigned[max];
  arr_y = new unsigned[max];
  for(unsigned i = 0; i < max; i++){
    background[i] = NULL;
  }
  stickernumber = 0;
}


StickerSheet::~StickerSheet(){
  clear();
}


void StickerSheet::clear(){
  for(unsigned i = 0; i < stickernumber; i++){
    delete background[i];
    background[i] = NULL;
  }
  delete[] background;
  background = NULL;
  delete[] arr_x;
  arr_x = NULL;
  delete[] arr_y;
  arr_y = NULL;
}


StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);
}


void StickerSheet::copy(const StickerSheet & other){
  maxnum = other.maxnum;
  bottom = other.bottom;
  stickernumber = other.stickernumber;
  arr_x = new unsigned[maxnum];
  arr_y = new unsigned[maxnum];
  background = new Image* [maxnum];
  for (unsigned i = 0; i < maxnum; i++){
    background[i] = NULL;
  }

  for (unsigned i = 0; i < stickernumber; i++){
      background[i] = new Image();
      *background[i] = *other.background[i];
      arr_x[i] = other.arr_x[i];
      arr_y[i] = other.arr_y[i];
  }
}


const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
  clear();
  copy(other);
  return *this;
}


void StickerSheet::changeMaxStickers(unsigned new_max){
  if(new_max == stickernumber){
    return;
  }
  Image** newbackground = new Image*[new_max];
  for(unsigned i = 0; i < new_max; i++){
    newbackground[i] = NULL;
  }
  unsigned* newx = new unsigned[new_max];
  unsigned* newy = new unsigned[new_max];

  if(stickernumber < new_max){
    for (unsigned i = 0; i < stickernumber; i++){
      newbackground[i] = new Image();
      *newbackground[i] = *background[i];
      newx[i] = arr_x[i];
      newy[i] = arr_y[i];
    }
  }
  else{
    for (unsigned i = 0; i < new_max; i++){
      newbackground[i] = new Image();
      *newbackground[i] = *background[i];
      newx[i] = arr_x[i];
      newy[i] = arr_y[i];
    }
    stickernumber = new_max;
  }
  clear();
  background = newbackground;
  newbackground = NULL;
  arr_x = newx;
  newx = NULL;
  arr_y = newy;
  newy = NULL;
  maxnum = new_max;
}


int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  for (unsigned i = 0; i < maxnum; i++) {
if (i == stickernumber) {
			background[i] = new Image(sticker);
			arr_x[i] = x;
			arr_y[i] = y;
			stickernumber++;
return int(i);
		}
	}
return -1;
}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(index >= stickernumber){
    return false;
  }
  else{
    arr_x[index] = x;
    arr_y[index] = y;
    return true;
  }
}


void StickerSheet::removeSticker(unsigned index){
  if(index < stickernumber){
    for(unsigned i = index; i < (stickernumber-1); i++){
      *background[i] =  *background[i+1];
      arr_x[i] = arr_x[i+1];
      arr_y[i] = arr_y[i+1];
    }
    delete background[stickernumber-1];
    background[stickernumber] = NULL;
    stickernumber = stickernumber-1;
  }
}


Image * StickerSheet::getSticker(unsigned index) const{
  if (index < stickernumber){
    return background[index];
  }
  return NULL;
}

Image StickerSheet::render() const{
  Image new_image;
  unsigned max_width = bottom.width();
  unsigned max_height = bottom.height();

  for (unsigned i = 0; i < stickernumber; i++){
    if(background[i] != NULL){
      if(arr_x[i] + background[i]->width() > max_width){
        max_width = arr_x[i] + background[i]->width();
      }
      if(arr_y[i] + background[i]->height() > max_height){
        max_height = arr_y[i] + background[i]->height();
      }
    }
  }
  new_image = bottom;
  new_image.resize(max_width, max_height);

  for(unsigned i = 0; i < stickernumber; i++){
    if(background[i] != NULL){
      for(unsigned w = arr_x[i]; w < (arr_x[i] + background[i]->width()); w++){
        for(unsigned h = arr_y[i]; h < (arr_y[i] + background[i]->height()); h++){
          if(background[i]->getPixel((w - arr_x[i]), (h - arr_y[i])).a != 0){
            new_image.getPixel(w, h) = background[i]->getPixel((w - arr_x[i]), (h - arr_y[i]));
          }
        }
      }
    }
  }
  return new_image;
}