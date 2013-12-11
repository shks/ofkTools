/*
 *  ofkXMLProperties.cpp
 *
 *  Created by Shunichi Kasahara on 10/08/29.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofkXMLProperties.h"

ofkXMLProperties *ofkXMLProperties::m_pInstance = NULL;
string ofkXMLProperties::FileName = "fileName";

ofkXMLProperties::ofkXMLProperties()
{
	
}

ofkXMLProperties::~ofkXMLProperties()
{
	//destroy all.
	
}

bool ofkXMLProperties::setXMLFile(const string& fileName)
{
    FileName = fileName;
    bool res = false;
    ofkXMLProperties *pInstance = getInstance();

    if(NULL != pInstance){
        //pInstance->XMLへのアクセス
        
        bool isIOSpath = false;
#ifdef TARGET_OSX
        isIOSpath = false;
#else
        //iOS
        isIOSpath = pInstance->XML.loadFile(ofxiPhoneGetDocumentsDirectory() + fileName);
#endif

        if( isIOSpath )
        {
            ofLog(OF_LOG_NOTICE, fileName + " loaded from documents folder!");
            pInstance->XML.bDocLoaded = true;
        }
        else if( pInstance->XML.loadFile(fileName) )
        {
            ofLog(OF_LOG_NOTICE, fileName + " loaded from documents folder!");
            pInstance->XML.bDocLoaded = true;
        }
        else
        {
            ofLog(OF_LOG_NOTICE, "unable to load " + fileName + " check data/ folder");
            pInstance->XML.bDocLoaded = false;
        }
        
        res = pInstance->XML.bDocLoaded;
        
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkXMLProperties instance");
        res = false;
	}

    return res;
}

bool ofkXMLProperties::setLastOpenData()
{
    bool res = false;
    ofkXMLProperties *pInstance = getInstance();
    
    if(NULL != pInstance){
        //pInstance->XMLへのアクセス
        pInstance->XML.setValue("SETTINGS::LastOpenDateYear", ofGetYear());
        pInstance->XML.setValue("SETTINGS::LastOpenDateMonth", ofGetMonth());
        pInstance->XML.setValue("SETTINGS::LastOpenDateDay", ofGetDay());
        pInstance->XML.setValue("SETTINGS::LastOpenDateHour", ofGetHours());
        pInstance->XML.setValue("SETTINGS::LastOpenDateMinute", ofGetMinutes());
        pInstance->XML.setValue("SETTINGS::LastOpenDateSecond", ofGetSeconds());
        
#ifdef TARGET_OSX
        if (pInstance->XML.saveFile( FileName))
#else
        //iOS
        if (pInstance->XML.saveFile( ofxiPhoneGetDocumentsDirectory() + FileName))
#endif
        {
            ofLog(OF_LOG_NOTICE, "setLastOpenData:LastOpenDateSecond as " + ofToString(ofGetSeconds()));
            int res = getPropertyValue("SETTINGS::LastOpenDateSecond", -1);
            ofLog(OF_LOG_NOTICE, "setLastOpenData:LastOpenDateSecond as " + ofToString(res));
            ofLog(OF_LOG_NOTICE, "XML file was Saved ");
        }else
        {
            ofLog(OF_LOG_NOTICE, "XML file was not Saved ");
        }
    }
    
    return res;
}

//// load INT data //////
int ofkXMLProperties::getPropertyValue(const string& tag, int defaultValue)
{
	ofkXMLProperties *pInstance = getInstance();
    int res = defaultValue;
	
	if(NULL != pInstance){
            //pInstance->XMLへのアクセス
        if(pInstance->XML.bDocLoaded)
        {
            res = pInstance->XML.getValue(tag, defaultValue);
            ofLog(OF_LOG_NOTICE, "Vlaue at " + tag + " loaded as" +  ofToString(res) );
            
        }else{
            ofLog(OF_LOG_NOTICE, "XML file was not loaded ");
        }
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkXMLProperties instance");
	}
	return res;
}

//// load FLOAT data //////
float ofkXMLProperties::getPropertyValue(const string& tag, float defaultValue)
{
	ofkXMLProperties *pInstance = getInstance();
    float res = defaultValue;
	
	if(NULL != pInstance){
        //pInstance->XMLへのアクセス
        if(pInstance->XML.bDocLoaded)
        {
            res = pInstance->XML.getValue(tag, defaultValue);
            ofLog(OF_LOG_NOTICE, "Vlaue at " + tag + " loaded as" +  ofToString(defaultValue) );
            
        }else{
            ofLog(OF_LOG_NOTICE, "XML file was not loaded ");
        }
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkXMLProperties instance");
	}
	return res;
}

//// load STRING data /////
string ofkXMLProperties::getPropertyValue(const string& tag, const string& defaultValue)
{
	ofkXMLProperties *pInstance = getInstance();
    string res = defaultValue;
	
	if(NULL != pInstance){
        //pInstance->XMLへのアクセス
        if(pInstance->XML.bDocLoaded)
        {
            res = pInstance->XML.getValue(tag, defaultValue);
            ofLog(OF_LOG_NOTICE, "Vlaue at " + tag + " loaded as" + defaultValue);
        }else{
            ofLog(OF_LOG_NOTICE, "XML file was not loaded ");
        }
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkXMLProperties instance");
	}
	return res;
}


void ofkXMLProperties::setPropertyValue(const string& tag, int value)
{
	ofkXMLProperties *pInstance = getInstance();
    if(NULL != pInstance){
        
        pInstance->XML.setValue(tag, value);
#ifdef TARGET_OSX
        if (pInstance->XML.saveFile( FileName))
#else
    //iOS
        if (pInstance->XML.saveFile( ofxiPhoneGetDocumentsDirectory() + FileName))
#endif
        {
            ofLog(OF_LOG_NOTICE, "XML file was Saved ");            
        }else
        {
           ofLog(OF_LOG_NOTICE, "XML file was not Saved "); 
        }
    }else{
        ofLog(OF_LOG_NOTICE, "XML file was not Saved ");
    }
}

void ofkXMLProperties::setPropertyValue(const string& tag, float value)
{
	ofkXMLProperties *pInstance = getInstance();
    if(NULL != pInstance){
        
        pInstance->XML.setValue(tag, value);
#ifdef TARGET_OSX
        if (pInstance->XML.saveFile( FileName))
#else
            //iOS
       if (pInstance->XML.saveFile( ofxiPhoneGetDocumentsDirectory() + FileName))
#endif
        {
            ofLog(OF_LOG_NOTICE, "XML file was Saved ");
        }
    }else{
        ofLog(OF_LOG_NOTICE, "XML file was not loaded ");
    }
}


void ofkXMLProperties::setPropertyValue(const string& tag, const string& value)
{
	ofkXMLProperties *pInstance = getInstance();
    if(NULL != pInstance){
        
        pInstance->XML.setValue(tag, value);
#ifdef TARGET_OSX
        if (pInstance->XML.saveFile( FileName))
#else
            //iOS
        if (pInstance->XML.saveFile( ofxiPhoneGetDocumentsDirectory() + FileName))
#endif
        {
            ofLog(OF_LOG_NOTICE, "XML file was Saved ");
        }
    }else{
        ofLog(OF_LOG_NOTICE, "XML file was not loaded ");
    }
}


void ofkXMLProperties::setPropertyMatrix44f(const string& tag, const ofMatrix4x4& mat)
{
	ofkXMLProperties *pInstance = getInstance();
    if(NULL != pInstance){
 
        //setting value into XML
        //ex, MATRIX0, MATRIX1, MATRIX2, MATRIX3, 
        for(int i = 0 ; i < 16 ; i++)
        {
            string _tag = tag + ofToString(i);
            pInstance->XML.setValue(_tag, mat.getPtr()[i]);
        }
        
#ifdef TARGET_OSX
        if (pInstance->XML.saveFile( FileName))
#else
            //iOS
            if (pInstance->XML.saveFile( ofxiPhoneGetDocumentsDirectory() + FileName))
#endif
            {
                ofLog(OF_LOG_NOTICE, "XML file was Saved ");
            }
    }else{
        ofLog(OF_LOG_NOTICE, "XML file was not loaded ");
    }
    
    
}


ofMatrix4x4 ofkXMLProperties::getPropertyMatrix44f(const string& tag)
{
    ofkXMLProperties *pInstance = getInstance();
    
    ofMatrix4x4 mat;
    mat.makeIdentityMatrix();
	
	if(NULL != pInstance){
        //pInstance->XMLへのアクセス
        if(pInstance->XML.bDocLoaded)
        {
            for(int i = 0 ; i < 16 ; i++)
            {
                string _tag = tag + ofToString(i);
                mat.getPtr()[i] = pInstance->XML.getValue(_tag, 0.0);
            }            
        }else{
            ofLog(OF_LOG_NOTICE, "XML file was not loaded ");
        }
	}else {
        ofLog(OF_LOG_NOTICE, "Can not get ofkXMLProperties instance");
	}
	return mat;
    
}




//Static function
ofkXMLProperties* ofkXMLProperties::getInstance()
{
	if(NULL == m_pInstance){
		m_pInstance = new ofkXMLProperties();
	}
	return m_pInstance;
}


