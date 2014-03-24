/*
 *  ofxSoundPlayerManager.h
 *  iPhoneEmptyExample
 *
 *  Created by Shunichi Kasahara on 10/08/29.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


//シングルトン実装

#include "ofMain.h"
#include <map>

#ifndef _OFK_RES_MANEGER_H_
#define _OFK_RES_MANEGER_H_

class ofxSoundPlayerManager
{
	
public:
		
	static ofSoundPlayer * loadResource(string filePath , string ID);
	static ofSoundPlayer * getSoundPlayer(string ID);
    static void play(string ID, float volume, bool isLoop);
    static void stop(string ID);
    
//    /ofSoundPlayer  synth;
	
protected:
	static ofxSoundPlayerManager *getInstance();
	
private:	
	static ofxSoundPlayerManager *m_pInstance;
	
	std::map <string, ofSoundPlayer *> resList;

	ofxSoundPlayerManager();
	~ofxSoundPlayerManager();
	
};


#endif //_KS_RES_MANEGER_H_