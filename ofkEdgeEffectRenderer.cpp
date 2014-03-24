//
//  ofkEdgeEffectRenderer
//
//  Created by Shunichi Kasahara on 13/01/29.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "ofkEdgeEffectRenderer.h"

//dependencies : ofxCV , openCV

using namespace ofxCv;
using namespace cv;


void ofkEdgeEffectRenderer::init(int width, int height)
{
    maskFrameBuffer.allocate(width, height);
    effectFrameBuffer.allocate(width, height);
    
    r = 120;
    g = 20;
    b = 255;
    
    thresh = 200;
}

void ofkEdgeEffectRenderer::update(ofPixels gray)
{
    //you can change here later
    ofxCv::Canny(gray, edge, (int)thresh, 200, 3);
    ofxCv::blur(edge,  edge, 2);
    edge.update();
    
    ofxCv::blur(edge,  edge2, 30);
    edge2.update();
    
}

void ofkEdgeEffectRenderer::render(float x, float y, float w, float h, bool renderToFB)
{
    
    // --------------  rendering effect FrameBuffer //// From Here
    effectFrameBuffer.begin();
    ofClear(0, 0, 0, 255);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255, 255, 255, 255);
	edge.draw(0, 0);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(r, g, b);
    edge2.draw(0, 0);
    edge2.draw(0, 0);
    edge2.draw(0, 0);
    
    if(isUseMask)
    {
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        ofSetColor(255, 255, 255);
        maskFrameBuffer.draw(0, 0);                     // RENDERING MASK TEXTURE        
    }
    
    effectFrameBuffer.end();
    // --------------  rendering effect FrameBuffer //// END
    
    if(renderToFB)
    {
        //draw mode as add blend
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(255, 255 ,255, 255);
        effectFrameBuffer.draw(x,y,w,h);
        
    }
}

void ofkEdgeEffectRenderer::setEnableMask(bool _isUseMask)
{
    isUseMask = _isUseMask;
}

void ofkEdgeEffectRenderer::beignMask()
{
    maskFrameBuffer.begin();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofClear(0, 0, 0, 255);
}

void ofkEdgeEffectRenderer::endMask()
{
    maskFrameBuffer.end();
    
}

void ofkEdgeEffectRenderer::setAuraColor(int _r, int _g ,int _b)
{
    r = _r;
    g = _g;
    b = _b;
}

void ofkEdgeEffectRenderer::renderMaskImage(float x, float y, float w, float h)
{
    maskFrameBuffer.draw(x, y, w, h);
}

ofTexture& ofkEdgeEffectRenderer::getTextureReference()
{
    return effectFrameBuffer.getTextureReference();
}

