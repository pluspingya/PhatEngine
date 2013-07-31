//
//  col.h
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef COL_H_INCLUDED
#define COL_H_INCLUDED

/////////////////////////////////////////////////////////
// 4D Integer Colour
struct col4d {
	int r, g, b, a;
	col4d() {
		r = g = b = a = 255;
	}
	col4d(int _r, int _g, int _b, int _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
};
// 4D Float Colour
struct col4f {
	float r, g, b, a;
	col4f() {
		r = g = b = a = 1.0f;
	}
	col4f(float _r, float _g, float _b, float _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
    void set(float _r, float _g, float _b, float _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
    void copy(col4f col) {
        r = col.r;
        g = col.g;
        b = col.b;
        a = col.a;
    }
};

#endif  //COL_H_INCLUDED
