/*
 *  ofkXMLProperties.h
 *
 *  Created by Shunichi Kasahara on 12/12/28.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


/*
 in Header file : 
 
 #include "ofkXMLProperties.h"
 
 in Cpp file:
 
 mySettings.xml
 and prepare file with name "xxxxx.xml"

 */

//シングルトン実装

#include "ofMain.h"
#include "ofxiPhoneExtras.h"
#include "ofxXmlSettings.h"

#ifndef _ofkXMLProperties_H_
#define _ofkXMLProperties_H_

class ofkXMLProperties
{
	
public:
    
    static bool setXMLFile(const string& fileName);
    static bool setLastOpenData();
    
    static int getPropertyValue(const string& tag, int defaultValue);
    static float getPropertyValue(const string& tag, float defaultValue);
    static string getPropertyValue(const string& tag, const string& defaultValue);

    static void setPropertyValue(const string& tag, int value);
    static void setPropertyValue(const string& tag, float value);
    static void setPropertyValue(const string& tag, const string& value);
	
protected:
	static ofkXMLProperties *getInstance();
	
private:	
	static ofkXMLProperties *m_pInstance;
    static string FileName;
    ofxXmlSettings XML;

	ofkXMLProperties();
	~ofkXMLProperties();
	
};


#endif //_ofkXMLProperties_H_