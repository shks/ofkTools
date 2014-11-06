//
//  glslBufferMixer.cpp
//  glslbufferMixer
//
//  Created by Shunichi Kasahara on 2014/11/05.
//
//

#include "ofxGlslBufferMixer.h"


void ofxGlslBufferMixer::setupGLSL(int w, int h)
{
    
    mWidth = w;
    mHeight = h;
    
    std::ostringstream oss;
    
    //initialize
    oss.str("");
    
    oss << "#version 120 " << endl
    << "#extension GL_ARB_texture_rectangle : enable" << endl
    
    << "uniform sampler2DRect texture0;" << endl
    << "uniform sampler2DRect texture1;" << endl
    << "uniform sampler2DRect texture2;" << endl
    << "uniform sampler2DRect texture3;" << endl
    << "uniform sampler2DRect texture4;" << endl
    << "uniform sampler2DRect texture5;" << endl
    << "//uniform float weight;" << endl
    << "void main(void)" << endl
    << "{" << endl
    << "vec2 src0 = gl_TexCoord[0].st;" << endl
//    << "src0 *= 1;" << endl
    << "vec4 col0 = texture2DRect(texture0, src0);" << endl
    << "vec4 col1 = texture2DRect(texture1, src0);" << endl
    << "vec4 col2 = texture2DRect(texture2, src0);" << endl
    << "vec4 col3 = texture2DRect(texture3, src0);" << endl
    << "vec4 col4 = texture2DRect(texture4, src0);" << endl
    << "vec4 col5 = texture2DRect(texture5, src0);" << endl
    << "gl_FragColor = (col0 + col1 + col2 + col3 + col4 + col5) / 6.0;" << endl
    << "}" << endl;
    
    GLint success;      //ERROR CODE
    
    string glslSourceString = oss.str();
    const char * glslSource = glslSourceString.c_str();

    //shader files
//    string filename = "glsl";
//    ofBuffer buffer = ofBufferFromFile(filename);
//    const char * glslSource = buffer.getText().c_str();

    
    //compile GLSL
    glslProgramObject = glCreateProgramObjectARB();
    glslShaderObject = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
    
    glShaderSourceARB(glslShaderObject,1, &glslSource, NULL);
    glCompileShaderARB(glslShaderObject);
    
    //ERROR CHECk
    glGetObjectParameterivARB(glslShaderObject,GL_OBJECT_COMPILE_STATUS_ARB, &success);
    if(!success){
        cerr << "shader program could not be compiled." << endl;
    }
    
    glAttachObjectARB(glslProgramObject, glslShaderObject);
    glLinkProgramARB(glslProgramObject);
    
    //ERROR CHECk
    glGetObjectParameterivARB(glslProgramObject,GL_OBJECT_LINK_STATUS_ARB, &success);
    if(!success){
        cerr << "shader program could not be linked." << endl;
    }

    output.allocate(w, h, GL_RGB);
    mRingBufferPointer = 0;

}

void ofxGlslBufferMixer::render()
{
    output.begin();
    
    float w = mWidth;
    float h = mHeight;
    
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    glUseProgramObjectARB(glslProgramObject);
    
    glUniform1iARB(glGetUniformLocationARB(glslProgramObject, "texture0"),10);
    glUniform1iARB(glGetUniformLocationARB(glslProgramObject, "texture1"),11);
    glUniform1iARB(glGetUniformLocationARB(glslProgramObject, "texture2"),12);
    glUniform1iARB(glGetUniformLocationARB(glslProgramObject, "texture3"),13);
    glUniform1iARB(glGetUniformLocationARB(glslProgramObject, "texture4"),14);
    glUniform1iARB(glGetUniformLocationARB(glslProgramObject, "texture5"),15);
    
    GLenum GL_TEX_LIST[6] = {GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15};
    for(int i = 0 ; i < 6 ; i++)
    {
        //GL_TEX_LIST
        glActiveTexture(GL_TEX_LIST[i]);
        glBindTexture(GL_TEXTURE_RECTANGLE_ARB, imgRingBuffer[i].getTextureReference().getTextureData().textureID);
    }
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(0,0);
    glVertex2f(0,0);
    
    glTexCoord2f(0,h);
    glVertex2f(0,h);
    
    glTexCoord2f(w,h);
    glVertex2f(w,h);
    
    glTexCoord2f(w,0);
    glVertex2f(w,0);
    
    glEnd();
    
    glUseProgramObjectARB(0);
    
    output.end();
    
}

void ofxGlslBufferMixer::update(ofPixelsRef pixelRef)
{
    
    if(mRingBufferPointer < RingBufferNum && mRingBufferPointer >= 0)
    {
        imgRingBuffer[mRingBufferPointer].setFromPixels(pixelRef);
        imgRingBuffer[mRingBufferPointer].update();
        imgRingBuffer[mRingBufferPointer].setUseTexture(true);
        mRingBufferPointer ++;
    }
    
    if(mRingBufferPointer == RingBufferNum)
        mRingBufferPointer = 0;
    
    render();
}

void ofxGlslBufferMixer::drawDebug()
{
    //
    {
        float w = ofGetWidth() / RingBufferNum;
        float h = w  * (imgRingBuffer[0].getHeight() / imgRingBuffer[0].getWidth() );
        for(int i = 0 ; i < RingBufferNum ; i++)
        {
            imgRingBuffer[i].draw(i * w, 0, w, h);
        }
    }
    
    output.draw(0, 300);    
}

void ofxGlslBufferMixer::draw(float x,float y,float w,float h)
{
    output.draw(x, y, w, h);
}
const ofFbo& ofxGlslBufferMixer::getFboReference()
{
    return output;
}