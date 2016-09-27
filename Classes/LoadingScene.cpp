//
//  LoadingScene.cpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#include "LoadingScene.hpp"
#include "MenuScene.hpp"

cocos2d::Scene* LoadingScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = LoadingScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool LoadingScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("loadingscene/background.jpg");
    bg->setAnchorPoint(Vec2(0,0));
    this->addChild(bg);

    
    auto logoAnimate = Sprite::create();
    Vector<SpriteFrame*> animFrames(16);
    char str[100] = {0};
    for(int i = 0; i < 16; i++)
    {
        sprintf(str, "loadingscene/frame_%d.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,288,288));
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f,-1);
    auto animate = Animate::create(animation);
    logoAnimate->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(logoAnimate);
    logoAnimate->runAction(animate);

   
    Ads::preload();

    return true;
}

void LoadingScene::onEnter()
{
    Layer::onEnter();
    
    auto gg =  DelayTime::create(0.2*16);
    
    auto endMove = CallFuncN::create([&](Node *pSender) {
        this->gotoMenu(1);
    });
    
    this->runAction(Sequence::createWithTwoActions(gg, endMove));

    
}

void LoadingScene::gotoMenu(float dt)
{
       log("LoadingScene::gotoMenu");
       Director::getInstance()->replaceScene(MenuScene::createScene());
}
