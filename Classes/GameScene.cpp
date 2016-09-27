//
//  GameScene.cpp
//  PopoHit
//
//  Created by Pham Thanh on 4/12/16.
//
//

#include "GameScene.hpp"
#include "Sound.hpp"
#include "MenuScene.hpp"
#include "Mouse.hpp"
#include "GameManager.hpp"

#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

//    int mouseX[3][3] = {
//                   {145,337,531},
//                   {120,337,531},
//                   {120,337,555},
//    };
//    int mouseY[] = {275-20,186-20,88-20};

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

static int MaxTrix[3][3] = {
    {0,0,0},
    {0,0,0},
    {0,0,0},
};

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }

    
    GameManager::getInstance();

    
    this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    // init background
    // init game object: button, item ...
    // add count down before start
    // start game
    auto winSize = Director::getInstance()->getWinSize();
    
    
    auto bg = Sprite::create("gamescene/background.png");
    bg->setAnchorPoint(Vec2(0,0));
    this->addChild(bg);
    
    
    auto sound_btn = Button::create("common/sound_btn.png");
    sound_btn->addTouchEventListener(CC_CALLBACK_2(GameScene::SoundTouchCallback,this));
    this->addChild(sound_btn);
    sound_btn->setPosition(Vec2(winSize.width - sound_btn->getContentSize().width/2, winSize.height - sound_btn->getContentSize().height/2 ));
    if (!readBoolXML(MUSIC))
    {
        sound_btn->setBright(false);
    }
    
    if (readBoolXML(MUSIC))
    {
            Sound::getInstance()->playGameBackground();
    }
    saveBoolXML(ISNEWS, false);
    
    auto home_btn = Button::create("common/home_btn.png");
    home_btn->addTouchEventListener(CC_CALLBACK_2(GameScene::HomeTouchCallback,this));
    this->addChild(home_btn);
    home_btn->setPosition(Vec2(winSize.width - home_btn->getContentSize().width/2 - sound_btn->getContentSize().width,winSize.height - home_btn->getContentSize().height/2));

    
    auto pause_btn = Button::create("common/pause_btn.png");
    pause_btn->addTouchEventListener(CC_CALLBACK_2(GameScene::PauseTouchCallback,this));
    this->addChild(pause_btn);
    pause_btn->setPosition(Vec2(winSize.width - sound_btn->getContentSize().width- home_btn->getContentSize().width- pause_btn->getContentSize().width/2,winSize.height - pause_btn->getContentSize().height/2));
    
    auto help_btn = Button::create("common/camera.png", "common/camera.png");
    help_btn->addTouchEventListener(CC_CALLBACK_2(GameScene::capture,this));
    this->addChild(help_btn);
    help_btn->setPosition(Vec2(0 +help_btn->getContentSize().width/2 , winSize.height - help_btn->getContentSize().height/2));
    
    
    
    bg_canavas = Sprite::create("gamescene/bg_canvas.png");
    bg_canavas->setAnchorPoint(Vec2::ZERO);
    bg_canavas->setPosition(Vec2((winSize.width - bg_canavas->getContentSize().width)/2,(winSize.height - bg_canavas->getContentSize().height)/2));
    this->addChild(bg_canavas);
    
    
    lab_setp = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 24);
    lab_setp->setPosition(Vec2(600,420));
    
    this->addChild(lab_setp);
    
     bg_top = Sprite::create("gamescene/bg_top.png");
    bg_top->setAnchorPoint(Vec2::ZERO);
    bg_top->setPosition(Vec2((winSize.width - bg_top->getContentSize().width)/2,(winSize.height - bg_top->getContentSize().height)/2));
    this->addChild(bg_top,101);
    
     bg_mid = Sprite::create("gamescene/bg_middle.png");
    bg_mid->setAnchorPoint(Vec2::ZERO);
    bg_mid->setPosition(Vec2((winSize.width - bg_mid->getContentSize().width)/2,(winSize.height - bg_mid->getContentSize().height)/2));
    this->addChild(bg_mid,103);
    
     bg_bot = Sprite::create("gamescene/bg_bottom.png");
    bg_bot->setAnchorPoint(Vec2::ZERO);
    bg_bot->setPosition(Vec2((winSize.width - bg_bot->getContentSize().width)/2,(winSize.height - bg_bot->getContentSize().height)/2));
    this->addChild(bg_bot,105);
    

    auto bg1 = Sprite::create("gamescene/time_roller_bg.png");
    bg1->setAnchorPoint(Vec2::ZERO);
    bg1->setPosition(Vec2(250, 400));
    addChild(bg1);
    progressTimer = ProgressTimer::create( Sprite::create("gamescene/time_roller_progress.png") );
    if ( progressTimer != NULL )
    {
        progressTimer->setType(ProgressTimer::Type::BAR);
      
        progressTimer->setMidpoint(Vec2(1, 0));
        progressTimer->setBarChangeRate(Vec2(1, 0));
        progressTimer->setPercentage(100);
        progressTimer->setAnchorPoint(Vec2::ZERO);
        progressTimer->setPosition(Vec2(250+47, 407));
        addChild(progressTimer);
    }
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
                   MaxTrix[i][j] = 0;
        }
    }
    this->schedule(schedule_selector(GameScene::TimeUpdate), 1.5f);
    this->schedule(schedule_selector(GameScene::GameUpdate), 1.5f);
    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
    if (Director::getInstance()->isPaused()) {
        return false;
    }
    Point pt = pTouch->getLocation();
    if (gameNext != NULL && gameNext->isVisible() && gameNext->getNumberOfRunningActions()==0) {
        Rect recTemp= gameNext->boundingBox();
        if(recTemp.containsPoint(pt ) ) {
            
            GameManager::getInstance()->Score = 0;
            GameManager::getInstance()->CurrentTimer = 90;
            GameManager::getInstance()->Timer = 90;
            this->schedule(schedule_selector(GameScene::GameUpdate), 1.5f);
            this->schedule(schedule_selector(GameScene::TimeUpdate), 1.5f);
            gameNext->setVisible(false);
            return true;
        }
    }
    
    for (int i=mouses.size()-1; i>=0; i--) {
        Mouse* m = mouses.at(i);
        if (m->getPositionY()<p[m->index].y + m->getContentSize().height) {
            continue;
        }
        Rect recTemp= m->boundingBox();
        if(recTemp.containsPoint(pt ) ) {
            
            m->onTouchBegan(pTouch,pEvent);
            return true;
        }

    }
    
      //  Sound::getInstance()->playAttack();
    
    return false ;
}

void GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent){
        Director::getInstance()->convertToGL(pTouch->getLocationInView());
        Point p= Director::getInstance()->convertToGL(pTouch->getLocationInView());
}

void GameScene::HomeTouchCallback(Ref* pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    log("GameScene::HomeTouchCallback");
    Sound::getInstance()->playBtn();

    Director::getInstance()->replaceScene(MenuScene::createScene());
}
void GameScene::afterCaptured(bool succeed, const std::string& outputFile)
{
    if (succeed)
    {
        // show screenshot
//        auto sp = Sprite::create(outputFile);
//        addChild(sp,233);
        Size s = Director::getInstance()->getWinSize();
//        sp->setPosition(s.width / 2, s.height / 2);
//        sp->setScale(0.25);
      //  log("%s",outputFile.c_str());
        
        auto label = Label::createWithTTF(outputFile.c_str(),"fonts/Marker Felt.ttf", 24);
        label->setPosition(Vec2(s.width / 2, s.height / 6));
        addChild(label,233);
        auto delay = DelayTime::create(3);
        label->runAction(Sequence::createWithTwoActions(delay, RemoveSelf::create()));
    }
    else
    {
        log("Capture screen failed.");
    }
}

void GameScene::capture(Ref* pSender, Widget::TouchEventType type)
{
        int lastPic = readIntXML("lastPic");
   
    FileUtils::getInstance()->createDirectory(FileUtils::getInstance()->getWritablePath()+"popohit");
    utils::captureScreen(CC_CALLBACK_2(GameScene::afterCaptured, this),__String::createWithFormat("%spopohit/CaptureScreen_%d.png",FileUtils::getInstance()->getWritablePath().c_str(),lastPic)->getCString());
    saveIntXML("lastPic",lastPic+1);
}

