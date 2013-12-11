#include "ofkiosApp.h"

#define BUFSIZE (9216 * 4)
#define DISP_RATIO ((ofGetWidth() / 640.0))         //Compare with retina Screen Width

#define WIDGET_OPENED_POSX (0)
#define WIDGET_CLOSED_POSX ( - ofGetWidth() * 0.7)

//--------------------------------------------------------------
void ofkiosApp::setup(){	
	ofxAccelerometer.setup();
    ofSetFrameRate(30);
    
	ofBackground(0,0,0);
    ofBackgroundHex(0x000000);
    
    initGUILayout();
    
    //multiTouch Enable
    multiTouchEvent.enable();
    ofAddListener(multiTouchEvent.touchTwoFingerEvent, this, &ofkiosApp::touchTwoFinger);
        
    //Splash Image
    float Delaytime = 1.2;
    if(ofGetHeight() == 960)
    {
        mSplashImage.setImageFile("Default@2x.png");
        Delaytime = 1.0;
    }
    else if(ofGetHeight() == 1136)
    {
        mSplashImage.setImageFile("Default-568h@2x.png");
        Delaytime = 1.5;
    }
    else if(ofGetHeight() == 480)
    {
        mSplashImage.setImageFile("Default.png");
        Delaytime = 0.2;
    }
    
    mSplashImage.useImageSize();
    mSplashImage.x = ofGetWidth() / 2.0;
    mSplashImage.y = ofGetHeight() / 2.0;
    mSplashImage.a = 1.0;
    
    Tweener.addTween(mSplashImage.a, 0.0, 1.0, &ofxTransitions::easeOutQuint, Delaytime);
    
    //mHelpImage
    
    if(ofGetHeight() == 960)
    {
        mHelpImage.setImageFile("help@2x.png");
    }
    else if(ofGetHeight() == 1136)
    {
        mHelpImage.setImageFile("help-568h@2x.png");
    }
    else if(ofGetHeight() == 480)
    {
        mHelpImage.setImageFile("help.png");
    }
    
    mHelpImage.useImageSize();
    mHelpImage.x = ofGetWidth() / 2.0;
    mHelpImage.y = ofGetHeight() / 2.0;
    mHelpImage.a = 0.0;
    
    
    /// -------------- XML Properties  ------------- --------------　 --------------//
    ofkXMLProperties::setXMLFile("mySettings.xml");
    int lastOpenedDay = ofkXMLProperties::getPropertyValue("SETTINGS::LastOpenDateDay", -1);
    
    //cout << "=--------- lastOpenedMonth" << lastOpenedDay << endl;
    //cout << "=--------- lastOpenedSecond" << lastOpenedSEC << endl;

    //NumOpenedEver
    bool isShowHint = false;
    int NumOpenedEver = ofkXMLProperties::getPropertyValue("SETTINGS::NumOpenedEver", -1);
    if(NumOpenedEver == 0 )
    {
        //cout << "=--------- This is first Time Open " << NumOpenedEver << endl;
        isShowHint = true;
        
    }else if( abs(ofGetDay() - lastOpenedDay) > 6 )
    {
        //cout << "=--------- Open in different Week " << lastOpenedDay << endl;
        isShowHint = true;
    }
    
    //debug
    if(isShowHint)
    {
        Tweener.addTween(mHelpImage.a, 1.0, 1.0, &ofxTransitions::easeOutQuint, Delaytime + 0.2);
    }
    
    ofkXMLProperties::setLastOpenData();    
    ofkXMLProperties::setPropertyValue("SETTINGS::NumOpenedEver", NumOpenedEver + 1);
}

//--------------------------------------------------------------
void ofkiosApp::update(){

    Tweener.update();
}

//--------------------------------------------------------------
void ofkiosApp::draw(){
    
    ofPushMatrix();
    ofPopMatrix();
    
    ofSetColor(255, 255, 255);
    
    ofSetupScreen();
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    mSplashImage.render();
    
    if(mHelpImage.a > 0.01)
    {
        mHelpImage.render();
    }
    ofTranslate(mGUISlidePos, 0);
}

//--------------------------------------------------------------
void ofkiosApp::exit(){

}

