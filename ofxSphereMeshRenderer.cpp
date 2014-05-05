//
//  ofxSphereMeshRenderer.cpp
//
//  Created by Shunichi Kasahara on 11/29/13.
//
//

#include "ofxSphereMeshRenderer.h"


ofxSphereMeshRenderer::ofxSphereMeshRenderer()
{
    
}
void ofxSphereMeshRenderer::init(float radius, float horizontalDeg, float verticalDeg, float alpha)
{
    //
    
    m_alpha = alpha;
    int resolution = 20;
    mSphere = createSphereMesh(radius, resolution, OF_PRIMITIVE_TRIANGLES, horizontalDeg, verticalDeg);
    mSphere.enableTextures();
    
    
}

void ofxSphereMeshRenderer::udpate()
{
    
}

void ofxSphereMeshRenderer::render()
{
    ofEnableNormalizedTexCoords();
    tex.bind();
    mSphere.draw();
    tex.unbind();
    ofDisableNormalizedTexCoords();
    
}


void ofxSphereMeshRenderer::rednerDebug()
{
    ofPushStyle();
    
    ofSetColor(255, 255, 255, 100);
    mSphere.setMode(OF_PRIMITIVE_LINES);
    mSphere.draw();
    mSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    
    ofPopStyle();
    
}

void ofxSphereMeshRenderer::setTexture(const ofTexture &_tex)
{
    tex = _tex;
}

void ofxSphereMeshRenderer::setTexture(const ofTexture * pTex)
{
    if(NULL != pTex){
        tex = *pTex;
    }else{
        ofLogError("ofxSphereMeshRenderer:: texture pointer NULL");
    }
}

void ofxSphereMeshRenderer::setAlpha(float alpha)
{
    m_alpha = alpha;
    
    createSphereMesh(m_radius,
                     m_res,
                     m_mode,
                     m_horizontalDeg,
                     m_verticalDeg);
}

ofMesh ofxSphereMeshRenderer::createSphereMesh( float radius, int res, ofPrimitiveMode mode, float horizontalDeg, float verticalDeg )
{
    m_radius    = radius;
    m_res       = res;
    m_mode      = mode;
    m_horizontalDeg = horizontalDeg;
    m_verticalDeg   = verticalDeg;


    ofMesh mesh;
        
        float startHorRad = -horizontalDeg / 2.f / 180.f * PI;
        float endHorRad = horizontalDeg / 2.f / 180.f * PI;
        
        float startVertRad = -verticalDeg / 2.f / 180.f * PI;
        float endVertRad = verticalDeg / 2.f / 180.f * PI;
        
        float doubleRes = res*2.f;
        float polarInc = (verticalDeg/360.f) * PI/(res); // ringAngle
        float azimInc = (horizontalDeg/360.f) * PI/(res);//TWO_PI/(doubleRes); // segAngle //
        //(horizontalDeg/360.f) *
        
        mode = OF_PRIMITIVE_TRIANGLES;
       
        mesh.setMode(mode);
        
        ofVec3f vert;
        ofVec2f tcoord;
        
        for(float i = 0; i < res+1; i++) {
            
            float tr = sin( (i * polarInc * 2 + startVertRad + 0.5 * PI) );
            float ny = cos( (i * polarInc * 2 + startVertRad + 0.5 * PI) );
            
            tcoord.y = i / res;
            
            for(float j = 0; j <= doubleRes; j++) {
                
                float nx = tr * sin(j * azimInc + startHorRad);
                float nz = tr * cos(j * azimInc + startHorRad);
                
                tcoord.x = 1.0 -  j / (doubleRes);
                
                vert.set(nx, ny, nz);
                mesh.addNormal(vert);
                vert *= radius;
                mesh.addVertex(vert);
                mesh.addTexCoord(tcoord);
                ofFloatColor col;
                
                col.set(1.0,1.0, 1.0, m_alpha);

                //col.set((float)i / (float)res , (float)j / (float)doubleRes, 0.5);
                mesh.addColor(col);
            }
        }
        
        int nr = doubleRes+1;
        if(mode == OF_PRIMITIVE_TRIANGLES) {
            
            int index1, index2, index3;
            
            for(float iy = 0; iy < res; iy++) {
                for(float ix = 0; ix < doubleRes; ix++) {
                    
                    // first tri //
                    if(iy >= 0) {
                        index1 = (iy+0) * (nr) + (ix+0);
                        index2 = (iy+0) * (nr) + (ix+1);
                        index3 = (iy+1) * (nr) + (ix+0);
                        
                        mesh.addIndex(index1);
                        mesh.addIndex(index3);
                        mesh.addIndex(index2);
                    }
                    
                    if(iy <= res-1 ) {
                        // second tri //
                        index1 = (iy+0) * (nr) + (ix+1);
                        index2 = (iy+1) * (nr) + (ix+1);
                        index3 = (iy+1) * (nr) + (ix+0);
                        
                        mesh.addIndex(index1);
                        mesh.addIndex(index3);
                        mesh.addIndex(index2);
                        
                    }
                }
            }
            
        } else {
            for(int y = 0; y < res; y++) {
                for(int x = 0; x <= doubleRes; x++) {
                    mesh.addIndex( (y)*nr + x );
                    mesh.addIndex( (y+1)*nr + x );
                }
            }
            
        }
    
    return mesh;
}
