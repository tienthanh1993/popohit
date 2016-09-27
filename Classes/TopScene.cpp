//
//  TopScene.cpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#include "TopScene.hpp"
#include "Define.h"
#include "MenuScene.hpp"

Scene* TopScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = TopScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool TopScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    log("TopScene::init");
    auto winSize = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("background.png");
    bg->setAnchorPoint(Vec2(0,0));
    this->addChild(bg);
    
    auto back_btn = Button::create("common/back_btn.png", "common/back_btn1.png");
    back_btn->addTouchEventListener(CC_CALLBACK_2(TopScene::BackCallback,this));
    this->addChild(back_btn);
    back_btn->setPosition(Vec2(winSize.width/2,winSize.height/5));
    
    return true;
}

void TopScene::BackCallback(Ref* pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    log("TopScene::BackCallback");
    Director::getInstance()->replaceScene(MenuScene::createScene());
    
}
