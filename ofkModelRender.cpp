//
//  ofkModelRender.coo.cpp
//  tool class for loading and rendering model
//
//  Created by Shunichi Kasahara on 12/03/04.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofkModelRender.h"


ofkModelRender::ofkModelRender()
{

}

void ofkModelRender::init(string assetFilePath)
{
    // we need GL_TEXTURE_2D for our models coords.
    ofDisableArbTex();
    
    if(model.loadModel(assetFilePath,true)){
    	model.setAnimation(0);
    	model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.75 , 0);
    	//model.createLightsFromAiModel();
    	//model.disableTextures();
    	//model.disableMaterials();
        
    	mesh = model.getMesh(0);
    	position = model.getPosition();
    	normScale = model.getNormalizedScale();
    	scale = model.getScale();
    	sceneCenter = model.getSceneCenter();
    	material = model.getMaterialForMesh(0);
        tex = model.getTextureForMesh(0);
    }
    //some model / light stuff
    //glShadeModel(GL_SMOOTH);
    
	bAnimate		= true;
	bAnimateMouse 	= false;
	animationTime	= 0.0;

}



void ofkModelRender::update()
{
    //this is for animation if the model has it. 
	if( bAnimate ){
		animationTime += ofGetLastFrameTime();
		if( animationTime >= 1.0 ){
			animationTime = 0.0;
		}
	    model.setNormalizedTime(animationTime);
		mesh = model.getCurrentAnimatedMesh(0);
	}
        
	if( bAnimateMouse ){
	    model.setNormalizedTime(animationTime);
		mesh = model.getCurrentAnimatedMesh(0);
	}    
}

void ofkModelRender::render()
{
    //ofPushStyle();
    ofSetColor(255, 255, 255, 255);
	//note we have to enable depth buffer in main.mm
	//see: window->enableDepthBuffer(); in main.mm
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    glShadeModel(GL_SMOOTH);
    //light.enable();
    ofEnableSeparateSpecularLight();
	glEnable(GL_DEPTH_TEST);	
    glPushMatrix();
    
    glScalef(0.005, 0.005, 0.005);
    ofPoint vec = model.getPosition();
    glTranslatef(-vec.x, -vec.y, -vec.z);
    
    model.drawFaces();
    glPopMatrix();
    
    /*
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
    ofDrawBitmapString("fingers 2-5 load models", 10, 30);
    ofDrawBitmapString("num animations for this model: " + ofToString(model.getAnimationCount()), 10, 45);
     */
    
    //ofPopStyle();
    
}

