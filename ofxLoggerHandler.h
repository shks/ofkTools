//
//  ofxLoggerHandler.h
//  loggerTest
//
//  Created by Shunichi Kasahara on 9/6/13.
//
//

#ifndef __loggerTest__ofxLoggerHandler__
#define __loggerTest__ofxLoggerHandler__

#include "ofMain.h"
#include "ofxLogger.h"

class ofxLoggerHandler
{
public:
    static void debugDraw()
    {
        ofSetupScreen();
        ofSetColor(23, 130,255);
        
        if(isLog){            
            ofDrawBitmapStringHighlight("IsLogging", 0, ofGetHeight() * 0.95);
        }

        ofDrawBitmapStringHighlight("UserID" + UserID, 100, ofGetHeight() * 0.95);
        ofSetColor(255, 255,255);
    }
    
    static void setUserID(string ID)
    {
        UserID = ID;
    };
    
    static void setRecogState(string recogState)
    {
        RecogState = recogState;
    };
    
    static void setAppState(string appState)
    {
        AppState = appState;
    };
    
    static bool getIsLogActive()
    {
        return isLog;
    };
    
    static void init()
    {
        //if(filePath != "")
        //{
           // ofxLog::setFilePath(filePath);
        //}
        
        ofxLog::enableFileRotationMins(1);
        ofxLog::enableHeader();
        ofxLog::enableHeaderFrameNum();
        ofxLog::enableHeaderMillis();
        ofxLog::setFileRotationMaxNum(100);
            
    }
        //all static functoin
    static void startLog(string logNote)
    {
        ofxLog::enableFileRotationMins(1);
        ofxLog::enableHeader();
        ofxLog::enableHeaderFrameNum();
        ofxLog::enableHeaderMillis();
        ofxLog::setFileRotationMaxNum(100);
        
        
        ofxLog::enableHeader();
        ofxLog::enableHeaderFrameNum();
        ofxLog::enableHeaderMillis();
        
        ofxLog::setLevel(OF_LOG_NOTICE);
        ofxLog() << "log file: " << ofxLog::getFilePath();
        ofxLog() << UserID << "," << logNote;
    
        isLog = true;
    };
    
    static void pauseLog()
    {
        ofxLog::enableHeader();
        ofxLog() << UserID << "," << "pauseLog";
        
        isLog = false;
    };

    static string genStringOfMatrix(const string matName, const ofMatrix4x4 & mat)
    {
        ofVec3f eularAng = mat.getRotate().getEuler();
        ofVec3f trans = mat.getTranslation();
        
        string str;
        str = matName + ",eularAng," + ofToString(eularAng.x,3) + ","
                                    + ofToString(eularAng.y,3) + ","
                                    + ofToString(eularAng.z,3) + ","
                        +"Trans,"   + ofToString(trans.x,3) + ","
                                    + ofToString(trans.y,3) + ","
                                    + ofToString(trans.z,3) + ",";
        
        return str;
        
    };
    
    static bool addLogLineWithMatrix(const string logLine, const ofMatrix4x4 & mat)
    {
        if(!isLog)
            return false;

        ofVec3f eularAng = mat.getRotate().getEuler();
        ofVec3f trans = mat.getTranslation();
        
        ofxLog() << UserID << ","
                << AppState << ","
                << RecogState << ","
                <<logLine << "," << "eularAng" << "," << eularAng.x << "," << eularAng.y << "," << eularAng.z << "," << "Trans" << "," << trans.x << "," << trans.y << "," << trans.z;

        return true;
    }
    
    static bool addLogLine(const string logLine)
    {
        if(isLog){
            //ofxLog() << UserID << "," << RecogState << "," << logLine;
            ofxLog()
            << UserID << ","
            << AppState << ","
            << RecogState << ","
            << logLine << ",";
            
            return true;
        }else{
            return false;
        }

    }
private:
    static bool     isLog;
    static string   UserID;
    static string   RecogState;
    static string   AppState;
};


#endif /* defined(__loggerTest__ofxLoggerHandler__) */
