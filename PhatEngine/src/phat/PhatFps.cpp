//
//  PhatFps.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 8/6/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#include <phat/PhatFps.h>

/////////////////////////////////////////////////////////
// Constructor - Intialize
void PhatFps::_initialize() {
    _frameCount = _xframeCount = 0;
    _fps = _xfps = 60;
    _timeElapsed = 0;
}
PhatFps::PhatFps() {
    _initialize();
}

/////////////////////////////////////////////////////////
// Destructor - Release
void PhatFps::_release() {
    
}
PhatFps::~PhatFps() {
    _release();
}

/////////////////////////////////////////////////////////
// Core functions - must be called
void PhatFps::Update() {
    _frameCount++;
    unsigned int now = GetNow();
    if (now - _timeElapsed > 1000) { //Miliseconds
        _timeElapsed = now;
        _fps = _frameCount;
        _frameCount = 0;
        _xfps = _xframeCount;
        _xframeCount = 0;
    }
}
void PhatFps::XUpdate() {
    _xframeCount++;
}

/////////////////////////////////////////////////////////
// Optional functions
unsigned int PhatFps::GetNow() {
    unsigned int now = 0;
#if __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    static unsigned int tmp_hold = (unsigned int)(CACurrentMediaTime() * 1000);
    now = (unsigned int)(CACurrentMediaTime() * 1000) - tmp_hold;
#elif TARGET_OS_MAC
#endif
#elif ANDROID
    clock_t uptime = clock();// / (CLOCKS_PER_SEC / 1000);
	t_timeCurrent = (int)uptime;
	/*
     struct timeval stTimeVal;
     gettimeofday(&stTimeVal, NULL);
     t_timeCurrent = int(stTimeVal.tv_sec * 1000000ll + stTimeVal.tv_usec);
     */
#elif _WIN32
	SYSTEMTIME time;
	GetSystemTime(&time);
	WORD millis = (time.wSecond * 1000) + time.wMilliseconds;
	t_timeCurrent = (int)millis;
#endif
	return now;
}
int PhatFps::GetFPS() {
    return _fps;
}
int PhatFps::GetXFPS() {
    return _xfps;
}
int PhatFps::GetNumberOfUpdate() {
    //int x = (int)round(_fps/MAX_FPS);
    int n = (int)round(MAX_FPS/_fps);
    if (n > MAX_DUP) {
        n = MAX_DUP;
    }
    return n;
}
