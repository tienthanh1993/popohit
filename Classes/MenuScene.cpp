//
//  MenuScene.cpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#include "MenuScene.hpp"
#include "Sound.hpp"
#include "TopScene.hpp"
#include "GameScene.hpp"
#include "StoreScene.hpp"
#include "ChapterScene.hpp"
#include "GameManager.hpp"

#include "AdsIntergrate.hpp"


static Point p[9] = {
    Point(155,220),
    Point(345,220),
    Point(545,210),
    
    Point(130,122),
    Point(345,122),
    Point(546,122),
    
    Point(120,25),
    Point(347,23),
    Point(566,25),
};

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = MenuScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

void MenuScene::onEnter() {
    Layer::onEnter();
    
    Ads::showAdmob("home");
}

bool MenuScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    

    auto winSize = Director::getInstance()->getWinSize();
    
    
    auto bg = Sprite::create("background.png");
    bg->setAnchorPoint(Vec2(0,0));
    this->addChild(bg);
    auto bg_canavas = Sprite::create("menuscene/bg_canvas.png");
    bg_canavas->setAnchorPoint(Vec2::ZERO);
    bg_canavas->setPosition(Vec2((winSize.width - bg_canavas->getContentSize().width)/2,(winSize.height - bg_canavas->getContentSize().height)/2 + 50));
    this->addChild(bg_canavas);
    
    auto start_btn = Button::create("menuscene/play_btn.png", "menuscene/play_btn_active.png");
    start_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::StartGameCallback,this));
    this->addChild(start_btn);
    start_btn->setPosition(Vec2(winSize.width/1.4,winSize.height/2));
    
    
    auto top_btn = Button::create("menuscene/help_btn.png", "menuscene/help_btn_active.png");
    top_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::HelpCallback,this));
    this->addChild(top_btn);
    top_btn->setPosition(Vec2(start_btn->getPositionX(),start_btn->getPositionY() - top_btn->getContentSize().height - 15 ));
    
    
//    auto store_btn = Button::create("common/store_btn.png", "common/store_btn1.png");
//    store_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::StoreCallback,this));
//    this->addChild(store_btn);
//    store_btn->setPosition(Vec2(top_btn->getPositionX(),top_btn->getPositionY() - store_btn->getContentSize().height - 15 ));
//    
    
    auto vip = Button::create("common/vipIcon.png");
    vip->setAnchorPoint(Vec2(0.5f, 0.f));
    vip->addTouchEventListener(CC_CALLBACK_2(MenuScene::StoreCallback, this));
    this->addChild(vip,10);
    vip->setPosition(Vec2(vip->getContentSize().width,vip->getContentSize().height));
    vip->runAction(RepeatForever::create(
                                         Sequence::create(
                                                          ScaleTo::create(0.5f, 1.f, 0.7f)
                                                          , Spawn::create(MoveBy::create(0.5f, Vec2(0.f, 30.f)), ScaleTo::create(0.5f, 1.f, 1.f), NULL)
                                                          , DelayTime::create(0.2f)
                                                          , Spawn::create(MoveBy::create(0.5f, Vec2(0.f, -30.f)), ScaleTo::create(0.5f, 1.f, 0.7f), NULL)
                                                          , DelayTime::create(0.1f)
                                                          , ScaleTo::create(0.5f, 1.f, 1.f)
                                                          , DelayTime::create(0.5f)
                                                          , NULL)
                                         ));
    
    
    
    auto exit_btn = Button::create("menuscene/exit_btn.png", "menuscene/exit_btn_active.png");
    exit_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::ExitCallback,this));
    this->addChild(exit_btn);
    exit_btn->setPosition(Vec2(top_btn->getPositionX(),top_btn->getPositionY() - exit_btn->getContentSize().height - 15 ));


    auto sound_btn = Button::create("common/sound_btn.png", "common/sound_btn1.png");
    sound_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::SoundCallback,this));
    this->addChild(sound_btn);
    sound_btn->setPosition(Vec2(winSize.width - sound_btn->getContentSize().width/2 , winSize.height - sound_btn->getContentSize().height/2));
    
    if (!readBoolXML(MUSIC))
    {
        sound_btn->setBright(false);
    }
    
    if (readBoolXML(MUSIC))
    {
        Sound::getInstance()->playMenuBackground();
    }
    saveBoolXML(ISNEWS, false);

    
    auto help_btn = Button::create("common/help_btn.png", "common/help_btn1.png");
    help_btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::HelpCallback,this));
    this->addChild(help_btn);
    help_btn->setPosition(Vec2(0 +help_btn->getContentSize().width/2 , winSize.height - help_btn->getContentSize().height/2));

    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
