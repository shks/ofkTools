//
//  ofxCamParamHelper.cpp
//  SyncGhost2
//
//  Created by Shunichi Kasahara on 12/17/13.
//
//

#include "ofxCamParamHelper.h"


float ofxCamParamHelper::getFovY(float fovX, float cameraWidth,  float cameraHeight)
{
    float ratio = cameraHeight / cameraWidth;
    return  2 * atan(ratio * tan( fovX / 2.0  / 180.0 * PI))  / PI * 180.0;
}

float ofxCamParamHelper::getFovX(float fovY, float cameraWidth,  float cameraHeight)
{
    float ratio = cameraWidth / cameraHeight;
    return 2 * atan(ratio * tan( fovY / 2.0  / 180.0 * PI))  / PI * 180.0;
}

