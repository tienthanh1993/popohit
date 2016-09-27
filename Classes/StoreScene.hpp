//
//  StoreScene.hpp
//  Skeleton
//
//  Created by Pham Thanh on 4/13/16.
//
//

#ifndef StoreScene_hpp
#define StoreScene_hpp
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define SDKBOX_ENABLED 1
#else

#endif

#ifdef SDKBOX_ENABLED
#include "PluginIAP/PluginIAP.h"
#endif
class StoreScene : public cocos2d::Layer
#ifdef SDKBOX_ENABLED
, public sdkbox::IAPListener
#endif
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void BackCallback(Ref* pSender, Widget::TouchEventType type);
    void BuyItemCallback(Ref* pSender, Widget::TouchEventType type);
    
    CREATE_FUNC(StoreScene);
    #ifdef SDKBOX_ENABLED
private:
    virtual void onInitialized(bool ok) override;
    virtual void onSuccess(sdkbox::Product const& p) override;
    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
    virtual void onCanceled(sdkbox::Product const& p) override;
    virtual void onRestored(sdkbox::Product const& p) override;
    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
    virtual void onProductRequestFailure(const std::string &msg) override;
    void onRestoreComplete(bool ok, const std::string &msg);
    #endif
};

#endif /* StoreScene_hpp */
