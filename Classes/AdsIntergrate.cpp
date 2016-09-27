//
//  AdsIntergrate.cpp
//  Skeleton
//
//  Created by Pham Thanh on 4/13/16.
//
//

#include "AdsIntergrate.hpp"
#include "Define.h"
#include <cocos2d.h>
USING_NS_CC;

void Ads::init() {
 //   CCLOG("Ads::init");
#ifdef SDKBOX_ENABLED
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
         sdkbox::init("18655e36de141367f8ebff3fe8636e66","4bf50cac5bebea12");
         sdkbox::PluginAdMob::init();
        sdkbox::IAP::init();

    #elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        sdkbox::init("d791c46d9a37267b62e68b2254772051","d30bbf45089f6e8d");
        sdkbox::PluginAdMob::init();
        sdkbox::IAP::init();

    #endif
   
#endif
}

void Ads::showAdmob(std::string unit) {
        if ( readBoolXML(ADS)) {
            return;
        }
//        CCLOG("Ads::showAdmob");
#ifdef SDKBOX_ENABLED
    if (sdkbox::PluginAdMob::isAvailable(unit)) {
          sdkbox::PluginAdMob::show(unit);
    }
#endif
}

void Ads::hideAdmob(std::string unit) {
    if ( readBoolXML(ADS)) {
        return;
    }
//        CCLOG("Ads::hideAdmob");
#ifdef SDKBOX_ENABLED
    sdkbox::PluginAdMob::hide(unit);
#endif
}
void Ads::preload() {
 //           CCLOG("Ads::preload");
    preloadAdmob();
}
void Ads::preloadAdmob() {
//        CCLOG("Ads::preloadAdmob");
#ifdef SDKBOX_ENABLED
    sdkbox::PluginAdMob::cache("home");
    sdkbox::PluginAdMob::cache("gameover");
#endif
}