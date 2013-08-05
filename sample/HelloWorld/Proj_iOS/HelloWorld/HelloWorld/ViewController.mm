//
//  ViewController.m
//  HelloWorld
//
//  Created by Plus Pingya on 7/31/13.
//  Copyright (c) 2013 Plus Pingya. All rights reserved.
//

#import "ViewController.h"

#include <SceneManager.h>

@interface ViewController () {
    SceneManager *sceneManager;
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
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    printf("ScreenSize: %dx%d\n", (int)self.view.frame.size.width, (int)self.view.frame.size.height);
    sceneManager = new SceneManager();
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    self.effect = nil;
    delete sceneManager; sceneManager = NULL;
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
    sceneManager->Update();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    sceneManager->Render();
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    int touchid = 0;
    for (UITouch *touch in touches) {
        CGPoint position = [touch locationInView:[UIApplication sharedApplication].keyWindow];
        sceneManager->Input->SetTouch(TOUCHBEGAN, touchid, vec2d(position.x, position.y));
        touchid++;
    }
}
- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    int touchid = 0;
    for (UITouch *touch in touches) {
        CGPoint position = [touch locationInView:[UIApplication sharedApplication].keyWindow];
        sceneManager->Input->SetTouch(TOUCHMOVED, touchid, vec2d(position.x, position.y));
        touchid++;
    }
}
- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    int touchid = 0;
    for (UITouch *touch in touches) {
        CGPoint position = [touch locationInView:[UIApplication sharedApplication].keyWindow];
        sceneManager->Input->SetTouch(TOUCHENDED, touchid, vec2d(position.x, position.y));
        touchid++;
    }
}

@end
