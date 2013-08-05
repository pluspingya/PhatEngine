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

class PhatScene {
    
    void _initialize();
    void _release();
    
public:
    
    PhatScene();
    ~PhatScene();
    
    virtual void Update(PhatContext *context);
    virtual void Render(PhatContext *context);
    
};

#endif  //PHATENGINE_H_INCLUDED
