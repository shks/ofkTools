//
//  ofkglImageRenderer.coo.cpp
//  eventsExample
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

void ofkglImageRenderer::update()
{

}

void ofkglImageRenderer::render()
{
    glPushMatrix();
    
    //ofSetColor(r*255, g*255, b*255, 255);
    
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
        mImage.draw(-mWidth / 2.0f, -mHeight / 2.0f ,mWidth, mHeight);        
   
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
       mImage.draw(0.0f, 0.0f ,mWidth, mHeight); 
        
    }else if(rectMode == RECTMODE_LEFTTOP)
    {
        mImage.draw(0.0f, -mHeight ,mWidth, mHeight); 
        
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
        
        mImage.draw(-mWidth, -mHeight / 2.0f ,mWidth, mHeight);    
        
    }else if(rectMode == RECTMODE_RIGTHBOTTOM)
    {
        mImage.draw(-mWidth, 0.0f ,mWidth, mHeight); 
    }else if(rectMode == RECTMODE_RIGTHTOP)
    {
        mImage.draw(-mWidth, -mHeight ,mWidth, mHeight);         
        
    }else if(rectMode == RECTMODE_UPPERSIDE)
    {
        mImage.draw(-mWidth / 2.0f, mHeight ,mWidth, mHeight);         
        
    }else if(rectMode == RECTMODE_BOTTOMSIDE)
    {
        mImage.draw(-mWidth / 2.0f, 0.0F ,mWidth, mHeight);     
        
    }else{
        //if rectMode is not define 
        // apply center rendering
        mImage.draw(-mWidth / 2.0f, -mHeight / 2.0f ,mWidth, mHeight);        
    }
    
    //MAYBE WE NEED CHECK THESE LOGIC 
    
    glPopMatrix();
    glColor4f(1.0, 1.0, 1.0, 1.0);
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


void ofkglImageRenderer::setUV(float* uvArray)
{
    for(int i = 0 ; i < 8 ; i ++)
    {
        squareTexCoord[i] = uvArray[i];
    }
}