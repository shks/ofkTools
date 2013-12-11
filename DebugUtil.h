//
//  DebugUtil.h
//
//  Created by Shunichi Kasahara on 2013/12/08.
//
//

#ifndef __LivesphereView__DebugUtil__
#define __LivesphereView__DebugUtil__

#include <iostream>

class DebugUtil
{
public:
    
    static void setDebugDraw(bool is){_debugUtil_is_debug_draw_ = is;}
    static bool isDebugDraw(){return _debugUtil_is_debug_draw_;}
    
    
private:
    
    static bool _debugUtil_is_debug_draw_;
    
    
};

#endif /* defined(__LivesphereView__DebugUtil__) */
