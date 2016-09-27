//
//  AdsIntergrate.hpp
//  Skeleton
//
//  Created by Pham Thanh on 4/13/16.
//
//

#ifndef AdsIntergrate_hpp
#define AdsIntergrate_hpp

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define SDKBOX_ENABLED 1
#else

#endif

#ifdef SDKBOX_ENABLED
#include "Sdkbox/Sdkbox.h"
#include "PluginAdMob/PluginAdMob.h"
#include "PluginIAP/PluginIAP.h"
#endif
class Ads {
public:
    static void init();
    static void preload();
    
    static void preloadAdmob();
    static void showAdmob(std::string unit);
    static void hideAdmob(std::string unit);
};

#endif /* AdsIntergrate_hpp */
