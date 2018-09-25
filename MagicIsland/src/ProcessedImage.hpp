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
    
    void load(string imgPath);      // Load an original image.

    void update();                  // Update original and processed image textures.
    
    void addEffect(Effect e);       // Add an Effect to be applied to the image. Effects are applied in order.
    
    void applyEffects();            // Apply all the effects in the order they were added.
    
    void draw(float x, float y);    // Draw the image and the processed image underneath it.
    
    void reset();                   // Reset by loading the original image back in to the source buffer and applying the effects again.
    
protected:
    void swapBuffers();             // Swap the source and destination buffer. (used internally only)
};

#endif /* ProcessedImage_hpp */
