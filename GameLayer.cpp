//
//  GameLayer.cpp
//  hello
//
//  Created by student on 15/8/4.
//
//



#include "GameLayer.h"
#include "Data.h"
#include "Plants.h"
#include "Bullet.h"
#include "Tools.h"
#include "Zoombie.h"
#include "menuLayer.h"

Scene* GameLayer::scene()
{
    auto scene=Scene::create();
    auto layer=GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    auto size=Director::getInstance()->getVisibleSize();
    auto sp=Sprite::create("background1.jpg");
    sp->setPosition(Vec2(size.width/2+135,size.height/2));
    sp->setTag(2);
    this->addChild(sp);
    //背景设置移动   设置移动时间
    auto moveto=MoveTo::create(0, Vec2(size.width/2-133, size.height/2));
    auto func=CallFuncN::create(CC_CALLBACK_0(GameLayer::selectPlant, this));
    auto seque=Sequence::create(moveto,DelayTime::create(1),func,NULL);
    sp->runAction(seque);
    
    selectedPlantsArray=__Array::create();
    selectedPlantsArray->retain();
    carArray=__Array::create();
    carArray->retain();
    plantsArray=__Array::create();
    plantsArray->retain();
    menuArray=__Array::create();
    menuArray->retain();
    selectPlantsIndex = -1;
    bulletsArray=__Array::create();
    bulletsArray->retain();
    zombieArray=__Array::create();
    zombieArray->retain();
    
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            map[i][j] = 0;
        }
    }
    
    
    return true;
}

