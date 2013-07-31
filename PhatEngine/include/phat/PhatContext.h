//
//  PhatContext.h
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef PHATCONTEXT_H_INCLUDED
#define PHATCONTEXT_H_INCLUDED

#include <stdio.h>
#include <assert.h>

// OpenGL Libraries
#if TARGET_OS_IPHONE || TARGET_OS_IPHONE_SIMULATOR || __APPLE__
#include <OpenGLES/EAGL.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif

// Values Object (vo)
#include <vo/vec.h>
#include <vo/col.h>
#include <vo/rec.h>

class PhatContext {
    
    void _initialize(vec2d screensize, col4f screencolour);
    void _release();
    
public:
    
    vec2d ScreenSize;
    rec4f Viewport;
    vec2f Scaling;
    rec4f Ortho;
    float ZoomFactor;
    
    col4f ScreenColour;
    int   Dimension;
    
    PhatContext();
    PhatContext(vec2d screensize);
    PhatContext(vec2d screensize, col4f screencolour);
    ~PhatContext();
    
    // Core functions - must be called
    void SetScreenSize(vec2d screensize);
    void SetScreenColour(col4f screencolour);
    void SetDimension(int dimension);
    void BeginRender();
    void EndRender();
    
};

#endif  //PHATCONTEXT_H_INCLUDED
