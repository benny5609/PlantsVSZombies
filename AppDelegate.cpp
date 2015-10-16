#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "menuLayer.h"
#include "WelcomeLayer.h"

#include "GameLayer.h"


USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    //自适应屏幕大小宽度
    glview->setDesignResolutionSize(480, 320, ResolutionPolicy::EXACT_FIT);
    
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
  }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    
    auto scene = wait(<#int *#>)::scene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
