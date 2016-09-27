#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    //SavePngFromPlist("mainUi0.plist","");
    return true;
}
#include <string.h>

char *strrev(char *str)
{
    char *p1, *p2;
    
    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}


void HelloWorld::SavePngFromPlist(char *plistName,char *path){
    
    char *temp = strdup(plistName);
    temp = strrev(temp);
    temp = strchr(temp,'.');
    temp = strrev(temp);
    temp = strcat(temp,"png");
    char *PngFileName = temp;
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistName);
    SpriteBatchNode *SpriteSheet = SpriteBatchNode::create("mainUi0.png");
    
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plistName);
    Dictionary *dict = Dictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
    Dictionary *frameDict = (Dictionary*)dict->objectForKey("frames");
    __Array *allKeyArray = frameDict->allKeys();
    
    Object *obj = NULL;
    CCARRAY_FOREACH(allKeyArray,obj){
        __String *tempName = (__String*)obj;
      
       SpirtetoImame(tempName->getCString());
 
    }
}

Image * HelloWorld::SpirtetoImame(const std::string& spriteFrameName){
    Sprite *sprite = Sprite::createWithSpriteFrameName(spriteFrameName.c_str());
    Point p = sprite->getAnchorPoint();
    sprite->setAnchorPoint(Vec2(0,0));
    RenderTexture *render = RenderTexture::create(sprite->getContentSize().width,sprite->getContentSize().height);
    render->begin();
    sprite->visit();
    render->end();
    sprite->setAnchorPoint(p);
    
    if (render->saveToFile(spriteFrameName.c_str(), Image::Format::PNG))
        log("failed");
    return nullptr;
}

#include "MenuScene.hpp"
void HelloWorld::menuCloseCallback(Ref* pSender)
{
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
    Director::getInstance()->replaceScene(MenuScene::createScene());
}
