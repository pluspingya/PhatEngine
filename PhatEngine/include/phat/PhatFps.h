//
//  PhatFps.h
//  PhatEngine
//
//  Created by Plus Pingya on 8/6/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef PHATFPS_H_INCLUDED
#define PHATFPS_H_INCLUDED

#include <stdio.h>

#if __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE // iOS Simulator or iOS device
#include <QuartzCore/CABase.h>
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
// Unsupported platform
#endif
#elif ANDROID_NDK
#include <android/log.h>
#elif _WIN32
#include "windows.h"
#endif

#define MAX_FPS 64
#define MAX_DUP 5

class PhatFps {
    
    int _frameCount, _xframeCount;
    int _fps, _xfps;
    unsigned int _timeElapsed;
    
    void _initialize();
    void _release();
    
public:
    
    PhatFps();
    ~PhatFps();
    
    void Update();
    void XUpdate();
    
    unsigned int GetNow();
    int GetFPS();
    int GetXFPS();
    int GetNumberOfUpdate();
    
};

#endif  //PHATFPS_H_INCLUDED