//    auto closeItem = Button::create("CloseNormal.png", "StartGameCallback");
//    closeItem->addTouchEventListener(CC_CALLBACK_2(MenuScene::HelpCallback,this));
//    this->addChild(closeItem);
//    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));

    
    
    GameManager::getInstance();
    
    int mtype = 1;
    int pos = 0;
    
    auto m = Mouse::createMouse(GameManager::getInstance()->mouseList[mtype].speed,GameManager::getInstance()->mouseList[mtype].live,GameManager::getInstance()->mouseList[mtype].die);
    m->point = GameManager::getInstance()->mouseList[mtype].point;
    m->point_type = GameManager::getInstance()->mouseList[mtype].point_type;
    m->setAnchorPoint(Vec2::ZERO);
    m->index = pos;
    m->setPosition(Vec2(p[pos].x+bg_canavas->getPositionX(),p[pos].y+m->getContentSize().height+bg_canavas->getPositionY()));
    this->addChild(m);
     pos = 1;
       mtype = 2;
     m = Mouse::createMouse(GameManager::getInstance()->mouseList[mtype].speed,GameManager::getInstance()->mouseList[mtype].live,GameManager::getInstance()->mouseList[mtype].die);
    m->point = GameManager::getInstance()->mouseList[mtype].point;
    m->point_type = GameManager::getInstance()->mouseList[mtype].point_type;
    m->setAnchorPoint(Vec2::ZERO);
    m->index = pos;
    m->setPosition(Vec2(p[pos].x+bg_canavas->getPositionX(),p[pos].y+m->getContentSize().height+bg_canavas->getPositionY()));
    this->addChild(m);
    pos = 3;
       mtype = 3;
    m = Mouse::createMouse(GameManager::getInstance()->mouseList[mtype].speed,GameManager::getInstance()->mouseList[mtype].live,GameManager::getInstance()->mouseList[mtype].die);
    m->point = GameManager::getInstance()->mouseList[mtype].point;
    m->point_type = GameManager::getInstance()->mouseList[mtype].point_type;
    m->setAnchorPoint(Vec2::ZERO);
    m->index = pos;
    m->setPosition(Vec2(p[pos].x+bg_canavas->getPositionX(),p[pos].y+m->getContentSize().height+bg_canavas->getPositionY()));
    this->addChild(m);
    
    pos = 4;
      mtype = 4;
    m = Mouse::createMouse(GameManager::getInstance()->mouseList[mtype].speed,GameManager::getInstance()->mouseList[mtype].live,GameManager::getInstance()->mouseList[mtype].die);
    m->point = GameManager::getInstance()->mouseList[mtype].point;
    m->point_type = GameManager::getInstance()->mouseList[mtype].point_type;
    m->setAnchorPoint(Vec2::ZERO);
    m->index = pos;
    m->setPosition(Vec2(p[pos].x+bg_canavas->getPositionX(),p[pos].y+m->getContentSize().height+bg_canavas->getPositionY()));
    this->addChild(m);
    
    pos = 6;
      mtype = 5;
    m = Mouse::createMouse(GameManager::getInstance()->mouseList[mtype].speed,GameManager::getInstance()->mouseList[mtype].live,GameManager::getInstance()->mouseList[mtype].die);
    m->point = GameManager::getInstance()->mouseList[mtype].point;
    m->point_type = GameManager::getInstance()->mouseList[mtype].point_type;
    m->setAnchorPoint(Vec2::ZERO);
    m->index = pos;
    m->setPosition(Vec2(p[pos].x+bg_canavas->getPositionX(),p[pos].y+m->getContentSize().height+bg_canavas->getPositionY()));
    this->addChild(m);
    pos = 7;
      mtype = 6;
    m = Mouse::createMouse(GameManager::getInstance()->mouseList[mtype].speed,GameManager::getInstance()->mouseList[mtype].live,GameManager::getInstance()->mouseList[mtype].die);
    m->point = GameManager::getInstance()->mouseList[mtype].point;
    m->point_type = GameManager::getInstance()->mouseList[mtype].point_type;
    m->setAnchorPoint(Vec2::ZERO);
    m->index = pos;
    m->setPosition(Vec2(p[pos].x+bg_canavas->getPositionX(),p[pos].y+m->getContentSize().height+bg_canavas->getPositionY()));
    this->addChild(m);

    return true;
}


