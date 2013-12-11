/*
 *  ofkTexResManager.cpp
 *  iPhoneEmptyExample
 *
 *  Created by Shunichi Kasahara on 10/08/29.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofkTexResManager.h"

ofkTexResManager *ofkTexResManager::m_pInstance = NULL;

ofkTexResManager::ofkTexResManager():
m_isBGRtoRGB(false)
{
	
}

ofkTexResManager::~ofkTexResManager()
{
	//destroy all.
	
}

void ofkTexResManager::setBGRtoRGB(bool isBGRtoRGB)
{
	ofkTexResManager *pInstance = getInstance();
	if(NULL != pInstance){
		pInstance->m_isBGRtoRGB = isBGRtoRGB;
	}else{
	
	}
}

//Static function
ofImage * ofkTexResManager::loadResource(string filePath , string ID)
{
	ofkTexResManager *pInstance = getInstance();
	ofImage *pImg = NULL;
	if(NULL != pInstance){
		pImg = new ofImage();
		pImg->loadImage(filePath);
		
		if(pInstance->m_isBGRtoRGB){
			cout << " BGRtoRGB is not implemented" <<  endl;
			//KsHelper::BGRtoRGB(pImg);
		}
		
		pInstance->resList.insert(pair <string,  ofImage *>(ID, pImg));		
	}else{

		pImg = new ofImage();
	}
	return pImg;
}

//Static function
ofImage* ofkTexResManager::getImage(string ID)
{
	ofkTexResManager *pInstance = getInstance();
	ofImage *pimage = NULL;
	
	if(NULL != pInstance){
		std::map<string, ofImage *>::iterator itr;
		itr = pInstance->resList.find(ID);
		
		if(itr != pInstance->resList.end()){
			pimage = itr->second;
		}else{
			pimage = new ofImage();
		}
		
	}else {
		pimage = new ofImage();
	}
	return pimage;
}

//Static function
ofkTexResManager* ofkTexResManager::getInstance()
{
	if(NULL == m_pInstance){
		m_pInstance = new ofkTexResManager();
	}
	return m_pInstance;
}


