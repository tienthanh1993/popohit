//
//  TopScene.hpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#ifndef TopScene_hpp
#define TopScene_hpp
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class TopScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void BackTouchCallback(Ref* pSender);
    void GameUpdate(float dt);
    
     void BackCallback(Ref* pSender, Widget::TouchEventType type);
    CREATE_FUNC(TopScene);
};

#endif /* TopScene_hpp */
