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
#include <cmath>

using namespace std;

//----------------------------------------------Constructeur Image------------------------------------------
/**
 * @brief Construct a new Image:: Image object
 * 
 * @param width 
 * @param height 
 */
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

//----------------------------------------------Destructeur Image------------------------------------------
/**
 * @brief Destroy the Image:: Image object
 * 
 */
Image::~Image()
{
     delete [] tabPixel;
}

//------------------------------------------------------Getters------------------------------------------
/**
 * @brief Returns width of this
 * 
 * @return int 
 */
int Image::width() const
{
     return w;
}

/**
 * @brief Returns height of this
 * 
 * @return int 
 */
int Image::height() const
{
     return h;
}

/**
 * @brief Returns size(number of pixels) of this
 * 
 * @return int 
 */
int Image::size() const
{
     return h*w;
}

/**
 * @brief Gets pixel in the i-th row and j-th column
 * 
 * @param i 
 * @param j 
 * @return Color 
 */
Color Image::getPixel(int i, int j) const
{
     assert((1 <= i <= height()) && (1 <= j <= width()));
     return tabPixel[((i-1) * w + j)];
}

/**
 * @brief sets the given color to the i-th row and j-th column
 * 
 * @param i 
 * @param j 
 * @param col 
 */
void Image::setPixel(int i, int j, Color col)
{
     assert((1 <= i <= height()) && (1 <= j <= width()));
     tabPixel[((i-1) * w + j)] = col;
}

/**
 * @brief Maps a coordinate (i, j) to a unique identifier
 * 
 * @param i 
 * @param j 
 * @return int 
 */
int Image::toIndex(int i, int j) const
{
     return (i*w)+j;
}

/**
 * @brief Maps an identifier to the corresponding coordinates
 * 
 * @param k 
 * @return std::pair<int,int> 
 */
std::pair<int,int> Image::toCoordinate(int k) const
{
     int i,j;
     i = (k / this->width()) + 1;
     j = k % this->width();
     if (j == 0) { j = this->width(); }
     return std::make_pair(i,j);
}

/**
 * @brief Fills the Image with the given color
 * 
 * @param c 
 */
void Image::fill(Color c)
{
     for (int i = 0; i < size(); i++)
     {
          tabPixel[i] = c;
     }
}

/**
 * @brief Fills a given square with given color
 * 
 * @param i1 
 * @param j1 
 * @param i2 
 * @param j2 
 * @param c 
 */
void Image::fillRectangle(int i1, int j1, int i2, int j2, Color c)
{

     tabPixel[((i1-1) * w + j1)] = c;
     tabPixel[(((i1-1) * w + j1)) + 1] = c;
     tabPixel[((i2-1) * w + j2)] = c;
     tabPixel[(((i2-1) * w + j2)) - 1] = c;
     
}

/**
 * @brief creates an SVG file
 * 
 * @param filename 
 * @param pixelSize 
 */
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

/**
 * @brief creates an AIP file
 * 
 * @param filename 
 */
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

/**
 * @brief reads an AIP file and returns an Image
 * 
 * @param filename 
 * @return Image 
 */
Image Image::readAIP(const std::string& filename)
{
     std::ifstream file;
     std::string widthFILE;
     std::string heightFILE;
     std::string currentLine;
     Color c;
     file.open(filename + ".aip");

     if (!file) throw std::runtime_error("error open file (read AIP)");
     
     

     file >> widthFILE; //Lire 1er ligne de la file jusqu'a un espace
     file >> heightFILE; //Lire 1er ligne de la file jusqu'a un espace aprés file >> widthFILE


     Image image(std::stoi(widthFILE),std::stoi(heightFILE));

     cout << image.width() << ' ' << image.height() << endl;

     for (int i = 1; i <= std::stoi(heightFILE); i++)
     {
          file >> currentLine; //Gets ASCII characteres from file
          for (int j = 0; j < std::stoi(widthFILE); j++)
          {
               int colorCode = (int)(currentLine[j]); // Transform ASCII charracter to int

               if (colorCode == 52) { c = Color::Green; }
               if (colorCode == 51) { c = Color::Blue; }
               if (colorCode == 50) { c = Color::Red; }
               if (colorCode == 49) { c = Color::White; }
               if (colorCode == 48) { c = Color::Black; }

               image.setPixel(i,j+1,c); //Sets the corresponding color to pixel
          }

     }

     return image;
}


/**
 * @brief Returns true if this and img are equal
 * 
 * @param img 
 * @return true 
 * @return false 
 */
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

/**
 * @brief Returns true if this and img are different
 * 
 * @param img 
 * @return true 
 * @return false 
 */
bool Image::operator!=(const Image& img) const{
     !operator==(img);
     return true;
}

/**
 * @brief Returns true if (i1, j1) and (i2, j2) are two consecutive piels of this
 * 
 * @param i1 
 * @param j1 
 * @param i2 
 * @param j2 
 * @return true 
 * @return false 
 */
bool Image::areConsecutivePixels(int i1, int j1, int i2, int j2){
     assert(((1 <= i1 <= w ) && (1 <= j1 <= h )) && ((1 <= i2 <= w ) && (1 <= j2 <= h )));
     //Droite,bas,gauche,haut
     if( (i2 == i1+1 && j2 == j1) || (i2 == i1 && j2 == j1+1) || (i2 == i1-1 && j2 == j1) || (i2 == i1 && j2 == j1-1) )
     {
        return true;  
     }

     return 0;
     
}

/**
 * @brief Tests if (i,j) is the coordinates of some pixel of this
 * 
 * @param i 
 * @param j 
 * @return true 
 * @return false 
 */
bool Image::isValidCoordinate(int i, int j) const{
     if(1 <= i <= width() && 1 <= j <= height())
     {
       return true;   
     }

     return 0;
     
}

/**
 * @brief creates an w x h Image with random colors 
 * 
 * @param w 
 * @param h 
 * @return Image 
 */
Image makeRandomImage(int w, int h)
{
     Image img(w,h);
     for (int i = 1; i <= h; i++)
     {
          for (int j = 1; j <= w ; j++)
          {
               int colorCode = rand() % 4;
               img.setPixel(i , j ,Color::makeColor(colorCode));
          }
     }
     
     return img;
}

