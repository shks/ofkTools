//
//  ofkUDPjpegReceiver.h
//  SecondSurfaceServer
//
//  Created by Shunichi Kasahara on 11/23/12.
//
//

#ifndef __SecondSurfaceServer__ofkUDPjpegReceiver__
#define __SecondSurfaceServer__ofkUDPjpegReceiver__

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxNetwork.h"

/*
 
 // in testApp.h, define this function to get decoded pixel data
 void onReceiveImgae(ofkPixelsWithIP & pix);
 
 
 // add the onReceiveImgae method to listen for ofkUDPjpegReceiver newReceivedPixelEvent
 ofAddListener(newReceivedPixelEvent,this,&testApp::onReceiveImgae);

 //usage Exmaple
 mUDPjpegReceiver.init(4054, 9216 * 4);
 ofAddListener(mUDPjpegReceiver.newReceivedPixelEvent,this,&testApp::onReceiveImgae);

 */
class ofkPixelsWithIP : public ofPixels
{
public:
    string IP;
};

class ofkUDPjpegReceiver
{
    
public:
    
    ofkUDPjpegReceiver(void);
    
    void init(int port, int BufferSize);
    void update(ofEventArgs & args);
    
    void enable(){
	    ofAddListener(ofEvents().update, this, &ofkUDPjpegReceiver::update);
	};
    
	void disable(){
	    ofRemoveListener(ofEvents().update, this, &ofkUDPjpegReceiver::update);
	};
    
    ofEvent< ofkPixelsWithIP > newReceivedPixelEvent;
    
private:
    
    ofxUDPManager udpConnect;
    int mBufferSize;
    ofBuffer jpegVideoBuffer;
    
};


#endif /* defined(__SecondSurfaceServer__ofkUDPjpegReceiver__) */
