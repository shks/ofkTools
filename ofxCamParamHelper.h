//
//  ofxCamParamHelper.h
//
//  Created by Shunichi Kasahara on 12/17/13.
//
//

#ifndef __SyncGhost2__ofxCamParamHelper__
#define __SyncGhost2__ofxCamParamHelper__

#include "ofMain.h"

class ofxCamParamHelper
{
public:
    static float getFovY(float fovX, float cameraWidth,  float cameraHeight);
    static float getFovX(float fovY, float cameraWidth,  float cameraHeight);
    
private:
    
    
    
    
};

#endif /* defined(__SyncGhost2__ofxCamParamHelper__) */
