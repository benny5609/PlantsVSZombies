//
//  Zoombie.h
//  hello
//
//  Created by student on 15/8/13.
//
//

#ifndef __hello__Zoombie__
#define __hello__Zoombie__
USING_NS_CC;
#include <stdio.h>
#define LIFEVALUE 10;

typedef enum
{
    Zombie = 0,
    BucketheadZombie,
    ConeheadZombie,
    FlagZombie,
    PoleVaultingZombie,
}ZoombieType;

class Zoombie:public Sprite
{
public:
    
    ZoombieType zoombieType;
    double blood; //血量
    char plistStr[50];//加载的纹理图册的名字
    char attackStr[50]; //不同类型攻击纹理图册  死亡僵尸的动画
    char dieStr[50]; //加载死亡的纹理图集名字
    Zoombie(ZoombieType zoombieType); //构造僵尸函数
    void startMove();//僵尸开始移动
    void remove();  //将僵尸移除掉
    void runDieAction();
    void runAttackAction(); //僵尸的攻击行为
    void continueMove();
    
    void loadSpriteFrameFiles();   //预先加载纹理图集
    void runZombieAction(char* plist); //僵尸正常行走的行为
    bool isAttack;   //攻击
    
};




#endif /* defined(__hello__Zoombie__) */
