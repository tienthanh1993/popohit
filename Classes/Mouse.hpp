//
//  Mouse.hpp
//  Skeleton
//
//  Created by Pham Thanh on 4/14/16.
//
//

#ifndef Mouse_hpp
#define Mouse_hpp
#include <cocos2d.h>
USING_NS_CC;
struct MouseAttr {
    float speed;
    int point_type;
    int point;
    char live[64];
    char die[64];
};
class Mouse : public Layer {
public:
    enum mouse_status {
        state_hide,
        state_up,
        state_smile,
        state_down,
        state_die,
        state_end,
        state_finished,
    };
    bool init(float speed, std::string live, std::string die);
    static Mouse* createMouse(float speed, std::string live, std::string die);
    MouseAttr attr;
    // + - * /
    int point_type;
    // point
    int point;
    
    // live sprite
    std::string live;
    //die sprite
    std::string die;
    // mouse index
    int index;
    // mouse status
    int status;
    // mouse heigth
    int height;
    // speed
    float speed;
    
    
    int type; // type

    void Hit();
    void Run(float speed=1.0,float heigth= 72);
       Sprite* spr;
        int state;
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    virtual void onTouchMoved(Touch *touch, Event *event);
    private :
 
    Sprite* myStart;

    
    virtual void onTouchEnded(Touch *touch, Event *event);
};

#endif /* Mouse_hpp */
