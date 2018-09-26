//
//  ProcessedImage.cpp
//  MagicIsland
//
//  Created by cafe on 21/09/2018.
//

#include "ProcessedImage.hpp"

void ProcessedImage::update() {
    ofImage::update();
    processed.update();
}

void ProcessedImage::load(string imgPath) {
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

void ProcessedImage::addEffect(Effect e) {
    e.addUniform("inputTexture", srcBuffer);
    e.addUniform("resolution", &resolution);
    effects.push_back(e);
}

void ProcessedImage::swapBuffers() {
    ofFbo* tmpBuff = dstBuffer;
    dstBuffer = srcBuffer;
    srcBuffer = tmpBuff;
    for(int i = 0; i < effects.size(); i++) {
        effects[i].addUniform("inputTexture", srcBuffer);
    }
}

// Here we apply our effects in order to our buffers.
// We always start assuming the srcBuffer is pointing to the current image and we don't care what is in the dst buffer.
// Once we apply all the effects we ensure that the dst buffer holds the final processed image, the src Buffer will hold the second last effect pass.
// But we don't really care what it holds.
// Then we update the processed image texture so we can perform cv operations on it.
void ProcessedImage::applyEffects() {
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

void ProcessedImage::draw(float x, float y) {
    ofImage::draw(x, y);
    processed.draw(x, y+getHeight());
}

void ProcessedImage::reset() {
    srcBuffer->begin();
    ofImage::draw(0, 0);
    srcBuffer->end();
    
    srcBuffer->updateTexture(0);
    
    applyEffects();
}
