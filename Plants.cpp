//
//  Plants.cpp
//  hello
//
//  Created by student on 15/8/6.
//
//

#include "Plants.h"


Plants::Plants(PlantsName name)
{
    plantsName = name;
    needWait = false;
    canAttack = true;
    switch (name)
    {
        case Sunflower:
        {  placeType = LandMammals;
            timeType = Day;
            specialSkill = SunshineSkill;
            lifeForce = 10;
            plantInterval = 5;
            tempPlantInterval = 5;
            needSunShine = 50;
            
            createSunInterval = 5;
            tempCreateSunInterval = 5;
            char t[] = "SunFlower";
            this->createPlantsByName(t);
            break;   }
    
        case SmallPea:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = BulletSkill;
            lifeForce = 10;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 100;
            char t[] = "Peashooter";
            this->createPlantsByName(t);
            break;
        }
          
        case MiddlePea:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = BulletSkill;
            lifeForce = 10;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 200;
            char t[] = "Repeater";
            this->createPlantsByName(t);
            break;
        }
            
        case ThreeBulletPea:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = BulletSkill;
            lifeForce = 10;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 325;
            char t[] = "Threepeater";
            this->createPlantsByName(t);
            break;
        }
            
        case Pumpkin:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = CollapsedSkill;
            lifeForce = 10;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 50;
            char t[] = "Squash";
            this->createPlantsByName(t);
            break;
        }
            
        case Paprika:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = ChimaeSkill ;
            lifeForce = 10;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 125;
            char t[] = "Jalapeno";
            this->createPlantsByName(t);
            break;
        }
            
        case Cherry:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = BombSkill;
            lifeForce = 10;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 150;
            char t[] = "CherryBomb";
            this->createPlantsByName(t);
            break;
        }
            
        case SmallNut:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = ObstructSkill;
            lifeForce = 15;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 50;
            char t[] = "WallNut";
            this->createPlantsByName(t);
            break;
        }
            
        case LargeNut:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = ObstructSkill;
            lifeForce = 20;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 125;
            char t[] = "TallNut";
            this->createPlantsByName(t);
            break;
        }
            
        case Lilypad:
        {
            placeType = LandMammals;
            timeType = Day;
            specialSkill = GraftingSkill;
            lifeForce = 10;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 25;
            char t[] = "LilyPad";
            this->createPlantsByName(t);
            break;
        }
            
        case CorpseFlower:
        {
            placeType = LandMammals;
            timeType = Day;
            lifeForce = 5;
            specialSkill = SwallowSkill;
            plantInterval = 5;
            tempPlantInterval =5;
            needSunShine = 150;
            char t[] = "Chomper";
            this->createPlantsByName(t);
            break;
        }
     
        default:
            break;
      
    }
    this->setScale(0.5);
}

void Plants::createPlantsByName(char *name)
{
    
    char temp[50];
    auto cache = SpriteFrameCache::getInstance();//得到很多精灵
    sprintf(temp, "%s_default.plist", name);
    cache->addSpriteFramesWithFile(temp);
    
    
    auto dic = __Dictionary::createWithContentsOfFile(temp);
    auto dic2 = (__Dictionary*)dic->objectForKey("frames");
    int num = (int)dic2->allKeys()->count();
    
    sprintf(temp, "%s－2（被拖移）.tiff",name);
    this->initWithSpriteFrameName(temp);
    //使用新方法，容器存储
    Vector<SpriteFrame*>vec;
    for (int i = 1; i<num; i++)
    {
        sprintf(temp, "%s－%d（被拖移）.tiff",name,i);
        auto frame = cache->getSpriteFrameByName(temp);
        vec.pushBack(frame);
    }
    
    
    if(strcmp(name, "jalapeno") == 0 || strcmp(name, "CherryBomb") == 0)
    {
        this->runOnceAction(vec);
        return;
    }
    this->runRepeatAction(vec);
}

//跑3次动作
void Plants::runOnceAction(Vector<SpriteFrame*>vec)
{
    auto plistAnimation = Animation::createWithSpriteFrames(vec,0.15f);
    auto plistAnimate = Animate::create(plistAnimation);
    auto call = CallFunc::create(CC_CALLBACK_0(Plants::paprikaCherryAction, this));
    auto seq = Sequence::create(Repeat::create(plistAnimate,2),call,NULL);
    this->runAction(seq);
}

void Plants::runRepeatAction(Vector<SpriteFrame *> vec)
{
    auto *plistAnimation = Animation::createWithSpriteFrames(vec,0.15f);
    auto plistAnimate = Animate::create(plistAnimation);
    this->runAction(RepeatForever::create(plistAnimate));
}


