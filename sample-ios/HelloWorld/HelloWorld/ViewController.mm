//
//  ViewController.m
//  HelloWorld
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//

#import "ViewController.h"

#include <phat/PhatContext.h>
#include <phat/PhatPlane.h>
#include <phat/PhatTexture.h>

PhatContext     *phat       = NULL;
PhatPlane       *plane      = NULL;
PhatTexture     *texture    = NULL;

@interface ViewController () {

}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation ViewController

- (void)dealloc
{
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [_context release];
    [_effect release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1] autorelease];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    NSLog(@"ScreenSize: %dx%d", (int)self.view.frame.size.width, (int)self.view.frame.size.height);
    phat = new PhatContext();
    
    plane = new PhatPlane(vec2f(100.0f, 100.0f));
    plane->SetPivotType(TOP_LEFT);
    
    texture = new PhatTexture("Assets/", "test.png");
    texture->AnimateTexture(4, 1, 10, vec2f(100.0f));
    
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    self.effect = nil;
    
    delete texture;     texture = NULL;
    delete plane;       plane   = NULL;
    
    delete phat;        phat    = NULL;
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    texture->Update();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    phat->BeginRender();
    phat->SetDimension(2);
    
    
    plane->Position.set(phat->ScreenSize.x/2.0f, phat->ScreenSize.y/2.0f);
    //texture->CropTexture(1, vec2f(100.0f, 100.0f));
    //texture->FlipTexture(false, false);
    plane->SetPivotType(BOTTOM_RIGHT);
    plane->Render(phat, texture);
    
    texture->CropTexture(rec4f(100.0f, 0.0f, 100.0f, 100.0f));
    plane->SetPivotType(BOTTOM_LEFT);
    plane->Render(phat, texture);
    /*
    texture->CropTexture(rec4f(0.0f, 100.0f, 100.0f, 100.0f));
    plane->SetPivotType(TOP_RIGHT);
    plane->Render(phat, texture);
    
    texture->CropTexture(rec4f(100.0f, 100.0f, 100.0f, 100.0f));
    //texture->FlipTexture(true, true);
    plane->SetPivotType(TOP_LEFT);
    plane->Render(phat, texture);
    */
    phat->EndRender();
}

@end
