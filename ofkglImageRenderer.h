//
//  Created by Shunichi Kasahara on 12/03/04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//  2012.06.04  add useImageSize() function 

#ifndef eventsExample_ofkglImageRenderer_h
#define eventsExample_ofkglImageRenderer_h

#include "ofMain.h"

class ofkglImageRenderer
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
    
    /* 
     
     +------+
     |      |
     |      |
     +------+
     
    */
    
    ofkglImageRenderer();
    ~ofkglImageRenderer();

	void update();
    void render();
    
    void setImageFile(string imageFileName);
    void setImage(ofImage image);
    void setTexture(ofTexture tex);
    void useImageSize();
    
    //void setUV(float * uvArray);
    void setSize(float width, float height);

    bool upsideDown;
    float r, b, g, a;
    float x, y, z;
    float rx, ry, rz;
    float scaleX, scaleY;
    RECTMODE rectMode;
    
    float getWidth(){ return mWidth; }
    float getHeight(){ return mHeight; }
    float getImgRatio() {return (mHeight / mWidth);}
    bool  isHitTest(ofPoint FrameBufferPoint);
    
private:
    
    float mWidth;
    float mHeight;
    float squareTexCoord[8];
    
    void internalDraw(float x, float y, float w, float h);
    ofTexture mTexture;
    ofImage mImage;
};
#endif
