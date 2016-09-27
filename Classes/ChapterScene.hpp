//
//  ChapterScene.hpp
//  Skeleton
//
//  Created by Pham Thanh on 4/13/16.
//
//

#ifndef ChapterScene_hpp
#define ChapterScene_hpp
#include <cocos2d.h>
USING_NS_CC;

class ChapterScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    
    CREATE_FUNC(ChapterScene);
};
#endif /* ChapterScene_hpp */
