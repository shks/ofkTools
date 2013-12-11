//
//  ofkARObject.h
//
//  Created by Shunichi Kasahara on 2/5/13.
//
//

#ifndef __ofkARObject_h_
#define __ofkARObject_h_

#include "ofMain.h"

//this will be separated
class ofkARObject
{
    //this store name, ID, and matrix
public:
    ofkARObject()
    {
        name = "";
        ID = -1;
        isFound = false;
    }
    string name;
    int ID;
    ofMatrix4x4 modelViewMat;
    ofMatrix4x4 projectionMat;
    bool isFound;
};

class ofkARTextureObject : public ofkARObject
{
public:
    ofTexture tex;
};





    
#endif /* defined(__SalogationMobile__ofkARObject__) */
