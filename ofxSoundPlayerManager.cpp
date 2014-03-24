/*
 *  ofxSoundPlayerManager.cpp
 *
 *  Created by Shunichi Kasahara on .
 *
 */

#include "ofxSoundPlayerManager.h"

ofxSoundPlayerManager *ofxSoundPlayerManager::m_pInstance = NULL;

ofxSoundPlayerManager::ofxSoundPlayerManager()
{
	
}

ofxSoundPlayerManager::~ofxSoundPlayerManager()
{
	//destroy all.
	
}

void ofxSoundPlayerManager::play(string ID, float volume, bool isLoop)
{
    
    if(NULL != ofxSoundPlayerManager::getSoundPlayer(ID))
    {
        ofxSoundPlayerManager::getSoundPlayer(ID)->setLoop(isLoop);
        ofxSoundPlayerManager::getSoundPlayer(ID)->setVolume(volume);
        ofxSoundPlayerManager::getSoundPlayer(ID)->play();
    }else{
        
    }
}


void ofxSoundPlayerManager::stop(string ID)
{
    ofxSoundPlayerManager::getSoundPlayer(ID)->stop();
}


//Static function
ofSoundPlayer * ofxSoundPlayerManager::loadResource(string filePath , string ID)
{
	ofxSoundPlayerManager *pInstance = getInstance();
	ofSoundPlayer *p = NULL;
	if(NULL != pInstance){
		p = new ofSoundPlayer();
		p->loadSound(filePath);
        pInstance->resList.insert(pair <string,  ofSoundPlayer *>(ID, p));
	}else{

		p = new ofSoundPlayer();
	}
	return p;
}

//Static function
ofSoundPlayer* ofxSoundPlayerManager::getSoundPlayer(string ID)
{
	ofxSoundPlayerManager *pInstance = getInstance();
	ofSoundPlayer *p = NULL;
	
	if(NULL != pInstance){
		std::map<string, ofSoundPlayer *>::iterator itr;
		itr = pInstance->resList.find(ID);
		
		if(itr != pInstance->resList.end()){
			p = itr->second;
		}else{
			p = new ofSoundPlayer();
		}
		
	}else {
		p = new ofSoundPlayer();
	}
	return p;
}

//Static function
ofxSoundPlayerManager* ofxSoundPlayerManager::getInstance()
{
	if(NULL == m_pInstance){
		m_pInstance = new ofxSoundPlayerManager();
	}
	return m_pInstance;
}


