//
//  ofxHeadRotationCamera.cpp
//  myAroundView
//
//  Created by Shunichi Kasahara on 4/1/14.
//
//

#include "ofxHeadRotationCamera.h"


void ofxHeadRotationCamera::setHeadRotationMode(HeadRotationMode mode)
{
    //
    mHeadRotationMode = mode;    
}

ofVec3f ofxHeadRotationCamera::getHeadRotations()
{
    return headRotations;
}

ofVec3f ofxHeadRotationCamera::getHeadingVector()
{
    return headingVector;
}


ofVec3f ofxHeadRotationCamera::getYawFixedHeadingVector()
{
    return yawFixedheadingVector;
}

void ofxHeadRotationCamera::updateEulerAngle(const ofVec3f &eulerAngle)
{
    ofVec3f vec = eulerAngle;

    
    //Store headRotations as ; //[x:Yaw, y:Pitch, Z:Roll]
    headRotations =vec;
    
    ofMatrix4x4 Mat;
    Mat.makeIdentityMatrix();
    
    Mat.glRotate(-vec.x, 0.0, 1.0, 0.0);     //Y ()
    Mat.glRotate(-vec.y, 1.0, 0.0, 0.0);     //X
    Mat.glRotate(vec.z, 0.0, 0.0, 1.0);     //Z
    
    headPosture = Mat;
    
    //
    ofVec3f headingVec(0.0, 0.0, -1.0f);
    
    headingVector = headPosture.preMult(headingVec);
    
	yawFixedheadingVector = headingVector;
	yawFixedheadingVector.y = 0;

    if(mHeadRotationMode == HEADROTATION_ALL)
    {
        //all rotation
        this->camera.setOrientation(headPosture.getRotate());
        
    }else if(mHeadRotationMode == HEADROTATION_YAW_PITCH)
    {
        //this is without roll
        this->camera.lookAt(headingVector);
        
    }else if(mHeadRotationMode == HEADROTATION_YAW)
	{
        this->camera.lookAt(yawFixedheadingVector);   
    }else if(mHeadRotationMode == HEADROTATION_NONE)
	{
		//do no update
        //this->camera.lookAt(yawFixedheadingVector);   
    }
    
    
}