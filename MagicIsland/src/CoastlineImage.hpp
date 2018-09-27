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
#include "CoastFrame.hpp"

#define PI 3.14159265358979323846

using namespace ofxCv;
using namespace cv;

class CoastlineImage : public ProcessedImage {
public:
    CoastlineImage() {
        contourFinder.setMinAreaRadius(10);
        contourFinder.setMaxAreaRadius(500);
    }
    
    void draw(float x, float y);
    void draw(CoastFrame* cf);
    
    ContourFinder contourFinder;
    
    vector<ofPolyline> polylines;
    ofPolyline coastline;
    ofPoint p1, p2, center;
    
    int findCoastline();
    
    void drawCoastline();
    
    void setTrimThreshold(float trimThresh) { trimThreshold = trimThresh; };
    
private:
    ofPolyline getLongestPolyline();
    void findContoursOfProcessedImage();
    void trimCornerPoints();
    void trimEdgePoints();
    
    float trimThreshold = 40;
    
    ofImage cropped;
    ofFbo cropBuffer;
};

#endif /* CoastlineImage_hpp */
