//
//  WelcomeLayer.cpp
//  hello
//
//  Created by student on 15/8/4.
//
//

#include "WelcomeLayer.h"
#include "menuLayer.h"

Scene* WelcomeLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = WelcomeLayer::create();
    scene->addChild(layer);
    return scene;
}

bool WelcomeLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    
    //背景大图
    auto sp = Sprite::create("titlescreen.png");
    sp->setPosition(Vec2(size.width/2,size.height/2));
    this->addChild(sp);
    //植物VS僵尸图
    auto sp2 = Sprite::create("pvz_logo.png");
    sp2->setPosition(Vec2(size.width/2-60,size.height-50));
    this->addChild(sp2);
    //泥土图
    auto sp3 = Sprite::create("down.png");
    sp3->setPosition(Vec2(size.width/2-60,size.height/2-150));
    this->addChild(sp3);

    //草坪滚动图
    auto progressTo=ProgressTo::create(4, 100);
    auto timer=ProgressTimer::create(Sprite::create("grass.png"));
    timer->setType(ProgressTimer::Type::BAR);
    timer->setPosition(Vec2(size.width/2-70, size.height/2-120));
    timer->setMidpoint(Vec2(0,0));//设置从最左边开始往右边滚动
    this->addChild(timer);
    timer->runAction(progressTo);
    
    //圆圈草坪旋转图
    auto sp4 = Sprite::create("scrollgrass.png");
    sp4->setPosition(Vec2(size.width/2-200,size.height/2-100));
    //sp4->setScale(2.4);
    auto rotate=RotateBy::create(0.05,3*3.14);
    auto repeat=RepeatForever::create(rotate);
    sp4->runAction(repeat);
    auto moveto=MoveTo::create(4, Vec2(size.width/2+80,size.height/2-90));
    auto func=CallFunc::create(CC_CALLBACK_0(WelcomeLayer::replaceScene, this));//跳转到第二个界面
    auto seque=Sequence::create(moveto,func, NULL);
    sp4->runAction(seque);
    this->addChild(sp4);
    
    
    return true;
}

//跳转到下一个界面
void WelcomeLayer::replaceScene()
{
    this->stopAllActions();
    TransitionFlipAngular *flip = TransitionFlipAngular::create(0.4, menuLayer::createScene(), cocos2d::TransitionScene::Orientation::UP_OVER);
    Director::getInstance()->replaceScene(flip);
}

