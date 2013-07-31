//
//  PhatTexture.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#include <phat/PhatTexture.h>

void PhatTexture::_initialize() {
    TextureID = -1;
}
PhatTexture::PhatTexture() {
    _initialize();
}

void PhatTexture::_release() {

}
PhatTexture::~PhatTexture() {
    _release();
}