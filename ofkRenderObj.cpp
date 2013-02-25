//
//  ofkRenderObj.cpp
//  SalogationMobile
//
//  Created by Shunichi Kasahara on 2/20/13.
//
//

#include "ofkRenderObj.h"


ofkRenderObj::ofkRenderObj()
{
    x = y = z = 0.0;
    rx = ry = rz = 0.0;
    scaleX = scaleY = scaleZ = 1.0f;    
}

void ofkRenderObj::applyMatrix()
{

    glTranslatef(x, y, z);
    glRotatef(rx, 1.0, 0.0, 0.0);
    glRotatef(ry, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0, 0.0, 1.0);
    glScalef(scaleX, scaleY, scaleZ);
    
}