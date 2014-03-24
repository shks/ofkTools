//
//  ofxglVideoRenderer.coo.cpp
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/03/04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
//  2012.06.04  add useImageSize() function 

#include "ofxglVideoRenderer.h"

ofxglVideoRenderer::ofxglVideoRenderer()
{
    r = b = g = a = 1.0;
    x = y = z = 0.0;
    rx = ry = rz = 0.0;
    scaleX = scaleY = 1.0f;
    
    mWidth = 100.0f;
    mHeight = 100.0f;
    upsideDown = false;
    rectMode = RECTMODE_CENTER;
    
    isPlayed = false;
}

void ofxglVideoRenderer::update()
{
	if(m_Video.isLoaded()){
		m_Video.update();
	}
}

void ofxglVideoRenderer::render()
{
    glPushMatrix();
    
    ofSetColor(r*255, g*255, b*255, a*255);

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
        m_Video.draw(0.0f, -mHeight / 2.0f ,mWidth, mHeight);               
    
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
        //if rectMode is not define 
        // apply center rendering
        internalDraw(-mWidth / 2.0f, -mHeight / 2.0f ,mWidth, mHeight);        
    }
    
    glPopMatrix();
   
}

void ofxglVideoRenderer::setVideoFile(string videoFileName)
{
	m_Video.loadMovie(videoFileName);

	if(m_Video.isLoaded())
	{
		useImageSize();        
	}else{
		ofLog(OF_LOG_WARNING , "Video file was not loaded from " + videoFileName );
	}

	//m_Video.setFrame(0);
	m_Video.setLoopState(OF_LOOP_NORMAL);
    m_Video.play();
    m_Video.setPaused(true);
    
}

void ofxglVideoRenderer::useImageSize()
{
    if (m_Video.isLoaded())
    {
        mWidth = m_Video.width;
        mHeight = m_Video.height;
    }
}

void ofxglVideoRenderer::setSize(float width, float height)
{
    mWidth = width;
    mHeight = height;
}

void ofxglVideoRenderer::setLoop(bool isloop)
{
	if(isloop){
		m_Video.setLoopState(OF_LOOP_NORMAL);
	}else{
		m_Video.setLoopState(OF_LOOP_NONE);
	}
}

void ofxglVideoRenderer::internalDraw(float x, float y, float w, float h)
{
    if(m_Video.isLoaded())
    {
        if(isPlayed)
        {
            m_Video.draw(x, y ,w, h);
        }
    }else
    {
        ofRect(x, y, w, h);
    }
}

void ofxglVideoRenderer::resume()
{
    m_Video.setPaused(false);
//	m_Video.play();
}

void ofxglVideoRenderer::play()
{
    m_Video.setSpeed(1.0);
    m_Video.setPaused(false);
    //m_Video.play();
	//m_Video.setFrame(0);
    
    isPlayed = true;
}

void ofxglVideoRenderer::stop()
{
    m_Video.setPaused(true);
	//m_Video.stop();
}

void ofxglVideoRenderer::setPosition(float frameNum)
{
	m_Video.setPosition(frameNum);
    
}


void ofxglVideoRenderer::playWithSpeed(float speed)
{
    m_Video.setSpeed(speed);
    m_Video.setPaused(false);
}

float ofxglVideoRenderer::getCurrentPos()
{
    return m_Video.getPosition();
}

