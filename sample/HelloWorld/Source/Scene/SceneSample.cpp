//
//  SceneSample.cpp
//  HelloWorld
//
//  Created by Plus Pingya Avalable on 8/5/56 BE.
//  Copyright (c) 2556 Plus Pingya. All rights reserved.
//

#include "SceneSample.h"

/////////////////////////////////////////////////////////
// Constructor
SceneSample::SceneSample() {
    plane = new PhatPlane(vec2f(100.0f, 100.0f));
    plane->SetPivotType(TOP_LEFT);
    
    texture = new PhatTexture("test.png");
    texture->AnimateTexture(0, 3, 10, vec2f(100.0f));
}

/////////////////////////////////////////////////////////
// Destructor
SceneSample::~SceneSample() {
    delete texture;     texture = NULL;
    delete plane;       plane   = NULL;
}

/////////////////////////////////////////////////////////
// Update
void SceneSample::Update(PhatContext *context) {
    texture->Update();
}

/////////////////////////////////////////////////////////
// Render
void SceneSample::Render(PhatContext *context) {
    plane->Position.set(context->ScreenSize.x/2.0f, context->ScreenSize.y/2.0f);
    //texture->CropTexture(0, vec2f(100.0f, 100.0f));
    //texture->FlipTexture(false, false);
    
    plane->SetPivotType(BOTTOM_RIGHT);
    plane->Render(context, texture);
    
    //texture->CropTexture(rec4f(100.0f, 0.0f, 100.0f, 100.0f));
    plane->SetPivotType(BOTTOM_LEFT);
    //texture->CropTexture(2, vec2f(100.0f, 100.0f));
    plane->Render(context, texture);
}

