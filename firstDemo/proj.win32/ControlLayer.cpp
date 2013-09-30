#include "ControlLayer.h"
#include "MainScene.h"
#include "GameScene.h"
#include "NoTouchLayer.h"

using namespace cocos2d;

static bool m_isPause;
ControlLayer::ControlLayer(void)
{
	m_isPause = false;
}

ControlLayer::~ControlLayer(void)
{
}

bool ControlLayer::init(void)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
		CCMenuItemFont *goBack = CCMenuItemFont::create("Back",this,menu_selector(ControlLayer::onGoBack));
		CC_BREAK_IF(!goBack);
		goBack->setFontSizeObj(20);
		CCMenuItemFont *reStart = CCMenuItemFont::create("Restart",this,menu_selector(ControlLayer::onReStart));
		CC_BREAK_IF(!reStart);
		reStart->setFontSizeObj(20);
		CCMenuItemFont *pause = CCMenuItemFont::create("Pause",this,menu_selector(ControlLayer::onPause));
		CC_BREAK_IF(!pause);
		pause->setFontSizeObj(20);
		CCMenuItemFont *fire = CCMenuItemFont::create("Fire",this,menu_selector(ControlLayer::onFire));
		CC_BREAK_IF(!fire);
		fire->setFontSizeObj(20);
		CCMenu * menu = CCMenu::create(goBack, reStart, pause,fire, NULL);
		menu->alignItemsVerticallyWithPadding(10);
		menu->setColor(ccc3(255,100,0));
		
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		menu->setPosition(winSize.width-30,winSize.height-50);
		this->addChild(menu,1,2);
		bRet = true;
	} while (0);

	return bRet;
}

void ControlLayer::backCallback(CCObject* pSender)
{
	//CCScene *scene = MainScene::scene();
	//CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2f, scene));
}

void ControlLayer::onGoBack(CCObject* pSender)
{
	CCScene *scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1.2f, scene));
}

void ControlLayer::onReStart(CCObject* pSender)
{
	CCScene *scene = GameScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1.2f, scene));
}

void ControlLayer::onPause(CCObject* pSender)
{
	//NoTouchLayer * layer = NoTouchLayer::create();
	//this->addChild(layer);

	if(m_isPause)
	{
		CCDirector::sharedDirector()->resume();
		m_isPause = false;
	}
	else
	{
		CCDirector::sharedDirector()->pause();
		m_isPause = true;
	}
}

void ControlLayer::onFire(CCObject* pSender)
{
	INT a = 10;
}


