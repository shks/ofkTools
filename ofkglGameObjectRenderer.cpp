#include "ofkglGameObjectRenderer.h"

ofkglGameObjectRenderer::ofkglGameObjectRenderer()
{
    isUsePointer = false;
}

void ofkglGameObjectRenderer::internalDraw( float x, float y, float w, float h )
{
    glPushMatrix();
    glTranslatef(x + w / 2.0 ,y + h / 2.0, 0.0);
    
    if(isUsePointer)
    {
        if(pImage != NULL)
        {
            pImage->draw(-w / 2.0, - h / 2.0 ,w, h);
        }else
        {
            ofPushStyle();
            ofNoFill();
            ofRect(-w / 2.0, - h / 2.0 , w, h);
            ofPopStyle();
        }
    }
    
    glPopMatrix();
}

void ofkglGameObjectRenderer::setImage( ofImage *pImg )
{
    if(pImg != NULL)
    {
        isUsePointer = true;
        pImage = pImg;
    }
}