void GameLayer::selectPlant()
{
    //选择植物框
    auto size=Director::getInstance()->getVisibleSize();
    auto sp2 = Sprite::create("SeedChooser_Background.png");
    sp2->setPosition(Vec2(size.width/2-60, size.height/2-35));
    sp2->setScale(1);
    sp2->setTag(1);
    this->addChild(sp2);
    
    //显示选择的植物框
    auto sp3 = Sprite::create ("barMenu1.png");
    sp3->setPosition(Vec2(size.width/2-45, size.height/2+135));
    this->addChild(sp3);
    
    //阳光
    auto sp4 = Sprite::create("sun2.png");
    sp4->setPosition(Vec2(size.width/2-220,size.height/2+140));
    this->addChild(sp4,1);
    
    //显示阳光值
    auto sp5 = Sprite::create("sunNum.png");
    sp5->setPosition(Vec2(size.width/2-218,size.height/2+108));
    this->addChild(sp5,1);
    
    //显示阳光数量
    char temp[20];
    sprintf(temp, "%d",SunNumber);
    sunNumberLB = Label::createWithTTF(temp, "fonts/Marker Felt.ttf", 15);
    sunNumberLB->setPosition(Vec2(size.width/2-218,size.height/2+108));
    sunNumberLB->setColor(Color3B::GRAY);
    this->addChild(sunNumberLB,2);
 
    //设置重置,确定
    auto item1 = MenuItemImage::create("selectSure0.png","selectSure1.png");
    auto item2 = MenuItemImage::create("selectReset0.png","selectReset1.png");
    item2->setCallback(CC_CALLBACK_0(GameLayer::cancelButtonFunc, this));
    auto menu = Menu::create(item2,item1, NULL);
    menu->alignItemsHorizontallyWithPadding(5);
    menu->setPosition(Vec2(size.width/2+30, size.height/2-120));
    menu->setTag(1003);
    this->addChild(menu);
    item1->setCallback(CC_CALLBACK_0(GameLayer::sureButtonFunc, this));

    //植物选择 图片  第一排
    auto item3 = MenuItemImage::create("SunFlower.png","SunFlower.png");
    auto items3 = MenuItemImage::create("SunFlower 副本.png","SunFlower 副本.png");
    auto toggle3 = MenuItemToggle::create(item3 );
    toggle3->addSubItem(items3);
    toggle3 -> setTag(3);
    //相当于一个按钮，点击之后才会触动
    toggle3->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto item4 = MenuItemImage::create("WallNut.png","WallNut.png");
    auto items4 = MenuItemImage::create("WallNut 副本.png","WallNut 副本.png");
    auto toggle4 = MenuItemToggle::create(item4);
    toggle4->addSubItem(items4);
    toggle4 -> setTag(4);
    toggle4->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto item5 = MenuItemImage::create("Squash.png","Squash.png");
    auto items5 = MenuItemImage::create("Squash 副本.png","Squash 副本.png");
    auto toggle5 = MenuItemToggle::create(item5);
    toggle5->addSubItem(items5);
    toggle5 -> setTag(5);
    toggle5->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto item6 = MenuItemImage::create("Jalapeno.png","Jalapeno.png");
    auto items6 = MenuItemImage::create("Jalapeno 副本.png","Jalapeno 副本.png");
    auto toggle6 = MenuItemToggle::create(item6);
    toggle6->addSubItem(items6);
    toggle6 -> setTag(6);
    toggle6->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto item7 = MenuItemImage::create("LilyPad.png","LilyPad.png");
    auto items7 = MenuItemImage::create("LilyPad 副本.png","LilyPad 副本.png");
    auto toggle7 = MenuItemToggle::create(item7);
    toggle7->addSubItem(items7);
    toggle7 -> setTag(7);
    toggle7->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto menu2 = Menu::create(toggle3,toggle4,toggle5,toggle6,toggle7,NULL);
    menu2->setPosition(Vec2(size.width/2-138, size.height/2-30));
    menu2->alignItemsHorizontallyWithPadding(10);
    menu2->setScale(0.7);
    menu2->setScaleY(0.6);
    menu2->setTag(1000);
    this->addChild(menu2);

    //植物选择 图片  第二排
    auto item8 = MenuItemImage::create("PeaShooter.png", "PeaShooter.png");
    auto items8 = MenuItemImage::create("PeaShooter 副本.png", "PeaShooter 副本.png");
    auto toggle8 = MenuItemToggle::create(item8);
    toggle8->addSubItem(items8);
    toggle8 -> setTag(8);
    toggle8->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto item9 = MenuItemImage::create("TallNut.png", "TallNut.png");
    auto items9 = MenuItemImage::create("TallNut 副本.png", "TallNut 副本.png");
    auto toggle9 = MenuItemToggle::create(item9);
    toggle9->addSubItem(items9);
    toggle9 -> setTag(9);
    toggle9->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto item10 = MenuItemImage::create("Chomper.png", "Chomper.png");
    auto items10 = MenuItemImage::create("Chomper 副本.png", "Chomper 副本.png");
    auto toggle10 = MenuItemToggle::create(item10);
    toggle10->addSubItem(items10);
    toggle10 -> setTag(10);
    toggle10->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto item11 = MenuItemImage::create("CherryBomb.png", "CherryBomb.png");
    auto items11 = MenuItemImage::create("CherryBomb 副本.png", "CherryBomb 副本.png");
    auto toggle11 = MenuItemToggle::create(item11);
    toggle11->addSubItem(items11);
    toggle11 -> setTag(11);
    toggle11->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto item12 = MenuItemImage::create("Repeater.png", "Repeater.png");
    auto items12 = MenuItemImage::create("Repeater 副本.png", "Repeater 副本.png");
    auto toggle12 = MenuItemToggle::create(item12);
    toggle12->addSubItem(items12);
    toggle12 -> setTag(12);
    toggle12->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto menu3 = Menu::create(toggle8,toggle9,toggle10,toggle11,toggle12,NULL);
    menu3->setPosition(Vec2(size.width/2-138, size.height/2-105));
    menu3->alignItemsHorizontallyWithPadding(10);
    menu3->setScale(0.7);
    menu3->setScaleY(0.6);
    menu3->setTag(1001);
    this->addChild(menu3);

    //第三排植物
    auto item13 = MenuItemImage::create("Threepeater.png", "Threepeater.png");
    auto items13 = MenuItemImage::create("Threepeater 副本.png", "Threepeater 副本.png");
    auto toggle13 = MenuItemToggle::create(item13);
    toggle13->addSubItem(items13);
    toggle13 -> setTag(13);
    toggle13->setCallback(CC_CALLBACK_1(GameLayer::selectPlantFunc, this));
    
    auto menu4 = Menu::create(toggle13,NULL);
    menu4->setPosition(Vec2(size.width/2-260, size.height/2-180));
    menu4->alignItemsHorizontallyWithPadding(10);
    menu4->setScale(0.7);
    menu4->setScaleY(0.6);
    menu4->setTag(1002);
    this->addChild(menu4);
}

