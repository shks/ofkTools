//
//  glslBufferMixer.cpp
//  glslbufferMixer
//
//  Created by Shunichi Kasahara on 2014/11/05.
//
//

#include "ofxGlslEmaFilter.h"


void ofxGlslEmaFilter::setupGLSL(int w, int h)
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
    << "uniform float weight;" << endl
    << "void main(void)" << endl
    << "{" << endl
    << "vec2 src0 = gl_TexCoord[0].st;" << endl
//    << "src0 *= 1;" << endl
    << "vec4 col0 = texture2DRect(texture0, src0);" << endl
    << "vec4 col1 = texture2DRect(texture1, src0);" << endl
    << "gl_FragColor = weight * col0 + (1.0 - weight) * col1;" << endl
    << "}" << endl;
    
    GLint success;      //ERROR CODE
    
    string glslSourceString = oss.str();
    const char * glslSource = glslSourceString.c_str();
    
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
}

void ofxGlslEmaFilter::render()
{
    output.begin();
    
    float w = mWidth;
    float h = mHeight;
    
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    glUseProgramObjectARB(glslProgramObject);
    
    glUniform1iARB(glGetUniformLocationARB(glslProgramObject, "texture0"),10);
    glUniform1iARB(glGetUniformLocationARB(glslProgramObject, "texture1"),11);
    glUniform1fARB(glGetUniformLocationARB(glslProgramObject, "weight"), mEMAWight);
                
    
    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, img.getTextureReference().getTextureData().textureID);
    
    glActiveTexture(GL_TEXTURE11);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, output.getTextureReference().getTextureData().textureID);
    
    
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

void ofxGlslEmaFilter::update(ofPixelsRef pixelRef, float newWeight)
{
    mEMAWight = newWeight;
    
    img.setFromPixels(pixelRef);
    img.update();
    img.setUseTexture(true);
    
    render();
}

void ofxGlslEmaFilter::draw(float x,float y,float w,float h)
{
    output.draw(x, y, w, h);
}