//--------------------------------------------------------------
void ofkiosApp::touchDown(ofTouchEventArgs & touch){

    isTouched = true;

    mTouchPos.x = touch.x * 1;
    mTouchPos.y = touch.y * 1;// -ofGetHeight() * 1.0;

    mTouchPosEx = mTouchDownPos = mTouchPos;
    isRitghDragOneDirection = true;
    
    mTouchOnTime = ofGetElapsedTimeMillis();
    
}

//--------------------------------------------------------------
void ofkiosApp::touchMoved(ofTouchEventArgs & touch){
        
    if(touch.numTouches != 1)
    {
        isTouched = false;
        return;
    }
    
    mTouchPos.x = touch.x * 1;
    mTouchPos.y = touch.y * 1;// -ofGetHeight() * 1.0;
    
    //-----Widgetz 初期の動きFBを付けること。
    if( abs(mTouchDownPos.x - mTouchPos.x) >  2 * abs(mTouchDownPos.y - mTouchPos.y))
    {
        //横方向への移動が支配的の時、 // CLOSE TO OPEN
        
        if(mTouchPos.x - mTouchDownPos.x > 0)
        {
            //右方向へのDrag // CLOSE to OPEN
            if(isRitghDragOneDirection)
            {
                if( mTouchPos.x - mTouchDownPos.x > ofGetWidth() * 0.33)
                {
                    //OPEN
                    changeWidgetState(WidgetOpened);
                    
                }else if( mTouchPos.x - mTouchDownPos.x > ofGetWidth() * 0.20)
                {
                    guiCanvas->setVisible(true);
                    
                    //CLOSEDの時に、
                    if( mWidgetState == WidgetClosed)
                    {
                        mGUISlidePos += (mTouchPos.x - mTouchPosEx.x) * 0.9;
                    }
                }
            }

        }else
        {
            //左方向へのDrag // OPEN to CLOSE
            isRitghDragOneDirection = false;
            
            //Touch Onの座標で棄却する。
            if( guiCanvas->getWidgetHit(mTouchDownPos.x, mTouchDownPos.y) == NULL)
            {
                
                if(mTouchPos.x - mTouchDownPos.x < - ofGetWidth() * 0.25)
                {
                    //CLOSE
                    changeWidgetState(WidgetClosed);
                }else if( mTouchPos.x - mTouchDownPos.x < - ofGetWidth() * 0.10)
                {
                    if( mWidgetState == WidgetOpened)
                    {
                        mGUISlidePos += (mTouchPos.x - mTouchPosEx.x) * 2.0;
                    }
                }                
            }
        }
    }
    
    mTouchPosEx = mTouchPos;
}

//--------------------------------------------------------------
void ofkiosApp::touchUp(ofTouchEventArgs & touch){
    
    isTouched = false;
    mTouchPos.x = touch.x * 1;
    mTouchPos.y = touch.y * 1;// -ofGetHeight() * 1.0;
    
    //吸着させる。
    changeWidgetState(mWidgetState);
    
    if( mTouchPos.y > (ofGetHeight() * (1.0 - 200.0 / 960.0)) )
    {
        if(mHelpImage.a > 0.1)
        {
            Tweener.addTween(mHelpImage.a, 0.0, 1.0, &ofxTransitions::easeOutQuint);
        }
    }
}

//--------------------------------------------------------------
void ofkiosApp::touchDoubleTap(ofTouchEventArgs & touch){
}


//--------------------------------------------------------------
void ofkiosApp::touchCancelled(ofTouchEventArgs & touch){
    
}

void ofkiosApp :: touchTwoFinger ( ofkMultiTouchEventArgs &multiTouch )
{
    //Check GUI Widget
    if(isGUIWidgetActive())
        return;
    
    if(abs(multiTouch.angleDif) * 5  > abs(multiTouch.pinchLengthDif))
    {
        //ROTATE
        
    }else{
        //PINCH
    }

}

//--------------------------------------------------------------
void ofkiosApp::lostFocus(){

}

//--------------------------------------------------------------
void ofkiosApp::gotFocus(){

}

