//
//  GameScene.hpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <cocostudio/CocoStudio.h>
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

#include "GameNews.h"
#include "Mouse.hpp"


class   GameScene : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    void ExitCallback(Ref *pSender, Widget::TouchEventType type);
    void RestartCallback(Ref *pSender, Widget::TouchEventType type);
    void HomeTouchCallback(Ref* pSender, Widget::TouchEventType type);
    void SoundTouchCallback(Ref* pSender, Widget::TouchEventType type);
    void PauseTouchCallback(Ref* pSender, Widget::TouchEventType type);
    void OkPauseTouchCallback(Ref* pSender, Widget::TouchEventType type);
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    void RandMouse(int percent);
    void GameUpdate(float dt);
    void TimeUpdate(float dt);
    CREATE_FUNC(GameScene);
    Label* lab_setp;
    void UpdateScore();
    
 
    void GameOver();
    void ShowNext();
    
    void afterCaptured(bool succeed, const std::string& outputFile);
    void capture(Ref* pSender, Widget::TouchEventType type);
    
private:
    News* _news;
    Mouse* m;
    Sprite* bg_canavas;
    Vector<Mouse*> mouses ;
    ProgressTimer* progressTimer ;
    CC_SYNTHESIZE(int, Score, Score);
    
    Sprite* gameNext;
     Layer* gameOver;
    
    Sprite* bg_bot;
    Sprite* bg_top;
    Sprite* bg_mid;
};

#endif /* GameScene_hpp */
