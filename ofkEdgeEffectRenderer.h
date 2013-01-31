//
//  ofkOnsetDetector.cpp
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/07/01.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.


#ifndef _ofkEdgeEffectRenderer_H_
#define _ofkEdgeEffectRenderer_H_

#include "ofMain.h"
#include "ofxCv.h"


/*
 CAUTION CALL ORDER
 void beignMask();           //begin rendering mask buffer
 //draw something for mask
 void endMask();             //end rendering mask buffer

 //then render effect
 void render(float x, float y, float w, float h);
 */

class ofkEdgeEffectRenderer{
public:

    void init(int width, int height);
    void update(ofPixels gray); //this should be gray image
    void render(float x, float y, float w, float h);
    void setEnableMask(bool isUseMask);
    
    void beignMask();           //begin rendering mask buffer
    void endMask();             //end rendering mask buffer
    void setAuraColor(int r, int g ,int b);
    void renderMaskImage(float x, float y, float w, float h);
    
    //
    int r, g, b;
    bool isUseMask;

    ofImage edge;
	ofImage edge2;
    ofFbo maskFrameBuffer;
    ofFbo effectFrameBuffer;
    
 };
#endif
