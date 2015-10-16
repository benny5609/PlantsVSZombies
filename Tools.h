//
//  Tools.h
//  hello
//
//  Created by student on 15/8/8.
//
//

#ifndef __hello__Tools__
#define __hello__Tools__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Tools
{
public:
    static Point getCenterPoint(Point p);
    static bool iscollision(Sprite * sprite1,Sprite* sprite2);
    
};



#endif /* defined(__hello__Tools__) */
