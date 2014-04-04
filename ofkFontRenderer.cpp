//
//  ofkFontRenderer.cpp
//
//  Created by Shunichi Kasahara on 3/17/13.
//
//

#include "ofkFontRenderer.h"


ofkFontRenderer *ofkFontRenderer::m_pInstance = NULL;

ofkFontRenderer::ofkFontRenderer()
{
    resList.clear();
}

ofkFontRenderer::~ofkFontRenderer()
{
    //TODO , closing
    //resList.clear();
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

void ofkFontRenderer::loadFont(const string& filePath, float pointSize, string ID )
{
    ofkFontRenderer *pInstance = getInstance();
	
	if(NULL != pInstance){
        
        if(ID == "")
        {
            //default
            pInstance->font.loadFont(filePath, pointSize);
            
        }else{
            ofTrueTypeFont *font = new ofTrueTypeFont();
            font->loadFont(filePath, pointSize);
            pInstance->resList.insert(pair <string,  ofTrueTypeFont *>(ID, font));
        }

	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkFontRenderer instance");
	}    
}

void ofkFontRenderer::renderString(const string& srt, string ID)
{
    ofkFontRenderer *pInstance = getInstance();
	
	if(NULL != pInstance){
        
        //getFontInstance
        ofTrueTypeFont* pFont = pInstance->getFontInstance(ID);
        if(NULL != pFont)
        {
            pFont->drawString(srt, 0, 0);
        }

	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkFontRenderer instance");
	}
}

void ofkFontRenderer::renderString(const string& srt, float scale, string ID)
{
	glPushMatrix();
	glScalef(scale, scale, scale);
    renderString(srt, ID);
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

ofRectangle ofkFontRenderer::getStringBoundingBox(string str, string ID )
{
    ofkFontRenderer *pInstance = getInstance();
	
    ofRectangle rect;
	if(NULL != pInstance){
        
        
        //getFontInstance
        ofTrueTypeFont* pFont = pInstance->getFontInstance(ID);
        if(NULL != pFont)
        {
            rect = pFont->getStringBoundingBox(str, 0, 0);
        }else{
            ofLog(OF_LOG_NOTICE, "[ofkFontRenderer] invaliad ID");
        }
        
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkFontRenderer instance");
	}
    
    return rect;
}

ofTrueTypeFont* ofkFontRenderer::getFontInstance(string ID)
{
    ofTrueTypeFont* pFont = NULL;
    
    if(ID == "")
    {
        pFont = &font;
    }else{
        std::map<string, ofTrueTypeFont *>::iterator itr;
		itr = resList.find(ID);
        pFont = itr->second;
        
        if(NULL != pFont)
        {
            pFont = &font;
        }else
		{
            ofLog(OF_LOG_NOTICE, "[ofkFontRenderer] invaliad ID, set as a Default");
		}
    }
    
    return pFont;
}

