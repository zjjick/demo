#include "NoTouchLayer.h"

USING_NS_CC;

NoTouchLayer::NoTouchLayer(void)
{
}

NoTouchLayer::~NoTouchLayer(void)
{
}

bool NoTouchLayer::init(void)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		pSprite->setPosition(ccp(size.width/2,size.height/2));
		pSprite->setOpacity(200);
		this->addChild(pSprite,0);	
		setTouchEnabled(true);
		bRet = true;
	} while (0);

	return bRet;
}

void NoTouchLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,INT_MIN,true);
}



bool NoTouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
//	this->release();
	return true;
} 


void NoTouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{ 

}

void NoTouchLayer::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{

}
