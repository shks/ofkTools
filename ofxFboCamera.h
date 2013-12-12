//
//  ofxFboCamera.h
//  Cam_EyeTest
//
//  Created by Shunichi Kasahara on 12/12/13.
//
//

#ifndef __Cam_EyeTest__ofxFboCamera__
#define __Cam_EyeTest__ofxFboCamera__

#include "ofMain.h"

class ofxFboCamera
{
public:
    ofxFboCamera(void);
    void init(int FboWidth, int FboHeight, string _cameraName);
    void begin(bool isFbo);
    void end();
    
    void draw(float x, float y);
    void draw(float x, float y, float w, float h);
    void draw(float x, float y, float scale);
    
    ofCamera camera;
    ofFbo fbo;
    
    static bool setEnableDebugInfo(bool is);
    
private:
    
    void drawDebug();

    bool isFBOuse;
    string cameraName;
    static bool isShowDebugInformation;
    
    
};

#endif /* defined(__Cam_EyeTest__ofxFboCamera__) */
