//
//  Bullet.cpp
//  hello
//
//  Created by student on 15/8/10.
//
//

#include "Bullet.h"
//#include "Data.h"


Bullet::Bullet(Plants *aplants,Point p,Layer *layer)
{
    plants = new Plants(aplants->plantsName);
    switch (aplants->plantsName) {
        case Sunflower:
        {
            this->creatSunflowerBullet(p,layer);
            break;
        }
        case SmallPea:
        case MiddlePea:
        case ThreeBulletPea:
        {
            this->creatPeaBullet(p, layer);
            break;
        }
        default:
            break;
    }
}

void Bullet::creatSunflowerBullet(Point p, Layer* layer)
{
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Sun_default.plist");
    this->initWithSpriteFrameName("Sun－1（被拖移）.tiff");
    this->setScale(0.5);
    
    char temp[50];
    Vector<SpriteFrame*>vec;
    for(int i=1;i<22;i++)
    {
        sprintf(temp, "Sun－%i（被拖移）.tiff",i);
        auto frame = cache->getSpriteFrameByName(temp);
        vec.pushBack(frame);
     }
    auto animation = Animation::createWithSpriteFrames(vec,0.1);
    auto animate = Animate::create(animation);
    this->runAction(RepeatForever::create(animate));
    auto m = MenuItemSprite::create(this, this,CC_CALLBACK_1(Bullet::collectSunshine, this));
    m->setTag(31);
    auto menu = Menu::create(m,NULL);//将精灵添加到menu中，menu是他的father
    menu->setPosition(p);
    menu->setEnabled(true);
    layer->addChild(menu,5);
    auto jumpTo = JumpTo::create(0.7, Vec2(menu->getPosition().x-20, menu->getPosition().y-5), 30, 1);
    menu->runAction(jumpTo);
    menu->setTag(41);
}

void Bullet::collectSunshine(Ref* sender)
{
    auto size = Director::getInstance()->getVisibleSize();
    auto m = (MenuItemSprite*)sender;
    printf("\nsender.tag = %i",m->getTag());
    auto moveTo = MoveTo::create(1.0, Vec2(size.width/2-210,size.height/2+170));
    extern int SunNumber;
    SunNumber = SunNumber+50;
    auto call = CallFuncN::create(CC_CALLBACK_1(Bullet::moveSunshine, this));
    auto seq = Sequence::create(moveTo,call, NULL);
    m->getParent()->runAction(seq);//在menu上运行这个action
}

void Bullet::moveSunshine(Node* sender)
{
    sender->removeFromParent();
}

//豌豆的子弹
void Bullet::creatPeaBullet(Point p, Layer* layer)
{
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("PeashooterBullet_default.plist");
    this->initWithSpriteFrameName("PeashooterBullet－1（被拖移）.tiff");
    this->setPosition(Vec2(p.x+10,p.y+10));
    this->setScale(0.5);
    layer->addChild(this);
    float distance = 500-this->getPosition().x;
    float time = distance/BulletSpeedRatio;
    //将子弹移除
    auto call = CallFuncN::create(CC_CALLBACK_1(Bullet::moveSunshine, this));
    //子弹运行到的位置
    auto moveTo = MoveTo::create(time, Vec2(400,this->getPosition().y));
    auto seq = Sequence::create(moveTo,call, NULL);
    this->runAction(seq);
}




