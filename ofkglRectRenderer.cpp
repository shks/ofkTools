//
//  ofkglRectRenderer.coo.cpp
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/03/04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofkglRectRenderer.h"

static const float verticies[16]=
{
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

ofkglRectRenderer::ofkglRectRenderer()
{
    r = b = g = a = 1.0;
    x = y = z = 0.0;
    rx = ry = rz = 0.0;
}

void ofkglRectRenderer::init()
{
    mWidth = 100.0f;
    mHeight = 100.0f;
    
    squareTexCoord[0] = 0.0f;
    squareTexCoord[1] = 0.0f;
    
    squareTexCoord[2] = 1.0f;
    squareTexCoord[3] = 0.0f;
    
    squareTexCoord[4] = 1.0f; 
    squareTexCoord[5] = 1.0f;
    
    squareTexCoord[6] = 0.0f;
    squareTexCoord[7] = 1.0f; 
}

void ofkglRectRenderer::update()
{

}

void ofkglRectRenderer::render()
{
    glMatrixMode(GL_MODELVIEW);
        
    ofEnableNormalizedTexCoords();
    
    glPushMatrix();
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    
    mTexture.bind(); 
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, squareTexCoord);
    
    glColor4f(r, g, b, a);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verticies);
    
    glTranslatef(x, y, z);
    glRotatef(rx, 1.0, 0.0, 0.0);
    glRotatef(ry, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0, 0.0, 1.0);
    
    glScalef(mWidth, mHeight, 1.0f);
    glScalef(1.0f, -1.0f, 1.0f);
    
    //Draw it! 
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    glDisableClientState(GL_VERTEX_ARRAY);	

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
    
    glDisable(GL_BLEND);

    glPopMatrix();
    mTexture.unbind();    
    
    ofDisableNormalizedTexCoords();
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


void ofkglRectRenderer::setImage(ofImage image)
{
    mImage = image;
    mImage.setUseTexture(true);
    mTexture = mImage.getTextureReference();
}


void ofkglRectRenderer::setTexture(ofTexture tex)
{
    mTexture = tex;
}


void ofkglRectRenderer::setSize(float width, float height)
{
    mWidth = width;
    mHeight = height;
}


void ofkglRectRenderer::setUV(float* uvArray)
{
    for(int i = 0 ; i < 8 ; i ++)
    {
        squareTexCoord[i] = uvArray[i];
    }
}