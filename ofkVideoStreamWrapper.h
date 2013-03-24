#pragma once

#include "ofMain.h"
#include "ofkUDPjpegReceiver.h"

/*
Wrap camera video Stream and UDP Jpeg Stream 
TODO : debug the behaivor in windows
*/

#ifdef WIN32
    #define USE_VIDEO_GRABBER
#else

#endif

#define USE_VIDEO_GRABBER

class ofkVideoStreamWrapper
{
public:

	enum VideoStreamMode
	{
		VIDEOSTREAM_CAMERA,
		VIDEOSTREAM_UDPRECIEVE,
        VIDEOSTREAM_FILE
	};
    
	ofkVideoStreamWrapper(void);
	~ofkVideoStreamWrapper(void);

	void init(VideoStreamMode mode);
	
	void renderDebug();
	ofPixelsRef getPixel();
	ofTexture& getTexture();

	void setStreamMode(VideoStreamMode mode);
	bool isFrameNew();
	
	void update();                      //-> this will be protected. Event Driven

private:
	VideoStreamMode mVideoStreamMode;
	
	void initVideoGrabber(int deviceID, int w, int h);
	void initUDPjpegReceiver();
	void onReceiveImgae(ofkPixelsWithIP & pix);

	//Video Grab
#ifdef USE_VIDEO_GRABBER
	ofVideoGrabber 		vidGrabber;
#endif
    ofVideoPlayer       vidPlayer;
    
	//jpeg Stream
	ofkUDPjpegReceiver	mUDPjpegReceiver;
	ofkPixelsWithIP mPixelsWithIP;		
	bool isUDPjpegReceiverNew;
    ofImage errImage;
    
	ofTexture mReceivedPixelTexture;

};

