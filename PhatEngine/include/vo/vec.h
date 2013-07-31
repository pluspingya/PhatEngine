//
//  vec.h
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

/////////////////////////////////////////////////////////
// 2D Integer Vector
struct vec2d {
	int x, y;
	vec2d() {
		x = y = 0;
	}
	vec2d(int _xy) {
		x = y = _xy;
	}
	vec2d(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	}
    void copy(vec2d vec) {
        x = vec.x;
        y = vec.y;
    }
};
// 2D Float Vector
struct vec2f {
	float x, y;
	vec2f() {
		x = y = 0.0f;
	}
	vec2f(float _xy) {
		x = y = _xy;
	}
	vec2f(float _x, float _y) {
		x = _x;
		y = _y;
	}
    void set(float _xy) {
        x = y = _xy;
    }
	void set(float _x, float _y) {
		x = _x;
		y = _y;
	}
    void copy(vec2f vec) {
        x = vec.x;
        y = vec.y;
    }
};

/////////////////////////////////////////////////////////
// 3D Integer Vector
struct vec3d {
	int x, y, z;
	vec3d() {
		x = y = z = 0;
	}
	vec3d(int _x, int _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	}
    
};
// 3D Float Vector
struct vec3f {
	float x, y, z;
	vec3f() {
		x = y = z = 0.0f;
	}
	vec3f(float _v) {
		x = y = z = _v;
	}
	vec3f(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	void set() {
		x = y = z = 0.0f;
	}
	void set(float _x, float _y) {
		x = _x;
		y = _y;
	}
	void set(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

#endif  //VEC_H_INCLUDED
