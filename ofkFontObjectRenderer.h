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

class ofkFontObjectRenderer
{
public:
    ofkFontObjectRenderer();

    void init(string fontFilePath, int size);    
    void render();
    
    float x, y, z;
    float rx, ry, rz;
    float scaleX, scaleY, scaleZ;
    string text;
    bool isMultiLine;
    
    
    static bool isRenderDebug;
    
    
private:
    
    void checkMultiLine();
    void applyMatrix();

    ofTrueTypeFont font;
    
    string fontPath;
    float initFontSize;
    
    string ex_text;

};


#endif /* defined(__SalogationMobile__ofkRenderObj__) */
