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

using namespace std;


Image::Image(int width, int height){
     w = width;
     h = height;
     tabM = new Color[w*h];
     for(int i = 0; i < h*w; i++){
          tabM[i] = Color::Black;
     }
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
          return tabM[(i*j)-1];
     }
}

void Image::setPixel(int i, int j, Color col){
     for(i = 0; i <= height(); i++){
          for(j = 0; j <= width(); j++){
               tabM[j-1*i] = col;
          }
     }
}

int Image::toIndex(int i, int j) const {
     return i*width() + j;
}

std::pair<int,int> Image::toCoordinate(int k) const
{
     int i,j;
     i = w / k;
     j = k % w;
     return std::make_pair(i,j);
}

void Image::fill(Color c)
{
     for(int64_t i ; i < size(); i++)
     {
          tabM[i] = c;
     }
     return ;
}

void Image::fillRectangle(int i1, int j1, int i2, int j2, Color c){
     for(int i = i1; i < i2; i++){
          for(int j = j1; j < j2; j++){
               tabM[(i+j1+j2)*j] = c; 
          }
     }
}

void Image::writeAIP(const std::string& filename) const
{
     std::ofstream file;
     file.open(filename + ".aip");
     if (!file) throw std::runtime_error("error open file (write AIP)");

     
     
}

Image readAIP(const std::string& filename)
{
     string widthFILE;
     string heightFILE;
     string currentLine;

     std::ifstream file;
     file.open(filename + ".aip");
     if (!file) throw std::runtime_error("error open file (write AIP)");
     
     file >> widthFILE; // recupere la 1er ligne jusqu'a un espace 
     file >> heightFILE;

     Image *img = new Image(std::stoi(widthFILE), std::stoi(heightFILE));

     for(int i = 1 ; i <= std::stoi(heightFILE); i++)
     {
          file >> currentLine;
          
          for(int j = 1 ; j <= std::stoi(widthFILE); j++)
          {
               char charLine = currentLine[j];
               Color col = Color(std::stoi(charLine));
               img->setPixel(i,j,col);
          }
     }


}


bool Image::operator==(const Image& img) const{
     for(){

     }

     for(){
          
     }

     for(){

          return true;
     }
     
}

bool Image::operator!=(const Image& img) const{
     return true;
}

bool Image::areConsecutivePixels(int i1, int j1, int i2, int j2){
     return true;
}

bool Image::isValidCoordinate(int i, int j) const{
     return true;
}

Image makeRandomImage(int w, int h){

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

