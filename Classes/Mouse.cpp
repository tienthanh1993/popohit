//
//  Mouse.cpp
//  Skeleton
//
//  Created by Pham Thanh on 4/14/16.
//
//

#include "Mouse.hpp"
#include "GameManager.hpp"
#include "Sound.hpp"
#include <string.h>

#define MAX_HEIGTH 72

Mouse* Mouse::createMouse(float speed, std::string live, std::string die)
{
    auto mouse = new Mouse;
    if (mouse&&mouse->init(speed,live,die))
    {
        mouse->autorelease();
        return mouse;
    }
    CC_SAFE_DELETE(mouse);
    return NULL;
}

bool Mouse::init(float speed, std::string live, std::string die) {
    if (!Layer::init()) {
        
        return false;
        
    }
    
    this->live = live;
    this->die = die;
    this->speed = speed;
    
    spr = Sprite::create(live.c_str());
    spr->setAnchorPoint(Vec2::ZERO);
    this->addChild(spr);
    state = state_hide;
    this->setContentSize(spr->getContentSize());
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = CC_CALLBACK_2(Mouse::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Mouse::onTouchEnded, this);
 //   _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
      return true;
}

void Mouse::Run(float speed ,float heigth) {
    if (this->state == state_hide) {
        this->state = state_up;
        auto moveUp = MoveBy::create(speed, Vec2(0,spr->getContentSize().height));
        auto smile = CallFuncN::create([&](Node *pSender) {
             this->state = state_smile;
        });
        auto moveDown = MoveBy::create(speed, Vec2(0,-spr->getContentSize().height));
        auto endMove = CallFuncN::create([&](Node *pSender) {
            this->state = state_down;
            state = state_finished;
            this->removeFromParentAndCleanup(true);
        });
        
          auto seq = Sequence::create(moveUp,smile,moveDown,endMove, NULL);
          this->runAction(seq);
    }
}

void Mouse::Hit() {
    // add point
    // set death
    // wait
    // disapear
    // release point

    if (state == state_die || state == state_hide|| state == state_finished) {
        log("can't hit")    ;
        return;
    }

    this->stopAllActions();
    spr->setVisible(false);
    spr = Sprite::create(this->die);
    spr->setAnchorPoint(Vec2::ZERO);
    this->addChild(spr);
    this->state = state_die;
    Sound::getInstance()->playDead();
    auto moveLeft = MoveBy::create(0.1, Vec2(-2,0));
    auto moveRight = MoveBy::create(0.1, Vec2(+2,0));
    auto cleanMe = CallFuncN::create([&](Node *pSender) {
            this->removeFromParentAndCleanup(true);
    });
    auto endOfLife = CallFuncN::create([&](Node *pSender) {
        state = state_finished;

        auto lab_setp = Label::createWithTTF(__String::createWithFormat("+%d",point)->getCString(), "fonts/Marker Felt.ttf", 24);
        lab_setp->setPosition(Vec2(72/2,72/2));
        this->addChild(lab_setp,2222);
          lab_setp->setScale(0.1);
         auto scale = ScaleTo::create(0.4, 1);
        auto moveUp = MoveBy::create(0.4, Vec2(0,30));
        
        if (point_type == 0 ) { // cong
              GameManager::getInstance()->Score += point;
            lab_setp->setString(__String::createWithFormat("+%d",point)->getCString());
        } else if (point_type == 1 ) { // tru
             GameManager::getInstance()->Score -= point;
            if ( GameManager::getInstance()->Score < 0) {
                 GameManager::getInstance()->Score = 0;
            }
             lab_setp->setString(__String::createWithFormat("-%d",point)->getCString());
        } else if (point_type == 2 ) { // nhan
             GameManager::getInstance()->Score *= point;
             lab_setp->setString(__String::createWithFormat("x%d",point)->getCString());
        } else if (point_type == 3 ) { // chia
             lab_setp->setString(__String::createWithFormat("/%d",point)->getCString());
            GameManager::getInstance()->Score /= point;
        } else if (point_type == 4 ) { // percent
             lab_setp->setString(__String::createWithFormat("+%%%d",point)->getCString());
            GameManager::getInstance()->Score += GameManager::getInstance()->Score*point/100;
        }
        lab_setp->runAction(Sequence::create(scale,moveUp,RemoveSelf::create(), NULL));

    });
    auto seq = Sequence::create(moveLeft,moveRight,moveLeft,moveRight,moveLeft,moveRight,moveLeft,moveRight,endOfLife,DelayTime::create(1),cleanMe, NULL);
    this->runAction(seq);
    
}
bool Mouse::onTouchBegan(Touch *touch, Event *event) {
    if (Director::getInstance()->isPaused()) {
        return false;
    }
    Point pt = touch->getLocation();

    Rect recTemp= this->boundingBox();
    if(recTemp.containsPoint(pt )) {
 
            this->Hit();
            return false;
    }
    return false;
}

void Mouse::onTouchMoved(Touch *touch, Event *event) {
    
}

void Mouse::onTouchEnded(Touch *touch, Event *event) {
    
}