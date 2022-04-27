////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Analyst.h"

using namespace std;

Analyst::Analyst(const Image& img)
{
    Analyst *image = new Analyst(img);
}

Analyst::~Analyst()
{
    delete image;
}

bool Analyst::belongToTheSameZone(int i1, int j1, int i2, int j2)
{
    if (image->getPixel(i1,j1) == image->getPixel(i2,j2))
    {
        return true ; 
    }
}




