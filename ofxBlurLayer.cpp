//
//  ofxBlurLayer.cpp
//  emptyExample
//
//  Created by Shunichi Kasahara on 9/30/13.
//
//

#include "ofxBlurLayer.h"


ofxBlurLayer::ofxBlurLayer():
    power(0.0),
    m_active(true),
	m_afterImage(255)
{
    
}

ofxBlurLayer::~ofxBlurLayer()
{
    
}

void ofxBlurLayer::setup(int width, int height)
{
    m_blur.setup(width, height, 6, .1, 4);
}

void ofxBlurLayer::update()
{
    m_blur.setScale(power);
//    blur.setRotation(ofMap(mouseY, 0, ofGetHeight(), -PI, PI));
}

void ofxBlurLayer::begin()
{
    if(m_active)
    {
        ofPushStyle();
        m_blur.begin();
		ofBackground(0,0,0,m_afterImage);
		ofEnableAlphaBlending();
    }
}

void ofxBlurLayer::end()
{
    if(m_active)
    {

        m_blur.end();
        ofPopStyle();        
    }
}

void ofxBlurLayer::draw()
{
    if(m_active){
        m_blur.draw();
    }
}

void ofxBlurLayer::drawDebug()
{
    if(m_active)
	{
		ofDrawBitmapStringHighlight("ofxBlurLayer", 0, 0);
    	m_blur.draw();
	}
}

void ofxBlurLayer::setActive(bool isActive)
{
	m_active = isActive;
}
	
void ofxBlurLayer::setAfterimageRate(int power)
{
	power = (power < 0)? 0 : power;
	power = (power > 255)? 255 : power;
	
	m_afterImage = 255 - power;
}