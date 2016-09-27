//
//  Sound.hpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#ifndef Sound_hpp
#define Sound_hpp

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Define.h"
USING_NS_CC;
using namespace CocosDenshion;
class Sound
{
public:
    static Sound* getInstance();
    void init();
    void UnInit();
    void playMenuBackground();  //≤Àµ•ΩÁ√Ê±≥æ∞
    void playGameBackground();  //”Œœ∑ΩÁ√Ê±≥æ∞
    void playAttack();  //π•ª˜
    void playBtn();    //∞¥≈•
    void playDead();    //À¿Õˆ
    bool isBackground();
    void stopBackground();
    void playGamePass();
    void playGameOver();
private:
    static Sound* _instance;
};

#endif /* Sound_hpp */
