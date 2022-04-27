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
  Image img(10,15);
  //img.fill(Color::Red);
  //img.fillRectangle(1,1,5,5,Color::Green);
  //img.writeSVG("test",5);
  //img.writeAIP("test");
  img.readAIP("amazonie_0");
  img.writeSVG("amazonie_0",1);

  return 0;
}
