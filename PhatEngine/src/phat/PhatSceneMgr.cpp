//
//  PhatSceneMgr.cpp
//  PhatEngine
//
//  Created by Plus Pingya Avalable on 8/5/56 BE.
//  Copyright (c) 2556 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#include <phat/PhatSceneMgr.h>

/////////////////////////////////////////////////////////
// Constructor - Initialize
void PhatSceneMgr::_intialize() {
    Context = new PhatContext();
    Fps = new PhatFps();
    Input = new PhatInput();
    Text = new PhatText("tahoma.ttf", 32.0f);
    Scene = NULL;
    SceneSelect = 0;
    SceneCurrent = 0;
}
PhatSceneMgr::PhatSceneMgr() {
    _intialize();
}

/////////////////////////////////////////////////////////
// Destructor - Release
void PhatSceneMgr::_release() {
    delete Scene;   Scene   = NULL;
    delete Text;    Text    = NULL;
    delete Input;   Input   = NULL;
    delete Fps;     Fps     = NULL;
    delete Context; Context = NULL;
}
PhatSceneMgr::~PhatSceneMgr() {
    _release();
}

/////////////////////////////////////////////////////////
// Update
int PhatSceneMgr::Update(PhatScene *scene) {
    int result = -1;
    Fps->Update();
    if (scene) {
        for (int i=0; i<Fps->GetNumberOfUpdate(); i++) {
            Fps->XUpdate();
            result = scene->Update(Context, Fps, Input, Text);
        }
    }
    return result;
}

/////////////////////////////////////////////////////////
// Render
void PhatSceneMgr::Render(PhatScene *scene) {
    Context->BeginRender();
    if (scene) {
        scene->Render(Context, Fps, Input, Text);
    }
    Context->EndRender();
}
