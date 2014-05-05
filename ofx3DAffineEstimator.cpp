//
//  ofx3DAffineEstimator.cpp
//  ofApp
//
//  Created by Shunichi Kasahara on 1/5/14.
//
//

#include "ofx3DAffineEstimator.h"
#include "DebugUtil.h"

using namespace ofxCv;
using namespace cv;

//estimate 3D affine transform matrix
ofMatrix4x4 ofx3DAffineEstimator::estimate(vector <ofVec3f> &from, vector <ofVec3f> &to)
{

	ofMatrix4x4 rigidEstimate = estimateAffine3D(from, to);

    return rigidEstimate;
}

//maybe

void ofx3DAffineEstimator::drawDebug(ofMatrix4x4 &affineMat, ofPoint pos)
{
    ofPushMatrix();
    ofTranslate(pos);
    drawDebug(affineMat);
    ofPopMatrix();
}

void ofx3DAffineEstimator::drawDebug(ofMatrix4x4 &affineMat)
{
    ofVec3f decompTranslation, decompScale;
	ofQuaternion decompRotation, decompSo;
	affineMat.decompose(decompTranslation, decompRotation, decompScale, decompSo);
    
    ofDrawBitmapString("- - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - ", 50, 10);
    ofDrawBitmapString("FPS." + ofToString(ofGetFrameRate()), 50, 30);
    ofDrawBitmapString( "translation: " + DebugUtil::toString(decompTranslation), 50, 50);
    ofDrawBitmapString( "Scale: " + DebugUtil::toString(decompScale), 50, 70);
    ofDrawBitmapString( "Rotation: " + DebugUtil::toString(decompRotation), 50, 90);
    ofDrawBitmapString( "SO: " + DebugUtil::toString(decompSo), 50, 90);
    
}


void ofx3DAffineEstimator::drawDebug(ofImage fromImg, ofImage &toImg, ofMatrix4x4 &affineMat, vector <ofVec3f> &from, vector <ofVec3f> &to)
{
    ///----rendering captured Image
    
    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 150);
    
    glPushMatrix();
    fromImg.draw(0, 0);
    
    ofMatrix4x4 revertMat = affineMat.getInverse();
    glMultMatrixf(revertMat.getPtr());
    toImg.draw(0, 0);
    glPopMatrix();
    
    ofPopStyle();
    
    ///----rendering feature pixels
    
    ofPushStyle();
    ofNoFill();
    for(int i=0; i < from.size() ; i++)
    {
        ofSetColor(255, 0, 0, 200);
        ofRect(from[i].x, from[i].y, from[i].z, 2, 2);
    }

    for(int i=0; i < to.size() ; i++)
    {
        ofSetColor(0, 255, 0, 200);
        ofRect(to[i].x, to[i].y, to[i].z, 2, 2);
    }
    ofPopStyle();
    
}
