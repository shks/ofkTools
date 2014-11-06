//
//  glslBufferMixer.h
//  glslbufferMixer
//
//  Created by Shunichi Kasahara on 2014/11/05.
//
//

#ifndef __glslbufferMixer__glslBufferMixer__
#define __glslbufferMixer__glslBufferMixer__

#include "ofMain.h"
#include <iostream>

class ofxGlslBufferMixer
{
public:
    
    void setupGLSL(int w, int h);
    void update(ofPixelsRef pixelRef);
    void draw(float x,float y,float w,float h);
    
    void drawDebug();
    
    void readToPixel(ofPixels & pixels){
        output.readToPixels(pixels);
    };
    //
    
    const ofFbo& getFboReference();

    
private:
    //shader object
    GLhandleARB glslProgramObject;
    GLhandleARB glslShaderObject;

    void render();
    
    ofFbo               output;
    int                 mRingBufferPointer;
    static const int    RingBufferNum = 6;
    ofImage             imgRingBuffer[RingBufferNum];
    float               mWidth, mHeight;
};

#endif /* defined(__glslbufferMixer__glslBufferMixer__) */
