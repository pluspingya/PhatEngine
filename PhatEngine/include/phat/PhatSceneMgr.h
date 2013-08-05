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
#include <phat/PhatText.h>
#include <phat/PhatInput.h>

class PhatSceneMgr {
    
    void _intialize();
    void _release();
    
public:

    PhatContext     *Context    = NULL;
    PhatText        *Text       = NULL;
    PhatInput       *Input      = NULL;

    PhatSceneMgr();
    ~PhatSceneMgr();

    void Update();
    void Render();

};

#endif  //PHATSCENEMGR_H_INCLUDED
