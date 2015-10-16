//
//  Zoombie.cpp
//  hello
//
//  Created by student on 15/8/13.
//
//

#include "Zoombie.h"

void Zoombie::loadSpriteFrameFiles()
{
    //加载纹理僵尸，不同的僵尸类型
    auto frame = SpriteFrameCache::getInstance();
    frame->addSpriteFramesWithFile("Zombie_default.plist");
    frame->addSpriteFramesWithFile("BucketheadZombie_default.plist");
    frame->addSpriteFramesWithFile("ConeheadZombie_default.plist");
    frame->addSpriteFramesWithFile("FlagZombie_default.plist");
    frame->addSpriteFramesWithFile("PoleVaultingZombie_default.plist");
}

Zoombie::Zoombie(ZoombieType zoombieType)
{
    this->loadSpriteFrameFiles();
    isAttack = false;
    switch (zoombieType) {
        case 0:
            this->zoombieType=zoombieType;
            this->blood=1*LIFEVALUE;
            this->initWithSpriteFrameName("Zombie1.png");
            this->setScale(0.5);
            sprintf(plistStr, "Zombie");
            break;
         case 1:
            this->zoombieType=zoombieType;
            this->initWithSpriteFrameName("BucketheadZombie1.png");
            this->setScale(0.5);
            this->blood = 1.5*LIFEVALUE;
            sprintf(plistStr, "BucketheadZombie");
            break;
         case 2:
            this->zoombieType=zoombieType;
            this->initWithSpriteFrameName("ConeheadZombie1.png");
            this->blood=LIFEVALUE;
            sprintf(plistStr, "ConeheadZombie");
            this->setScale(0.5);
            break;
         case 3:
            this->zoombieType=zoombieType;
            this->initWithSpriteFrameName("FlagZombie1.png");
            this->blood=LIFEVALUE;
            this->setScale(0.5);
            sprintf(plistStr, "FlagZombie");
            break;
        case 4:
            this->zoombieType=zoombieType;
            this->initWithSpriteFrameName("PoleVaultingZombie1.png");
            this->setScale(0.5);
            this->blood=LIFEVALUE;
            sprintf(plistStr, "PoleVaultingZombie");
            break;
            
        default:
            break;
    }
    this->setScaleY(0.3);
    runZombieAction(plistStr);
}

//根据僵尸类型 类型的不同执行不同的动作
void Zoombie::runZombieAction(char* plist)
{
    char name[50];
    sprintf(name, "%s_default.plist",plistStr);
    auto frame = SpriteFrameCache::getInstance();
    frame->addSpriteFramesWithFile(name);
    auto dic=__Dictionary::createWithContentsOfFile(name);
    dic->retain();
    auto a = (__Dictionary*)dic->objectForKey("frames");
    a->retain();
    int num = (int) a->allKeys()->count();
    
    Vector<SpriteFrame*>vec;
    
    for(int i=0; i<num; i++)
    {
        char frame[50];
        sprintf(frame, "%s%d.png",plist,i+1);
        
        auto frames = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame);
        vec.pushBack(frames);
      }
    auto animation = Animation::createWithSpriteFrames(vec,0.08f);
    auto animate = Animate::create(animation);
    auto forever = RepeatForever::create(animate);
    this->runAction(forever);
}

void Zoombie::startMove()
{
    //要根据距离计算出时间（让速度是一个恒定的值）
    float x = this->getPosition().x;
    float distance = (x+70);
    float time = distance * 0.1;
    //僵尸移动到小推车这边
    auto moveTo = MoveTo::create(time, Vec2(-70,this->getPosition().y));
    auto call = CallFunc::create(CC_CALLBACK_0(Zoombie::remove, this));
    auto seq = Sequence::create(moveTo,call, NULL);
    this->runAction(seq);
                                 
}

//移除
void Zoombie::remove()
{
    this->removeFromParent();
}

//僵尸消失
void Zoombie::runDieAction()
{
    this->blood = 0;
    int type = this->zoombieType;  //僵尸类型结构体
    this->stopAllActions();
    switch (type) {
        case 0:
        case 1:
        case 2:
            sprintf(dieStr, "ZombieDie");
            break;
        case 3:
            sprintf(dieStr, "FlagZombieLostHead");
            break;
        case 4:
            sprintf(dieStr, "PoleVaultingZombieDie");
            break;
        default:
            break;
    }
    char name[50];
    sprintf(name, "%s_default.plist",dieStr);
    auto frame = SpriteFrameCache::getInstance();
    frame->addSpriteFramesWithFile(name);
    auto dic = __Dictionary::createWithContentsOfFile(name);
    dic->retain();
    auto a = (__Dictionary*)dic->objectForKey("frames");
    a->retain();
    int num= (int)a->allKeys()->count();
    
    Vector<SpriteFrame*>vec;
    for (int i=0; i<num; i++) {
        char frame[50];
        sprintf(frame, "%s%d.png",dieStr,i+1);
        
        auto frames = SpriteFrameCache::getInstance()->getSpriteFrameByName(frame);
        vec.pushBack(frames);
    }
    auto animation = Animation::createWithSpriteFrames(vec,0.2f);
    auto animate = Animate::create(animation);
    auto call = CallFunc::create(CC_CALLBACK_0(Zoombie::remove, this));
    auto seq = Sequence::create(animate,call, NULL);
    this->runAction(seq);
}

void Zoombie::runAttackAction()
{
    int type =this->zoombieType;
    this->stopAllActions();
    switch (type) {
        case 0:
            sprintf(attackStr, "ZombieAttack");
            break;
        case 1:
            sprintf(attackStr, "BucketheadZombieAttack");
            break;
        case 2:
            sprintf(attackStr, "ConeheadZombieAttack");
            break;
        case 3:
            sprintf(attackStr, "FlagZombieAttack");
            break;
         case 4:
            sprintf(attackStr, "PoleVaultingZombieAttack");
            break;
        
        default:
            break;
    }
    this->runZombieAction(attackStr);
}

void Zoombie::continueMove()
{
    this->stopAllActions();
    switch (zoombieType) {
        case 0:
            sprintf(plistStr, "Zombie");
            break;
         case 1:
            sprintf(plistStr, "BucketheadZombie");
            break;
        case 2:
            sprintf(plistStr, "ConeheadZombie");
            break;
        case 3:
            sprintf(plistStr, "FlagZombie");
            break;
        case 4:
            sprintf(plistStr, "PoleVaultingZombie");
            break;
        default:
            break;
    }
    runZombieAction(plistStr);
}