void GameLayer::selectPlantFunc(Ref* sender)
{
    Plants *a;
    auto toggle = (MenuItemToggle*)sender;//谁监听就代表谁，这里是把内容放到toggle中就是转化成toggle

    switch (toggle->getTag())
    {
        case 3:
        {
            a = new Plants(Sunflower);
            break;
        }
        case 4:
        {
            a = new Plants(SmallNut);
            break;
        }
        case 5:
        {
            a = new Plants(Pumpkin);
            break;
        }
        case 6:
        {
            a = new Plants(Paprika);
            break;
        }
        case 7:
        {
            a = new Plants(Lilypad);
            break;
        }
        case 8:
        {
            a = new Plants(SmallPea);
            break;
        }
        case 9:
        {
            a = new Plants(LargeNut);
            break;
        }
        case 10:
        {
            a = new Plants(CorpseFlower);
            break;
        }
        case 11:
        {
            a = new Plants(Cherry);
            break;
        }
        case 12:
        {
            a = new Plants(MiddlePea);
            break;
        }
        case 13:
        {
            a = new Plants(ThreeBulletPea);
            break;
        }
   
        default:
            break;
    }
    selectedPlantsArray->addObject(a);
    this->addPlantMenuToBar();
    toggle->setEnabled(false);
   
    if(menuArray->count() == 5)
    {
        for(int i=0;i<=2;i++)  //设置三行中的植物不可点
        {
            auto tt = (Menu*)this->getChildByTag(1000+i);
            if(tt)
            {
                tt->setEnabled(false);
            }
        }
    }
    
}

//点击植物选择
void GameLayer::addPlantMenuToBar()
{
    
    Plants *plants = (Plants *)selectedPlantsArray->getLastObject();
    //int number = (int )selectedPlantsArray->count()-1;
    
    //Plants *plants = (Plants *)selectedPlantsArray->getObjectAtIndex(number);
    switch (plants->plantsName)
    {
        case Sunflower:
        {
            char a[] = "SunFlower.png";
            char b[] = "SunFlower 副本.png";
            this->addMenu(a, b,plants->needSunShine,3,101);
            break;
        }
        case SmallPea:
        {
            char a[] = "PeaShooter.png";
            char b[] = "PeaShooter 副本.png";
            this->addMenu(a, b,plants->needSunShine,4,102);
            break;
        }
        case MiddlePea:
        {
            char a[] = "Repeater.png";
            char b[] = "Repeater 副本.png";
            this->addMenu(a, b,plants->needSunShine,5,103);
            break;
        }
        case ThreeBulletPea:
        {
            char a[] = "Threepeater.png";
            char b[] = "Threepeater 副本.png";
            this->addMenu(a, b,plants->needSunShine,6,104);
            break;
        }
        case Pumpkin:
        {
            char a[] = "Squash.png";
            char b[] = "Squash 副本.png";
            this->addMenu(a, b,plants->needSunShine,7,105);
            break;
        }
        case Paprika:
        {
            char a[] = "Jalapeno.png";
            char b[] = "Jalapeno 副本.png";
            this->addMenu(a, b,plants->needSunShine,8,106);
            break;
        }
        case Cherry:
        {
            char a[] = "CherryBomb.png";
            char b[] = "CherryBomb 副本.png";
            this->addMenu(a, b,plants->needSunShine,9,107);
            break;
        }
        case SmallNut:
        {
            char a[] = "WallNut.png";
            char b[] = "WallNut 副本.png";
            this->addMenu(a, b,plants->needSunShine,10,108);
            break;
        }
        case LargeNut:
        {
            char a[] = "TallNut.png";
            char b[] = "TallNut 副本.png";
            this->addMenu(a, b,plants->needSunShine,11,109);
            break;
        }
        case Lilypad:
        {
            char a[] = "LilyPad.png";
            char b[] = "LilyPad 副本.png";
            this->addMenu(a, b,plants->needSunShine,12,110);
            break;
        }
        case CorpseFlower:
        {
            char a[] = "Chomper.png";
            char b[] = "Chomper 副本.png";
            this->addMenu(a, b,plants->needSunShine,13,111);
            break;
        }
        default:
            break;
    }
}


