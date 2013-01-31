//
//  ofkMeshRectRenderer.cpp
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/03/05.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofkMeshRectRenderer.h"


void ofkMeshRectRenderer::init()
{
    mWidth = 50.0f;
    mHeight = 50.0f;

    updateMeshInternal();
}

void ofkMeshRectRenderer::update()
{
    
    
}

void ofkMeshRectRenderer::render()
{
    glMatrixMode(GL_MODELVIEW);
    ofPushMatrix();
    
    ofEnableNormalizedTexCoords();
    
    mTexture.bind();
    
    for (int vertical = 0; vertical < GridRES; vertical++) 
    {
        mVbos[vertical].draw(GL_TRIANGLE_STRIP, 0, 2*(GridRES+1));
        mVbos[vertical].draw(GL_LINE_STRIP, 0, 2*(GridRES+1));

    }
    
    ofDisableNormalizedTexCoords();
    
    mTexture.unbind();
    
    glMatrixMode(GL_MODELVIEW);
    ofPopMatrix();
    
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    
    glMatrixMode(GL_MODELVIEW);
    
    
}

void ofkMeshRectRenderer::renderDebug()
{
    ofSetupScreen();
    
    ofSetColor(255,255,255,255);
    
    for(int vertical = 0 ; vertical < GridRES ; vertical++ )
    {
        //mVbos[vertical].draw(GL_LINE_STRIP, 0, 2*(GridRES+1));
        
    for(int i = 0; i <  2*(GridRES+1) ; i++)
    {
        
        if(vertical % 10 == 0)
        {
            if(i%10 == 0)
            {
                //
                ofDrawBitmapString( "V" + ofToString(vertical) + "UV" + ofToString(i), mTranslatedUV[vertical][i].x * ofGetWidth(), mTranslatedUV[vertical][i].y * ofGetHeight());
                
            }
        }
        //
        //ofDrawBitmapString( "V" + ofToString(vertical) + "UV" + ofToString(i), mTranslatedUV[vertical][i].x * ofGetWidth(), mTranslatedUV[vertical][i].y * ofGetHeight());
    }
    }
}

void ofkMeshRectRenderer::setVideoImage(ofImage image)
{
    mImage = image;
    mImage.setUseTexture(true);
    mTexture = mImage.getTextureReference();
}

void ofkMeshRectRenderer::setVIdeoTexture(ofTexture tex)
{
    mTexture = tex; 
}

void ofkMeshRectRenderer::setSize(float width, float height)
{
    mWidth = width;
    mHeight = height;
    updateMeshInternal();
}

void ofkMeshRectRenderer::updateMeshInternal()
{
    float unitInterval = 1.0 / (float) GridRES;
    
    for (int vertical = 0; vertical < GridRES; vertical++) {        
        for(int i = 0; i < GridRES+1 ; i++)
        {
            mHorizonVerts[vertical][2 * i] = ofVec3f(mWidth *(unitInterval * i - 0.5), mHeight * (unitInterval * (vertical + 0) - 0.5));
            mHorizonVerts[vertical][2 * i + 1] = ofVec3f(mWidth *( unitInterval * i  - 0.5), mHeight * (unitInterval * (vertical + 1) -0.5));   
            
            //TODO change Alpha
            mHorizonColors[vertical][2 * i].set(1.0,1.0,1.0,0.5);
            mHorizonColors[vertical][2 * i + 1].set(1.0,1.0,1.0,0.5);
        }
        
        mVbos[vertical].setVertexData(mHorizonVerts[vertical], 2*(GridRES+1), GL_DYNAMIC_DRAW);   
        mVbos[vertical].setColorData(mHorizonColors[vertical], 2*(GridRES+1), GL_DYNAMIC_DRAW);   
    }
    
    updateUVCoordibate();
}

void ofkMeshRectRenderer::updateUVCoordibate()
{
    for (int vertical = 0; vertical < GridRES; vertical++) {
        
        for(int i = 0; i < 2*(GridRES+1) ; i++)
        {
            ofVec3f FBARpoint = mARProjectionMatrix.preMult(mARmodelViewMatrix.preMult(mHorizonVerts[vertical][i]));
            FBARpoint.x = (FBARpoint.x + 1)*0.5 * ofGetWidth();
            //TODO use Image Width
            //FBARpoint.y = (1 - FBARpoint.y)*0.5 * ofGetHeight();
            
            FBARpoint.y = (1 - FBARpoint.y)*0.5 * ofGetHeight();
            //TODO use Image Height

            mTranslatedUV[vertical][i]= ofVec3f( FBARpoint.x / ofGetWidth() , FBARpoint.y / ofGetHeight());
        }
        mVbos[vertical].setTexCoordData(mTranslatedUV[vertical], 2*(GridRES+1), GL_DYNAMIC_DRAW);
    }
}


void ofkMeshRectRenderer::setModelViewMatrix(ofMatrix4x4 ModelViewMat)
{
    mARmodelViewMatrix =  ModelViewMat;    
}

void ofkMeshRectRenderer::setProjectionMatrix(ofMatrix4x4 ProjectionMat)
{
    mARProjectionMatrix =  ProjectionMat;    
}

void ofkMeshRectRenderer::setAlpha(float alpha)
{    
    mAlpha = alpha;
    for (int vertical = 0; vertical < GridRES; vertical++) {        
        for(int i = 0; i < GridRES+1 ; i++)
        {
            mHorizonColors[vertical][2 * i].set(1.0,1.0,1.0,mAlpha);
            mHorizonColors[vertical][2 * i + 1].set(1.0,1.0,1.0,mAlpha);
        }
        mVbos[vertical].setColorData(mHorizonColors[vertical], 2*(GridRES+1), GL_DYNAMIC_DRAW);   
    }
}


