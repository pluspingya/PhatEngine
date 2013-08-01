//
//  PhatTexture.h
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef PHATTEXTURE_H_INCLUDED
#define PHATTEXTURE_H_INCLUDED

// OpenGL Libraries
#if TARGET_OS_IPHONE || TARGET_OS_IPHONE_SIMULATOR || __APPLE__
#include <OpenGLES/ES1/gl.h>
#endif

#include <vo/vec.h>
#include <vo/rec.h>

class PhatTexture {
    
private:
    
    vec2f _textureSize;
    vec2f _maximumSize;
    
    void _initialize();
    void _release();
    
public:
    
    GLuint TextureID;
    
    vec2f TexCoord[4];
    vec2d TexFlip;
    
    PhatTexture();
    PhatTexture(const char *filename);
    PhatTexture(const char *path, const char *filename);
    ~PhatTexture();
    
    GLuint LoadTexture(const char *filename);
    GLuint LoadTexture(const char *path, const char *filename);
    void CropTexture(int frame, vec2f cropsize);
    void CropTexture(rec4f croprect);
    void FlipTexture(bool x, bool y);
    void AnimateTexture(int startframe, int endframe, int delay, vec2f cropsize);

};

#endif  //PHATTEXTURE_H_INCLUDED
