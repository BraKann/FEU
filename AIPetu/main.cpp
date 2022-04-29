////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <ctime>
#include <sstream>
#include "FireSimulator.h"
#include "Image.h"
#include "Color.h"

using namespace std;

int main(void)
{
  srand(time(nullptr));

  Color col = Color::Red;

  Image img(50,30);

  //img.setPixel(3,2,col);

  //img.fillRectangle(1,1,2,2,Color::Blue);

  //img.writeSVG("test1",1);
  //img.writeAIP("test1");

  Image image(Image::readAIP("amazonie_0"));

  image.writeSVG("test2",3);
  

  //Image image(Image::readAIP("amazonie_0"));

  //image.writeSVG("amazonie0",50);
  

  return 0;
}
