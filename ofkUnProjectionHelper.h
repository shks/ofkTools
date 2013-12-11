

#ifndef _ofkUnProjectionHelper_
#define _ofkUnProjectionHelper_

#include "ofMain.h"


class ofkUnProjectionHelper 
{
public:
    
    //Caution, this function will enable GL_DEPTH_TEST, and clear GL_DEPTH_BUFFER_BIT.
    //and in this function, viewport, projection Matrix and modelView matrix will be changed.
    
    static ofVec3f getProjectionPoint(float ofScreenPosX, float ofScreenPosY, const GLdouble *model, const GLdouble *proj, const GLint *view);
    static ofVec3f getProjectionPoint(float ofScreenPosX, float ofScreenPosY, ofMatrix4x4 modelView, ofMatrix4x4 projection, float viewWidth, float viewHeight );
    
};

#endif /* _ofkUnProjectionHelper_ */
