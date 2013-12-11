//
//  Created by Shunichi Kasahara on 12/03/04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//  2012.06.04  add useImageSize() function 

#include "ofkglImageRenderer.h"

static const float verticies[16]=
{
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

ofkglImageRenderer::ofkglImageRenderer()
{
    r = b = g = a = 1.0;
    x = y = z = 0.0;
    rx = ry = rz = 0.0;
    scaleX = scaleY = 1.0f;
    
    mWidth = 100.0f;
    mHeight = 100.0f;
    upsideDown = false;
    rectMode = RECTMODE_CENTER;
}

ofkglImageRenderer::~ofkglImageRenderer()
{
	mTexture.clear();
	mImage.clear();
}

void ofkglImageRenderer::update()
{

}

void ofkglImageRenderer::render()
{
    glPushMatrix();
    
    glColor4f(r, g, b, a);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glTranslatef(x, y, z);
    glRotatef(rx, 1.0, 0.0, 0.0);
    glRotatef(ry, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0, 0.0, 1.0);
    glScalef(scaleX, scaleY, 1.0f);
    
    if(upsideDown)
    {
        glScalef(1.0, -1.0f, 1.0f);
    }
    
    //based on rect rendering mode
    if(rectMode == RECTMODE_CENTER)
    {
        internalDraw(-mWidth / 2.0f, -mHeight / 2.0f ,mWidth, mHeight);        
   
    }else if(rectMode == RECTMODE_LEFTSIDE)
    {
        /*
         +-----------
         +          |
         +          |
         +          |
         +-----------
         */
        mImage.draw(0.0f, -mHeight / 2.0f ,mWidth, mHeight);               
    
    }else if(rectMode == RECTMODE_LEFTBOTTOM)
    {
       internalDraw(0.0f, 0.0f ,mWidth, mHeight); 
        
    }else if(rectMode == RECTMODE_LEFTTOP)
    {
        internalDraw(0.0f, -mHeight ,mWidth, mHeight); 
        
    }else if(rectMode == RECTMODE_RIGHTSIDE)
    {
        //I need to test;
        /*
         +-----------
         |          +
         |          +
         |          +
         +-----------
         */
        
        internalDraw(-mWidth, -mHeight / 2.0f ,mWidth, mHeight);    
        
    }else if(rectMode == RECTMODE_RIGTHBOTTOM)
    {
        internalDraw(-mWidth, 0.0f ,mWidth, mHeight); 
    }else if(rectMode == RECTMODE_RIGTHTOP)
    {
        internalDraw(-mWidth, -mHeight ,mWidth, mHeight);         
        
    }else if(rectMode == RECTMODE_UPPERSIDE)
    {
        internalDraw(-mWidth / 2.0f, mHeight ,mWidth, mHeight);         
        
    }else if(rectMode == RECTMODE_BOTTOMSIDE)
    {
        internalDraw(-mWidth / 2.0f, 0.0F ,mWidth, mHeight);     
        
    }else{
        //  if rectMode is not define
        //  apply center rendering
        internalDraw(-mWidth / 2.0f, -mHeight / 2.0f ,mWidth, mHeight);        
    }

    glPopMatrix();
    glColor4f(1.0, 1.0, 1.0, 1.0);
}

bool ofkglImageRenderer::isHitTest(ofPoint FrameBufferPoint)
{
    ofPoint RT = ofPoint(x, y) + ofPoint(- mWidth * scaleX * 0.5 , - mHeight * scaleY * 0.5);
    ofPoint RB = ofPoint(x, y) + ofPoint(- mWidth * scaleX * 0.5 ,   mHeight * scaleY * 0.5);
    ofPoint LT = ofPoint(x, y) + ofPoint(+ mWidth * scaleX * 0.5 , - mHeight * scaleY * 0.5);
    ofPoint LB = ofPoint(x, y) + ofPoint(+ mWidth * scaleX * 0.5 ,   mHeight * scaleY * 0.5);
    
    bool res = false;
    
    if(RT.x < FrameBufferPoint.x && FrameBufferPoint.x < LT.x)
    {
        if(RT.y < FrameBufferPoint.y && FrameBufferPoint.y < RB.y)
        {
            res = true;
        }
    }

    return res;
}

void ofkglImageRenderer::setImage(ofImage image)
{
    mImage = image;
    mImage.setUseTexture(true);
    mTexture = mImage.getTextureReference();
}


void ofkglImageRenderer::setTexture(ofTexture tex)
{
    mTexture = tex;
}

void ofkglImageRenderer::setImageFile(string imageFileName)
{
    mImage.loadImage(imageFileName);
    mTexture = mImage.getTextureReference();
}

void ofkglImageRenderer::useImageSize()
{
    if (mImage.isAllocated())
    {
        mWidth = mImage.width;
        mHeight = mImage.height;
    }
}


void ofkglImageRenderer::setSize(float width, float height)
{
    mWidth = width;
    mHeight = height;
}

/*
void ofkglImageRenderer::setUV(float* uvArray)
{
    for(int i = 0 ; i < 8 ; i ++)
    {
        squareTexCoord[i] = uvArray[i];
    }
}*/

void ofkglImageRenderer::internalDraw(float x, float y, float w, float h)
{
    if(mImage.bAllocated())
    {
        mImage.draw(x, y ,w, h); 
    }else
    {
        ofRect(x, y, w, h);
    }
}

