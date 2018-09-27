//
//  CoastlineImage.cpp
//  MagicIsland
//
//  Created by cafe on 25/09/2018.
//

#include "CoastlineImage.hpp"

ofVec2f c2p(ofVec2f c) {
    return { sqrt(c.x*c.x + c.y*c.y), atan2(c.y, c.x) };
}

ofVec2f p2c(ofVec2f p) {
    return { p.x * cos(p.y), p.x * sin(p.y) };
}

void CoastlineImage::findContoursOfProcessedImage() {
    contourFinder.findContours(processed);
    polylines = contourFinder.getPolylines();
}

int CoastlineImage::findCoastline() {
    findContoursOfProcessedImage();
    // We could do this by finding the largest polyline and working from that.
    getLongestPolyline();
    coastline = getLongestPolyline();
    coastline.setClosed(false);
    trimEdgePoints();
    if(coastline.getVertices().size() > 0) {
        p1 = coastline.getVertices()[0];
        p2 = coastline.getVertices()[coastline.getVertices().size() - 1];
        center = (p1 + p2) / 2.0;
        return -1;
    }

    
    cropBuffer.clear();
    cropBuffer.allocate(getWidth() - 2 * trimThreshold, getHeight() - 2 * trimThreshold);
    cropped.allocate(cropBuffer.getWidth(), cropBuffer.getHeight(), OF_IMAGE_COLOR);
    
    cropBuffer.begin();
    ofPushMatrix();
    ofImage::drawSubsection(0, 0, getWidth() - trimThreshold*2, getHeight() - trimThreshold*2, trimThreshold, trimThreshold);
    ofPopMatrix();
    
    cropBuffer.end();
    
    cropBuffer.readToPixels(cropped);
    cropped.update();
    
    return 1;
}

void CoastlineImage::trimCornerPoints() {
    vector<ofPoint> vs = coastline.getVertices();
    vector<vector<ofPoint>::iterator> iteratorsToRemove;
    for(int i = 0; i < vs.size(); i++) {
        int next = (i+1)%vs.size();
        next = (next < 0) ? -1 * next : next;
        int last = (i-1)%vs.size();
        last = (last < 0) ? -1 * last : last;

        float distL = ofDist(vs[last].x, vs[last].y, vs[i].x, vs[i].y);
        float distN = ofDist(vs[next].x, vs[next].y, vs[i].x, vs[i].y);
        
        if(distL > trimThreshold && distN > trimThreshold) {
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

void CoastlineImage::trimEdgePoints() {
    vector<ofPoint> vs = coastline.getVertices();
    
    for(auto it = vs.begin(); it != vs.end();) {
        if(it->x < trimThreshold || it->x > getWidth() - trimThreshold || it->y < trimThreshold || it->y > getHeight() - trimThreshold) {
            it = vs.erase(it);
        } else {
            it++;
        }
    }
    
    for(int i = 0; i < vs.size(); i++) {
        vs[i] -= ofPoint(trimThreshold, trimThreshold);
    }
    
    coastline.clear();
    coastline.addVertices(vs);
    
    ofPixels p = getPixels();
}

void CoastlineImage::draw(CoastFrame* cf) {
    
    ofVec2f cDiff = cf->center - ofVec2f(cf->x, cf->y) - center;

    ofVec2f vMe = p1 - p2;
    ofVec2f vCf = cf->p1- cf->p2;

    float scale = (vCf.length() / vMe.length());
    
    ofVec2f p1Pol = c2p(p1 - center);
    ofVec2f cp1Pol = c2p(cf->p1 - cf->center);
    
    float a =  cp1Pol.y - p1Pol.y;
    
    cf->buffer.begin();
    ofPushMatrix();
    ofTranslate(cDiff);
    ofTranslate(center);
    ofRotate(a * 180 / PI, 0, 0, 1);
    ofScale(scale, scale);
    ofTranslate(-center);
    draw(0, 0);
    ofPopMatrix();
    cf->buffer.end();
    
    cf->buffer.draw(cf->x, cf->y);
}

void CoastlineImage::draw(float x, float y) {
    ofPushMatrix();
    cropped.draw(x, y);
//    drawCoastline();
    ofPopMatrix();
}

void CoastlineImage::drawCoastline() {
    ofPushStyle();
    coastline.draw();
    vector<ofPoint> vs = coastline.getVertices();
    for(int i = 0; i < vs.size(); i++) {
        ofSetColor(255.0 / vs.size() * i, 0, 0);
        ofDrawCircle(vs[i], 4);
    }
    ofSetColor(255, 255 ,0);
    ofDrawCircle(p1, 4);
    ofSetColor(0, 255 ,255);
    ofDrawCircle(p2, 4);
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
