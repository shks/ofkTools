//
//  ofkOSCcommunicator.h
//  oscSenderExample
//
//  Created by Shunichi Kasahara on 12/03/19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"
#include "ofxOsc.h"

#ifndef oscSenderExample_ofkOSCcommunicator_h
#define oscSenderExample_ofkOSCcommunicator_h

/*
 
in Header, Define function for CallBack
 
 static void myOscCallBack(ofxOscMessage recieveMessage, void *pUserdata);
 
 
 //function exsample
 void testApp::myOscCallBack(ofxOscMessage recieveMessage, void *pUserdata)
 {
 testApp *pThis = (testApp *)pUserdata;
 
 if( recieveMessage.getAddress() == "/touch/position" ){
 // both the arguments are int32's
 pThis->mouseX = recieveMessage.getArgAsInt32( 0 );
 pThis->mouseY = recieveMessage.getArgAsInt32( 1 );
 }
 }
 
 */

#define NUM_MSG_STRINGS 50

class ofkOSCcommunicator
{
public:
    typedef void oscCallBack(ofxOscMessage recieveMessage, void *pUserdata);
	//mean of code : 
    //we call function such that has input (ofxOscMessage recieveMessage)
	//and return void, "oscCallBack"
    
    ofkOSCcommunicator();

    void init(oscCallBack *pOSCCallBacK, void* pUserdata, int Revport = 4053, int Sendport = 4053);
   // void init(oscCallBack *pOSCCallBacK, void* pUserdata, int port = 4053);
    void finalize();
    void update();
    void render();
    void setSendIPAddress(string ip);
    void send(ofxOscMessage message);
    string getSendIPAddress(){return SEND_HOST_IP;}
    string getOnwIPAddress(){return OWN_IP;}
    void setDebugVisible(bool is){ isDebugVisible = is;}
    
    // PRE DEFINED OSC Messages gen and decoede
    static ofxOscMessage genofkOSC(string name, int ID, ofMatrix4x4 mat);
    static ofMatrix4x4 getFromofkOSC(ofxOscMessage message, string &name, int &ID);
    
    
    //PRE DEFINED CONSTANT STRING
    static string MESSAGE_MATRIX44;
    
private:
     
    void* mpUserdata;
    oscCallBack *pOSCcallbackFunc;

    ofxOscReceiver	receiver;
    ofxOscSender    sender;

    //for debug 
    int				current_msg_string;
    string			msg_strings[NUM_MSG_STRINGS];
    float			timers[NUM_MSG_STRINGS];
    
    bool isDebugVisible;

    string OWN_IP;
    string SEND_HOST_IP;
    string m_SEND_TEXT;
    int mPort;
    
};

#endif
