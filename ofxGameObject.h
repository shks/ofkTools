//
//  ofxGameObject.h
//  myAroundView
//
//  Created by Shunichi Kasahara on 3/16/14.
//
//

#ifndef __myAroundView__ofxGameObject__
#define __myAroundView__ofxGameObject__

#include "ofMain.h"
#include "ofkRenderObj.h"


class ofxGameObject : public ofkRenderObj
{

public:
    virtual void draw(){;}
    virtual void update(){;}
    virtual bool isWaitForDelete(){return false;}
    ofFloatColor col;

};

#endif /* defined(__myAroundView__ofxGameObject__) */
