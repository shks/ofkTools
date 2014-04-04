//
//  ofxHeadRotationCamera.h
//  myAroundView
//
//  Created by Shunichi Kasahara on 4/1/14.
//
//

#ifndef __myAroundView__ofxHeadRotationCamera__
#define __myAroundView__ofxHeadRotationCamera__

#include "ofMain.h"
#include "ofxFboCamera.h"

class ofxHeadRotationCamera : public ofxFboCamera
{
public:
    
    enum HeadRotationMode
    {
        HEADROTATION_ALL = 0,
        HEADROTATION_YAW_PITCH,
        HEADROTATION_YAW,
        HEADROTATION_NONE,  
		HEADROTATION_UNDEFINE

    };

    void    setHeadRotationMode(HeadRotationMode mode);        //
    void    updateEulerAngle(const ofVec3f &eulerAngle);       //update Euler angles
    ofVec3f getHeadingVector();
    ofVec3f getYawFixedHeadingVector();
    ofVec3f getHeadRotations();
    
private:
    ofMatrix4x4 headPosture;
    ofVec3f headRotations; //[x:Yaw, y:Pitch, Z:Roll]
    ofVec3f headingVector;		//this raw heading
	ofVec3f yawFixedheadingVector;		//this raw heading

    
    //this should nbe class
    HeadRotationMode mHeadRotationMode;
    
};

#endif /* defined(__myAroundView__ofxHeadRotationCamera__) */
