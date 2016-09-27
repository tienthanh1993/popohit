#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    void SavePngFromPlist(char * plistName,char *path);
    
    cocos2d::Image* SpirtetoImame(const std::string& spriteFrameName);
};

#endif // __HELLOWORLD_SCENE_H__
