//
//  ofkFontRenderer.h
//  SalogationMobile
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
    
    static void loadFont(const string& filePath, float pointSize);
    static void renderString(const string& srt);
    static bool isLoaded();
	
protected:
	static ofkFontRenderer *getInstance();
	
private:
	static ofkFontRenderer *m_pInstance;
    static ofTrueTypeFont font;
    
	ofkFontRenderer();
	~ofkFontRenderer();
    
};

#endif /* defined(__SalogationMobile__ofkFontRenderer__) */
