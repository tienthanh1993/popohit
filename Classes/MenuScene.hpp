//
//  MenuScene.hpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#ifndef MenuScene_hpp
#define MenuScene_hpp
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
#include "GameNews.h"

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    //big menu
    void StartGameCallback(Ref *pSender, Widget::TouchEventType type);
    void TopCallback(Ref *pSender, Widget::TouchEventType type);
    void ExitCallback(Ref *pSender, Widget::TouchEventType type);
    void StoreCallback(Ref *pSender, Widget::TouchEventType type);
    
    // small button
    void SoundCallback(Ref *pSender, Widget::TouchEventType type);
    void HelpCallback(Ref *pSender, Widget::TouchEventType type);
    void HelpOkCallback(Ref *pSender, Widget::TouchEventType type);
    
    
    CREATE_FUNC(MenuScene);
    News* _news;
    
private:
    Layer* help;
    
 };

#endif /* MenuScene_hpp */