void Plants::paprikaCherryAction()   //樱桃动作
{
    
    if(this->plantsName == Cherry)
    {
       
       this->initWithFile("Boom.png");
       auto call = CallFunc::create(CC_CALLBACK_0(Plants::removePlants, this));
        auto seq = Sequence::create(DelayTime::create(1),call, NULL);
        this->runAction(seq);
        
    }
    else if (this->plantsName==Paprika)
    {
    
            auto cache = SpriteFrameCache::getInstance();
            cache->addSpriteFramesWithFile("JalapenoAttack_default.plist");
            char temp[50];
            Vector<SpriteFrame*>vec;
            for(int i=1;i<=8;i++)
            {
                sprintf(temp, "JalapenoAttack－%i（被拖移）.tiff",i);
                auto frame = cache->getSpriteFrameByName(temp);
            
                vec.pushBack(frame);
            }
            auto animation = Animation::createWithSpriteFrames(vec,0.15f);
            auto animate= Animate::create(animation);
            this->setPosition(Vec2(286,this->getPosition().y));
            auto call = CallFunc::create(CC_CALLBACK_0(Plants::removePlants, this));
            auto seq = Sequence::create(animate,call, NULL);
            this->runAction(seq);
    }
    
    
}

void Plants::removePlants()
{
    this->removeFromParent();
}




//南瓜动作
void Plants::pumpkinAction(Sprite* pumpkin, Point p2)
{
    auto p1 = pumpkin->getPosition();
    auto frame = SpriteFrameCache::getInstance();
    frame->addSpriteFramesWithFile("SquashAttack_default.plist");
    Vector<SpriteFrame*>vec;
    for (int i = 1; i<=4; i++) {
        char temp[50];
        sprintf(temp,  "SquashAttack－%i（被拖移）.tiff",i);
        auto frames = frame->getSpriteFrameByName(temp);
        vec.pushBack(frames);
    }
    auto animation = Animation::createWithSpriteFrames(vec,0.3);
    auto animate = Animate::create(animation);
    pumpkin->runAction(animate);
    
    auto jumpTo = JumpTo::create(0.5, p2, 50, 1);
    auto call = CallFuncN::create(CC_CALLBACK_1(Plants::movepumpkin, this));
    auto seq = Sequence::create(jumpTo,call,NULL);
    pumpkin->runAction(seq);
}

//移除南瓜
void Plants::movepumpkin(Node* pumpkin)   //ref不能用于移除对象，应该用node
{
    pumpkin->removeFromParent();
}

//食人花
void Plants::corpseFlowerAction1()
{
    canAttack = true;
    this->stopAllActions();
    auto frame = SpriteFrameCache::getInstance();
    frame->addSpriteFramesWithFile("ChomperAttack_default.plist");
    Vector<SpriteFrame*>vec;
    for (int i = 1; i<=13; i++) {
        char temp[50];
        sprintf(temp, "Chomper－%i（被拖移）.tiff",i);
        auto frames = frame->getSpriteFrameByName(temp);
        vec.pushBack(frames);
    }
    auto animation = Animation::createWithSpriteFrames(vec,0.1);
    auto animate = Animate::create(animation);
    this->runAction(RepeatForever::create(animate));
}



//坚果
void Plants::smallNutAction1()
{
    this->stopAllActions();
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("WallNut_cracked1_default.plist");
    this->initWithSpriteFrameName("Wallnut_cracked1－11（被拖移）.tiff");
    char temp[50];
    Vector<SpriteFrame*>vec;
    for(int i = 1;i<=11;i++)
    {
        sprintf(temp, "Wallnut_cracked1－%i（被拖移）.tiff",i);
        auto frame = cache->getSpriteFrameByName(temp);
        vec.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(vec,0.5);
    auto animate = Animate::create(animation);
    this->runAction(animate);
    
}

void Plants::corpseFlowerAction()
{
    this->stopAllActions();
    auto animate1 = createPlantAnimate("ChomperAttack");
    auto animate2 = createPlantAnimate("ChomperDigest");
    auto seq = Sequence::create(animate1,DelayTime::create(1),animate2,NULL);
    this->runAction(seq);
}

Animate* Plants::createPlantAnimate(const char* name)
{
    std::string tempname = StringUtils::format("%s_default.plist",name);
    auto sc = SpriteFrameCache::getInstance();
    sc->addSpriteFramesWithFile(tempname);//添加动画帧到缓存
    
    auto dic = __Dictionary::createWithContentsOfFile(tempname.c_str());
    //获取frame个数
    auto dic2 = (__Dictionary*)dic->objectForKey("frames");
    long count = dic2->allKeys()->count();
    
    Vector<SpriteFrame*>vec;
    for (int i=1; i<=count;i++ ) {
        std::string str = StringUtils::format("%s－%d（被拖移）.tiff",name,i);
        SpriteFrame* spf = sc->getSpriteFrameByName(str);
        vec.pushBack(spf);
    }
    auto animation = Animation::createWithSpriteFrames(vec,0.2f);
    auto animate = Animate::create(animation);
    return animate;
}


