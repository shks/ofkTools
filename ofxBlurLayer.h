//
//  ofxBlurLayer.h
//  emptyExample
//
//  Created by Shunichi Kasahara on 9/30/13.
//
//

#ifndef __emptyExample__ofxBlurLayer__
#define __emptyExample__ofxBlurLayer__

#include "ofMain.h"
#include "ofxBlur.h"

class ofxBlurLayer
{
public:
    ofxBlurLayer();
    ~ofxBlurLayer();

    void setup(int width, int height);
    void update();
    void begin();
    void end();
    void draw();
    void drawDebug();
    
	void setActive(bool isActive);
	void setAfterimageRate(int power);	//0: no After image, 255: remains 

    // - - - - - - - - public access members - - - - - - //
    float	power;

private:
    ofxBlur m_blur;
	bool	m_active;
    int		m_afterImage;			
    
};


#endif /* defined(__emptyExample__ofxBlurLayer__) */
