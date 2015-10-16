//
//  menuLayer.h
//  hello
//
//  Created by student on 15/8/3.
//
//

#ifndef __hello__menuLayer__
#define __hello__menuLayer__

#include <stdio.h>

USING_NS_CC;
class menuLayer: public Layer
{
public:
static Scene* createScene();
virtual bool init();
void menuCloseCallback(Ref* pSender);
CREATE_FUNC(menuLayer);//初始化，显示界面

void replaceScene();
};


#endif /* defined(__hello__menuLayer__) */
