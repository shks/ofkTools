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

    void setAlpha(float alpha);
    float getRadious() { return m_radius;}

    /*
    void setRadius(float radius);
    void setDeg(float horizontalDeg, float verticalDeg);
*/
    
    
    void setTexture(const ofTexture * pTex);
    void setTexture(const ofTexture &tex);
private:
    ofMesh mSphere;
    ofMesh createSphereMesh( float radius, int res, ofPrimitiveMode mode, float horizontalDeg, float verticalDeg);
    
    ofTexture tex;
    
    float           m_alpha;
    float           m_radius;
    int             m_res;
    ofPrimitiveMode m_mode;
    float           m_horizontalDeg;
    float           m_verticalDeg;
    
};

#endif /* defined(__meshFromCamera__ofxSphereMeshRenderer__) */
