//
//  ofxVisualizeGraph.h
//
//  Created by Shunichi Kasahara on 2/9/14.
//
//

#ifndef _ofxVisualizeGraph__
#define _ofxVisualizeGraph__

#include "ofMain.h"


class ofxVisualizeGraph
{
public:
    
    static void draw3DPlotsNormalize(vector <ofQuaternion> &data);
    static void draw3DPlotsNormalize(vector <ofVec3f> &data){;}
    static void draw3DPlotsNormal(vector <ofVec3f> &data);
    static void draw3DPlotsNormalizeWithFixedAlpha(vector <ofQuaternion> &data);
    //
    static void draw2DPlotAngles(vector <ofQuaternion> &data);
    static void draw2DValueLogGraph(int channel, float updatedValue);

private:
    
    static void draw2DValueLogGraph(float updatedValue, float *data, int i);
    static const int DATA_NUM = 255;
    
    static float data_1[DATA_NUM];
    static float data_2[DATA_NUM];
    static float data_3[DATA_NUM];
    static float data_4[DATA_NUM];
    static float data_5[DATA_NUM];
    static float data_6[DATA_NUM];
    
};

#endif /* defined(__FAST_Opticalflow_test__ofxVisualizeGraph__) */
