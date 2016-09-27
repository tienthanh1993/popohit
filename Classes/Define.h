//
//  Define.h
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#ifndef __GAME_DEFINE_H__
#define __GAME_DEFINE_H__
#define saveBoolXML UserDefault::getInstance()->setBoolForKey
#define readBoolXML UserDefault::getInstance()->getBoolForKey
#define saveIntXML UserDefault::getInstance()->setIntegerForKey
#define readIntXML UserDefault::getInstance()->getIntegerForKey

#define MoveZorder 1000
#define StaticZorder 10
// 1 is chapter game
// 2 is mini game, one scene game
// 3 is online game or sth
#define GAME_TYPE 2
#define ISNEWS "isnew"
#define MUSIC "sound"
#define ADS "ads"
#define NOADS "noads"
#define GM "GM"
#include <SimpleAudioEngine.h>
#define preloadEffect SimpleAudioEngine::getInstance()->preloadEffect
#define playEffect SimpleAudioEngine::getInstance()->playEffect
#define preloadBackgroundMusic SimpleAudioEngine::getInstance()->preloadBackgroundMusic
#define playBackgroundMusic SimpleAudioEngine::getInstance()->playBackgroundMusic
#define unloadEffect SimpleAudioEngine::getInstance()->unloadEffect

#endif