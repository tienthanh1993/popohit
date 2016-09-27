//
//  GameManager.hpp
//  Skeleton
//
//  Created by Pham Thanh on 4/16/16.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp
#include <cocos2d.h>
USING_NS_CC;
struct MouseList {
    int id;
    int speed;
    int point_type;
    int point;
    std::string die;
    std::string live;
};
#define MAX_MOUSE 8
class GameManager {
private:
    GameManager();
    static GameManager* m_mySingleton;
    
public:
    static GameManager* getInstance();
    
    MouseList mouseList[MAX_MOUSE];
    
    int Stage;
    int Score;
    int RequireScore;
    int Timer;
    int CurrentTimer;

};

#endif /* GameManager_hpp */
