#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
#include <string>

int main() {

 Image back(880, 480);
 back.readFromFile("running-guy.png");
 text.readFromFile("text.png");
 error.readFromFile("error.png");

 StickerSheet finalpic(back, 4);
 finalpic.addSticker(text, 200, 200)
 finalpic.addSticker(error, 100, 150)
 Image out = finalpic.render();
 out.writeToFile("myImage.png");


  return 0;
}
