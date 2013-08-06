//
//  PhatSceneMgr.h
//  PhatEngine
//
//  Created by Plus Pingya Avalable on 8/5/56 BE.
//  Copyright (c) 2556 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef PHATSCENEMGR_H_INCLUDED
#define PHATSCENEMGR_H_INCLUDED

#include <phat/PhatContext.h>
#include <phat/PhatFps.h>
#include <phat/PhatInput.h>
#include <phat/PhatText.h>

#include <phat/PhatScene.h>

class PhatSceneMgr {
    
    void _intialize();
    void _release();
    
public:

    PhatContext     *Context    = NULL;
    PhatFps         *Fps        = NULL;
    PhatInput       *Input      = NULL;
    PhatText        *Text       = NULL;
    PhatScene       *Scene      = NULL;
    
    int             SceneSelect;
    int             SceneCurrent;

    PhatSceneMgr();
    ~PhatSceneMgr();

    int Update(PhatScene *scene);
    void Render(PhatScene *scene);

};

#endif  //PHATSCENEMGR_H_INCLUDED
