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

		// ���ñ�������
		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		// ��һ������״̬�Ĳ˵�����Ϊ����
		CCMenuItemFont *title1 = CCMenuItemFont::create("Sound");
		CC_BREAK_IF(! title1);
		title1->setEnabled(false);

		// ����ѡ�����壨���ò�ͬ��������ʾ����������
		CCMenuItemFont::setFontName("Marker Felt");
		CCMenuItemFont::setFontSize(26);
		// ���ÿ��л��Ĳ˵���˵�״̬�������ء�
		CCMenuItemToggle *item1 = CCMenuItemToggle::createWithTarget(NULL, NULL,
			CCMenuItemFont::create("On"), CCMenuItemFont::create("Off"), NULL);
		CC_BREAK_IF(! item1);

		// ���ñ�������
		CCMenuItemFont::setFontName("American Typewriter");
		CCMenuItemFont::setFontSize(18);
		CCMenuItemFont *title2 = CCMenuItemFont::create("Music");
		CC_BREAK_IF(! title2);
		title2->setEnabled(false);

		// ����ѡ������
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

		// ���ö�ѡ��Ч�������ȼ���һ����ѡ�subItems�����ټ���һ�������˶���Ӳ˵������顣
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

		// ��ϴ����˵���
		CCMenu *menu = CCMenu::create(title1, title2, item1, item2,
			title3, title4, item3, item4, back, NULL);
		CC_BREAK_IF(! menu);
		// ���ö��еĲ˵����
		menu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
		this->addChild(menu);

		// �ֹ�΢��һ�����һ���˵����λ��
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
