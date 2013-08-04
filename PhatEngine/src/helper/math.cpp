//
//  math.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 8/3/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com

#include <helper/math.h>

int makeExpotential(int x) {
	int sum = 1;
	while(sum < x) {
		sum *= 2;
	}
	return sum;
}
