//
//  CoastFrame.cpp
//  MagicIsland
//
//  Created by cafe on 27/09/2018.
//

#include "CoastFrame.hpp"

CoastFrame::CoastFrame() {
    buffer.allocate(width, height);
}

void CoastFrame::update() {
    center = (p1 + p2) / 2.0;
    buffer.clear();
    buffer.allocate(width, height);
}

void CoastFrame::draw() {
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofDrawRectangle(*this);
    ofFill();
    ofSetColor(255, 255, 0);
    ofDrawCircle(p1, 4);
    ofSetColor(0, 255, 255);
    ofDrawCircle(p2, 4);
    ofPopStyle();
}


