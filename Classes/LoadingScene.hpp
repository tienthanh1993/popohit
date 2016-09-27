//
//  LoadingScene.hpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp
#include <cocos2d.h>
USING_NS_CC;
#include "AdsIntergrate.hpp"

class LoadingScene : public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
   virtual void onEnter();
    Sprite* logoAnimate;
    Animate* animate;
    void gotoMenu(float dt);
    void AnimateCallback(Node* pSender);
    CREATE_FUNC(LoadingScene);
};

#endif /* LoadingScene_hpp */
