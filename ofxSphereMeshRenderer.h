//
//  ofxSphereMeshRenderer.h
//
//  Created by Shunichi Kasahara on 11/29/13.
//
//

#ifndef __meshFromCamera__ofxSphereMeshRenderer__
#define __meshFromCamera__ofxSphereMeshRenderer__

#include "ofMain.h"


class ofxSphereMeshRenderer
{
public:
    ofxSphereMeshRenderer();
    
    void init(float radius, float horizontalDeg, float verticalDeg);
    void udpate();
    void render();
    void rednerDebug();
    
    void setRadius(float radius);
    void setDeg(float horizontalDeg, float verticalDeg);
    
    void setTexture(const ofTexture &tex);
private:
    ofMesh mSphere;
    ofMesh createSphereMesh( float radius, int res, ofPrimitiveMode mode, float horizontalDeg, float verticalDeg);
    
    ofTexture tex;
    
};

#endif /* defined(__meshFromCamera__ofxSphereMeshRenderer__) */
