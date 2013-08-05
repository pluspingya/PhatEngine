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
    scene = new SceneSample();
}

/////////////////////////////////////////////////////////
// Destructor
SceneManager::~SceneManager() {
    delete scene;       scene   = NULL;
}

/////////////////////////////////////////////////////////
// Update
void SceneManager::Update() {
    scene->Update(Context);
}

/////////////////////////////////////////////////////////
// Render
void SceneManager::Render() {
    Context->BeginRender();
    Context->SetDimension(2);
    
    scene->Render(Context);
    
    Text->SetFontScale(1.0f);
    Text->SetPivotType(TOP_LEFT);
    Text->DrawText(Context, (char*)"HelloWorld", vec2f(10.0f));
    
    Text->SetFontScale(0.5f);
    Text->SetPivotType(BOTTOM_MIDDLE);
    sprintf(Text->TextBuffer, "cur=%d,%d", Input->GetTouch(TOUCHCURRENT, 0).x, Input->GetTouch(TOUCHCURRENT, 0).y);
    Text->DrawText(Context, Text->TextBuffer, vec2f(Input->GetTouch(TOUCHCURRENT, 0).x, Input->GetTouch(TOUCHCURRENT, 0).y));
    
    Context->EndRender();
}