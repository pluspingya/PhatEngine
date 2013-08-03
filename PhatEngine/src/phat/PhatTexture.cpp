//
//  PhatTexture.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#include <phat/PhatTexture.h>

/////////////////////////////////////////////////////////
// Constructor - Intialize
void PhatTexture::_initialize() {
    TextureID = -1;
    TexCoord[0] = vec2f(0.0f, 1.0f);
    TexCoord[1] = vec2f(1.0f, 1.0f);
    TexCoord[2] = vec2f(0.0f, 0.0f);
    TexCoord[3] = vec2f(1.0f, 0.0f);
    TexFlip = vec2d();
    
    _animationStartFrame = 0;
    _animationEndFrame = 0;
    _animationDelay = 0;
    _animationCropsize = vec2f();
    _animationCountDown = 0;
    _animationCurrenFrame = 0;
    
}
PhatTexture::PhatTexture() {
    _initialize();
}
PhatTexture::PhatTexture(const char *filename) {
    _initialize();
    LoadTexture(filename);
}
PhatTexture::PhatTexture(const char *path, const char *filename) {
    _initialize();
    LoadTexture(path, filename);
}


/////////////////////////////////////////////////////////
// Destructor - Release
void PhatTexture::_release() {

}
PhatTexture::~PhatTexture() {
    _release();
}

