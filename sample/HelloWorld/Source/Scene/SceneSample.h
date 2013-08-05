//
//  SceneSample.h
//  HelloWorld
//
//  Created by Plus Pingya Avalable on 8/5/56 BE.
//  Copyright (c) 2556 Plus Pingya. All rights reserved.
//

#ifndef __HelloWorld__SceneSample__
#define __HelloWorld__SceneSample__

#include <phat/PhatContext.h>
#include <phat/PhatPlane.h>
#include <phat/PhatTexture.h>
#include <phat/PhatScene.h>

class SceneSample: public PhatScene {
    
    PhatPlane       *plane      = NULL;
    PhatTexture     *texture    = NULL;
    
public:
    
    SceneSample();
    ~SceneSample();
    
    void Update(PhatContext *context);
    void Render(PhatContext *context);
    
};

#endif /* defined(__HelloWorld__SceneSample__) */
