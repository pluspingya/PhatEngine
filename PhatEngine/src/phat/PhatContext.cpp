//
//  PhatContext.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#include <phat/PhatContext.h>

/////////////////////////////////////////////////////////
// Constructor - Intialize
void PhatContext::_initialize(vec2d screensize, col4f screencolour) {
    ScreenSize.copy(screensize);
    ScreenColour.copy(screencolour);
    Viewport = rec4f(0.0f, 0.0f, screensize.x, screensize.y);
    Ortho = rec4f(0.0, 0.0, screensize.x, screensize.y);
    Scaling.set(1.0f);
    ZoomFactor = 1.0f;
}
PhatContext::PhatContext() {
    _initialize(vec2d(320, 480), col4f(1.0f, 0.0f, 0.0f, 1.0f));
}
PhatContext::PhatContext(vec2d screensize) {
    _initialize(screensize, col4f(0.0f, 0.0f, 0.0f, 1.0f));
}
PhatContext::PhatContext(vec2d screensize, col4f screencolour) {
    _initialize(screensize, screencolour);
}

/////////////////////////////////////////////////////////
// Destructor - Release
void PhatContext::_release() {
    
}
PhatContext::~PhatContext() {
    _release();
}

/////////////////////////////////////////////////////////
// Core functions - must be called
void PhatContext::SetScreenSize(vec2d screensize) {
    ScreenSize.set(screensize.x, screensize.y);
}
void PhatContext::SetScreenColour(col4f screencolour) {
    ScreenColour.set(screencolour.r, screencolour.g, screencolour.b, screencolour.a);
}
void PhatContext::SetDimension(int dimension) {
    
    if(dimension > 0) {
        Dimension = dimension;
    }
    
    //glViewport(Viewport.x*Scaling.x, Viewport.y*Scaling.y, Viewport.w*Scaling.x, Viewport.h*Scaling.y);
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, Viewport.w, Viewport.h);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity( );
    
    if(Dimension == 3) {
        
    }else { //otherwise, they all are 2D
        glOrthof(Ortho.x-((Ortho.w)*(ZoomFactor-1.0f)), Ortho.x+(Ortho.w*ZoomFactor), Ortho.y+(Ortho.h*ZoomFactor), Ortho.y-((Ortho.h)*(ZoomFactor-1.0f)), -1.0f, 1.0f);
        //glOrthof(0.0f, 320.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    }
    glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
    
/*
		case SC_BOTTOMUP: {
			glOrtho(Ortho.x-((Ortho.w)*(ZoomFactor-1.0f)), Ortho.x+(Ortho.w*ZoomFactor), Ortho.y-((Ortho.h)*(ZoomFactor-1.0f)), Ortho.y+(Ortho.h*ZoomFactor), -1.0f, 1.0f);
			//glOrtho(0.0f, 38, 0.0f, 32.0f, -1.0f, 1.0f);
*/
	//}
	
}
void PhatContext::BeginRender() {
    glClearColor(ScreenColour.r, ScreenColour.g, ScreenColour.b, ScreenColour.a);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
void PhatContext::EndRender() {
    
}