//
//  SceneManager.h
//  HelloWorld
//
//  Created by Plus Pingya Avalable on 8/5/56 BE.
//  Copyright (c) 2556 Plus Pingya. All rights reserved.
//

#ifndef __HelloWorld__SceneManager__
#define __HelloWorld__SceneManager__

#include <phat/PhatSceneMgr.h>
#include <phat/PhatScene.h>
#include <Scene/SceneSample.h>

class SceneManager: public PhatSceneMgr {
    
    PhatScene     *scene      = NULL;
    
public:

    SceneManager();
    ~SceneManager();
    
    void Update();
    void Render();
    
};

#endif /* defined(__HelloWorld__SceneManager__) */
