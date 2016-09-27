//
//  StoreScene.cpp
//  Skeleton
//
//  Created by Pham Thanh on 4/13/16.
//
//

#include "StoreScene.hpp"
#include "Define.h"
#include "MenuScene.hpp"
#include "Sound.hpp"
Scene* StoreScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = StoreScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool StoreScene::init()
{
    if (!Layer::init()) {
        return false;
    }
       
    log("StoreScene::init");

    Size winSize = Director::getInstance()->getWinSize();
    auto bg = Sprite::create("background.png");
    bg->setAnchorPoint(Vec2(0,0));
    this->addChild(bg);
    
    auto removeads_btn = Button::create("storescene/no_ads.png", "storescene/no_ads_active.png");
    removeads_btn->addTouchEventListener(CC_CALLBACK_2(StoreScene::BuyItemCallback,this));
    this->addChild(removeads_btn);
    removeads_btn->setPosition(Vec2(winSize.width/2,winSize.height/2));
    if (readBoolXML(ADS)) {
        removeads_btn->setBright(false);
    }
    auto back_btn = Button::create("common/back_btn.png", "common/back_btn_active.png");
    back_btn->addTouchEventListener(CC_CALLBACK_2(StoreScene::BackCallback,this));
    this->addChild(back_btn);
    back_btn->setPosition(Vec2(winSize.width/2,winSize.height/4));
    
    
#ifdef SDKBOX_ENABLED
    sdkbox::IAP::setListener(this);
#endif
    return true;
}

void StoreScene::BackCallback(Ref* pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    Sound::getInstance()->playBtn();
    log("StoreScene::BackCallback");
    Director::getInstance()->replaceScene(MenuScene::createScene());
    
}

void StoreScene::BuyItemCallback(Ref* pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    log("StoreScene::BuyItemCallback");
    if (readBoolXML(ADS))
        return;
       Sound::getInstance()->playBtn();
#ifdef SDKBOX_ENABLED
        sdkbox::IAP::purchase("remove_ads");
#endif
    

}

#ifdef SDKBOX_ENABLED
void StoreScene::onInitialized(bool ok) {
    
}
void StoreScene::onSuccess(sdkbox::Product const& p){
        saveBoolXML(ADS,true);
}
void StoreScene::onFailure(sdkbox::Product const& p, const std::string &msg){
    
}
void StoreScene::onCanceled(sdkbox::Product const& p){
    
}
void StoreScene::onRestored(sdkbox::Product const& p){
    
}
void StoreScene::onProductRequestSuccess(std::vector<sdkbox::Product> const &products){
    
}
void StoreScene::onProductRequestFailure(const std::string &msg){
    
}
void StoreScene::onRestoreComplete(bool ok, const std::string &msg){
    
}
#endif