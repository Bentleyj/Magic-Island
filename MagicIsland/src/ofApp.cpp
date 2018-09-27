#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    // first thing's first we're going to load all our images.
    ofxNestedFileLoader loader;
    vector<string> imageNames = loader.load("TestImages");
    for(int i = 0; i < imageNames.size(); i++) {
        CoastlineImage* img = new CoastlineImage();
        img->load(imageNames[i]);
        
        Effect HSV;
        HSV.loadShader("Shaders/hsv");
        HSV.width = img->getWidth();
        HSV.height = img->getHeight();
        
        Effect BlurHor;
        BlurHor.loadShader("Shaders/BlurHor");
        BlurHor.addUniform("blurAmnt", &blurAmount);
        BlurHor.width = img->getWidth();
        BlurHor.height = img->getHeight();
        
        Effect BlurVert;
        BlurVert.loadShader("Shaders/BlurVert");
        BlurVert.addUniform("blurAmnt", &blurAmount);
        BlurVert.width = img->getWidth();
        BlurVert.height = img->getHeight();
        
        Effect BandW;
        BandW.loadShader("Shaders/BandW");
        BandW.width = img->getWidth();
        BandW.height = img->getHeight();
        
        Effect threshold;
        threshold.loadShader("Shaders/sandwichThreshold");
        threshold.addUniform("threshMin", &threshMin);
        threshold.addUniform("threshMax", &threshMax);
        threshold.width = img->getWidth();
        threshold.height = img->getHeight();
        
        Effect sobel;
        sobel.loadShader("Shaders/sobel");
        sobel.width = img->getWidth();
        sobel.height = img->getHeight();
        
        img->addEffect(BlurHor);
        img->addEffect(BlurVert);

        img->addEffect(HSV);
        img->addEffect(threshold);

        images.push_back(img);
        
        img->setTrimThreshold(trimThreshold);
        img->reset();
        if(img->findCoastline() > 0) {
            images.push_back(img);
        }
    }
    
    for(int i = 0; i < images.size(); i++) {
        images[i]->reset();
    }
    
    string settingsPath = "settings/settings.xml";
    gui.setup("Gui", settingsPath);
    gui.add(threshMin.set("Threshold Min", 0.5, 0, 1.0));
    gui.add(threshMax.set("Threshold Max", 0.5, 0, 1.0));
    gui.add(blurAmount.set("Blur Amount", 1, 0, 10));
    gui.add(trimThreshold.set("Trim Threshold", 20, 0, 50));
    threshMin.addListener(this, &ofApp::onParamChanged);
    threshMax.addListener(this, &ofApp::onParamChanged);
    blurAmount.addListener(this, &ofApp::onParamChanged);
    trimThreshold.addListener(this, &ofApp::onParamChanged);

    gui.loadFromFile(settingsPath);
    
    float x, y, size;
    x = y = 0;
    size = 800;
    for(int i = 0; i < 9; i++) {
        CoastFrame* cf = new CoastFrame();
        cf->width = size;
        cf->height = size;
        cf->x = x;
        cf->y = y;
        x += size;
        if(x > (size)*2) {
            x = 0;
            y += size;
        }
        if(i != 4) {
            coastFrames.push_back(cf);
        }
    }
    
    coastFrames[0]->p1 = ofVec2f(coastFrames[0]->x + coastFrames[0]->width/2, coastFrames[0]->y + coastFrames[0]->height);
    coastFrames[0]->p2 = ofVec2f(coastFrames[0]->x + coastFrames[0]->width, coastFrames[0]->y + coastFrames[0]->height/2);
    
    coastFrames[1]->p1 = ofVec2f(coastFrames[1]->x, coastFrames[1]->y + coastFrames[1]->height/2);
    coastFrames[1]->p2 = ofVec2f(coastFrames[1]->x + coastFrames[1]->width, coastFrames[1]->y + coastFrames[1]->height/2);
    
    coastFrames[2]->p1 = ofVec2f(coastFrames[2]->x, coastFrames[2]->y + coastFrames[2]->height/2);
    coastFrames[2]->p2 = ofVec2f(coastFrames[2]->x + coastFrames[2]->width/2, coastFrames[2]->y + coastFrames[2]->height);
    
    coastFrames[3]->p1 = ofVec2f(coastFrames[3]->x + coastFrames[3]->width/2, coastFrames[3]->y + coastFrames[3]->height);
    coastFrames[3]->p2 = ofVec2f(coastFrames[3]->x + coastFrames[3]->width/2, coastFrames[3]->y);
    
    coastFrames[4]->p1 = ofVec2f(coastFrames[4]->x + coastFrames[4]->width/2, coastFrames[4]->y);
    coastFrames[4]->p2 = ofVec2f(coastFrames[4]->x + coastFrames[4]->width/2, coastFrames[4]->y  + coastFrames[4]->height);
    
    coastFrames[5]->p1 = ofVec2f(coastFrames[5]->x + coastFrames[5]->width, coastFrames[5]->y + coastFrames[5]->height/2);
    coastFrames[5]->p2 = ofVec2f(coastFrames[5]->x + coastFrames[5]->width/2, coastFrames[5]->y);
    
    coastFrames[6]->p1 = ofVec2f(coastFrames[6]->x + coastFrames[6]->width, coastFrames[6]->y + coastFrames[5]->height/2);
    coastFrames[6]->p2 = ofVec2f(coastFrames[6]->x, coastFrames[6]->y + coastFrames[6]->height/2);
    
    coastFrames[7]->p1 = ofVec2f(coastFrames[7]->x + coastFrames[7]->width/2, coastFrames[7]->y);
    coastFrames[7]->p2 = ofVec2f(coastFrames[7]->x, coastFrames[7]->y + coastFrames[7]->height/2);
    
    for(int i = 0; i < coastFrames.size(); i++) {
        coastFrames[i]->update();
    }

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofScale(0.3, 0.3);
    float x, y;
    x = y = 0;
    for(int i = 0; i < coastFrames.size(); i++) {
        images[i%images.size()]->draw(coastFrames[i]);
    }
//    for(int i = 0; i < coastFrames.size(); i++) {
//        coastFrames[i]->draw();
//    }
    ofPopMatrix();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::onParamChanged(float & param) {
    for(int i = 0; i < images.size(); i++) {
        images[i]->setTrimThreshold(trimThreshold);
        images[i]->reset();
        images[i]->findCoastline();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
