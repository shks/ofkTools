//
//  ksRectRenderer.h
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/03/04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef eventsExample_ofkglRectRenderer_h
#define eventsExample_ofkglRectRenderer_h

#include "ofMain.h"

class ofkglRectRenderer
{
    
public:
    ofkglRectRenderer();
    void init();
    void update();
    void render();
    
    //
    void setImage(ofImage image);
    void setTexture(ofTexture tex);
    
    void setUV(float * uvArray);
    void setSize(float width, float height);
    
    float r, b, g, a;
    float x, y, z;
    float rx, ry, rz;

private:
    
    float mWidth;
    float mHeight;
    float squareTexCoord[8];

    ofTexture mTexture;
    ofImage mImage;
};
#endif