//big menu
void MenuScene::StartGameCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    if (help != NULL&&help->isVisible()) {
        return;
    }
    Ads::hideAdmob("home");
    
    Sound::getInstance()->playBtn();
    log("MenuScene::StartGameCallback");
    if (GAME_TYPE == 1 ) {
           Director::getInstance()->replaceScene(ChapterScene::createScene());
    } else if (GAME_TYPE == 2) {
        Director::getInstance()->replaceScene(GameScene::createScene());
    }
 
    
}

void MenuScene::TopCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    if (help != NULL&&help->isVisible()) {
        return;
    }
    Sound::getInstance()->playBtn();
    log("MenuScene::TopCallback");
    Director::getInstance()->replaceScene(TopScene::createScene());
}
void MenuScene::StoreCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    if (help != NULL&&help->isVisible()) {
        return;
    }
    Sound::getInstance()->playBtn();
    log("MenuScene::StoreCallback");
    Director::getInstance()->replaceScene(StoreScene::createScene());
}
void MenuScene::ExitCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    Sound::getInstance()->playBtn();
    log("MenuScene::ExitCallback");
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}

// small button
void MenuScene::SoundCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;

    auto sender = ((Button*)pSender);
    
    log("MenuScene::SoundCallback");
    if (readBoolXML(ISNEWS))
    {
        return;
    }
    sender->setBright(!sender->isBright());
    Sound::getInstance()->playBtn();

    
    if (readBoolXML(MUSIC))
    {
 
        saveBoolXML(MUSIC, false);
        Sound::getInstance()->stopBackground();
    }
    else
    {

        saveBoolXML(MUSIC, true);
        Sound::getInstance()->playMenuBackground();
    }

}

void MenuScene::HelpCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
  

    log("MenuScene::HelpCallback");
//    if (readBoolXML(ISNEWS))
//    {
//        return;
//    }
//    if (_news)
//    {
//        this->removeChild(_news);
//        _news = NULL;
//    }
//
//    saveBoolXML(ISNEWS, true);
//    _news = News::createNews(CC_CALLBACK_2(MenuScene::HelpOkCallback, this), 0, !readBoolXML("GM"));
//    this->addChild(_news, 100);
//    _news->setPosition(800.f, 0);
//    _news->runAction(MoveBy::create(1.f, Vec2(-800, 0)));
    
    
    auto winSize = Director::getInstance()->getWinSize();
    if (help == NULL) {
        help = Layer::create();
        help->setPosition(Vec2::ZERO);
        help->setAnchorPoint(Vec2::ZERO);
        auto bg_canavas = Sprite::create("menuscene/bg_help.png");
        bg_canavas->setAnchorPoint(Vec2::ZERO);
        bg_canavas->setPosition(Vec2((winSize.width - bg_canavas->getContentSize().width)/2,(winSize.height - bg_canavas->getContentSize().height)/2+50));
        help->addChild(bg_canavas);
        
        auto btnExit=Button::create("gamescene/menu_btn.png","gamescene/menu_btn_active.png");
        btnExit->addTouchEventListener(CC_CALLBACK_2(MenuScene::HelpOkCallback,this));
        help->addChild(btnExit,122);
        btnExit->setPosition(Vec2(470+180,190-40+50));
            Sound::getInstance()->playBtn();
        this->addChild(help);
        
    } else {
        if (help->isVisible()) {
            return;
        } else {
            help->setVisible(true);
                Sound::getInstance()->playBtn();
        }
    }


    log("need show help dialog or help scene");
}

void MenuScene::HelpOkCallback(Ref *pSender, Widget::TouchEventType type)
{

    log("MenuScene::HelpOkCallback");
     Sound::getInstance()->playBtn();    if (help !=NULL && help->isVisible()) {
        help->setVisible(false);
        
       
    }
//    if (!readBoolXML(GM))
//    {
//        saveBoolXML(GM, true);
//    }
//    _news->runAction(Spawn::create(
//                                   MoveBy::create(1.f, Vec2(800.f, 0))
//                                   , FadeOut::create(1.f)
//                                   , NULL));
//    saveBoolXML(ISNEWS, false);
}