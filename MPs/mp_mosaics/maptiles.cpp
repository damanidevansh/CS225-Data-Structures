/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

     vector<Point<3>> touslespoints;
     map<Point<3>, TileImage*> map;
     for (auto i = theTiles.begin(); i != theTiles.end(); i++) {
         LUVAPixel pixel = i->getAverageColor();
         Point<3> point = convertToXYZ(pixel);
         touslespoints.push_back(point);
         map[point] = &*i;
     }

     KDTree<3> point_tree(touslespoints);
     MosaicCanvas * canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

     for (int i = 0; i < canvas->getRows(); i++) {
         for (int j = 0; j < canvas->getColumns(); j++) {
             Point<3> avgcolour = convertToXYZ(theSource.getRegionColor(i,j));
             Point<3> bestcolour = point_tree.findNearestNeighbor(avgcolour);
             TileImage * finaltile = map[bestcolour];
             canvas->setTile(i, j, finaltile);
         }
     }

    return canvas;
}