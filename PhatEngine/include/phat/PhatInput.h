//
//  PhatInput.h
//  PhatEngine
//
//  Created by Plus Pingya on 8/4/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef PHATINPUT_H_INCLUDED
#define PHATINPUT_H_INCLUDED

#include <vo/vec.h>
#include <vo/rec.h>

#define MAX_TOUCHES     5

enum TOUCH_TYPE {
    TOUCHBEGAN,
    TOUCHMOVED,
    TOUCHENDED,
    TOUCHCURRENT
};

class PhatInput {
    
    vec2d _touch[4][MAX_TOUCHES];
    bool  _touched[MAX_TOUCHES];
    
    void _initialize();
    void _release();
    
public:
    
    PhatInput();
    ~PhatInput();
    
    void SetTouch(TOUCH_TYPE type, int touchid, vec2d touch);
    vec2d GetTouch(TOUCH_TYPE type, int touchid);
    
    bool IsTouched(TOUCH_TYPE type, int touchid);
    bool IsTouched(TOUCH_TYPE type, int touchid, rec4f rect);
    void SetTouched(int touchid, bool value);
    void SetTouched(int touchid);
    
};

#endif  //PHATINPUT_H_INCLUDED