void GameScene::SoundTouchCallback(Ref* pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    Sound::getInstance()->playBtn();
    auto sender = ((Button*)pSender);
    
    log("GameScene::SoundTouchCallback");
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

void GameScene::PauseTouchCallback(Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        log("GameScene::PauseTouchCallback");
        
        
        Sound::getInstance()->playBtn();
        if (Director::getInstance()->isPaused()) {
              Sound::getInstance()->playGameBackground();
            Director::getInstance()->resume();
        } else {
            
            Sound::getInstance()->stopBackground();
            Director::getInstance()->pause();
        }
    }
}

void GameScene::OkPauseTouchCallback(Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
          log("GameScene::OkPauseTouchCallback");
        Sound::getInstance()->playBtn();

        _news->runAction(Spawn::create(
                                       MoveBy::create(1.f, Vec2(Director::getInstance()->getWinSize().width, 0))
                                       , FadeOut::create(1.f)
                                       , NULL));
        saveBoolXML(ISNEWS, false);
    }
}

void GameScene::UpdateScore() {
    lab_setp->setString(__String::createWithFormat("Score: %d", GameManager::getInstance()->Score)->getCString());
}
void GameScene::TimeUpdate(float dt)
{
    GameManager::getInstance()->CurrentTimer--;
    progressTimer->setPercentage(GameManager::getInstance()->CurrentTimer*100/GameManager::getInstance()->Timer);
    this->UpdateScore();
    if (GameManager::getInstance()->CurrentTimer <= 0) {
        
        if (GameManager::getInstance()->Score < GameManager::getInstance()->RequireScore) {
            this->GameOver();
            log("game over");
        } else {
            this->ShowNext();
            log("game next");
        }
        
    }
    if (GameManager::getInstance()->CurrentTimer == 5 ) {
        this->schedule(schedule_selector(GameScene::GameUpdate), 0.1f);
    } else if (GameManager::getInstance()->CurrentTimer == 10 ) {
        this->schedule(schedule_selector(GameScene::GameUpdate), 0.5f);
    } else if (GameManager::getInstance()->CurrentTimer == 40 ) {
        this->schedule(schedule_selector(GameScene::GameUpdate), 1.0f);
    } else if (GameManager::getInstance()->CurrentTimer == 50 ) {
        this->schedule(schedule_selector(GameScene::GameUpdate), 1.0f);
    } else if (GameManager::getInstance()->CurrentTimer == 60 ) {
        this->schedule(schedule_selector(GameScene::GameUpdate), 1.0f);
    } else if (GameManager::getInstance()->CurrentTimer == 70 ) {
        this->schedule(schedule_selector(GameScene::GameUpdate), 1.0f);
    } else if (GameManager::getInstance()->CurrentTimer == 80 ) {
        this->schedule(schedule_selector(GameScene::GameUpdate), 1.2f);
    }
}
void GameScene::GameUpdate(float dt)
{
    for (int i=mouses.size()-1; i>=0; i--) {
        if (mouses.at(i)->state == 6) {
            int cellx = mouses.at(i)->index/3;
            int celly = mouses.at(i)->index%3;
            MaxTrix[cellx][celly] = 0;
            mouses.erase(i);
        }
    }
    int rate = cocos2d::RandomHelper::random_int(0, 100);
    
    
    RandMouse(rate);
    RandMouse(rate);
    RandMouse(rate);
    RandMouse(rate);
  
    this->UpdateScore();

    

}

