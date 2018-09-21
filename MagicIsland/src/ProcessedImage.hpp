//
//  ProcessedImage.hpp
//  MagicIsland
//
//  Created by cafe on 21/09/2018.
//

#ifndef ProcessedImage_hpp
#define ProcessedImage_hpp

#include "ofMain.h"
#include "Effect.hpp"

class ProcessedImage : public ofImage {
public:
    ofImage processed;              // Processed image after effects have been applied.
    vector<Effect> effects;         // Effects to be applied in order.
    ofFbo buf1, buf2;               // Swap buffers for holding the effects.
    ofFbo *srcBuffer, *dstBuffer;   // Pointers to buffers.
    ofVec2f resolution;             // Image Resolution.
    
    void update() {
        ofImage::update();
        processed.update();
    }
    
    void load(string imgPath) {
        ofImage::load(imgPath);
        resolution = ofVec2f(getWidth(), getHeight());
        processed.allocate(getWidth(), getHeight(), OF_IMAGE_COLOR);
        buf1.allocate(getWidth(), getHeight());
        buf2.allocate(getWidth(), getHeight());
        
        buf1.begin();
        ofImage::draw(0, 0);
        buf1.end();
        
        buf1.updateTexture(0);
        
        srcBuffer = &buf1;
        dstBuffer = &buf2;
    }
    
    void addEffect(Effect e) {
        e.addUniform("inputTexture", srcBuffer);
        e.addUniform("resolution", &resolution);
        effects.push_back(e);
    }
    
    void swapBuffers() {
        ofFbo* tmpBuff = dstBuffer;
        dstBuffer = srcBuffer;
        srcBuffer = tmpBuff;
        for(int i = 0; i < effects.size(); i++) {
            effects[i].addUniform("inputTexture", srcBuffer);
        }
    }
    
    void applyEffects() {
        for(int i = 0; i < effects.size(); i++) {
            dstBuffer->begin();
            effects[i].applyEffect();
            dstBuffer->end();
            swapBuffers();
            dstBuffer->updateTexture(0);
            srcBuffer->updateTexture(0);
        }
        swapBuffers();
        dstBuffer->getTexture().readToPixels(processed);
        processed.update();
    }
    
    void draw(float x, float y) {
        ofImage::draw(x, y);
        processed.draw(x, y+getHeight());
    }
};

#endif /* ProcessedImage_hpp */
