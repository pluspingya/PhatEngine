//
//  PhatObj3D.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#include <phat/PhatObj3D.h>

PhatObj3D::PhatObj3D() {
    Size = vec2f();
    Position = vec3f();
    Rotation = vec3f();
    Scaling = vec3f(1.0f);
    Colour = col4f(1.0f, 1.0f, 1.0f, 1.0f);
    this->SetPivotType(CENTER); //Pivot is set here
}

PhatObj3D::~PhatObj3D() {
    
}

void PhatObj3D::SetPivotType(OBJ3D_PIVOT_TYPE type) {
    switch(type) {
		case TOP_LEFT:      Pivot.set(-(Size.x/2.0f), -(Size.y/2.0f), 0.0f);    break;
		case TOP_RIGHT:     Pivot.set( (Size.x/2.0f), -(Size.y/2.0f), 0.0f);    break;
		case BOTTOM_LEFT:   Pivot.set(-(Size.x/2.0f),  (Size.y/2.0f), 0.0f);    break;
		case BOTTOM_RIGHT:  Pivot.set( (Size.x/2.0f),  (Size.y/2.0f), 0.0f);    break;
		default:
		case CENTER:    Pivot.set();    break;
	}
}
