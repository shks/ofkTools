//
//  ksRectRenderer.h
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/03/04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//  2012.06.04  add useImageSize() function 

#ifndef eventsExample_ofxglVideoRenderer_h
#define eventsExample_ofxglVideoRenderer_h

#include "ofMain.h"

class ofxglVideoRenderer
{
    
public:
    
    //how to render the image rectangle
    enum RECTMODE
    {
        RECTMODE_CENTER = 0,
        
        RECTMODE_LEFTSIDE,
        RECTMODE_RIGHTSIDE,
        RECTMODE_UPPERSIDE,
        RECTMODE_BOTTOMSIDE,
        
        RECTMODE_LEFTTOP,
        RECTMODE_LEFTBOTTOM,
        RECTMODE_RIGTHTOP,
        RECTMODE_RIGTHBOTTOM
    };
    

    ofxglVideoRenderer();
    void update();
    void render();
    
	void setLoop(bool isloop);
    void setVideoFile(string imageFileName);
    void setSize(float width, float height);
    void useImageSize();

	////Play control
	void resume();
	void play();
	void stop();
	void setFrame(int frameNum);

    bool upsideDown;
    float r, b, g, a;
    float x, y, z;
    float rx, ry, rz;
    float scaleX, scaleY;
    RECTMODE rectMode;
    
    float getWidth(){ return mWidth; }
    float getHeight(){ return mHeight; }
    float getImgRatio() {return (mHeight / mWidth);}

private:
    float mWidth;
    float mHeight;
    void internalDraw(float x, float y, float w, float h);

	ofVideoPlayer m_Video;

};
#endif
