#include "ofkVideoStreamWrapper.h"


ofkVideoStreamWrapper::ofkVideoStreamWrapper(void)
{
}


ofkVideoStreamWrapper::~ofkVideoStreamWrapper(void)
{
}

void ofkVideoStreamWrapper::init(VideoStreamMode mode)
{
	mVideoStreamMode = mode;
	
    if(mVideoStreamMode == VIDEOSTREAM_CAMERA)
	{
        //Initialise, Video Grabber.
        initVideoGrabber(0,640,480);
		
	}else if (mVideoStreamMode == VIDEOSTREAM_UDPRECIEVE)
	{
        //Initialise, UDP Jpeg Stream Grabber.
        initUDPjpegReceiver();
        isUDPjpegReceiverNew = false;
        
	}
	else
	{
        string FILENAME = "movie.mov";
        vidPlayer.loadMovie(FILENAME);
        vidPlayer.setLoopState(OF_LOOP_NORMAL);
		vidPlayer.play();
        
        
	}
    
    errImage.allocate(10, 10,OF_IMAGE_COLOR);
    
}

void ofkVideoStreamWrapper::init(string VideoFilePath)
{
	mVideoStreamMode = VIDEOSTREAM_FILE;
    vidPlayer.loadMovie(VideoFilePath);
    vidPlayer.setLoopState(OF_LOOP_NORMAL);
	vidPlayer.play();
}

void ofkVideoStreamWrapper::update()
{
	if(mVideoStreamMode == VIDEOSTREAM_CAMERA)
	{

#ifdef USE_VIDEO_GRABBER
		vidGrabber.update();
#else
		cout<< "NOT USE_VIDEO_GRABBER " << endl;
#endif
	}else if (mVideoStreamMode == VIDEOSTREAM_UDPRECIEVE)
	{
		//nothing to do ?
	} 
	else if (mVideoStreamMode == VIDEOSTREAM_UDPRECIEVE)
	{

    }
	else if (mVideoStreamMode == VIDEOSTREAM_FILE)
	{
        vidPlayer.update();
    }
}

void ofkVideoStreamWrapper::renderDebug()
{
	if(mVideoStreamMode == VIDEOSTREAM_CAMERA)
	{
		ofDrawBitmapString("ofkVideoStreamWrapper VIDEOSTREAM_CAMERA", 50,50,0);
		
#ifdef USE_VIDEO_GRABBER
		vidGrabber.draw(0,0);
#else
		cout<< "NOT USE_VIDEO_GRABBER " << endl;
#endif
        
        
	}else 	if(mVideoStreamMode == VIDEOSTREAM_UDPRECIEVE)
	{
		ofDrawBitmapString("ofkVideoStreamWrapper VIDEOSTREAM_UDPRECIEVE", 50,50,0);
		ofImage img;
		img.setFromPixels(mPixelsWithIP);
		img.draw(0,0);
	}
    else 	if(mVideoStreamMode == VIDEOSTREAM_FILE)
	{
		ofDrawBitmapString("ofkVideoStreamWrapper VIDEOSTREAM_FILE", 50,50,0);
		vidPlayer.draw(0, 0);
	}
}

//////////////////////////////////////
ofPixelsRef ofkVideoStreamWrapper::getPixel()
{
	if(mVideoStreamMode == VIDEOSTREAM_CAMERA)
	{
#ifdef USE_VIDEO_GRABBER
		return vidGrabber.getPixelsRef();;
#else
        return errImage.getPixelsRef();
		cout<< "NOT USE_VIDEO_GRABBER " << endl;
#endif
        
	}
    else 	if(mVideoStreamMode == VIDEOSTREAM_UDPRECIEVE)
	{
		//if you get some pixel, 
		//then new flag is changed to false
		isUDPjpegReceiverNew = false;
        
		return mPixelsWithIP;
	}
    else 	if(mVideoStreamMode == VIDEOSTREAM_FILE)
	{
		//isUDPjpegReceiverNew = false;
		return vidPlayer.getPixelsRef();
	}
    else
	{
        return errImage.getPixelsRef();
	}
}

//UDP Jepg Stream onReceiveImgae
void ofkVideoStreamWrapper::onReceiveImgae( ofkPixelsWithIP & pix )
{
	mPixelsWithIP = pix;
	isUDPjpegReceiverNew = true;	
}

void ofkVideoStreamWrapper::initUDPjpegReceiver()
{
	mUDPjpegReceiver.init(4054, 9216 * 4); // TODO BUFFER SIZE    
    ofAddListener(mUDPjpegReceiver.newReceivedPixelEvent,this,&ofkVideoStreamWrapper::onReceiveImgae);
}

void ofkVideoStreamWrapper::initVideoGrabber(int deviceID, int w, int h)
{
#ifdef USE_VIDEO_GRABBER
	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(deviceID);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(w, h);
#else
    cout<< "NOT INIT USE_VIDEO_GRABBER " << endl;
#endif
}

void ofkVideoStreamWrapper::setStreamMode( VideoStreamMode mode )
{
	mVideoStreamMode =  mode;
}

bool ofkVideoStreamWrapper::isFrameNew()
{
	if(mVideoStreamMode == VIDEOSTREAM_CAMERA)
	{
#ifdef USE_VIDEO_GRABBER
        return vidGrabber.isFrameNew();
#else
        return false;
        cout<< "NOT INIT USE_VIDEO_GRABBER " << endl;
#endif
    
	}else if(mVideoStreamMode == VIDEOSTREAM_UDPRECIEVE)
	{
		return isUDPjpegReceiverNew;
	}
    else if(mVideoStreamMode == VIDEOSTREAM_FILE)
	{
		return vidPlayer.isFrameNew();
	}
    else
	{
		return false;
	}

}

ofTexture& ofkVideoStreamWrapper::getTexture()
{
	if(mVideoStreamMode == VIDEOSTREAM_CAMERA)
	{
#ifdef USE_VIDEO_GRABBER
		return vidGrabber.getTextureReference();
#else
		return errImage.getTextureReference();
		cout<< "NOT USE_VIDEO_GRABBER " << endl;
#endif
	}
    else 	if(mVideoStreamMode == VIDEOSTREAM_UDPRECIEVE)
	{
		//if you get some pixel, 
		//then new flag is changed to false
		isUDPjpegReceiverNew = false;

		mReceivedPixelTexture.loadData(mPixelsWithIP);
		return mReceivedPixelTexture;
	}
    else 	if(mVideoStreamMode == VIDEOSTREAM_FILE)
	{
		return vidPlayer.getTextureReference();
	}
    else
	{
		return errImage.getTextureReference();
	}
}

