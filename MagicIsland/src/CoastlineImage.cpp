//
//  CoastlineImage.cpp
//  MagicIsland
//
//  Created by cafe on 25/09/2018.
//

#include "CoastlineImage.hpp"

void CoastlineImage::findContoursOfProcessedImage() {
    contourFinder.findContours(processed);
    polylines = contourFinder.getPolylines();
}

void CoastlineImage::findCoastline() {
    findContoursOfProcessedImage();
    // We could do this by finding the largest polyline and working from that.
    getLongestPolyline();
    coastline = getLongestPolyline();
    trimCornerPoints();
}

void CoastlineImage::trimCornerPoints() {
    float distThresh = 20;
    vector<ofPoint> vs = coastline.getVertices();
    vector<vector<ofPoint>::iterator> iteratorsToRemove;
    for(int i = 0; i < vs.size(); i++) {
        int next = (i+1)%vs.size();
        next = (next < 0) ? -1 * next : next;
        int last = (i-1)%vs.size();
        last = (last < 0) ? -1 * last : last;

        float distL = ofDist(vs[last].x, vs[last].y, vs[i].x, vs[i].y);
        float distN = ofDist(vs[next].x, vs[next].y, vs[i].x, vs[i].y);
        
        if(distL > distThresh && distN > distThresh) {
            iteratorsToRemove.push_back( vs.begin() + i);
        }
    }
    cout<<iteratorsToRemove.size()<<endl;
    if(iteratorsToRemove.size() > 0) {
        int i = 0;
        for(auto it = vs.begin(); it != vs.end();) {
            vector<ofPoint>::iterator itToRemove = iteratorsToRemove[i];
            if(it == itToRemove) {
                it = vs.erase(it);
                i++;
            } else {
                it++;
            }
        }
    }

    coastline.clear();
    coastline.addVertices(vs);
}

void CoastlineImage::drawCoastline() {
    ofPushStyle();
    coastline.draw();
    vector<ofPoint> vs = coastline.getVertices();
    ofSetColor(255, 0, 0);
    for(int i = 0; i < vs.size(); i++) {
        ofDrawCircle(vs[i], 4);
    }
    ofPopStyle();
}

ofPolyline CoastlineImage::getLongestPolyline() {
    if(polylines.size() < 1) {
        cout << " No polylines loaded, returning empty polyline! " << endl;
        return ofPolyline();
    }
    float maxArea = 0.0;
    int p = 0;
    for(int i = 0; i < polylines.size(); i++) {
        if(polylines[i].getArea() < maxArea) { // For some reason the areas are being returned as negative values?
            maxArea = polylines[i].getArea();
            p = i;
        }
    }
    return polylines[p];
}
