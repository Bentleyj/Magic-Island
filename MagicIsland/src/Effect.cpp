//
//  Effect.cpp
//  BeyondPhotography
//
//  Created by cafe on 16/01/2018.
//

#include "Effect.hpp"

Effect::Effect() {
    
}

void Effect::loadShader(string shaderPath) {
    shader.load(shaderPath);
    name = ofSplitString(shaderPath, ".")[0];
    int s = ofSplitString(name, "/").size();
    name = ofSplitString(name, "/")[s-1];
    
    button.set(name, false);
}
    
void Effect::applyEffect() {
    shader.begin();
    // Set the floats
    for(auto it = uniformFloats.begin(); it != uniformFloats.end(); it++) {
        shader.setUniform1f(it->first, *(it->second));
    }
    // Set the float parameters
    for(auto it = uniformFloatParameters.begin(); it != uniformFloatParameters.end(); it++) {
        shader.setUniform1f(it->first, *(it->second));
    }
    
    // set the Vec2fs
    for(auto it = uniformVec2fs.begin(); it != uniformVec2fs.end(); it++) {
        shader.setUniform2f(it->first, *(it->second));
    }
    
    // set the Vec3fs
    for(auto it = uniformVec3fs.begin(); it != uniformVec3fs.end(); it++) {
        shader.setUniform3f(it->first, *(it->second));
    }

    // set the Vec4fs
    for(auto it = uniformVec4fs.begin(); it != uniformVec4fs.end(); it++) {
        shader.setUniform4f(it->first, *(it->second));
    }

    // set the Textures
    int numTextures = 0;
    for(auto it = uniformTextures.begin(); it != uniformTextures.end(); it++) {
        shader.setUniformTexture(it->first, *(it->second), numTextures);
        numTextures++;
    }
    
    // set the BaseHasTextures
    for(auto it = uniformBaseHasTextures.begin(); it != uniformBaseHasTextures.end(); it++) {
        shader.setUniformTexture(it->first, *(it->second), numTextures);
        numTextures++;
    }

    ofDrawRectangle(0, 0, width, height);
    
    shader.end();
}

void Effect::addUniform(string s, float* f) {
    uniformFloats[s] = f;
}

void Effect::addUniform(string s, ofParameter<float>* f) {
    uniformFloatParameters[s] = f;
}

void Effect::addUniform(string s, ofVec2f* f) {
    uniformVec2fs[s] = f;
}

void Effect::addUniform(string s, ofVec3f* f) {
    uniformVec3fs[s] = f;
}

void Effect::addUniform(string s, ofVec4f* f) {
    uniformVec4fs[s] = f;
}

void Effect::addUniform(string s, ofTexture* f) {
    uniformTextures[s] = f;
}

void Effect::addUniform(string s, ofBaseHasTexture* f) {
    uniformBaseHasTextures[s] = f;
}


