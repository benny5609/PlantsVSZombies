//
//  Plants.h
//  hello
//
//  Created by student on 15/8/6.
//
//

#ifndef __hello__Plants__
#define __hello__Plants__

#include <stdio.h>

USING_NS_CC;

typedef enum
{
    Sunflower = 0, //向日葵
    SmallPea, //小豌豆
    MiddlePea,  //中等豌豆
    ThreeBulletPea,  //三发豌豆
    Pumpkin,//南瓜
    Paprika,//辣椒
    Cherry,//樱桃
    SmallNut,//小坚果
    LargeNut,//大坚果
    Lilypad,//荷叶
    CorpseFlower,//食人花
    
}PlantsName;

typedef enum
{
    BulletSkill=0, //子弹
    BombSkill,  //爆炸
    SwallowSkill,//吞噬
    CollapsedSkill,//压塌
    SankSkill,//下沉
    ChimaeSkill,//喷火 （辣椒）
    ObstructSkill,//阻挡 （坚果）
    GraftingSkill,//可以做嫁接的载体（荷叶）
    SunshineSkill,//能产生阳光
}SpecialSkill;

typedef enum
{
    Aquatic = 0, //水生植物
    LandMammals,  //陆地植物
}PlacePlantsType;

typedef enum
{
    Day = 0,
    Nigth,
}TimePlantsType;
class Plants :public Sprite
{
public:
    
    PlantsName plantsName;
    PlacePlantsType placeType;
    TimePlantsType timeType;
    SpecialSkill specialSkill;
    
    float attackForce; //攻击力
    float lifeForce;   //生命力
    int attackFrequency;  //攻击频率
    
    bool needWait;  //是否处在冷却的状态
    int plantInterval; //种植时间间隔（技能冷却时间）植物的技能冷却时间
    int tempPlantInterval;//间隔
    int needSunShine;   //需要的阳光值
    
    int createSunInterval;  //产生阳光的间隔
    int tempCreateSunInterval;  //temp用来使用的
    
    bool canAttack;  //能否攻击
    
    
public:
    Plants(PlantsName name);
    void createPlantsByName(char *name); //创建植物
    void runOnceAction(Vector<SpriteFrame*>vec);
    void paprikaCherryAction();  //辣椒 樱桃的动作
    void runRepeatAction(Vector<SpriteFrame*>vec);//永久动作
    void removePlants();
    
    void pumpkinAction(Sprite *pumpkin,Point p2);  //南瓜动作
    void movepumpkin(Node* pumpkin); //移除南瓜
    
    void smallNutAction1();  //小坚果动作   被吃受损的动作
    void smallNutAction2();  //受损更加严重
    void corpseFlowerAction1();//食人花动作1
   
    void corpseFlowerAction();
    Animate* createPlantAnimate(const char* name);
  };




#endif /* defined(__hello__Plants__) */
