//
//  ofkUDPjpegReceiver.cpp
//  SecondSurfaceServer
//
//  Created by Shunichi Kasahara on 11/23/12.
//
//

#include "ofkUDPjpegReceiver.h"

#define DEF_BUFSIZE (9216 * 4)

ofkUDPjpegReceiver::ofkUDPjpegReceiver():
mBufferSize(DEF_BUFSIZE)
{
    
}

void ofkUDPjpegReceiver::init(int port, int BufferSize)
{
    udpConnect.Create(); // UDPソケットの作成
    udpConnect.Bind(port); // ポート番号にバインドする
    udpConnect.SetNonBlocking(true); // ノンブロッキングモードにする
    udpConnect.SetReceiveBufferSize(BufferSize);
    
    mBufferSize = BufferSize;
    
    enable();
}

void ofkUDPjpegReceiver::update(ofEventArgs & args)
{
    char revBuffer[mBufferSize];
    int ret = udpConnect.Receive(revBuffer,mBufferSize);
    
    char address[255];
    udpConnect.GetRemoteAddr(address);
    string ip_String;
    ip_String = address;
    
    
    //CHECK THIS
    if(ret != -1)
    {
        //Read Buffer
        jpegVideoBuffer.set(revBuffer, mBufferSize);
        
        //decode from Buffer into Jpeg
        ofkPixelsWithIP decodedPix;
        if( ofLoadImage(decodedPix, jpegVideoBuffer))
        {
            //decodedvideoImage.setFromPixels(re_pix);
            decodedPix.IP = ip_String;
            ofNotifyEvent(newReceivedPixelEvent,decodedPix,this);
        }else
        {
            ofLog(OF_LOG_NOTICE, "Can not load from Buffer" + ofToString(ret));
        }
    }
}