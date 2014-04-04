//
//  ofxVisualizeGraph.cpp
//  FAST-Opticalflow-test
//
//  Created by Shunichi Kasahara on 2/9/14.
//
//

#include "ofxVisualizeGraph.h"

 float ofxVisualizeGraph::data_1[DATA_NUM];
 float ofxVisualizeGraph::data_2[DATA_NUM];
 float ofxVisualizeGraph::data_3[DATA_NUM];
 float ofxVisualizeGraph::data_4[DATA_NUM];
 float ofxVisualizeGraph::data_5[DATA_NUM];
 float ofxVisualizeGraph::data_6[DATA_NUM];

 int c[] = {0, 0, 0, 0, 0, 0};

void ofxVisualizeGraph::draw3DPlotsNormal(vector <ofVec3f> &data)
{
    
    ofPushStyle();
    int size = data.size();
    
    ofFloatColor *pColts = new ofFloatColor[size];
    ofVec3f *pVerts = new ofVec3f[size]; // 頂点の座標(3次元ベクトル)
    
    for(int i = 0 ; i < size; i++)
    {
        ofVec3f v = data[i];
        
        pVerts[i] = v;
        pColts[i].set(1.0, 1.0, 1.0, 1.0);
    }
    
    ofVbo vbo;
    vbo.setVertexData(pVerts, size * 1, GL_DYNAMIC_DRAW);
    vbo.setColorData(pColts, size * 1, GL_DYNAMIC_DRAW);
    
    glPointSize(1.0f);
    vbo.draw(GL_POINTS, 0,size * 1);
    
    ofNoFill();
    ofSetColor(255, 255, 255);
    ofDrawBox(0, 0, 0, 2.0);
    
    delete[] pVerts;
    delete[] pColts;
    
    ofPopStyle();
    
}

void ofxVisualizeGraph::draw3DPlotsNormalize(vector <ofQuaternion> &data)
{

    ofPushStyle();
    int size = data.size();

    
    ofFloatColor *pColts = new ofFloatColor[size * 2];
    ofVec3f *pVerts = new ofVec3f[size * 2]; // 頂点の座標(3次元ベクトル)
    
    for(int i = 0 ; i < size; i++)
    {
        float ang;
        ofVec3f v;
        
        data[i].getRotate(ang, v);
        pVerts[2 * i] = -1.0 * v;
        pColts[2 * i].set(ang / 50.0, 0.0, 1.0 - ang / 50.0, ang / 50.0f);
        
        pVerts[2 * i + 1] = v;
        pColts[2 * i + 1].set(ang / 50.0, 0.0, 1.0 - ang / 50.0, ang / 50.0f);
    }
    
    ofVbo vbo;
    vbo.setVertexData(pVerts, size * 2, GL_DYNAMIC_DRAW);
    vbo.setColorData(pColts, size * 2, GL_DYNAMIC_DRAW);
    
    glPointSize(1.0f);
    vbo.draw(GL_LINES, 0,size * 2);
    
    ofNoFill();
    ofSetColor(255, 255, 255);
    ofDrawBox(0, 0, 0, 2.0);
    
    delete[] pVerts;
    delete[] pColts;

    ofPopStyle();
    
}


void ofxVisualizeGraph::draw3DPlotsNormalizeWithFixedAlpha(vector <ofQuaternion> &data)
{
    ofPushStyle();
    int size = data.size();
    
    
    ofFloatColor *pColts = new ofFloatColor[size * 2];
    ofVec3f *pVerts = new ofVec3f[size * 2]; // 頂点の座標(3次元ベクトル)
    
    for(int i = 0 ; i < size; i++)
    {
        float ang;
        ofVec3f v;
        
        data[i].getRotate(ang, v);
        pVerts[2 * i] = -1.0 * v;
        pColts[2 * i].set(ang / 10.0, 1.0, 1.0 - ang / 10.0, 1.0);
        
        pVerts[2 * i + 1] = v;
        pColts[2 * i + 1].set(ang / 10.0, 1.0, 1.0 - ang / 10.0, 1.0);
    }
    
    ofVbo vbo;
    vbo.setVertexData(pVerts, size * 2, GL_DYNAMIC_DRAW);
    vbo.setColorData(pColts, size * 2, GL_DYNAMIC_DRAW);
    
    glPointSize(1.0f);
    vbo.draw(GL_LINES, 0,size * 2);
    
    ofNoFill();
    ofSetColor(255, 255, 255);
    ofDrawBox(0, 0, 0, 2.0);
    
    delete[] pVerts;
    delete[] pColts;
    
    ofPopStyle();
}



void ofxVisualizeGraph::draw2DValueLogGraph(int channel, float updatedValue)
{
    if(channel == 0)
    {
        draw2DValueLogGraph(updatedValue, data_1, 0);

    }else if(channel == 1)
    {
        draw2DValueLogGraph(updatedValue, data_2, 1);

    }else if(channel == 2)
    {
        draw2DValueLogGraph(updatedValue, data_3, 2);

    }else if(channel == 3)
    {
        draw2DValueLogGraph(updatedValue, data_4, 3);

    }else if(channel == 4)
    {
        draw2DValueLogGraph(updatedValue, data_5, 4);
        
    }else if(channel == 5)
    {
        draw2DValueLogGraph(updatedValue, data_6, 5);
    }
       
}

void ofxVisualizeGraph::draw2DValueLogGraph(float updatedValue, float *data, int i)
{
    float *pDate = data;
    
	ofDrawBitmapStringHighlight("Data" + ofToString(i), 0, 0, ofColor::blue);

    ofPushStyle();
    c[i] = c[i] % DATA_NUM;
    pDate[c[i]] = updatedValue;
    
    ofSetColor(255, 255, 255, 255);
    float max = 1.0;
    for(int i = 0 ; i< DATA_NUM - 1; i++)
    {
        ofLine(i , pDate[i], i + 1, pDate[i + 1]);
        max = MAX(pDate[i], max);
    }
    
    ofSetColor(255, 255, 255, 120);
    ofNoFill();
    ofRect(0, 0, DATA_NUM , max);
    
    ofPopStyle();
    c[i] ++;
}



void ofxVisualizeGraph::draw2DPlotAngles(vector <ofQuaternion> &data)
{
    
    
    
}

