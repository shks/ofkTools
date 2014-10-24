//
//  DebugUtil.cpp
//
//  Created by Shunichi Kasahara on 2013/12/08.
//
//

#include "DebugUtil.h"

bool DebugUtil::_debugUtil_is_debug_draw_ = false;



string DebugUtil::toString(ofVec3f vec)
{
    return "x:" + ofToString(vec.x) + ", y:" + ofToString(vec.y) + ", z:" + ofToString(vec.z);
}


string DebugUtil::toString(ofVec2f vec)
{
    return "x:" + ofToString(vec.x) + ", y:" + ofToString(vec.y) ;
}


string DebugUtil::toString(ofQuaternion quat)
{
    
    ofVec3f vec = quat.getEuler();
    return "alpha:" + ofToString(vec.x) + ", beta:" + ofToString(vec.y) + ", gamma:" + ofToString(vec.z);
}

string DebugUtil::extractFileNameFromFilePath(string filePath)
{
    
    vector< string > splittedPath = ofSplitString(filePath, "/");
    string fileName = splittedPath[splittedPath.size() - 1];
    
    return fileName;
}
