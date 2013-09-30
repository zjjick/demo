#include "SpriteBoxLayer.h"

using namespace cocos2d;

SpriteBoxLayer::SpriteBoxLayer(void)
{
}

SpriteBoxLayer::~SpriteBoxLayer(void)
{
}

bool SpriteBoxLayer::init(void)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void SpriteBoxLayer::backCallback(CCObject* pSender)
{

}
