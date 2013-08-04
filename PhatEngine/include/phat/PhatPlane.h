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
    void _tweening();
public:
    
    BLENDMODE   Blendmode;
    void *UserData;
    
    PhatTexture *Texture;
    
    bool  TweenActive;
    bool  TweenConstantly;
    float TweenSpeed;
    vec3f TweenDistination;
    
    PhatPlane();
    PhatPlane(vec2f size);
    ~PhatPlane();
    
    void Update();
    void Render(PhatContext *context);
    void Render(PhatContext *context, PhatTexture *texture);
    
    void Tween(vec3f start, vec3f distination, float speed, bool constantly);
};

#endif  //PHATPLANE_H_INCLUDED
