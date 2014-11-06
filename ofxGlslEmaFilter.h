//
//  ofxGlslEmaFilter.h
//  ofxGlslEmaFilter
//
//  Created by Shunichi Kasahara on 2014/11/05.
//
//

#ifndef __ofxGlslEmaFilter__ofxGlslEmaFilter__
#define __ofxGlslEmaFilter__ofxGlslEmaFilter__

#include "ofMain.h"
#include <iostream>


class ofxGlslEmaFilter
{
public:
    
    void setupGLSL(int w, int h);
    void update(ofPixelsRef pixelRef, float newWeight);
    void draw(float x,float y,float w,float h);
    void readToPixel(ofPixels & pixels){
        output.readToPixels(pixels);
    };

    
private:
    //shader object
    GLhandleARB glslProgramObject;
    GLhandleARB glslShaderObject;

    void render();
    
    float               mEMAWight;      //mEMAWight * newValue + (1.0 - mEMAWight) * oldoutput;
    ofImage             img;
    ofFbo               output;
    float               mWidth, mHeight;
};

#endif /* defined(__ofxGlslEmaFilter__ofxGlslEmaFilter__) */
