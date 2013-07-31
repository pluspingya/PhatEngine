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

class PhatTexture {
    
private:
    void _initialize();
    void _release();
    
public:
    
    GLuint TextureID;
    
    PhatTexture();
    ~PhatTexture();
};

#endif  //PHATTEXTURE_H_INCLUDED
