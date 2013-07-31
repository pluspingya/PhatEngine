//
//  rect.h
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef REC_H_INCLUDED
#define REC_H_INCLUDED

/////////////////////////////////////////////////////////
// 4D Float Rectangular
struct rec4f {
	float x, y, w, h;
	rec4f() {
		x = y = w = h = 0.0f;
	}
	rec4f(float _x, float _y, float _w, float _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}
};

#endif  //REC_H_INCLUDED
