//
//  SceneSample.h
//  HelloWorld
//
//  Created by Plus Pingya Avalable on 8/5/56 BE.
//  Copyright (c) 2556 Plus Pingya. All rights reserved.
//

#ifndef __HelloWorld__SceneSample__
#define __HelloWorld__SceneSample__

#include <phat/PhatScene.h>
#include <phat/PhatPlane.h>
#include <phat/PhatTexture.h>

#define SCENE_SAMPLE    0

class SceneSample: public PhatScene {
    
    PhatPlane       *plane      = NULL;
    PhatTexture     *texture    = NULL;
    
public:
    
    SceneSample();
    ~SceneSample();
    
    int Update(PhatContext *context, PhatFps *fps, PhatInput *input, PhatText *text);
    void Render(PhatContext *context, PhatFps *fps, PhatInput *input, PhatText *text);
    
};

#endif /* defined(__HelloWorld__SceneSample__) */
