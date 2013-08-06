//
//  PhatScene.h
//  PhatEngine
//
//  Created by Plus Pingya Avalable on 8/5/56 BE.
//  Copyright (c) 2556 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef PHATENGINE_H_INCLUDED
#define PHATENGINE_H_INCLUDED

#include <phat/PhatContext.h>
#include <phat/PhatFps.h>
#include <phat/PhatInput.h>
#include <phat/PhatText.h>

class PhatScene {
    
    void _initialize();
    void _release();
    
public:
    
    PhatScene();
    ~PhatScene();
    
    virtual int Update(PhatContext *context, PhatFps *fps, PhatInput *input, PhatText *text);
    virtual void Render(PhatContext *context, PhatFps *fps, PhatInput *input, PhatText *text);
    
};

#endif  //PHATENGINE_H_INCLUDED
