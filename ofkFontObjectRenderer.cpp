//
//  ofkRenderObj.cpp
//
//  Created by Shunichi Kasahara on 2/20/13.
//
//

#include "ofkFontObjectRenderer.h"


bool ofkFontObjectRenderer::isRenderDebug = false;

ofkFontObjectRenderer::ofkFontObjectRenderer()
{
    x = y = z = 0.0;
    rx = ry = rz = 0.0;
    scaleX = scaleY = scaleZ = 1.0f;
    text = "";
    isMultiLine = false;
}

void ofkFontObjectRenderer::init(string fontFilePath, int size)
{
    font.loadFont(fontFilePath, size);
    
    fontPath = fontFilePath;
    initFontSize  = size;
}

void ofkFontObjectRenderer::render()
{
    if(isMultiLine)
    {
        if(ex_text != text)
        {
            //Check  Multi Line
            //TODO 
        }
        
    }
    
    glPushMatrix();
    applyMatrix();

    font.drawString(text, 0, 0);

    glPopMatrix();
    
}

void ofkFontObjectRenderer::checkMultiLine()
{
    /*
    int len = text.length();
    
    string newtext = text;
    
    int cursor = 0;
    int newLineIndex = 0;
    while (cursor < len) {
        
        if(
        (font.getStringBoundingBox(text.substr(newLineIndex , cursor), 0, 0)).width > 300
           ){
            text.insert(cursor, "\n") ;
            newLineIndex = cursor;
        }
        cursor ++;
    }
     */
    
}

void ofkFontObjectRenderer::applyMatrix()
{

    glTranslatef(x, y, z);
    glRotatef(rx, 1.0, 0.0, 0.0);
    glRotatef(ry, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0, 0.0, 1.0);
    
    if(isRenderDebug)
    {
        ofDrawBitmapString("Font:" + fontPath + "Size :" +ofToString(initFontSize * scaleX) , 0,20);
    }
    
    glScalef(scaleX, scaleY, scaleZ);
    
}