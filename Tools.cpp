//
//  Tools.cpp
//  hello
//
//  Created by student on 15/8/8.
//
//

#include "Tools.h"
Point Tools::getCenterPoint(Point p)
{
    Point point;
    if(p.y<66)
        point.y = 40;
    else if(p.y<118)
        point.y = 95;
    else if(p.y<170)
        point.y = 150;
    else if(p.y<222)
        point.y=205;
    else point.y = 260;
    
    if(p.x<75)
        point.x = 50;
    else if(p.x<120)
        point.x = 100;
    else if(p.x<165)
        point.x = 140;
    else if(p.x<205)
        point.x = 185;
    else if (p.x<249)
        point.x = 228;
    else if(p.x<290)
        point.x = 270;
    else if(p.x<330)
        point.x = 310;
    else if(p.x<380)
        point.x = 350;
    else if (p.x<430)
        point.x = 400;
    return point;
    
}

//判断是否碰撞
bool Tools::iscollision(Sprite* sprite1, Sprite* sprite2)
{
    auto rect1 = sprite1->getBoundingBox();   //子弹   得到精灵的大小宽度
    auto rect2 = sprite2->getBoundingBox();  //僵尸
    float rect1MinX = rect1.getMinX();
    float rect1MaxX = rect1.getMaxX();
    float rect1MinY = rect1.getMinY();
    float rect1MaxY = rect1.getMaxY();
    
    float rect2MinX = rect2.getMinX()+50;
    float rect2MaxX = rect2.getMaxX()-50;
    float rect2MinY = rect2.getMinY();
    float rect2MaxY = rect2.getMaxY();
    
    //子弹与僵尸上下左右都没有碰撞
    if( rect1MinX>rect2MaxX || rect1MinY>rect2MaxY)
        return false;
    if(rect2MinX>rect1MaxX || rect2MinY>rect1MaxY)
        return false;
    return true;
}



