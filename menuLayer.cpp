//
//  menuLayer.cpp
//  hello
//
//  Created by student on 15/8/3.
//
//

#include "menuLayer.h"
#include "GameLayer.h" 

Scene* menuLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = menuLayer::create();
    scene->addChild(layer);
    return scene;
}


bool menuLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    //背景大图
    Size size = Director::getInstance()->getVisibleSize();
   
    auto sp=Sprite::create("main_background.png");
    sp->setPosition(Vec2(size.width/2,size.height/2));
    this->addChild(sp);
 
    //四种模式图
    auto item1 = MenuItemImage::create("select10.png","select11.png");
    auto item2 = MenuItemImage::create("select20.png","select21.png");
    auto item3 = MenuItemImage::create("select30.png","select31.png");
    auto item4 = MenuItemImage::create("select40.png","select41.png");
    auto menu2 = Menu::create(item1,item2,item3,item4, NULL);
    menu2->alignItemsVerticallyWithPadding(-20);
    menu2->setPosition(Vec2(size.width/2+90,size.height/2+40));
    this->addChild(menu2);
    
    //成就图
    auto menu5 = Menu::create();
    auto item5 = MenuItemImage::create("chengjiu1.png","chengjiu.png",CC_CALLBACK_1(menuLayer::menuCloseCallback, this));
    item5->setScale(0.55);
    menu5->setPosition(Vec2(size.width/2-130,size.height/2-80));
    menu5->addChild(item5);
    this->addChild(menu5);
    
    //图鉴
    auto menu6 = Menu::create();
    auto item6 = MenuItemImage::create("SelectorScreen_Almanac.png","SelectorScreen_AlmanacHighlight.png",CC_CALLBACK_1(menuLayer::menuCloseCallback, this));
    item6->setScale(0.55);
    menu6->setPosition(Vec2(size.width/2+25,size.height/2-70));
    menu6->addChild(item6);
    this->addChild(menu6);
    
    //商店
    auto menu7 = Menu::create();
    auto item7 = MenuItemImage::create("shop0.png","shop1.png",CC_CALLBACK_1(menuLayer::menuCloseCallback, this));
    item7->setScale(0.5);
    menu7->setPosition(Vec2(size.width/2+80,size.height/2-90));
    menu7->addChild(item7);
    this->addChild(menu7);
    
    //音乐
    auto itemon = MenuItemImage::create("musicbutton2.png", "musicbutton2.png");
    auto itemoff = MenuItemImage::create("musicbuttonstop 2.png", "musicbuttonstop 2.png");
    auto toggle = MenuItemToggle::create();
    toggle->addSubItem(itemon);
    toggle->addSubItem(itemoff);
    auto menumussic = Menu::create(toggle,nullptr);
    toggle->setSelectedIndex(0);
    toggle->setPosition(Vec2(size.width/2+200,size.height/2-70));
    toggle->setScale(0.5);
    menumussic->setPosition(Vec2(0,0));
    this->addChild(menumussic);

    //字体
    auto item10 = MenuItemFont::create("选项");
    item10->setColor(Color3B(0,0,255));
    item10->setScale(0.5);
    auto item11 = MenuItemFont::create("帮助");
    item11->setColor(Color3B(0,0,255));
    item11->setScale(0.5);
    auto menu10 = Menu::create(item10,item11, NULL);
    menu10->alignItemsHorizontallyWithPadding(20);
    menu10->setPosition(Vec2(size.width/2+160,size.height/2-130));
    this->addChild(menu10);
   
    

    
    
    return true;
}

//切换场景
void menuLayer::replaceScene()
{
    this->stopAllActions();
    Director::getInstance()->replaceScene(GameLayer::scene());
}

void menuLayer::menuCloseCallback(cocos2d::Ref *pSender)
{
    log("点击了！");
}