//
//  DebugUtil.h
//
//  Created by Shunichi Kasahara on 2013/12/08.
//
//

#ifndef __DebugUtil__
#define __DebugUtil__

#include <iostream>
#include "ofMain.h"

class DebugUtil
{
public:
    
    static void setDebugDraw(bool is){_debugUtil_is_debug_draw_ = is;}
    static bool isDebugDraw(){return _debugUtil_is_debug_draw_;}
    
    static string toString(ofVec3f vec);
    static string toString(ofVec2f vec);
    static string toString(ofQuaternion quat);
    
    
private:
    
    static bool _debugUtil_is_debug_draw_;
    
    
};

#endif /* defined(__LivesphereView__DebugUtil__) */
