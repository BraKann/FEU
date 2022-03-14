////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Image.h"


Image::Image(int width, int height){
     w = width;
     h = height;
     tabM = new Color[w*h];
}

Image::~Image(){
     delete [] tabM;
}

int Image::width() const {
     return w;
}

int Image::height() const {
     return h;
}

int Image::size() const {
     return h*w;
}

Color Image::getPixel(int i, int j) const {
     if( (1 <= i <= height() ) && (1 <= j <= width() ) ){
          return tabM[i*j];
     }
}

void Image::setPixel(int i, int j, Color col){
     for(i = 0; i <= height(); i++){
          for(j = 0; j <= width(); j++){
               col = Color::Black;
               tabM[j-1*i] = col;
          }
     }
}








void Image::writeSVG(const std::string& filename, int pixelSize) const
{
  assert(pixelSize > 0);

  std::ofstream file;
  file.open(filename + ".svg");

  if (!file) throw std::runtime_error("error open file (write SVG)");

  file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
       << std::endl
       << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\""
       << pixelSize*width()
       << "\" height=\""
       << pixelSize*height()
       << "\">"
       << std::endl;

  for (int i = 1; i <= height(); ++i)
    for (int j = 1; j <= width(); ++j)
      file << "<rect width=\""
           << pixelSize
           << "\" height=\""
           << pixelSize
           << "\" x=\""
           << pixelSize*(j-1)
           << "\" y=\""
           << pixelSize*(i-1)
           << "\" fill=\""
           << getPixel(i, j)
           << "\" />"
           << std::endl;

  file << "</svg>"
       << std::endl;

  file.close();
}

