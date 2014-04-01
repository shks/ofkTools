//
//  ofxHeadMotion.cpp
//  myAroundView
//
//  Created by Shunichi Kasahara on 3/30/14.
//
//

#include "ofxHeadMotion.h"


void ofxHeadMotion::customDraw()
{
    ofNode::customDraw();
    string str = "G pos;"
        + ofToString(ofNode::getX()) + ","
        + ofToString(ofNode::getY()) + ","
    + ofToString(ofNode::getZ());
    
    ofVec3f v = ofNode::getGlobalPosition();

    string str2 = "G pos;"
    + ofToString(v.x,2) + ","
    + ofToString(v.y,2) + ","
    + ofToString(v.z,2);
    
    ofDrawBitmapString(str, 0,0);
    ofDrawBitmapString(str2, 0,20);
    
}

