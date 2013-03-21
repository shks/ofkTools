//
//  ofkMeshRectRenderer.h
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/03/05.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _ofkMeshRectRenderer_h_ 
#define _ofkMeshRectRenderer_h_

#include "ofMain.h"

class ofkMeshRectRenderer
{
    
public:
    void init();
    void update();
    void render();
    void renderDebug();
    
    void updateMesh(){updateMeshInternal();}
    
    //set Captured Video Image
    void setVideoImage(ofImage image);
    void setVIdeoTexture(ofTexture tex);
    
    //this should be more than AR object , ex.AR boject Size X 5
    void setSize(float width, float height);
    void setAlpha(float alpha);
    
    //to calc model to FB coordinate
    void setModelViewMatrix(ofMatrix4x4 ModelViewMat);
    void setProjectionMatrix(ofMatrix4x4 ProjectionMat);
    
	bool isFlip;
private:
    
    void updateMeshInternal();
    void updateUVCoordibate();
    
    float mWidth;
    float mHeight;
    float mAlpha;
    
    ofTexture mTexture;
    ofImage mImage;
    int mTextureID;
    
    static const int GridRES = 40;
    ofVbo mVbos[GridRES];
    
    ofVec3f mHorizonVerts[GridRES][2*(GridRES+1)];
    ofFloatColor mHorizonColors[GridRES][2*(GridRES+1)];
    ofVec2f mTranslatedUV[GridRES][2*(GridRES+1)];
    
    ofMatrix4x4 mARmodelViewMatrix;
    ofMatrix4x4 mARProjectionMatrix;
};




#endif
