//
//  ofx3DAffineEstimator.h
//
//  Created by Shunichi Kasahara on 1/5/14.
//
//

#ifndef __ofApp__ofx3DAffineEstimator__
#define __ofApp__ofx3DAffineEstimator__

#include "ofMain.h"
#include "ofxCv.h"

class ofx3DAffineEstimator
{
public:
    
    //estimate 3D affine transform matrix
    static ofMatrix4x4 estimate(vector <ofVec3f> &from, vector <ofVec3f> &to);

    static void drawDebug(ofMatrix4x4 &affineMat, ofPoint pos);
    static void drawDebug(ofMatrix4x4 &affineMat);
    static void drawDebug(ofImage fFromImg, ofImage &toImg, ofMatrix4x4 &affineMat ,vector <ofVec3f> &from, vector <ofVec3f> &to);
    
    
private:
    
//    vector <ofVec2f> from;
 //   vector <ofVec2f> to;
    
    
};


#endif /* defined(__ofApp__ofx3DAffineEstimator__) */
