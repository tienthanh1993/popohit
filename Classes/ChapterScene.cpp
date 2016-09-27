//
//  ChapterScene.cpp
//  Skeleton
//
//  Created by Pham Thanh on 4/13/16.
//
//

#include "ChapterScene.hpp"

Scene* ChapterScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = ChapterScene::create();
    
    scene->addChild(layer);
    
    return scene;
    
}

bool ChapterScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    log("ChapterScene::init");
    
    auto bg = Sprite::create("background.png");
    bg->setAnchorPoint(Vec2::ZERO);
    this->addChild(bg);
    return true;
}