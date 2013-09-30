#include "HelpLayer.h"
#include "MainScene.h"

using namespace cocos2d;

HelpLayer::HelpLayer(void)
{
}

HelpLayer::~HelpLayer(void)
{
}

bool HelpLayer::init(void)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
		
		CCMenuItemFont *back = CCMenuItemFont::create("Go back",this, menu_selector(HelpLayer::backCallback));
		CC_BREAK_IF(! back);
	
		CCMenu *menu = CCMenu::create(back, NULL);
		CC_BREAK_IF(! menu);	
		menu->alignItemsHorizontally();
		this->addChild(menu);
		bRet = true;
	} while (0);

	return bRet;
}

void HelpLayer::backCallback(CCObject* pSender)
{
	CCScene *scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2f, scene));
}
