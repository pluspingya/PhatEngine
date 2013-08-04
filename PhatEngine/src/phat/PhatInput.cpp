//
//  PhatInput.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 8/4/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya
//

#include <phat/PhatInput.h>

/////////////////////////////////////////////////////////
// Constructor - Intialize
void PhatInput::_initialize() {
    for (int i=0; i<MAX_TOUCHES; i++) {
        _touched[i] = false;
    }
}
PhatInput::PhatInput() {
    _initialize();
}

/////////////////////////////////////////////////////////
// Destructor - Release
void PhatInput::_release() {
    
}
PhatInput::~PhatInput() {
    _release();
}

/////////////////////////////////////////////////////////
// Core functions - must be called
void PhatInput::SetTouch(TOUCH_TYPE type, int touchid, vec2d touch) {
    if (touchid>=0 && touchid<MAX_TOUCHES) {
        if (type == TOUCHENDED) {
            _touch[TOUCHBEGAN][touchid].set(0, 0);
            _touch[TOUCHMOVED][touchid].set(0, 0);
            _touch[TOUCHENDED][touchid].set(0, 0);
            SetTouched(touchid, false);
        }else {
            _touch[type][touchid].copy(touch);
        }
        _touch[TOUCHCURRENT][touchid].copy(touch);
    }
}
vec2d PhatInput::GetTouch(TOUCH_TYPE type, int touchid) {
    return _touch[type][touchid];
}
bool PhatInput::IsTouched(TOUCH_TYPE type, int touchid) {
    if (_touch[type][touchid].x > 0 && _touch[type][touchid].y > 0 && !_touched[touchid]) {
        return true;
    }
    return false;
}
bool PhatInput::IsTouched(TOUCH_TYPE type, int touchid, rec4f rect) {
    if (_touch[type][touchid].x >= rect.x && _touch[type][touchid].y <= rect.x+rect.w) {
        if (_touch[type][touchid].y >= rect.y && _touch[type][touchid].y <= rect.y+rect.h) {
            return IsTouched(type, touchid);
        }
    }
    return false;
}
void PhatInput::SetTouched(int touchid, bool value) {
    if (touchid>=0 && touchid<MAX_TOUCHES) {
        _touched[touchid] = value;
    }
}
void PhatInput::SetTouched(int touchid) {
    SetTouched(touchid, true);
}



