//
//  OSCcommunicator.h
//  oscSenderExample
//
//  Created by Shunichi Kasahara on 12/03/19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ofMain.h"
#include "ofxOsc.h"

#ifndef oscSenderExample_OSCcommunicator_h
#define oscSenderExample_OSCcommunicator_h

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
 

#define PORT 4053               //for kasahara debug port
#define NUM_MSG_STRINGS 5

class OSCcommunicator
{
public:
    typedef void oscCallBack(ofxOscMessage recieveMessage, void *pUserdata);
	//mean of code : 
    //we call function such that has input (ofxOscMessage recieveMessage)
	//and return void, "oscCallBack"
    
    OSCcommunicator();
    
    void init(oscCallBack *pOSCCallBacK, void* pUserdata);
    void finalize();
    void update();
    void render();
    void setSendIPAddress(string ip);
    void send(ofxOscMessage message);
    string getSendIPAddress(){return SEND_HOST_IP;}
    string getOnwIPAddress(){return OWN_IP;}
    
    void setDebugVisible(bool is){ isDebugVisible = is;}
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
    
};

#endif
