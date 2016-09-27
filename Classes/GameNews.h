#ifndef __GAME_NEWS_H__
#define __GAME_NEWS_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
class News: public Layer
{
public:
	typedef std::function<void(Ref*, Widget::TouchEventType)> ccTouchCallback;
	static News* createNews(ccTouchCallback _okCallback, int type, bool isCan);
	bool init(ccTouchCallback _okCallback, int type, bool isCan);
	void CloseTouchEventCallback(Ref *pSender, Widget::TouchEventType type);
	void initSay(int type,bool isCan);
    void initSay(std::string title,std::string msg,bool isCan);
private:
	Button* _close;
	Button* _ok;
	Label* _textLabel;
};
#endif