/////////////////////////////////////////////////////////
// Core functions - must be called
void PhatTexture::Update() {
    if(_animationStartFrame > 0 && _animationEndFrame > 0) {
        _animationCountDown--;
        if(_animationCountDown <= 0) {
            _animationCountDown = _animationDelay;
            if(_animationEndFrame > _animationStartFrame) {
                _animationCurrenFrame++;
                if (_animationCurrenFrame > _animationEndFrame) {
                    _animationCurrenFrame = _animationStartFrame;
                }else if (_animationCurrenFrame < _animationStartFrame) {
                    _animationCurrenFrame = _animationStartFrame;
                }
            }if (_animationStartFrame > _animationEndFrame) {
                _animationCurrenFrame--;
                if (_animationCurrenFrame < _animationEndFrame) {
                    _animationCurrenFrame = _animationStartFrame;
                }else if(_animationCurrenFrame > _animationStartFrame) {
                    _animationCurrenFrame = _animationEndFrame;
                }
            }
        }
    }
}
GLuint PhatTexture::LoadTexture(const char *filename) {
    return TextureID = LoadTexture((char*)"", filename);
}
GLuint PhatTexture::LoadTexture(const char *path, const char *filename) {
    if(TextureID) {
        glDeleteTextures(1, &TextureID);
        TextureID = -1;
    }
    
	char t_filename[256];
	sprintf(t_filename, "%s%s", path, filename);
    
#if TARGET_OS_IPHONE || TARGET_OS_IPHONE_SIMULATOR || __APPLE__

    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // Bind the number of textures we need, in this case one.
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    
    /*
     switch (_texturemode) {
     case TM_NEAREST:
     default: {
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     }break;
     case TM_LINER: {
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     }break;
     case TM_MIPMAPPED: {
     */
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    /*
     }break;
     }
     */
    
    // Load Texture File
    NSString *t_sfilename = [NSString stringWithUTF8String: filename];
    NSArray *_splitfilename = [t_sfilename componentsSeparatedByString:@"."];
	NSString *t_path = [[NSBundle mainBundle] pathForResource:[_splitfilename objectAtIndex:0] ofType:[_splitfilename objectAtIndex:1]];
	NSData *texData = [[NSData alloc] initWithContentsOfFile:t_path];
    UIImage *image = [[UIImage alloc] initWithData:texData];
    if (image == nil) {
        NSLog(@"Do real error checking with Texture %s", filename);
        return -1;
    }
    
    // Calculate Texture Coordination
 	GLuint width = CGImageGetWidth(image.CGImage);
    GLuint height = CGImageGetHeight(image.CGImage);
	int tmpWidth = 2, tmpHeight = 2;
	while (tmpWidth<width) {
		tmpWidth *= 2;
	}
	while (tmpHeight<height) {
		tmpHeight *= 2;
	}
    TexCoord[0].x = 0.0f;
    TexCoord[0].y = height/(float)tmpHeight;
    TexCoord[1].x = width/(float)tmpWidth;
    TexCoord[1].y = height/(float)tmpHeight;
    TexCoord[2].x = 0.0f;
    TexCoord[2].y = 0.0f;
    TexCoord[3].x = width/(float)tmpWidth;
    TexCoord[2].y = 0.0f;
    _maximumSize.x = TexCoord[1].x;
    _maximumSize.y = TexCoord[0].y;
    _textureSize.x = tmpWidth;
	_textureSize.y = tmpHeight;
    
    //NSLog(@"%fx%f", _textureSize.x, _textureSize.y);
    
    // iPhone Image Loader API
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc( tmpHeight * tmpWidth * 4 );
    CGContextRef context = CGBitmapContextCreate( imageData, tmpWidth, tmpHeight, 8, 4 * tmpWidth, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
    
    // Flip the Y-axis
    CGContextTranslateCTM (context, 0, tmpHeight);
    CGContextScaleCTM (context, 1.0, -1.0);
    
    CGColorSpaceRelease( colorSpace );
    CGContextClearRect( context, CGRectMake( 0, 0, width, height ) );
    CGContextDrawImage( context, CGRectMake( 0, 0, width, height ), image.CGImage );
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tmpWidth, tmpHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, tmpWidth, tmpHeight, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    
    // Release stuffs
    CGContextRelease(context);
    free(imageData);
    imageData = NULL;
	[image release];
    [texData release];
    /*
#elif TARGET_OS_MAC
    
    NSString *t_sfilename = [NSString stringWithUTF8String: _filename];
    NSArray *_splitfilename = [t_sfilename componentsSeparatedByString:@"."];
	NSString *path = [[NSBundle mainBundle] pathForResource:[_splitfilename objectAtIndex:0] ofType:[_splitfilename objectAtIndex:1]];
    
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char *data = SOIL_load_image((char*)[path UTF8String], &width, &height, &channels, 4);
    
	glGenTextures(1, &texture[0]);
	if(data) {
		glBindTexture(GL_TEXTURE_2D, texture[0]);
        //        switch (mode) {
        //            case TM_NEAREST:
        //            default: {
        //                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //            }break;
        //            case TM_LINER: {
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //            }break;
        //            case TM_MIPMAPPED: {
        //                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        //            }break;
        //        }
		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        delete data;
        data = NULL;
	}
    
    m_textureSize.x = width;
	m_textureSize.y = height;
    
    //NSLog(@"%s = %fx%f", _filename, m_textureSize.x, m_textureSize.y);
    
#elif ANDROID_NDK
    
    int t_width, t_height;
    __android_log_print(ANDROID_LOG_INFO, "INFO", "Before load (%s)\n", t_filename);
    texture[0] = loadTextureFromPNG(t_filename, t_width, t_height);
    m_textureSize.x = t_width;
    m_textureSize.y = t_height;
    __android_log_print(ANDROID_LOG_INFO, "INFO", "File %s (%dx%d)\n", t_filename, t_width, t_height);
    
#elif _WIN32
    
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char *data = SOIL_load_image(t_filename, &width, &height, &channels, 4);
    
	glGenTextures(1, &texture[0]);
	if(data) {
		glBindTexture(GL_TEXTURE_2D, texture[0]);
        //        switch (mode) {
        //            case TM_NEAREST:
        //            default: {
        //                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //            }break;
        //            case TM_LINER: {
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //            }break;
        //            case TM_MIPMAPPED: {
        //                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        //            }break;
        //        }
		glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        delete data;
        data = NULL;
	}
    
    m_textureSize.x = width;
	m_textureSize.y = height;
    
    printf("%s = %fx%f\n", t_filename, m_textureSize.x, m_textureSize.y);
    
#else
    */
    
    
#endif
    
    return TextureID;
}

/////////////////////////////////////////////////////////
// Optional functions
void PhatTexture::CropTexture(rec4f croprect) {
    TexCoord[0].x = (croprect.x/_textureSize.x);
    TexCoord[0].y = _maximumSize.y - (croprect.y/_textureSize.y);
    TexCoord[1].x = ((croprect.x+croprect.w)/_textureSize.x);
    TexCoord[1].y = _maximumSize.y - (croprect.y/_textureSize.y);
    TexCoord[2].x = (croprect.x/_textureSize.x);
    TexCoord[2].y = _maximumSize.y - ((croprect.y+croprect.h)/_textureSize.y);
    TexCoord[3].x = ((croprect.x+croprect.w)/_textureSize.x);
    TexCoord[3].y = _maximumSize.y - ((croprect.y+croprect.h)/_textureSize.y);
}
void PhatTexture::CropTexture(int frame, vec2f cropsize) {
    _animationCurrenFrame = frame;
    vec2d t_coord = vec2d();
    float t_width = (frame*cropsize.x);
    while (t_width > _textureSize.x) {
        t_coord.y ++;
        t_width -= _textureSize.x;
    }
    t_coord.x = (int)ceil(t_width/cropsize.x)-1;
    CropTexture(rec4f(t_coord.x*cropsize.x, t_coord.y*cropsize.y, cropsize.x, cropsize.y));
}
void PhatTexture::FlipTexture(bool x, bool y) {
    TexFlip.set((int)x, (int)y);
}
void PhatTexture::AnimateTexture(int startframe, int endframe, int delay, vec2f cropsize) {
    _animationStartFrame = startframe;
    _animationEndFrame = endframe;
    _animationDelay = delay;
    _animationCropsize.copy(cropsize);
}
// This function below will be called in PhatPlane's Render only
void PhatTexture::PhatPlane_CropForAnimation() {
    if(_animationCurrenFrame > 0) {
        CropTexture(_animationCurrenFrame, _animationCropsize);
    }
}