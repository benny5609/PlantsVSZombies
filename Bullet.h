//
//  Bullet.h
//  hello
//
//  Created by student on 15/8/10.
//
//

#ifndef __hello__Bullet__
#define __hello__Bullet__

#include <stdio.h>
#include "Plants.h"


USING_NS_CC;
#define BulletSpeedRatio 200; //子弹的速度
class Bullet:public Sprite
{
public:
    Plants *plants;
    
public:
    Bullet(Plants *aplants,Point p,Layer *layer);
    void creatSunflowerBullet(Point p,Layer *layer);
    void creatPeaBullet(Point p,Layer * layer);
    void collectSunshine(Ref* sender);
    void moveSunshine(Node*sender);
};


#endif /* defined(__hello__Bullet__) */
