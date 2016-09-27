#include "GameNews.h"
#include "Sound.hpp"
News* News::createNews(ccTouchCallback _okCallback,int type,bool isCan)
{
	auto news = new News;
	if (news&&news->init(_okCallback,type,isCan))
	{
		news->autorelease();
		return news;
	}
	CC_SAFE_DELETE(news);
	return NULL;
}

bool News::init(ccTouchCallback _okCallback, int type, bool isCan)
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();
	auto layer = LayerColor::create(Color4B(0.f,0.f,0.f,100.f), winSize.width, winSize.height);
	this->addChild(layer, -1);

	auto bg = Sprite::create("common/help_mark.png");
	this->addChild(bg, 0);
	bg->setPosition(winSize.width / 2, winSize.height / 2);

	auto bgSize = bg->getContentSize();

	_close = Button::create("common/close.png");
	_close->addTouchEventListener(CC_CALLBACK_2(News::CloseTouchEventCallback,this));
	this->addChild(_close);
	auto cSize = _close->getContentSize();
	_close->setPosition(Vec2(bg->getPositionX() + bgSize.width / 2 - cSize.width / 2, bg->getPositionY()+bgSize.height/2 - cSize.height / 2));

	_ok = Button::create("common/ok.png");
	_ok->addTouchEventListener(_okCallback);
	this->addChild(_ok);
	auto oSize = _ok->getContentSize();
	_ok->setPosition(Vec2(winSize.width/2,bg->getPositionY()-bgSize.height/2+oSize.height));


	_textLabel = Label::create();
	_textLabel->setSystemFontSize(36.f);
	this->addChild(_textLabel);
	_textLabel->setPosition(winSize.width / 2, winSize.height / 2);


	initSay(type, isCan);

	return true;
}

void News::CloseTouchEventCallback(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
       
		log("CloseTouchEventCallback");
		Sound::getInstance()->playBtn();
		this->runAction(Spawn::create(
			MoveBy::create(0.5f, Vec2( Director::getInstance()->getWinSize().width, 0))
			,FadeOut::create(0.5f)
			,NULL));
		saveBoolXML(ISNEWS, false);
	}
}

void News::initSay(int type, bool isCan)
{
	auto dictionary = Dictionary::createWithContentsOfFile("text/news.xml");
	switch (type)
	{
	case 0:
		if (isCan)
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("helloWordYes"));
			_textLabel->setString(text->getCString());
		}
		else
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("helloWordNo"));
			_textLabel->setString(text->getCString());
		}
		break;
	case 1:
		if (isCan)
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("selectYes"));
			_textLabel->setString(text->getCString());
		}
		else
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("selectNo"));
			_textLabel->setString(text->getCString());
		}
		break;
	case 2:
		if (isCan)
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("levelYes"));
			_textLabel->setString(text->getCString());
		}
		else
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("levelNo"));
			_textLabel->setString(text->getCString());
		}
		break;
	case 3:
		if (isCan)
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("gameYes"));
			_textLabel->setString(text->getCString());
		}
		else
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("gameNo"));
			_textLabel->setString(text->getCString());
		}
	case 4:
		if (isCan)
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("buyJb"));
			_textLabel->setString(text->getCString());
		}
		break;
	case 5:
		if (isCan)
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("buyKey"));
			_textLabel->setString(text->getCString());
		}
		break;
	case 6:
		if (isCan)
		{
			auto text = static_cast<__String*>(dictionary->objectForKey("buyStep"));
			_textLabel->setString(text->getCString());
		}
		break;
	}
}

void News::initSay(std::string title,std::string msg, bool isCan)
{
    _textLabel->setString(msg.c_str());
}




