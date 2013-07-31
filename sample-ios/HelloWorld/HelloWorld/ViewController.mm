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

PhatContext *phat = NULL;
PhatPlane *plane = NULL;

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
    
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    self.effect = nil;
    
    delete plane; plane = NULL;
    
    delete phat; phat = NULL;
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{

}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    phat->BeginRender();
    phat->SetDimension(2);
    
    plane->Position.set(0.0f, 0.0f);
    plane->Colour.set(0.0f, 0.0f, 1.0f, 1.0f);
    plane->Render(phat);
    
    plane->Position.set(phat->ScreenSize.x/2.0f, phat->ScreenSize.y/2.0f);
    plane->Colour.set(1.0f, 1.0f, 1.0f, 1.0f);
    plane->Render(phat);
    
    phat->EndRender();
}

@end
