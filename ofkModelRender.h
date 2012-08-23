//
//  ofkglRectRenderer.h
//  tool class for loading and rendering model
//
//  Created by Shunichi Kasahara on 12/03/04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef eventsExample_ofkModelRender_h
#define eventsExample_ofkModelRender_h

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

class ofkModelRender
{
    
public:
    ofkModelRender();
    void init(string assetFilePath);
    void update();
    void render();

private:
    float animationTime;
    ofxAssimpModelLoader model;
    
    ofVboMesh mesh;
    ofPoint position;
    float normScale;
    ofPoint scale;
    ofPoint sceneCenter;
    ofMaterial material;
    ofTexture tex;
    ofLight	light;
    
    bool bAnimate;
	bool bAnimateMouse;
    
};
#endif
