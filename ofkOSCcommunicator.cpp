//
//  ofkOSCcommunicator.cpp
//  oscSenderExample
//
//  Created by shunichi Kasahara on 12/03/19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ofkOSCcommunicator.h"
#include "IPAddress.h"

string ofkOSCcommunicator::MESSAGE_MATRIX44 = "/ofxOscMessage/ofMatrix4x4";

ofkOSCcommunicator::ofkOSCcommunicator():
mpUserdata(NULL), 
pOSCcallbackFunc(NULL)
{
    isDebugVisible = false;
}

void ofkOSCcommunicator::init(oscCallBack *pOSCCallBacK, void* pUserdata, int Revport , int Sendport)
{
    //set call back function 
    pOSCcallbackFunc = pOSCCallBacK;
    mpUserdata = pUserdata;
    
    InitAddresses();
	GetIPAddresses();
    if(NULL != ip_names[1])
    {
        OWN_IP = ip_names[1];        
    }else
    {
        OWN_IP = "NOT CONNECTED";
    }
    SEND_HOST_IP = "000.000.000.000";
    
    mPort = Sendport;
    
    receiver.setup( Revport );    
    sender.setup( SEND_HOST_IP, mPort );
    
	current_msg_string = 0;
}

void ofkOSCcommunicator::finalize()
{
    
}

void ofkOSCcommunicator::update()
{    
    // hide old messages
	for( int i=0; i<NUM_MSG_STRINGS; i++ ){
		if( timers[i] < ofGetElapsedTimef() )
			msg_strings[i] = "";
	}
    
	// check for waiting messages
	while( receiver.hasWaitingMessages() ){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
        
        //Function Pointer Callback
        if(NULL != pOSCcallbackFunc)
        {
            if(NULL != mpUserdata)
            {
                //send message to call back function 
                (*pOSCcallbackFunc)(m, mpUserdata);
            }
        }
        
        //Event Callback
        ofNotifyEvent(newReceivedOSCEvent, m);

    
        //ßunrecognized message: display on the bottom of the screen

        string msg_string;
        msg_string = m.getAddress();
        msg_string += " : ";
        for( int i=0; i<m.getNumArgs(); i++ ){
            // get the argument type
            //msg_string += m.getArgTypeName( i );
            msg_string += " : ";
            // display the argument - make sure we get the right type
            if( m.getArgType( i ) == OFXOSC_TYPE_INT32 )
                msg_string += ofToString( m.getArgAsInt32( i ) );
            else if( m.getArgType( i ) == OFXOSC_TYPE_FLOAT )
                msg_string += ofToString( m.getArgAsFloat( i ) );
            else if( m.getArgType( i ) == OFXOSC_TYPE_STRING )
                msg_string += m.getArgAsString( i );
            else
                msg_string += "unknown";
        }
        // add to the list of strings to display
        msg_strings[current_msg_string] = msg_string;
        timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
        current_msg_string = ( current_msg_string + 1 ) % NUM_MSG_STRINGS;
        // clear the next line
        msg_strings[current_msg_string] = "";

        
	}
}

void ofkOSCcommunicator::render()
{
    string buf;
	buf = "listening for osc messages on port " + ofToString( mPort );
	ofDrawBitmapString( buf, 10, 20 );
    
    string IP;
    IP = "I am : " + string(OWN_IP) + " PORT is " + ofToString(mPort);
    ofDrawBitmapString( IP, 10, 40 );
    
    IP = string("sending to ") +  string ( SEND_HOST_IP );
    ofDrawBitmapString( IP, 10, 60 );
    
    if(isDebugVisible)
    {
        for( int i=0; i<NUM_MSG_STRINGS; i++ ){
            ofDrawBitmapString( msg_strings[i], 10, 80+15*i );
        }
    }
}

void ofkOSCcommunicator::send(ofxOscMessage message)
{
    sender.sendMessage(message);
}

void ofkOSCcommunicator::setSendIPAddress(string ip)
{
    SEND_HOST_IP = ip;
    sender.setup(SEND_HOST_IP, mPort);
}

// PRE DEFINED OSC Messages gen and decoede
ofxOscMessage ofkOSCcommunicator::genofkOSC(string name, int ID, ofMatrix4x4 mat)
{
    ofxOscMessage m;
    m.setAddress(MESSAGE_MATRIX44);
    
    m.addStringArg(name);         //name
    m.addIntArg(ID);                //ID
    
    for(int i  = 0 ; i < 16 ; i ++)
    {
        m.addFloatArg(mat.getPtr()[i]);
    }
    
    return m;
}

ofMatrix4x4 ofkOSCcommunicator::getFromofkOSC(ofxOscMessage message, string &name, int &ID)
{
    ofMatrix4x4 mat;
    
    if( message.getAddress() == MESSAGE_MATRIX44 )
    {
        name = message.getArgAsString(0);
        ID = message.getArgAsInt32(1);
        
        int offset = 2;
        //MATRIX DATA
        for(int i = 0; i < 16 ; i++)
        {
            mat.getPtr()[i] = message.getArgAsFloat(i + offset);
        }
    }
    return mat;
}
