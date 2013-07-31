//
//  PhatObj3D.h
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef PHATOBJ3D_H_INCLUDED
#define PHATOBJ3D_H_INCLUDED

// Value Objects
#include <vo/vec.h>
#include <vo/col.h>
#include <vo/rec.h>

enum OBJ3D_PIVOT_TYPE {
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	CENTER
};

class PhatObj3D {
    
public:
    vec2f Size;
    vec3f Position;
    vec3f Rotation;
    vec3f Scaling;
    col4f Colour;
    vec3f Pivot;
    
    PhatObj3D();
    ~PhatObj3D();
    
    void SetPivotType(OBJ3D_PIVOT_TYPE type);
};

#endif  //PHATOBJ3D_H_INCLUDED
