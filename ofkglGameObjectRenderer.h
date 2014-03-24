#pragma once
#include "ofMain.h"
#include "ofkglImageRenderer.h"

class ofkglGameObjectRenderer : public ofkglImageRenderer
{
public:
    
    ofkglGameObjectRenderer();
    void setImage(ofImage *pImg);
    
protected:
    
    bool isUsePointer;
    ofImage *pImage;
    virtual void internalDraw(float x, float y, float w, float h);
};


