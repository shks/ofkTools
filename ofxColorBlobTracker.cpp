//
//  ofxColorBlobTracker.cpp
//  opencvExample
//
//  Created by Shunichi Kasahara on 12/16/13.
//
//

#include "ofxColorBlobTracker.h"


void ofxColorBlobTracker::init(int width, int height)
{
    one.pos = ofVec2f(0,0);
    
	camWidth = width;
	camHeight = height;
    
	colorImg.allocate(camWidth, camHeight);
	colorImgHSV.allocate(camWidth, camHeight);
    
	hueImg.allocate(camWidth, camHeight);
	satImg.allocate(camWidth, camHeight);
	briImg.allocate(camWidth, camHeight);
    
	reds.allocate(camWidth, camHeight);
    
	colorTrackedPixelsRed =new unsigned char [camWidth*camHeight];
    
	trackedTextureRed.allocate(camWidth, camHeight, GL_LUMINANCE);
    isShowDebug = false;
}

void ofxColorBlobTracker::update(ofPixelsRef pixelRef)
{
	colorImg.setFromPixels(pixelRef);
    
	colorImgHSV = colorImg;
	colorImgHSV.convertRgbToHsv();
    
	colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
    
	hueImg.flagImageChanged();
	satImg.flagImageChanged();
	briImg.flagImageChanged();
    
	unsigned char * huePixels = hueImg.getPixels();
	unsigned char * satPixels = satImg.getPixels();
	unsigned char * briPixels = briImg.getPixels();
    
	int nPixels = camWidth*camHeight;
    
    if(one.bri < 230)
    {
        for (int i = 0; i < nPixels; i++){                                           //let's go through every pixel in hue pixels
            if ((huePixels[i] >= one.hue - 12 && huePixels[i] <= one.hue + 12) &&    //if the hue is of a certain range
                (satPixels[i] >= one.sat - 24 && satPixels[i] <= one.sat + 40) &&
                (briPixels[i] >= one.bri - 30 && briPixels[i] <= one.bri + 30)){    //if the saturation is of a certain range
                colorTrackedPixelsRed[i] = 255;                                      //mark this corresponding pixel white
            } else {
                colorTrackedPixelsRed[i] = 0;                                        //if it doesn't fit then color the corresponding pixel black
            }
        }
        
    }else
    {
        for (int i = 0; i < nPixels; i++){                                           //let's go through every pixel in hue pixels
            if ((huePixels[i] >= one.hue - 24 && huePixels[i] <= one.hue + 24) &&    //if the hue is of a certain range
                (satPixels[i] >= one.sat - 24 && satPixels[i] <= one.sat + 200) &&
                (briPixels[i] >= one.bri - 150 && briPixels[i] <= one.bri + 150)){    //if the saturation is of a certain range
                colorTrackedPixelsRed[i] = 255;                                      //mark this corresponding pixel white
            } else {
                colorTrackedPixelsRed[i] = 0;                                        //if it doesn't fit then color the corresponding pixel black
            }
        }
    }
    
	reds.setFromPixels(colorTrackedPixelsRed, camWidth, camHeight);
    reds.blurGaussian();
    
	finderRed.findContours(reds, 10, nPixels/3, 1, false, true);
    
	trackedTextureRed.loadData(colorTrackedPixelsRed,
                               camWidth, camHeight, GL_LUMINANCE);
    
	if (finderRed.blobs.size()!= 0) {
		one.pos = ofVec2f(finderRed.blobs[0].centroid.x,
                          finderRed.blobs[0].centroid.y);
        
        isTrack = true;
        pos = one.pos;
        
        //Dispatch Event
        ofNotifyEvent(newFoundBlobEvent, pos);
        
	}else{
        isTrack = false;
    }
    
}

void ofxColorBlobTracker::draw()
{
    if(!isShowDebug) return;
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    ofFill();
    ofSetColor(0,0,0,200);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(255,12,120);
    ofDrawBitmapStringHighlight("ofxColorBlobTracker Debug View", 0, ofGetHeight() - 20);
    ofPopStyle();

    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofRect(0, 0, camWidth, camHeight);
    ofPopStyle();

    ofDrawBitmapStringHighlight("Video To Pickup Color MODE, point the color yo want to track", 0, 0);
    ofDrawBitmapStringHighlight("Video To Pickup Color", 0, 20);
    finderRed.draw();
    
    ofColor col;
    col.setHsb(one.hue, one.sat, one.bri);
    ofSetColor(col);
    ofRect(0, camHeight + 20, 20, -20);
    ofSetColor(255);
    ofDrawBitmapString("hue : " + ofToString(one.hue) + "Sat : " + ofToString(one.sat) + "Bri : " + ofToString(one.bri) , 20, camHeight + 20);
    
	colorImgHSV.draw(camWidth + 20, 0.0);

	
	glPushMatrix();
    glTranslatef(camWidth + 20, camHeight + 40, 0);
    reds.draw(0, 0);
	glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, camHeight + 40, 0);
    trackedTextureRed.draw(0, 0);
    finderRed.draw();
	glPopMatrix();
    
    
    
    //reds
    
	if (finderRed.blobs.size()!=0) {
		char tempStr1[255];
		sprintf(tempStr1, "x:%f y:%f",
                finderRed.blobs[0].centroid.x,
                finderRed.blobs[0].centroid.y);
		ofDrawBitmapString(tempStr1, 20, 250);
	}
    
}


void ofxColorBlobTracker::mousePressed(int x, int y)
{
    unsigned char * huePixels = hueImg.getPixels();  //teh hue
    unsigned char * satPixels = satImg.getPixels();  //teh saturation
    unsigned char * briPixels = briImg.getPixels();  //teh brightness*/ //unnecessary really, hue and sat should be enough
    
    x = MIN(x,hueImg.width-1);     //find the smallest value out of those two so we don't crash if we click outside of the camera image
    y = MIN(y,hueImg.height-1);
    
        one.hue = huePixels[x+(y*hueImg.width)];  //set the hue
        one.sat = satPixels[x+(y*satImg.width)];  //set the sat
        one.bri = briPixels[x+(y*briImg.width)];
    
}

void ofxColorBlobTracker::setTrackColor(HSBColor col)
{
    one = col;
}

HSBColor ofxColorBlobTracker::pickupColor(int x, int y)
{
    if(!isShowDebug)
    {
        HSBColor _col;
        return _col;
    }
    
    unsigned char * huePixels = hueImg.getPixels();  //teh hue
    unsigned char * satPixels = satImg.getPixels();  //teh saturation
    unsigned char * briPixels = briImg.getPixels();  //teh brightness*/ //unnecessary really, hue and sat should be enough

    x = MIN(x,hueImg.width-1);     //find the smallest value out of those two so we don't crash if we click outside of the camera image
    y = MIN(y,hueImg.height-1);

    HSBColor _one;
    
    _one.hue = huePixels[x+(y*hueImg.width)];  //set the hue
    _one.sat = satPixels[x+(y*satImg.width)];  //set the sat
    _one.bri = briPixels[x+(y*briImg.width)];
    
    return _one;
}

void ofxColorBlobTracker::setVisible(bool is)
{
    isShowDebug = is;
}

