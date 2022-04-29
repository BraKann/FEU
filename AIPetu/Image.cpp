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
#include "Color.h"

using namespace std;


Image::Image(int width, int height)
{
     w = width;
     h = height;
     tabPixel = new Color[w*h];
     for (int i = 0; i < h*w; i++)
     {
          tabPixel[i] = Color::Black;
     }
}

Image::~Image()
{
     delete [] tabPixel;
}

int Image::width() const
{
     return w;
}

int Image::height() const
{
     return h;
}

int Image::size() const
{
     return h*w;
}

Color Image::getPixel(int i, int j) const
{
     assert((1 <= i <= height()) && (1 <= j <= width()));
     return tabPixel[((i-1) * w + j)];
}

void Image::setPixel(int i, int j, Color col)
{
     assert((1 <= i <= height()) && (1 <= j <= width()));
     tabPixel[((i-1) * w + j)] = col;
}

int Image::toIndex(int i, int j) const
{
     return (i*w)+j;
}

std::pair<int,int> Image::toCoordinate(int k) const
{
     int i,j;
     j = k % w;
     i = (k-j) / w;
     return std::make_pair(i,j);
}

void Image::fill(Color c)
{
     for (int i = 0; i < size(); i++)
     {
          tabPixel[i] = c;
     }
}

void Image::fillRectangle(int i1, int j1, int i2, int j2, Color c)
{

     tabPixel[((i1-1) * w + j1)] = c;
     tabPixel[(((i1-1) * w + j1)) + 1] = c;
     tabPixel[((i2-1) * w + j2)] = c;
     tabPixel[(((i2-1) * w + j2)) - 1] = c;
     
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

void Image::writeAIP(const std::string& filename) const
{
     std::ofstream file;
     file.open(filename + ".aip");

     if (!file) throw std::runtime_error("error open file (write AIP)");

     file << width();
     file << " ";
     file << height() << std::endl;

     for (int i = 1; i <= height(); i++)
     {
          for (int j = 1; j <= width(); j++)
          {
               file << tabPixel[toIndex(i,j)].toInt();
          }
          file<< std::endl;
     }

     file.close();
}

Image Image::readAIP(const std::string& filename)
{
     std::ifstream file;
     std::string widthFILE;
     std::string heightFILE;
     std::string currentLine;
     Color c;
     file.open(filename + ".aip");

     if (!file) throw std::runtime_error("error open file (read AIP)");
     
     

     file >> widthFILE;
     file >> heightFILE;


     Image image(std::stoi(widthFILE),std::stoi(heightFILE));

     cout << image.width() << ' ' << image.height() << endl;

     for (int i = 1; i <= std::stoi(heightFILE); i++)
     {
          file >> currentLine;
          for (int j = 0; j < std::stoi(widthFILE); j++)
          {
               int colorCode = (int)(currentLine[j]);
               if (colorCode == 52) { c = Color::Green; }
               if (colorCode == 51) { c = Color::Blue; }
               if (colorCode == 50) { c = Color::Red; }
               if (colorCode == 49) { c = Color::White; }
               if (colorCode == 48) { c = Color::Black; }
               image.setPixel(i,j+1,c);
          }

     }

     return image;
}

bool Image::operator==(const Image& img) const
{
     bool isEqual = false;

     if(img.width() == width())
          if(img.height() == height())
               for(int i = 0; i < img.size() ; i++)
               {
                    if(img.tabPixel[i] != tabPixel[i])
                         return isEqual;
                    else isEqual = true;

               }
     return isEqual;
}

bool Image::operator!=(const Image& img) const{
     !operator==(img);
     return true;
}

bool Image::areConsecutivePixels(int i1, int j1, int i2, int j2){
     assert(((1 <= i1 <= w ) && (1 <= j1 <= h )) && ((1 <= i2 <= w ) && (1 <= j2 <= h )));
     //Droite,bas,gauche,haut
     if( (i2 == i1+1 && j2 == j1) || (i2 == i1 && j2 == j1+1) || (i2 == i1-1 && j2 == j1) || (i2 == i1 && j2 == j1-1) )
     {
        return true;  
     }

     return 0;
     
}

bool Image::isValidCoordinate(int i, int j) const{
     if(1 <= i <= width() && 1 <= j <= height())
     {
       return true;   
     }

     return 0;
     
}

Image makeRandomImage(int w, int h){
     Image img(w,h);
     //La remplir d'une couleur random ?
     return img;
}

