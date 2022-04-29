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

  // ------------------------------------------------------------Création Objet Image de 3x3 ----------------------------------------
  Image img(3,3);
  //-------------------------------------------------------------Test les methodes de Image.h-------------------------------------
  
  img.toCoordinate(7);

  Color col = Color::Red;
  img.setPixel(3,2,col);

  img.fillRectangle(1,1,2,2,Color::Blue);

  //Test writeSVG et writeAIP
  img.writeSVG("test",1);
  img.writeAIP("test");

  //Test de readAIP et puis writeSVG
  Image image(Image::readAIP("amazonie_0"));
  image.writeSVG("amazonie0",50);

  //Test pour makeRandomImage(w,h)
  Image image = makeRandomImage(3,3);
  image.writeSVG("randomImage",1);

  return 0;
}