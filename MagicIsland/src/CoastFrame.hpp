//
//  CoastFrame.hpp
//  MagicIsland
//
//  Created by cafe on 27/09/2018.
//

#ifndef CoastFrame_hpp
#define CoastFrame_hpp

#include "ofMain.h"

class CoastFrame : public ofRectangle {
public:
    ofPoint p1, p2, center;
    ofFbo buffer;

    CoastFrame();
    void update();
    void draw();
};

#endif /* CoastFrame_hpp */