//--------------------------------------------------------------
void ofkiosApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofkiosApp::deviceOrientationChanged(int newOrientation){

}


void ofkiosApp::initGUILayout()
{
    float WidgetWidth = ofGetWidth() * 0.7;
    int xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    int FONT_LARGE = (int) 30 / 1.2 * DISP_RATIO;
    int FONT_MID= (int) 25  /1.2 * DISP_RATIO;
    int FONT_SMALL= (int) 20 / 1.2 * DISP_RATIO;
    float length = WidgetWidth - xInit;
    
    //-guiHeader-----------------------------------------------------------//
    
    float guiHeaderHEIGHT = 2.0 * DISP_RATIO;
    
    guiCanvas = new ofxUICanvas(0,0 ,WidgetWidth,ofGetHeight() * guiHeaderHEIGHT);
    
    //guiCanvas->setTheme(OFX_UI_THEME_HACKER);
    
    ofColor cb = ofColor( 0*255.0, 0*255.0, 0*255.0, 0.7*255.0 );
    ofColor co = ofColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.392157*255.0 );
    ofColor coh = ofColor( 0.294118*255.0, 0*255.0, 0.0588235*255.0, 0.784314*255.0 );
    ofColor cf = ofColor( 0.784314*255.0, 1*255.0, 0*255.0, 0.784314*255.0 );
    ofColor cfh = ofColor( 0.980392*255.0, 0.00784314*255.0, 0.235294*255.0, 1*255.0 );
    ofColor cp = ofColor( 0.0156863*255.0, 0*255.0, 0.0156863*255.0, 0.392157*255.0 );
    ofColor cpo = ofColor( 0.254902*255.0, 0.239216*255.0, 0.239216*255.0, 0.784314*255.0 );
    guiCanvas->setUIColors( cb, co, coh, cf, cfh, cp, cpo );
     
    guiCanvas->setFont("Roboto-Light.ttf");
    guiCanvas->setFontSize(OFX_UI_FONT_LARGE , FONT_LARGE);
    guiCanvas->setFontSize(OFX_UI_FONT_MEDIUM , FONT_MID);
    guiCanvas->setFontSize(OFX_UI_FONT_SMALL , FONT_SMALL);
    
    {
        
        float SliderHeight = 60 * DISP_RATIO;
        float SpaceOffset = 100 * DISP_RATIO;

        guiCanvas->addWidgetDown(new ofxUILabel("DotLight Settings", OFX_UI_FONT_LARGE));

        guiCanvas->addSpacer(length-xInit, SpaceOffset)->setVisible(false);
        guiCanvas->addSpacer(length-xInit, 1)->setVisible(true);

        guiCanvas->addWidgetDown(new ofxUISpacer(length-xInit, 1));
    }
    
    //ofAddListener(guiCanvas->newGUIEvent, this, &ofkiosApp::guiEvent);
    guiCanvas->disableTouchEventCallbacks();
    
    // ----------- Widget State Init -------//
    
    mWidgetState = WidgetClosed;
    mGUISlidePos = WIDGET_CLOSED_POSX;
}

void ofkiosApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "TEST")
    {
		ofxUIButton *button = (ofxUIButton *) e.widget;
        if(button->getValue())
        {
        }
    }
}

bool ofkiosApp::isGUIWidgetActive()
{
    bool res = false;
    
    if(WIDGET_OPENED_POSX == mWidgetState)
    {
        res = true;
    }
    return res;
}

void ofkiosApp::changeWidgetState( WidgetState nextState)
{
    //アニメーション追加する；
    if(true)
    {
        if(WidgetOpened == nextState)
        {
            Tweener.addTween(mGUISlidePos, WIDGET_OPENED_POSX, 0.2, &ofxTransitions::easeOutQuint);
            guiCanvas->setVisible(true);
            
            printf("WidgetOpened /n");

        }else if (WidgetClosed == nextState)
        {
            Tweener.addTween(mGUISlidePos, WIDGET_CLOSED_POSX, 0.2, &ofxTransitions::easeOutQuint);
            guiCanvas->disable();
            guiCanvas->setVisible(false);

            printf("WidgetClosed /n");
        }
        mWidgetState = nextState;
    }
}

