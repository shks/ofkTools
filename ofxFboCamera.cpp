//
//  ofxFboCamera.cpp
//  Cam_EyeTest
//
//  Created by Shunichi Kasahara on 12/12/13.
//
//

#include "ofxFboCamera.h"

bool ofxFboCamera::isShowDebugInformation = false;

//static function
bool ofxFboCamera::setEnableDebugInfo(bool is)
{
    isShowDebugInformation = is;
}

ofxFboCamera::ofxFboCamera(void) :
isFBOuse(false),
cameraName("Undefined")
{
    
}

void ofxFboCamera::init(int FboWidth, int FboHeight, string _cameraName)
{
    fbo.allocate(FboWidth, FboHeight, GL_RGBA);
    cameraName = _cameraName;
}

void ofxFboCamera::begin(bool isFbo)
{
    isFBOuse = isFbo;

    if(isFBOuse && fbo.isAllocated()) fbo.begin();
    camera.begin();
}

void ofxFboCamera::end()
{
    camera.end();
    if(isFBOuse && fbo.isAllocated()) fbo.end();
}

void ofxFboCamera::draw(float x = 0, float y = 0)
{
    draw(x, y, fbo.getWidth(), fbo.getHeight());
}

void ofxFboCamera::draw(float x, float y, float scale)
{
    draw(x, y, fbo.getWidth() * scale, fbo.getHeight() * scale);
}

void ofxFboCamera::draw(float x, float y, float w, float h)
{
    if(fbo.isAllocated()){
        fbo.draw(x, y, w, h);
    }
    
    if(isShowDebugInformation){
        
        ofPushStyle();
        
        ofSetColor(255, 255, 255);
        ofNoFill();
        ofRect(x, y, w, h);
        ofPopStyle();
        
        
        ofPushMatrix();
        ofTranslate(x, y);
        drawDebug();
        ofPopMatrix();
    }
}

void ofxFboCamera::drawDebug()
{
    ofDrawBitmapStringHighlight(cameraName, 0, 20);
    
}
