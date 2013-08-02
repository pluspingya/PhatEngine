//
//  PhatPlane.cpp
//  PhatEngine
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//  Contact pluspingya@gmail.com
//

#include <phat/PhatPlane.h>

/////////////////////////////////////////////////////////
// Constructor - Intialize
void PhatPlane::_initialize(vec2f size) {
    Size.copy(size);
    Blendmode = NORMAL;
    UserData = NULL;
    
    TweenActive = false;
    TweenConstantly = false;
    TweenSpeed = 1.0f;
    
}
PhatPlane::PhatPlane() {
    _initialize(vec2f(100.0f, 100.0f));
}
PhatPlane::PhatPlane(vec2f size) {
    _initialize(size);
}

/////////////////////////////////////////////////////////
// Destructor - Release
void PhatPlane::_release() {
    
}
PhatPlane::~PhatPlane() {
    _release();
}

/////////////////////////////////////////////////////////
// Core functions - must be called
void PhatPlane::Update() {
    _tweening();
}
void PhatPlane::Render(PhatContext *context) {
    Render(context, NULL);
}
void PhatPlane::Render(PhatContext *context, PhatTexture *texture) {
    bool drawit = true;

    /*
     switch(pinningType) {
     default:
     case PT_TOPLEFT: {
     if((position.x*scale.x*_screenscale.x > -size.x*scale.x*_screenscale.x) && (position.x*scale.x*_screenscale.x < _visiblearea.x*scale.x*_screenscale.x)) {
     if((position.y*scale.y*_screenscale.y > -size.y*scale.y*_screenscale.y) && (position.y*scale.y*_screenscale.y < _visiblearea.y*scale.y*_screenscale.y)) {
     drawit = true;
     }
     }
     }break;
     case PT_CENTER: {
     if((position.x*scale.x*_screenscale.x > -(size.x/2.0)*scale.x*_screenscale.x) && (position.x*scale.x*_screenscale.x < _visiblearea.x+(size.x/2.0)*scale.x*_screenscale.x)) {
     if((position.y*scale.y*_screenscale.y > -(size.y/2.0)*scale.y*_screenscale.y) && (position.y*scale.y*_screenscale.y < _visiblearea.y+(size.y/2.0)*scale.y*_screenscale.y)) {
     drawit = true;
     }
     }
     }break;
     }
     */
    
    if (Colour.a <= 0.0f) {
        drawit = false;
    }
    
	if(drawit) {
		glLoadIdentity();
        
		//Translation
        glTranslatef((Position.x-Pivot.x)*context->Scaling.x, (Position.y-Pivot.y)*context->Scaling.y, 0.0);
        //glTranslatef(0.0f, 0.0f, 0.0f);
		
		//Rotation
		glRotatef(Rotation.z, 0.0, 0.0, 1.0);
        glRotatef(Rotation.y, 0.0, 1.0, 0.0);
        glRotatef(Rotation.x, 1.0, 0.0, 0.0);
        
		//Scaling
		glScalef(Scaling.x, Scaling.y, Scaling.z);
		
		//Coloring
		glColor4f(Colour.r, Colour.g, Colour.b, Colour.a);
        
        //Blending
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        switch (Blendmode) {
            default:
            case NORMAL:    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  break;
            case NORMAL_ONE:glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);        break;
            case GROW:      glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);            break;
            case GROW_TEST: glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  break;
        }
        
        if(texture) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture->TextureID);
        }else {
            glDisable(GL_TEXTURE_2D);
        }
        
		GLfloat squareVertices[] = {
            -(Size.x/2.0f)*Scaling.x, -(Size.y/2.0f)*Scaling.y,
			 (Size.x/2.0f)*Scaling.x, -(Size.y/2.0f)*Scaling.y,
            -(Size.x/2.0f)*Scaling.x,  (Size.y/2.0f)*Scaling.y,
			 (Size.x/2.0f)*Scaling.x,  (Size.y/2.0f)*Scaling.y,
		};
        
		GLfloat normals[] = {
			0.0, 0.0, 1.0,
			0.0, 0.0, 1.0,
			0.0, 0.0, 1.0,
			0.0, 0.0, 1.0
		};
        
		GLfloat texCoords[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f
        };
		if(texture) {
#ifdef ANDROID_NDK
			texCoords[0] = texture->TexCoord[0].x;	texCoords[1] = texture->TexCoord[0].y;
			texCoords[2] = texture->TexCoord[1].x;	texCoords[3] = texture->TexCoord[1].y;
			texCoords[4] = texture->TexCoord[2].x;	texCoords[5] = texture->TexCoord[2].y;
			texCoords[6] = texture->TexCoord[3].x;	texCoords[7] = texture->TexCoord[3].y;
#else
			texCoords[0] = texture->TexCoord[0].x;	texCoords[1] = texture->TexCoord[0].y;
			texCoords[2] = texture->TexCoord[1].x;	texCoords[3] = texture->TexCoord[1].y;
			texCoords[4] = texture->TexCoord[2].x;	texCoords[5] = texture->TexCoord[2].y;
			texCoords[6] = texture->TexCoord[3].x;	texCoords[7] = texture->TexCoord[3].y;
#endif
		}
        
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		
		glVertexPointer(2, GL_FLOAT, 0, squareVertices);
		glNormalPointer(GL_FLOAT, 0, normals);
        
		if(texture) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
		}
         
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
    
}

/////////////////////////////////////////////////////////
// Optional functions
void PhatPlane::Tween(vec3f start, vec3f distination, float speed, bool constantly) {
    TweenActive     = true;
    TweenConstantly = constantly;
    Position.copy(start);
    TweenDistination.copy(distination);
    TweenSpeed      = speed;
}

/////////////////////////////////////////////////////////
// Machanism
void PhatPlane::_tweening() {
    if (TweenActive) {
        float x = TweenDistination.x - Position.x;
        float y = TweenDistination.y - Position.y;
        float s = TweenSpeed;
        if (!TweenConstantly) {
            float d = sqrtf(x * x + y * y);
            s = (d/100.0)*TweenSpeed;
        }
        float angle = atan2(y, x);
        if(abs(x)>s||abs(y)>s) {
            Position.x += s * cos(angle);
            Position.y += s * sin(angle);
        }
        if (Position.x == TweenDistination.x && Position.y == TweenDistination.y) {
            TweenActive = false;
        }
        /*
        if (Rotation.z < 0.0f) {
            Rotation.z += 360.0f;
        }
        if (this.trotation < 0.0) {
            this.trotation += 360.0;
        }
        if (this.rotation > 360.0) {
            this.rotation -= 360.0;
        }
        if (this.trotation > 360.0) {
            this.trotation -= 360.0;
        }
        var z = this.trotation - this.rotation;
        var d2 = Math.sqrt(d*d + z*z);
        sp = (d2/100.0)*speed;
        angle = Math.atan2(z, d);
        this.rotation += (sp * Math.sin(angle));
        */
    }
}
