////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Analyst.h"
#include "Image.h"

using namespace std;

/**
 * @brief Construct a new Analyst:: Analyst object
 * 
 * @param img 
 */
Analyst::Analyst(const Image& img){
    int numPart = 0;
    Image image = img;
    tabPart = new Partition[image.size()];
    for(int i = 0; i < image.height(); i++)
    {
        for(int j = 0; j < image.width(); j++)
        {
            //Cas particulier : Pixel haut gauche, pixels de la premiere ligne et premiere colonne
            if( (1 <= i-1 <= image.width())  (1 <= j-1 <= image.height()) )
            { 
                //Si le pixel haut ou le pixel gauche precede le pixel actuel, ou car cas particulier
                if( (image.areConsecutivePixels(i,j,i-1,j))  (image.areConsecutivePixels(i,j,i,j-1)) ) 
                {
                    //Si le pixel en haut ou le pixel a gauche du pixel courant sont de meme couleur
                    if( (image.getPixel(i,j) == image.getPixel(i-1,j)) || (image.getPixel(i,j) == image.getPixel(i,j-1)) ) 
                    {
                        //Le pixel actuel prend le dernier numéro de partition attribuer 
                        tabPart[i].nPartirion = numPart;
                        tabPart[i].indexCouleur = image.getPixel(i,j);
                    }
                }
            } else {
                //attribue un nouveau numéro de partition pour le pixel actuel
                tabPart[i].nPartirion = numPart++;
                tabPart[i].indexCouleur = image.getPixel(i,j);
            }
        }
    }
}

/**
 * @brief Destroy the Analyst:: Analyst object
 * 
 */
Analyst::~Analyst()
{
    delete [] tabPart;
}


