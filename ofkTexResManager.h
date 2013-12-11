/*
 *  ofkTexResManager.h
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

class ofkTexResManager
{
	
public:
		
	static ofImage * loadResource(string filePath , string ID);
	static ofImage * getImage(string ID);
	static void setBGRtoRGB(bool isBGRtoRGB);
	
protected:
	static ofkTexResManager *getInstance();
	
private:	
	static ofkTexResManager *m_pInstance;
	bool m_isBGRtoRGB;
	
	std::map <string, ofImage *> resList;

	ofkTexResManager();
	~ofkTexResManager();
	
};


#endif //_KS_RES_MANEGER_H_