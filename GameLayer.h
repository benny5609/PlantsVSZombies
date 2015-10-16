//
//  GameLayer.h
//  hello
//
//  Created by student on 15/8/4.
//
//

#ifndef __hello__GameLayer__
#define __hello__GameLayer__


#include <stdio.h>



USING_NS_CC;
class GameLayer :public Layer
{
public:
    CREATE_FUNC(GameLayer);
    static Scene* scene();
    virtual bool init();
    
    
    void selectPlant();
    void selectPlantFunc(Ref* sender);
    void addPlantMenuToBar();
    void addMenu(char a[],char b[],int needSunnumber,int itemTag,int menuTag);
    void cancelButtonFunc();
    void updataSunShine(float);

    void sureButtonFunc();
    void bgGroundMoveBack();
    void prepareStartGame();
    void getRC(int &x,int &y,Point p);
    void menuFunc(Ref* sender);
    void changedMenuStatus();
    bool needWait;//是否处在冷却状态
    void updataBullet(float);
    void updataPlants(float);//方法里面要求传递一个float参数
    void zombieAppear(float);
    void cheekupHit(float);   //攻击僵尸
    void removeCar(Node * car);
    void zombieDisappear(float);
    
    virtual void onEnter();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchEnd(Touch *touch, Event *unused_ecent);
private:
    __Array* selectedPlantsArray;
    __Array* carArray;
    __Array* plantsArray;
    __Array* menuArray;
    __Array* bulletsArray;//子弹
    __Array* zombieArray;
    
    Label* sunNumberLB;
    int selectPlantsIndex;
    int map[5][9];
    
    
};




#endif /* defined(__hello__GameLayer__) */
