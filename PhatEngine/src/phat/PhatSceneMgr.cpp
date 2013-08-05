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
    Text = new PhatText("tahoma.ttf", 32.0f);
    Input = new PhatInput();
}
PhatSceneMgr::PhatSceneMgr() {
    _intialize();
}

/////////////////////////////////////////////////////////
// Destructor - Release
void PhatSceneMgr::_release() {
    delete Input;   Input   = NULL;
    delete Text;    Text    = NULL;
    delete Context; Context = NULL;
}
PhatSceneMgr::~PhatSceneMgr() {
    _release();
}

/////////////////////////////////////////////////////////
// Update
void PhatSceneMgr::Update() {
    if(Input->IsTouched(TOUCHBEGAN, 0)) {
        Input->SetTouched(0);
        printf("Touched\n");
    }
}

/////////////////////////////////////////////////////////
// Render
void PhatSceneMgr::Render() {
   
}