//在bar上显示选择的植物 方法
void GameLayer::addMenu(char a[],char  b[],int needSunnumber,int itemTag,int menuTag)
{
    auto i = (int)selectedPlantsArray->count();
   
    auto size = Director::getInstance()->getVisibleSize();
    
    int x = size.width/2-275+i*53;
    auto item1 = MenuItemImage::create(a, a);
    auto item2 = MenuItemImage::create(b,b);
    auto toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameLayer::menuFunc, this), item1,item2, NULL);
    toggle->setTag(1004+i);
    auto menu1 = Menu::create(toggle, NULL);
    menu1->setScaleX(0.7);
    menu1->setScaleY(0.4);
    menu1->setPosition(Vec2(x, size.height/2+40));
    menu1->setTag(1010+i);
    this->addChild(menu1);
    menuArray->addObject(menu1);
    //这里是什么意思
    if(needSunnumber > SunNumber)
    {
        toggle->setSelectedIndex(1);
        menu1->setEnabled(false);
    }
    
}

//得到显示在bar上的植物tag值
void GameLayer::menuFunc(Ref* sender)
{
    auto toggle = (MenuItemToggle*)sender;
    selectPlantsIndex = toggle->getTag();
}

//移除小框中的植物
void GameLayer::cancelButtonFunc()
{
    selectedPlantsArray->removeAllObjects();
    for(int i=0;i<3;i++)
    {
        //将大框中的植物变为可选
        auto tt = (Menu*)this->getChildByTag(1000+i);
        if(tt)
        {
            for (int j=0; j<tt->getChildrenCount(); j++) {
                auto t = (MenuItemToggle *) tt->getChildren().at(j);//把menu里面的植物给取出
                t->setEnabled(true);
                t->setSelectedIndex(0);//设置toggle的值，使得图片进入可选状态
            }
            tt->setEnabled(true);   //设置选择框的植物可选
        }
        //移除bar中的植物
        for(int i=0; i<menuArray->count();i++)
        {
            auto m = (Menu*)menuArray->getObjectAtIndex(i);
            m->removeFromParent();//移除了menu中的植物；
        }
    }
    menuArray->removeAllObjects();
}

//确定按钮，移动背景
void GameLayer::sureButtonFunc()
{
   if(selectedPlantsArray->count()<5)
    { return;}
  
    auto t = (Sprite *)this->getChildByTag(1);
    t->removeFromParent();//从大背景图中移除
    log("111");
    auto m = (Menu*)this->getChildByTag(1000);
    m->removeFromParent();
    m = (Menu*)this->getChildByTag(1001);
    m->removeFromParent();
    m = (Menu*)this->getChildByTag(1002);
    m->removeFromParent();
    m = (Menu*)this->getChildByTag(1003);
    m->removeFromParent();
    this->bgGroundMoveBack();
    
}

//选完了植物之后，移动到种植物的界面
void GameLayer::bgGroundMoveBack()
{
    auto size = Director::getInstance()->getVisibleSize();
    auto t = (Sprite *)this->getChildByTag(2);
    auto moveTo = MoveTo::create(1, Vec2(size.width/2+30,size.height/2));
    auto call = CallFunc::create(CC_CALLBACK_0(GameLayer::prepareStartGame, this));
    auto seq = Sequence::create(moveTo,call, NULL);
    t->runAction(seq);
}

//增加车子，准备开始游戏
void GameLayer::prepareStartGame()
{
    auto size = Director::getInstance()->getVisibleSize();
    for(int i=0;i<5;i++)
    {
        auto car = Sprite::create("LawnMower.png");
        car->setPosition(Vec2(size.width/2-250,40+i*55));
        //car->setOrderOfArrival(9);
        this->addChild(car);
        carArray->addObject(car);
     }
    //监听事件写在此处，可以使得准备之后才可以种植物
    auto dispatcher = Director::Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnd, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //开启一些线程
    //发射子弹
    this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::updataBullet),2);
   // this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::updataPlants),2.0);
    //僵尸出现方法
    this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::zombieAppear), 4.0);
    this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::cheekupHit), 0.01);
    this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::zombieDisappear),1.0);
    //更新阳光值方法
    this->schedule(CC_SCHEDULE_SELECTOR(GameLayer::updataSunShine), 3.0);
    
}


//触摸事件
void GameLayer::onEnter()
{
    CCLayer::onEnter();
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
    return true;
    log("began");
}

