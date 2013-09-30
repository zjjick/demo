#include "MySprite.h"

USING_NS_CC;

MySprite::MySprite(void):canBoxMove(false),isFatherGW(false),glayer(NULL),isDoMove(false),reMoveTouch(false)
{
}

MySprite::~MySprite(void)
{
}

void MySprite::initGameLayer(GameLayer* layer)
{
	this->glayer = layer;
}

void MySprite::onEnter(void)
{
	CCSprite::onEnter();

	// 我们希望独占被“认领”的触摸事件，所以第3个参数传入true
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -101, true);
}

void MySprite::onExit(void)
{
	///CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);

	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

CCRect MySprite::rect(void)
{
	// 后面的比较是以锚点为标准的
	const CCSize& s = getTextureRect().size;
	const CCPoint& p = this->getAnchorPointInPoints();
	return CCRectMake(-p.x, -p.y, s.width, s.height);
}

bool MySprite::containsTouchLocation(CCTouch *touch)
{
	//CCPoint pos = touch->getLocationInView();
	CCPoint pos = convertTouchToNodeSpaceAR(touch);
	//return CCRect::CCRectContainsPoint(rect(), pos);
	return rect().containsPoint(pos);
}

bool MySprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(reMoveTouch)
		return false;
	if (! containsTouchLocation(pTouch))
		return false;
	oldPoint = this->getPosition();
	//自动收缩boxSprite
	canBoxMove = true;
	return true;
}

void MySprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(reMoveTouch)
		return;

	isDoMove = true;
	CCPoint touchPoint = pTouch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//这个位置是相对BoxSprite来说的，要把屏幕的坐标转换为BoxSprite的  369为boxSprite的宽度
	//touchPoint = ccp(touchPoint.x-(size.width-369)/2,touchPoint.y);
	if(canBoxMove && (!isFatherGW))
	{
		canBoxMove = false;
		glayer->OnBoxAutoOut(this);
		isFatherGW = true;
	}
	CCPoint gPos = glayer->gameWorld->getPosition();
	touchPoint = ccp(touchPoint.x-gPos.x, touchPoint.y-gPos.y);
	setPosition(touchPoint);
}

void MySprite::ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent)
{
	if(reMoveTouch)
		return;
	if(!isDoMove)
		return;
	isDoMove = false;
	CCPoint touchPoint = pTouch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
	CCPoint gPos = glayer->gameWorld->getPosition();
	touchPoint = ccp(touchPoint.x-gPos.x, touchPoint.y-gPos.y);
	//如果在光圈点(这里先随意设置),则放置精灵位置
	if(touchPoint.x<40 && touchPoint.y<40)
	{
		reMoveTouch = true;
		glayer->doActionAuto(this);
	}
	else
	{
		glayer->addMySpriteManager(this,oldPoint);
		isFatherGW = false;
	}
	//this->setPosition(oldPoint);
}

MySprite* MySprite::MySpriteWithBatchNode(cocos2d::CCSpriteBatchNode *batchNode, const cocos2d::CCRect& rect)
{
	MySprite *pobSprite = new MySprite();
	if (pobSprite && pobSprite->initWithTexture(batchNode->getTexture(), rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}

	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
