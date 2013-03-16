#include "ofkMatrixHelper.h"


ofVec3f ofkMatrixHelper::getUnProjectionPoint(float ofScreenPosX, float ofScreenPosY, const GLdouble *model, const GLdouble *proj, const GLint *viewPort)
{
    ofVec3f res;
    
    // ---------------- SETTING MATRIX  ----------------  //
    glViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadMatrixd(proj);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixd(model);

    // ---------------- DRAW and pickup points ---------------  //
    //Enable Depth
    glEnable(GL_DEPTH_TEST);
    
    //DEpth Buffer Clear
    glClear(GL_DEPTH_BUFFER_BIT);
    
    //Once Render one Plane to Draw Depth Buffer
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 0);
    ofFill();
    ofRect(-10000, -10000, 20000, 20000);

    //-> FUNC
    double objX;
	double objY;
	double objZ;
    float z;
    
    //-> FUNC
    glReadPixels(ofScreenPosX, viewPort[3] - ofScreenPosY ,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&z);
    gluUnProject(ofScreenPosX, viewPort[3] - ofScreenPosY ,z,model, proj, viewPort,&objX,&objY,&objZ);
    
    res.x = objX;
    res.y = objY;
    res.z = 0.0;  // Actually , we'll get small number in objZ , I guess it's computation Error of double
    
	//no no we need to modify this

    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    return res;
}

ofVec3f ofkMatrixHelper::getUnProjectionPoint(float ofScreenPosX, float ofScreenPosY, ofMatrix4x4 modelView, ofMatrix4x4 projection, float viewWidth, float viewHeight )
{
    GLdouble modelMAT[16];
    GLdouble projectionMAT[16];
    GLint view[4];
    
    for(int i = 0 ; i < 16 ; i++)
    {
        modelMAT[i] = modelView.getPtr()[i];
        projectionMAT[i] = projection.getPtr()[i];
    }
    
    view[0] = 0;
    view[1] = 0;
    view[2] = viewWidth;
    view[3] = viewHeight;
    
    return getUnProjectionPoint(ofScreenPosX,  ofScreenPosY, modelMAT, projectionMAT, view);
}

ofVec3f ofkMatrixHelper::getProjectionPoint(ofVec3f pos, const GLdouble *model, const GLdouble *proj, const GLint *view)
{	
	double winX, winY, winZ;//ウィンドウ座標格納用
	gluProject(pos.x,pos.y,pos.z,model,proj,view,&winX,&winY,&winZ); //座標変換の計算
	return ofVec3f((float)winX, (float)winY, (float)winZ);
}