void GameLayer::onTouchEnd(Touch *touch, Event *unused_ecent)
{
    auto p = touch->getLocation();
    p = Tools::getCenterPoint(p);
    int r,c;
    this->getRC(r,c,p);
    
    if(map[r][c] == 1)
    {
        return;
    }
    
    if(selectPlantsIndex!=-1)
        switch (selectPlantsIndex) {
            case 1005:
            {
                auto a = (Plants *) selectedPlantsArray->getObjectAtIndex(0);
//                if(SunNumber < a->needSunShine);
//                return;
                a->needWait = true;
                SunNumber = SunNumber -a->needSunShine;
                Plants *b = new Plants(a->plantsName);
               plantsArray->addObject(b);
                if(b->plantsName  == Pumpkin)
                    b->setAnchorPoint(Vec2(0.5,0.2));
                b->setPosition(p);
                this->addChild(b);
                map[r][c]=1;
                break;
            }
            case 1006:
            {
                auto a = (Plants *)selectedPlantsArray->getObjectAtIndex(1);
//                if(SunNumber < a->needSunShine);
//                return;
                a->needWait = true;
                SunNumber = SunNumber -a->needSunShine;
                Plants *b = new Plants(a->plantsName);
                plantsArray->addObject(b);
                if(b->plantsName  == Pumpkin)
                    b->setAnchorPoint(Vec2(0.5,0.2));
                b->setPosition(p);
                this->addChild(b);
                map[r][c]=1;
                
                break;
            }
            case 1007:
            {
                auto a = (Plants *)selectedPlantsArray->getObjectAtIndex(2);
//                if(SunNumber < a->needSunShine);
//                return;
                a->needWait = true;
                SunNumber = SunNumber -a->needSunShine;
                Plants *b = new Plants(a->plantsName);
                plantsArray->addObject(b);
                if(b->plantsName  == Pumpkin)
                    b->setAnchorPoint(Vec2(0.5,0.2));
                b->setPosition(p);
                this->addChild(b);
                map[r][c]=1;
                
                break;
            }
            case 1008:
            {
                auto a = (Plants *)selectedPlantsArray->getObjectAtIndex(3);
//                if(SunNumber < a->needSunShine);
//                return;
                a->needWait = true;
                SunNumber = SunNumber -a->needSunShine;
                Plants *b = new Plants(a->plantsName);
                if(b->plantsName  == Pumpkin)
                    b->setAnchorPoint(Vec2(0.5,0.2));
                plantsArray->addObject(b);
                b->setPosition(p);
                this->addChild(b);
                map[r][c]=1;
                
                break;
            }

            case 1009:
            {
                auto a = (Plants *)selectedPlantsArray->getObjectAtIndex(4);
//                if(SunNumber < a->needSunShine);
//                return;
                a->needWait = true;
                SunNumber = SunNumber -a->needSunShine;
                Plants *b = new Plants(a->plantsName);
                if(b->plantsName  == Pumpkin)
                    b->setAnchorPoint(Vec2(0.5,0.2));
                plantsArray->addObject(b);
                b->setPosition(p);
                this->addChild(b);
                map[r][c]=1;
                
                break;
            }
                
                default:
                break;
               }
    selectPlantsIndex = -1;
    char a[50];
    sprintf(a, "%d",SunNumber);
    sunNumberLB->setString(a);
    this->changedMenuStatus();
}

void GameLayer::getRC(int &x,int &y,Point p)
{
    if(p.y==40)
        y=0;
    else if (p.y==95)
        y=1;
    else if (p.y==150)
        y=2;
    else if (p.y==205)
        y=3;
    else if (p.y==260)
        y=4;
    
    if(p.x==50)
        x=0;
    else if(p.x==100)
        x=1;
    else if (p.x==140)
        x=2;
    else if (p.x==185)
        x=3;
    else if (p.x==228)
        x=4;
    else if (p.x==270)
        x=5;
    else if (p.x==310)
        x=6;
    else if (p.x==350)
        x=7;
    else if (p.x==400)
        x=8;
}

void GameLayer::updataSunShine(float)
{
    for(int i = 0;i<plantsArray->count();i++)
    {
        Plants *plant = (Plants*) plantsArray->getObjectAtIndex(i);
        if(plant->plantsName == Sunflower)
        {
            plant->tempCreateSunInterval--;//间隔
            if(plant->tempCreateSunInterval == 0)
            {
                new Bullet(plant,plant->getPosition(),this);
                plant->tempCreateSunInterval = plant->createSunInterval;
                char tmp[50];
                sprintf(tmp, "%d",SunNumber);
                sunNumberLB->setString(tmp);
            }
            
        }
    }
    this->changedMenuStatus();
}

