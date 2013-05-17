

#ifndef _ofkMatrixHelper_
#define _ofkMatrixHelper_

#include "ofMain.h"

class ofkMatrixHelper 
{
public:
    
    //Caution, this function will enable GL_DEPTH_TEST, and clear GL_DEPTH_BUFFER_BIT.
    //and in this function, viewport, projection Matrix and modelView matrix will be changed.
    
	//float transRate : Rotation and Scale factor fitler rate
	//float rotScaleRate : Rotation and Scale factor 
    static void matrixInterpolationFilter(ofMatrix4x4 *currentMat, ofMatrix4x4 *targetMat, float rotScaleRate, float transRate)
	{
		for(int i = 0 ; i < 12 ; i++)
		{
			currentMat->getPtr()[i] += (targetMat ->getPtr()[i] - currentMat->getPtr()[i]) * rotScaleRate;
		}

		//12,13,14,15
		for(int i = 12; i < 16 ; i++)
		{
			currentMat->getPtr()[i] += (targetMat ->getPtr()[i] - currentMat->getPtr()[i]) * transRate;
		}
	}

    static ofVec3f getUnProjectionPoint(float ofScreenPosX, float ofScreenPosY, const GLdouble *model, const GLdouble *proj, const GLint *view);
    static ofVec3f getUnProjectionPoint(float ofScreenPosX, float ofScreenPosY, ofMatrix4x4 modelView, ofMatrix4x4 projection, float viewWidth, float viewHeight );
	static ofVec3f getProjectionPoint(ofVec3f pos, const GLdouble *model, const GLdouble *proj, const GLint *view);
	static ofVec3f getProjectionPoint(ofVec3f pos, const ofMatrix4x4 modelView, ofMatrix4x4 projection, const int *view);


	static ofVec2f getParamVector2D(ofPoint pos0, ofPoint pos1, ofPoint posBase, ofPoint srcVec )
	{

		float _x = srcVec.x - posBase.x;
		float _y = srcVec.y - posBase.y;

		float mat[2][2];
		mat[0][0] = pos0.x - posBase.x;
		mat[0][1] = pos1.x - posBase.x;
		mat[1][0] = pos0.y - posBase.y;
		mat[1][1] = pos1.y - posBase.y;

		float detA = 1.0 / (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);

		float invMat[2][2];
		invMat[0][0] = detA * mat[1][1];
		invMat[0][1] = -1 * detA * mat[0][1];
		invMat[1][0] = -1 * detA * mat[1][0];
		invMat[1][1] = detA * mat[0][0];


		float A = invMat[0][0] * (float)_x + invMat[0][1] * (float)_y;
		float B = invMat[1][0] * (float)_x + invMat[1][1] * (float)_y;

		return ofVec2f(A,B);
	}

};

#endif /* _ofkUnProjectionHelper_ */
