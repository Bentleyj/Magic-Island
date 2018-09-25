//
//  CoastlineImage.hpp
//  MagicIsland
//
//  Created by cafe on 25/09/2018.
//

#ifndef CoastlineImage_hpp
#define CoastlineImage_hpp

#include "ofMain.h"
#include "ProcessedImage.hpp"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

class CoastlineImage : public ProcessedImage {
public:
    CoastlineImage() {
        contourFinder.setMinAreaRadius(10);
        contourFinder.setMaxAreaRadius(500);
    }
    
    ContourFinder contourFinder;
    
    vector<ofPolyline> polylines;
    ofPolyline coastline;
    ofPoint p1, p2;
    int index;
    
    void findCoastline();
    
    void drawCoastline();
    
private:
    ofPolyline getLongestPolyline();
    void findContoursOfProcessedImage();
    void trimCornerPoints();
};

#endif /* CoastlineImage_hpp */