void GameScene::GameOver() {
      log("GameScene::GameOver");
       this->unschedule(schedule_selector(GameScene::TimeUpdate));
   this->unschedule(schedule_selector(GameScene::GameUpdate));

    auto winSize = Director::getInstance()->getWinSize();
    if (gameOver == NULL) {
        gameOver = Layer::create();
        gameOver->setAnchorPoint(Vec2::ZERO);
        gameOver->setContentSize(Director::getInstance()->getWinSize());
        gameOver->setPosition(Vec2::ZERO);
        auto txtGameOver = Sprite::create("gamescene/gameover.png");
        txtGameOver->setAnchorPoint(Vec2::ZERO);
        txtGameOver->setPosition(Vec2((winSize.width - txtGameOver->getContentSize().width)/2,(winSize.height - txtGameOver->getContentSize().height)/2));
        gameOver->addChild(txtGameOver,122);
        
        
        txtGameOver->runAction(Sequence::create( ScaleTo::create(0.5f, 1.f, 0.7f)
                                                , Spawn::create(MoveBy::create(0.5f, Vec2(0.f, 40.f)), ScaleTo::create(0.5f, 1.f, 1.f), NULL)
                                                , DelayTime::create(0.1f)
                                                , Spawn::create(MoveBy::create(0.5f, Vec2(0.f, -40.f)), ScaleTo::create(0.5f, 1.f, 0.7f), NULL)
                                                , DelayTime::create(0.1f)
                                                , ScaleTo::create(0.5f, 1.f, 1.f)
                                                , DelayTime::create(0.1f)
                                                , NULL)
                               );
        auto btnRestart=Button::create("gamescene/restart_btn.png","gamescene/restart_btn_active.png");
        btnRestart->addTouchEventListener(CC_CALLBACK_2(GameScene::RestartCallback,this));
        gameOver->addChild(btnRestart,122);
        btnRestart->setPosition(Vec2(txtGameOver->getPositionX(),txtGameOver->getPositionY()-150));;
        
        auto btnExit=Button::create("gamescene/menu_btn.png","gamescene/menu_btn_active.png");
        btnExit->addTouchEventListener(CC_CALLBACK_2(GameScene::ExitCallback,this));
        gameOver->addChild(btnExit,122);
        btnExit->setPosition(Vec2(txtGameOver->getPositionX()+txtGameOver->getContentSize().width,txtGameOver->getPositionY()-150));
        this->addChild(gameOver,122);

    } else {
        if (!gameOver->isVisible()) {
            gameOver->setVisible(true);
        }
    }
#ifdef SDKBOX_ENABLED
    sdkbox::PluginAdMob::show("gameover");
#endif
       Sound::getInstance()->playGameOver();
}

void GameScene::ExitCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    Sound::getInstance()->playBtn();
    GameManager::getInstance()->Score = 0;
    GameManager::getInstance()->Timer = 90;
    GameManager::getInstance()->CurrentTimer = 90;
    gameOver->setVisible(false);
    log("MenuScene::ExitCallback");
    Director::getInstance()->replaceScene(MenuScene::createScene());
    
}

void GameScene::RestartCallback(Ref *pSender, Widget::TouchEventType type)
{
    if (readBoolXML(ISNEWS))
        return;
    if (type != Widget::TouchEventType::ENDED)
        return;
    Sound::getInstance()->playBtn();
    gameOver->setVisible(false);
    GameManager::getInstance()->Score = 0;
    GameManager::getInstance()->Timer = 90;
    GameManager::getInstance()->CurrentTimer = 90;
    log("MenuScene::RestartCallback");
    this->schedule(schedule_selector(GameScene::GameUpdate),1.5f);
    this->schedule(schedule_selector(GameScene::TimeUpdate), 1.5f);
    
}

