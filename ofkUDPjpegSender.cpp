//
//  ofkUDPjpegSender.cpp
//  imageLoaderExample
//
//  Created by Shunichi Kasahara on 11/3/12.
//
//

#include "ofkUDPjpegSender.h"

ofkUDPjpegSender::ofkUDPjpegSender():
isInitlized(false),
mQuality(OF_IMAGE_QUALITY_LOW),
sendDataSize(0)
{
    
}

bool ofkUDPjpegSender::init(string targetIP, int port, int BufferSize)
{
    bool ret = false;
    
    // first Close it
    udpConnect.Close();
    
    if(udpConnect.Create())
    {
        if(udpConnect.Connect(targetIP.c_str(), port))
        {
            if(udpConnect.SetSendBufferSize(BufferSize))
            {
                ret = true;
                isInitlized = true;
            }
        }
    }
    
    return ret;    
}

bool ofkUDPjpegSender::setBufferSize(int BufferSize)
{
    if(!isInitlized)
        return  false;

    return udpConnect.SetSendBufferSize(BufferSize);
    
}


void ofkUDPjpegSender::setjpegQuality(ofImageQualityType q)
{
    mQuality = q;
}

void ofkUDPjpegSender::setEnableBroadCast(bool isEnableBroadCast)
{
    if(!isInitlized)
        return  ;
    
    udpConnect.SetEnableBroadcast(isEnableBroadCast);
}

bool ofkUDPjpegSender::sendImage(ofPixels &pix)
{
    if(!isInitlized)
        return  false;
    
    s_measureStart = ofGetElapsedTimeMillis();
    
    ofSaveImage(pix, jpegVideoBuffer ,OF_IMAGE_FORMAT_JPEG,mQuality);
    sendDataSize = jpegVideoBuffer.size();
    
    int sent = -1;
    if(sendDataSize < udpConnect.GetSendBufferSize())
    {
        sent = udpConnect.Send(jpegVideoBuffer.getBinaryBuffer(),  jpegVideoBuffer.size());
    }else{
        ofLog(OF_LOG_FATAL_ERROR , "BUFFER SIZE OVER");
    }
    
    s_measureEnd = ofGetElapsedTimeMillis();

    return (-1 != sent);
}

unsigned long ofkUDPjpegSender::getProcessTime()
{
    
    return (s_measureEnd - s_measureStart);
    
}

string ofkUDPjpegSender::getSendIPAdress()
{
    char *adr;
    string res = "ofkUDPjpegSender::undefined";
    if(udpConnect.GetRemoteAddr(adr))
    {
        res = adr;
    }
    
    return res;
}

