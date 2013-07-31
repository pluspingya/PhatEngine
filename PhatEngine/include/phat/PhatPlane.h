//
//  PhatPlane.h
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com

#ifndef PHATPLANE_H_INCLUDED
#define PHATPLANE_H_INCLUDED

#include <phat/PhatContext.h>
#include <phat/PhatObj3D.h>
#include <phat/PhatTexture.h>

enum BLENDMODE {
    NORMAL,
    NORMAL_ONE,
    GROW,
    GROW_TEST
};

class PhatPlane: public PhatObj3D {
    
private:
    void _initialize(vec2f size);
    void _release();
    
public:
    
    BLENDMODE   Blendmode;
    
    PhatPlane();
    PhatPlane(vec2f size);
    ~PhatPlane();
    
    void Render(PhatContext *context);
    void Render(PhatContext *context, PhatTexture *texture);
    
};

#endif  //PHATPLANE_H_INCLUDED