//改变菜单中5样植物的状态
void GameLayer::changedMenuStatus()
{
    for(int i=1;i<=4;i++)
    {
        Plants *p = (Plants *)selectedPlantsArray->getObjectAtIndex(i);
        auto m = (Menu*)this->getChildByTag(1010+i);
        auto t = (MenuItemToggle*)m->getChildByTag(1004+i);
        if(!(p->needWait)&&SunNumber >= p->needSunShine) //满足条件可以使用
        {
            m->setEnabled(true);
            
            t->setSelectedIndex(0);//设置toggle中的第一个
        }else
        {
            m->setEnabled(false);
            t->setSelectedIndex(1);
        }
    }
}


//豌豆发射子弹
void GameLayer::updataBullet(float)
{
    for(int i=0;i<plantsArray->count();i++)
    {
        Plants* a = (Plants *)plantsArray->getObjectAtIndex(i);
        if(a->plantsName == SmallPea)
        {
            Bullet *bb = new Bullet(a,a->getPosition(),this);
            bulletsArray->addObject(bb);
        }
        else if(a->plantsName == MiddlePea)
        {
            Bullet *bb = new Bullet(a,a->getPosition(),this);
            bulletsArray->addObject(bb);
        }
        else if(a->plantsName == ThreeBulletPea)
        {
            Bullet *dd1 = new Bullet(a,Vec2(a->getPosition().x,a->getPosition().y+8),this);
            Bullet *dd2 = new Bullet(a,Vec2(a->getPosition().x,a->getPosition().y),this);
            Bullet *dd3 = new Bullet(a,Vec2(a->getPosition().x,a->getPosition().y-8),this);
            bulletsArray->addObject(dd1);
            bulletsArray->addObject(dd2);
            bulletsArray->addObject(dd3);
        }
    }
}


//植物的技能冷却
void GameLayer::updataPlants(float)
{
    //首先将所有的植物的tempplantintercal减1 植物选择的时候的间隔
    for(int i = 0;i<selectedPlantsArray->count();i++)
    {
        Plants *a = (Plants *)selectedPlantsArray->getObjectAtIndex(i);
        if(a->needWait)  //如果正在技能冷却   植物产后生之后，必须要等待时间之后才能有下一个
        {
            a->tempPlantInterval = a->tempPlantInterval - 1;
            if(a->tempPlantInterval == 0)  //已经冷却好了
            {    a->needWait=false;
            a->tempPlantInterval = a->plantInterval;
            if(SunNumber >= a->needSunShine)  //阳光值够的话就可以点击植物进行种植
            {
                auto m = (Menu*)this->getChildByTag(1010+i);
                m->setEnabled(true);
                auto c = (MenuItemToggle *)m->getChildByTag(1004+i);
                c->setSelectedIndex(0);
            }
            }
        }
    
    }
}


//僵尸开始出现
void GameLayer::zombieAppear(float)
{
    int r = rand()%5;
    Zoombie* currentZombie;
    switch (r) {
        case 0:
            currentZombie = new Zoombie(Zombie);
            zombieArray->addObject(currentZombie);
            currentZombie->setPosition(Vec2(450,40+arc4random_uniform(5)*55));
            this->addChild(currentZombie);
            currentZombie->startMove();
            break;
         case 1:
            currentZombie = new Zoombie(BucketheadZombie);
            zombieArray->addObject(currentZombie);
            currentZombie->setPosition(Vec2(450,40+arc4random_uniform(5)*55));
            this->addChild(currentZombie);
            currentZombie->startMove();
            break;
         case 2:
            currentZombie = new Zoombie(ConeheadZombie);
            zombieArray->addObject(currentZombie);
            currentZombie->setPosition(Vec2(450,40+arc4random_uniform(5)*55));
            this->addChild(currentZombie);
            currentZombie->startMove();
            break;
          case 3:
            currentZombie = new Zoombie(FlagZombie);
            zombieArray->addObject(currentZombie);
            currentZombie->setPosition(Vec2(450,40+arc4random_uniform(5)*55));
            this->addChild(currentZombie);
            currentZombie->startMove();
            break;
          case 4:
            currentZombie = new Zoombie(PoleVaultingZombie);
            zombieArray->addObject(currentZombie);
            currentZombie->setPosition(Vec2(450,40+arc4random_uniform(5)*55));
            this->addChild(currentZombie);
            currentZombie->startMove();
            break;
        
            
        default:
            break;
    }

}

