//
//  ofkFontRenderer.h
//
//  Created by Shunichi Kasahara on 3/17/13.
//
//

#ifndef __SalogationMobile__ofkFontRenderer__
#define __SalogationMobile__ofkFontRenderer__

#include "ofMain.h"


//Singleton
class ofkFontRenderer
{
public:
    
    //add by shks ID map
    static void loadFont(const string& filePath, float pointSize, string ID = "");
//    static void loadFont(const string& filePath, float pointSize);
    static void renderString(const string& srt, string ID = "");
	static void renderString(const string& srt, float scale, string ID = "");
    static bool isLoaded();
	static ofRectangle getStringBoundingBox(string str, string ID = "");

protected:
	static ofkFontRenderer *getInstance();
    
	
private:
	static ofkFontRenderer *m_pInstance;
    
    
    ofTrueTypeFont font;
    std::map <string, ofTrueTypeFont *> resList;
    ofTrueTypeFont* getFontInstance(string ID);
    
	ofkFontRenderer();
	~ofkFontRenderer();
    
};

#endif /* defined(__SalogationMobile__ofkFontRenderer__) */
