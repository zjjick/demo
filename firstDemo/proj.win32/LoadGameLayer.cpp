#include "LoadGameLayer.h"
#include "MainScene.h"

using namespace cocos2d;

LoadGameLayer::LoadGameLayer(void)
{
}

LoadGameLayer::~LoadGameLayer(void)
{
}

bool LoadGameLayer::init(void)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());

		CCMenuItemFont *back = CCMenuItemFont::create("Go back",this, menu_selector(LoadGameLayer::backCallback));
		CC_BREAK_IF(! back);
	
		CCMenu *menu = CCMenu::create(back, NULL);
		CC_BREAK_IF(! menu);	
		menu->alignItemsHorizontally();
		this->addChild(menu);

		// 手工微调一下最后一个菜单项的位置
		/*
		cocos2d::CCPoint cp_back = back->getPosition();
		cp_back.y -= 50.0f;
		back->setPosition(cp_back);
		*/

		bRet = true;
	} while (0);

	return bRet;
}

void LoadGameLayer::backCallback(CCObject* pSender)
{
	CCScene *scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2f, scene));
}
