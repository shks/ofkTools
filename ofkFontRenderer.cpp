//
//  ofkFontRenderer.cpp
//  SalogationMobile
//
//  Created by Shunichi Kasahara on 3/17/13.
//
//

#include "ofkFontRenderer.h"


ofkFontRenderer *ofkFontRenderer::m_pInstance = NULL;
ofTrueTypeFont ofkFontRenderer::font;

ofkFontRenderer::ofkFontRenderer()
{
	
}

ofkFontRenderer::~ofkFontRenderer()
{
	//destroy all.
	
}


//Static function
ofkFontRenderer* ofkFontRenderer::getInstance()
{
	if(NULL == m_pInstance){
		m_pInstance = new ofkFontRenderer();
	}
	return m_pInstance;
}

void ofkFontRenderer::loadFont(const string& filePath, float pointSize)
{
    ofkFontRenderer *pInstance = getInstance();
	
	if(NULL != pInstance){
        
        pInstance->font.loadFont(filePath, pointSize);
        
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkFontRenderer instance");
	}    
}

void ofkFontRenderer::renderString(const string& srt)
{
    ofkFontRenderer *pInstance = getInstance();
	
	if(NULL != pInstance){
        pInstance->font.drawString(srt, 0, 0);
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkFontRenderer instance");
	}
}

void ofkFontRenderer::renderString(const string& srt, float scale)
{
	glPushMatrix();
	glScalef(scale, scale, scale);
    renderString(srt);
	glPopMatrix();
}

bool ofkFontRenderer::isLoaded()
{
    ofkFontRenderer *pInstance = getInstance();
	bool is = false;
    if(NULL != pInstance){
        is = pInstance->font.isLoaded();
	}else {
        is = false;
	}
    return is;
}

ofRectangle ofkFontRenderer::getStringBoundingBox(string str)
{
    ofkFontRenderer *pInstance = getInstance();
	
    ofRectangle rect;
	if(NULL != pInstance){
        rect = pInstance->font.getStringBoundingBox(str, 0, 0);
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkFontRenderer instance");
	}
    
    return rect;
}