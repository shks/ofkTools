//
//  ofkARMatrixUtil.cpp
//  Existence
//
//  Created by 俊一 笠原 on 6/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofkARMatrixUtil.h"

float ofkARMatrixUtil::virtualiPadSize = 0.8;


void ofkARMatrixUtil::drawStringMatrix(ofMatrix4x4 mat, float x, float y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofDrawBitmapString( ofToString(mat.getPtr()[0]) + " : "
                       + ofToString(mat.getPtr()[1]) + " : "
                       + ofToString(mat.getPtr()[2]) + " : "
                       + ofToString(mat.getPtr()[3]) + " : ",0,0);

    ofDrawBitmapString( ofToString(mat.getPtr()[4]) + " : "
                       + ofToString(mat.getPtr()[5]) + " : "
                       + ofToString(mat.getPtr()[6]) + " : "
                       + ofToString(mat.getPtr()[7]) + " : ",0,20);
    
    ofDrawBitmapString( ofToString(mat.getPtr()[8]) + " : "
                       + ofToString(mat.getPtr()[9]) + " : "
                       + ofToString(mat.getPtr()[10]) + " : "
                       + ofToString(mat.getPtr()[11]) + " : ",0,40);
    
    ofDrawBitmapString( ofToString(mat.getPtr()[12]) + " : "
                       + ofToString(mat.getPtr()[13]) + " : "
                       + ofToString(mat.getPtr()[14]) + " : "
                       + ofToString(mat.getPtr()[15]) + " : ",0,60);
    
    ofPopMatrix();
}


void ofkARMatrixUtil::drawStringMatrix(GLdouble mat[16], float x, float y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofDrawBitmapString(  ofToString(mat[0]) + " : "
                       + ofToString(mat[1]) + " : "
                       + ofToString(mat[2]) + " : "
                       + ofToString(mat[3]) + " : ",0,0);
    
    ofDrawBitmapString(  ofToString(mat[4]) + " : "
                       + ofToString(mat[5]) + " : "
                       + ofToString(mat[6]) + " : "
                       + ofToString(mat[7]) + " : ",0,20);
    
    ofDrawBitmapString(  ofToString(mat[8]) + " : "
                       + ofToString(mat[9]) + " : "
                       + ofToString(mat[10]) + " : "
                       + ofToString(mat[11]) + " : ",0,40);
    
    ofDrawBitmapString(  ofToString(mat[12]) + " : "
                       + ofToString(mat[13]) + " : "
                       + ofToString(mat[14]) + " : "
                       + ofToString(mat[15]) + " : ",0,60);
    
    ofPopMatrix();
}