void GameLayer::cheekupHit(float)
{
    char tmp[50];
    sprintf(tmp, "%i",SunNumber);
    sunNumberLB->setString(tmp);
    
    auto tempArray1 = __Array::create();  //消失的子弹
    auto tempArray2 = __Array::create();  //消失的僵尸
    tempArray1->retain();
    tempArray2->retain();
    
    //子弹与僵尸碰撞检测（移除子弹和移除死亡的僵尸）
    for (int i=0; i<bulletsArray->count(); i++) {
        Bullet *b = (Bullet *)bulletsArray->getObjectAtIndex(i);
        
        for(int j=0; j<zombieArray->count();j++)
        {
            Zoombie *z = (Zoombie *)zombieArray->getObjectAtIndex(j);
            if(Tools::iscollision(b,z))
            {
                b->removeFromParent();
                tempArray1->addObject(b); //碰撞后将子弹移除
                z->blood = z->blood-1;
                if(z->blood <= 0)
                {
                    z->runDieAction();
                    tempArray2->addObject(z);
                }
            }
        }
    }
    for (int i=0; i<tempArray1->count(); i++) {
        Bullet *b = (Bullet *)tempArray1->getObjectAtIndex(i);
        bulletsArray->removeObject(b);
    }
    for (int i=0; i<tempArray2->count(); i++) {
        Zoombie *z = (Zoombie *)tempArray2->getObjectAtIndex(i);
        zombieArray->removeObject(z);
    }
  
    //僵尸与植物碰撞检测（僵尸和植物都需要移除）    //显示各种植物的动作
    tempArray1->removeAllObjects();
    for (int i=0; i<plantsArray->count(); i++) {
        tempArray2->removeAllObjects();
        Plants* p = (Plants*)plantsArray->getObjectAtIndex(i);
        
        if(p->plantsName == Cherry)   //樱桃
        {
            auto pp = p->getPosition();
            int r,c;
            this->getRC(r, c, pp);
            map[r][c] = 0;
            tempArray1->addObject(p);
            for(int j=0;j<zombieArray->count();j++)
            {
                Zoombie* z = (Zoombie *)zombieArray->getObjectAtIndex(j);
                if(Tools::iscollision(p, z))
                {
                  
                    auto func = CallFunc::create(CC_CALLBACK_0(Zoombie::runDieAction, z));
                   auto seq = Sequence::create(DelayTime::create(2),func,NULL);
                    z->runAction(seq);
                    tempArray2->addObject(z);
                    
                }
            }
            for (int j = 0; j<tempArray2->count(); j++) {
                zombieArray->removeObject(tempArray2->getObjectAtIndex(j));
                
            }
            continue;
        }
        
        if (p->plantsName == Paprika)   //辣椒
        {
            auto pp = p->getPosition();
            int r,c;
            this->getRC(r, c, pp);
            map[r][c] = 0; //判断是否能种植物，0为能种
            
            tempArray1->addObject(p);
            for(int j=0;j<zombieArray->count();j++)
            {
                Zoombie *z = (Zoombie *)zombieArray->getObjectAtIndex(j);

                if(p->getPosition().y == z->getPosition().y)
                {
                    auto func = CallFunc::create(CC_CALLBACK_0(Zoombie::runDieAction, z));
                    Sequence *seq = Sequence::create(DelayTime::create(2),func,NULL);
                    z->runAction(seq);
                    tempArray2->addObject(z);
                }
                
            }
            for (int j=0; j<tempArray2->count(); j++) {
                zombieArray->removeObject(tempArray2->getObjectAtIndex(j));
            }
            continue;
        }
        else if (p->plantsName == Pumpkin)  //南瓜
        {
            auto pp = p->getPosition();
            int r,c;
            this->getRC(r, c, pp);
            map[r][c] = 0;
            for(int j=0;j<zombieArray->count();j++)
            {
                Zoombie *z = (Zoombie *)zombieArray->getObjectAtIndex(j);
                if (Tools::iscollision(p, z)) {
                    p->pumpkinAction(p, z->getPosition());
                   auto func = CallFunc::create(CC_CALLBACK_0(Zoombie::runDieAction, z));
                    auto seq = Sequence::create(DelayTime::create(0.5),func, NULL);
                    z->runAction(seq);
                    tempArray1->addObject(p);
                    tempArray2->addObject(z);
                    break;
                }
            }
            for (int j=0; j<tempArray2->count(); j++) {
                zombieArray->removeObject(tempArray2->getObjectAtIndex(j));
                
            }
            continue;
        }
        
        else if (p->plantsName == CorpseFlower)//可以多次使用   食人花
        {
            for (int j = 0;j< zombieArray->count(); j++) {
                Zoombie *z = (Zoombie*) zombieArray->getObjectAtIndex(j);
                if(Tools::iscollision(p, z)&&p->canAttack)
                {
                    p->corpseFlowerAction();
                  auto func = CallFunc::create(CC_CALLBACK_0(Zoombie::runDieAction, z));
                    auto seq = Sequence::create(DelayTime::create(1),func, NULL);
                    z->runAction(seq);
                    zombieArray->removeObject(z);
                    break;
                }
            }
        }
        
        for (int j = 0; j<zombieArray->count(); j++)
        {
            Zoombie *z = (Zoombie *)zombieArray->getObjectAtIndex(j);
            if(Tools::iscollision(p, z))
            {
                if(!z->isAttack)
                {
                    z->runAttackAction();
                    z->isAttack = true;
                }
             
            p->lifeForce = p->lifeForce - 0.1;
            if(p->lifeForce <= 0)
            {
                auto pp = p->getPosition();
                int r,c;
                this->getRC(r, c, pp);
                map[r][c] = 0;
                p->removeFromParent();
                for (int k = 0; k<zombieArray->count(); k++)
                {
                    Zoombie *zz = (Zoombie *)zombieArray->getObjectAtIndex(k);
                    if(Tools::iscollision(p, zz))
                    {
                        zz-> continueMove();
                        zz->startMove();
                        zz->isAttack = false;
                    }
                }
                tempArray1->addObject(p);
                break;
            }
        }
    }
   
   }
    for (int i = 0; i<tempArray1->count(); i++) {
        plantsArray->removeObject(tempArray1->getObjectAtIndex(i));
    }

    //僵尸和小车的碰撞检测
    
    tempArray1->removeAllObjects();
    tempArray2->removeAllObjects();
    
    for (int i = 0; i<carArray->count(); i++)
    {
        auto car = (Sprite*)carArray->getObjectAtIndex(i);
        for (int j = 0; j<zombieArray->count(); j++)
        {
            Zoombie* z = (Zoombie*)zombieArray->getObjectAtIndex(j);
        
        if (Tools::iscollision(car, z))
        {
           auto moveTo = MoveTo::create(1, Vec2(500,car->getPosition().y));
            auto funcND = CallFuncN::create(CC_CALLBACK_1(GameLayer::removeCar, this));
            auto seq = Sequence::create(moveTo,funcND, NULL);
            car->runAction(seq);
            tempArray2->addObject(car);
             for (int k = 0; k<zombieArray->count(); k++) {
                Zoombie *zz = (Zoombie *)zombieArray->getObjectAtIndex(k);
                 //此处坐标有问题
                if(zz->getPosition().y == car->getPosition().y )
                {
                    zz->runDieAction();
                    tempArray1->addObject(zz);
                }
            }

            break;
         }
       }
    }
    for (int i=0; i<tempArray1->count(); i++) {
        zombieArray->removeObject(tempArray1->getObjectAtIndex(i));
    }
    for (int i=0; i<tempArray2->count(); i++) {
        auto car = (Sprite*)tempArray2->getObjectAtIndex(i);
        carArray->removeObject(car);
    }
    tempArray1->release();
    tempArray2->release();


    }



void GameLayer::removeCar(Node* car)
{
    car->removeFromParent();
}

void GameLayer::zombieDisappear(float)
{
    for (int i = 0; i<zombieArray->count(); i++) {
        Zoombie* everyZombie=(Zoombie*)zombieArray->getObjectAtIndex(i);
        if (everyZombie->getPosition().x<-5) {
            zombieArray->removeObjectAtIndex(i);
            everyZombie->removeFromParentAndCleanup(true);
            //游戏失败
            this->stopAllActions();
            //切换布景
            Director::getInstance()->replaceScene(menuLayer::createScene());
        }
    }
    
}



