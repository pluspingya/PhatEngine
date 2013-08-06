//
//  SceneManager.cpp
//  HelloWorld
//
//  Created by Plus Pingya Avalable on 8/5/56 BE.
//  Copyright (c) 2556 Plus Pingya. All rights reserved.
//

#include "SceneManager.h"

/////////////////////////////////////////////////////////
// Constructor
SceneManager::SceneManager() {
    
}

/////////////////////////////////////////////////////////
// Destructor
SceneManager::~SceneManager() {
    
}

/////////////////////////////////////////////////////////
// Update
void SceneManager::Update() {
    if (!Scene) {
        switch (SceneSelect) {
            default:
            case SCENE_SAMPLE:
                Scene = new SceneSample();
                break;
        }
        SceneCurrent = SceneSelect;
    }else {
        if(PhatSceneMgr::Update(Scene) != SceneCurrent) {
            delete Scene;
            Scene = NULL;
        }
    }
}

/////////////////////////////////////////////////////////
// Render
void SceneManager::Render() {
    
    PhatSceneMgr::Render(Scene);
    
    Text->SetFontScale(1.0f);
    Text->SetPivotType(TOP_LEFT);
    swprintf(Text->TextBuffer, 255, L"FPS: %d -> %d", Fps->GetFPS(), Fps->GetXFPS());
    Text->DrawText(Context, Text->TextBuffer, vec2f(10.0f));
    
    Text->SetFontScale(0.5f);
    Text->SetPivotType(BOTTOM_MIDDLE);
    swprintf(Text->TextBuffer, 255, L"%d,%d", Input->GetTouch(TOUCHCURRENT, 0).x, Input->GetTouch(TOUCHCURRENT, 0).y);
    Text->DrawText(Context, Text->TextBuffer, vec2f(Input->GetTouch(TOUCHCURRENT, 0).x, Input->GetTouch(TOUCHCURRENT, 0).y));
    
}