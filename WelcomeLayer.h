//
//  WelcomeLayer.h
//  hello
//
//  Created by student on 15/8/4.
//
//

#ifndef __hello__WelcomeLayer__
#define __hello__WelcomeLayer__

#include <stdio.h>

USING_NS_CC;
class WelcomeLayer:public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    void menuCloseCallback(Ref* pSender);
    void replaceScene();
    CREATE_FUNC(WelcomeLayer);
};


#endif /* defined(__hello__WelcomeLayer__) */
