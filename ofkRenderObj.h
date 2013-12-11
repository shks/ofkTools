//
//  ofkRenderObj.h
//  SalogationMobile
//
//  Created by Shunichi Kasahara on 2/20/13.
//
//

#ifndef __SalogationMobile__ofkRenderObj__
#define __SalogationMobile__ofkRenderObj__

#include "ofMain.h"

class ofkRenderObj
{
public:
 
    
    ofkRenderObj();
    
    void applyMatrix();
    
    float x, y, z;
    float rx, ry, rz;
    float scaleX, scaleY, scaleZ;
    
};


#endif /* defined(__SalogationMobile__ofkRenderObj__) */
