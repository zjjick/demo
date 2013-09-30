#include "SettingsLayer.h"
#include "MainScene.h"

using namespace cocos2d;

SettingsLayer::SettingsLayer(void)
{
}

SettingsLayer::~SettingsLayer(void)
{
}

bool SettingsLayer::init(void)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());

		// 设置标题字体
		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		// 用一个禁用状态的菜单项作为标题
		CCMenuItemFont *title1 = CCMenuItemFont::create("Sound");
		CC_BREAK_IF(! title1);
		title1->setEnabled(false);

		// 设置选项字体（设置不同的字体以示与标题的区别）
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		// 设置可切换的菜单项，菜单状态：开、关。
		CCMenuItemToggle *item1 = CCMenuItemToggle::createWithTarget(NULL, NULL,
			CCMenuItemFont::create("On"), CCMenuItemFont::create("Off"), NULL);
		CC_BREAK_IF(! item1);

		// 设置标题字体
		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		CCMenuItemFont *title2 = CCMenuItemFont::create("Music");
		CC_BREAK_IF(! title2);
		title2->setEnabled(false);

		// 设置选项字体
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		CCMenuItemToggle *item2 = CCMenuItemToggle::createWithTarget(NULL, NULL,
			CCMenuItemFont::create("On"), CCMenuItemFont::create("Off"), NULL);
		CC_BREAK_IF(! item2);

		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		CCMenuItemFont *title3 = CCMenuItemFont::create("AI");
		CC_BREAK_IF(! title3);
		title3->setEnabled(false);

		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		CCMenuItemToggle *item3 = CCMenuItemToggle::createWithTarget(NULL, NULL,
			CCMenuItemFont::create("Attack"), CCMenuItemFont::create("Defense"), NULL);
		CC_BREAK_IF(! item3);

		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		CCMenuItemFont *title4 = CCMenuItemFont::create("Mode");
		CC_BREAK_IF(! title4);
		title4->setEnabled(false);

		// 设置多选项效果。首先加入一个子选项（subItems），再加入一个包含了多个子菜单的数组。
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		CCMenuItemToggle *item4 = CCMenuItemToggle::createWithTarget(NULL, NULL,
			CCMenuItemFont::create("Easy"), NULL);
		CC_BREAK_IF(! item4);
	
		CCArray *more_items = CCArray::create(CCMenuItemFont::create("Normal"),CCMenuItemFont::create("Hard"), CCMenuItemFont::create("Nightmare"), NULL);

		//CCMultableArray<CCMenuItem *> *more_items =
		//	CCMultableArray<CCMenuItem *>::arrayWithObjects(CCMenuItemFont::itemWithString("Normal"),
		//	CCMenuItemFont::itemWithString("Hard"), CCMenuItemFont::itemWithString("Nightmare"), NULL);

		CC_BREAK_IF(! more_items);
		// TIP: you can manipulate the items like any other CCMutableArray
		item4->getSubItems()->addObjectsFromArray(more_items);
		// you can change the one of the items by doing this
		item4->setSelectedIndex(0);

		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		CCLabelBMFont *label = CCLabelBMFont::create("Go back", "font01.fnt");
		CC_BREAK_IF(! label);
		CCMenuItemLabel *back = CCMenuItemLabel::create(label, this, menu_selector(SettingsLayer::backCallback));
		CC_BREAK_IF(! back);
		back->setScale(0.8f);

		// 组合创建菜单层
		CCMenu *menu = CCMenu::create(title1, title2, item1, item2,
			title3, title4, item3, item4, back, NULL);
		CC_BREAK_IF(! menu);
		// 设置多列的菜单项布局
		menu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
		this->addChild(menu);

		// 手工微调一下最后一个菜单项的位置
		cocos2d::CCPoint cp_back = back->getPosition();
		cp_back.y -= 50.0f;
		back->setPosition(cp_back);

		bRet = true;
	} while (0);

	return bRet;
}

void SettingsLayer::backCallback(CCObject* pSender)
{
	CCScene *scene = MainScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2f, scene));
}
