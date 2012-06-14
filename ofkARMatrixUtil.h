/*
 *  ofkARMatrixUtil.h
 *  
 *  Created by Shunichi Kasahara on 12/06/08.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _OFXARMATRIXULIT_
#define _OFXARMATRIXULIT_

#include "ofMain.h"

/*
 * how to use 
 * projectedPos = getProjectionPoint(touchPoint, mARModelViewMat, mARProjectionMat);
 * this algrithm is not complete version.x
 */

class ofkARMatrixUtil{

public:
    
    static ofMatrix4x4 getWatchMatrix(ofMatrix4x4 ARmodelViewMatrix)
    {
        ofMatrix4x4 wacthMatrix = ARmodelViewMatrix.getInverse();
        
        //maybe need some trans matrix
        wacthMatrix.translate(0.0f, 0.0, 0.0f);

        return wacthMatrix;
    }
    
    static ofVec3f getProjectionPoint(ofPoint FrameBufferPos, ofMatrix4x4 modelViewMatrix, ofMatrix4x4 projectoinMatrix)
    {
        //FrameBufferPos
        ofVec3f FBpos;
        FBpos.x = 2.0f * FrameBufferPos.x / (float)ofGetWidth() - 1.0f;
        FBpos.y = 1.0f - 2.0f * FrameBufferPos.y /(float)ofGetHeight();
        FBpos.z = 0.0;
        
        //[A]
        ofVec3f PosOnObj_CENTER;
        PosOnObj_CENTER.x = 0.0;
        PosOnObj_CENTER.y = 0.0f;
        PosOnObj_CENTER.z = 0;
        ofVec3f PosOnFB_CENTER = projectoinMatrix.preMult((modelViewMatrix.preMult(PosOnObj_CENTER)));
        
        //[B] = alpha
        ofVec3f PosOnObj_X;
        PosOnObj_X.x = 0.5;
        PosOnObj_X.y = 0.0f;
        PosOnObj_X.z = 0;
        ofVec3f PosOnFB_X = projectoinMatrix.preMult((modelViewMatrix.preMult(PosOnObj_X)));
        
        //[C] = beta
        ofVec3f PosOnObj_Y;
        PosOnObj_Y.x = 0.0f;
        PosOnObj_Y.y = 0.5f;
        PosOnObj_Y.z = 0;
        ofVec3f PosOnFB_Y = projectoinMatrix.preMult((modelViewMatrix.preMult(PosOnObj_Y)));
        
        /*     
         [A] ---- [B] (alpha)
         |
         |
         |
         [C] (beta)
         
         */
        
        //Calc trans matrix
        ofMatrix3x3 TransMat;
        
        TransMat[0] = (PosOnFB_X.x - PosOnFB_CENTER.x);
        TransMat[1] = (PosOnFB_Y.x - PosOnFB_CENTER.x);
        TransMat[2] = (0);
        
        TransMat[3] = (PosOnFB_X.y - PosOnFB_CENTER.y);
        TransMat[4] = (PosOnFB_Y.y - PosOnFB_CENTER.y);
        TransMat[5] = (0);
        
        TransMat[6] = (1);
        TransMat[7] = (1);
        TransMat[8] = (1);
        
        TransMat.invert();
        
        float alpha = TransMat[0] * (FBpos.x - PosOnFB_CENTER.x) + TransMat[1] * (FBpos.y - PosOnFB_CENTER.y);
        float beta  = TransMat[3] * (FBpos.x - PosOnFB_CENTER.x) + TransMat[4] * (FBpos.y - PosOnFB_CENTER.y);
        
        ofVec3f modelViewPos;
        modelViewPos.x = alpha / 2.0f;
        modelViewPos.y = beta / 2.0f;
        modelViewPos.z = (modelViewMatrix.preMult(PosOnObj_CENTER)).z;
        
        return modelViewPos;
    };
};
#endif //_OFXARMATRIXULIT_