void GameScene::ShowNext() {
    log("GameScene::ShowNext");
    

   this->unschedule(schedule_selector(GameScene::TimeUpdate));
    this->unschedule(schedule_selector(GameScene::GameUpdate));
  
    
    auto winSize = Director::getInstance()->getWinSize();
    gameNext = Sprite::create("gamescene/next.png");
    gameNext->setAnchorPoint(Vec2::ZERO);
    gameNext->setPosition(Vec2((winSize.width - gameNext->getContentSize().width)/2,(winSize.height - gameNext->getContentSize().height)/2));
    auto yourScore = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    yourScore->setAnchorPoint(Vec2::ZERO);
    yourScore->setColor(Color3B(100, 100, 100));
    yourScore->setString(__String::createWithFormat("%d", GameManager::getInstance()->Score)->getCString());
    yourScore->setPosition(Vec2(300,141));
    gameNext->addChild(yourScore,123);
    
    auto nextLevelScore = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    nextLevelScore->setColor(Color3B(100, 100, 100));
    GameManager::getInstance()->RequireScore+=2000;
    nextLevelScore->setString(__String::createWithFormat("%d", GameManager::getInstance()->RequireScore)->getCString());
    nextLevelScore->setAnchorPoint(Vec2::ZERO);
    nextLevelScore->setPosition(Vec2(300,98));
    gameNext->addChild(nextLevelScore,123);
    Sound::getInstance()->playGamePass();
    this->addChild(gameNext,122);
    
    int uscore = readIntXML("topscore");
   if (GameManager::getInstance()->Score > uscore) {
        saveIntXML("topscore",GameManager::getInstance()->Score);
        
        auto topScore = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
        topScore->setColor(Color3B(100, 100, 100));
        GameManager::getInstance()->RequireScore+=2000;
        topScore->setString(__String::createWithFormat("High Score: %d", GameManager::getInstance()->Score)->getCString());
        topScore->setColor(Color3B(0,255,0));
        topScore->setAnchorPoint(Vec2::ZERO);
        topScore->setPosition(Vec2(150,50));
        gameNext->addChild(topScore,123);
    }
    
    gameNext->runAction(
                        Sequence::create(
                                         ScaleTo::create(0.5f, 1.f, 0.7f)
                                         , Spawn::create(MoveBy::create(0.5f, Vec2(0.f, 30.f)), ScaleTo::create(0.5f, 1.f, 1.f), NULL)
                                         , DelayTime::create(0.2f)
                                         , Spawn::create(MoveBy::create(0.5f, Vec2(0.f, -30.f)), ScaleTo::create(0.5f, 1.f, 0.7f), NULL)
                                         , DelayTime::create(0.1f)
                                         , ScaleTo::create(0.5f, 1.f, 1.f)
                                         , DelayTime::create(0.5f)
                                         , NULL)
                        );
}

void GameScene::RandMouse(int percent) {
   
    int pos = cocos2d::RandomHelper::random_int(0, 8);
    int cellx = pos/3;
    int celly = pos%3;
    
    if (cocos2d::RandomHelper::random_int(0, 100)>  percent && !MaxTrix[cellx][celly]) {
        MaxTrix[cellx][celly] = 1;
        
        int mtype = cocos2d::RandomHelper::random_int(0, MAX_MOUSE-1);
        
        auto m = Mouse::createMouse(GameManager::getInstance()->mouseList[mtype].speed,GameManager::getInstance()->mouseList[mtype].live,GameManager::getInstance()->mouseList[mtype].die);
        m->point = GameManager::getInstance()->mouseList[mtype].point;
        m->point_type = GameManager::getInstance()->mouseList[mtype].point_type;
        m->setAnchorPoint(Vec2::ZERO);
        m->index = pos;
        m->setPosition(Vec2(p[pos].x+bg_canavas->getPositionX(),p[pos].y+bg_canavas->getPositionY()));
        mouses.pushBack(m);
        if (pos <3 ) {
                  this->addChild(m,99);
        } else if (pos < 6) {
             this->addChild(m,101);
        } else if (pos < 9) {
             this->addChild(m,103);
        }
        

        m->Run(0.7, 72);
    }

}