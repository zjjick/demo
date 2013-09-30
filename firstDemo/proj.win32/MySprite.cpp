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

	// ����ϣ����ռ�������족�Ĵ����¼������Ե�3����������true
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
	// ����ıȽ�����ê��Ϊ��׼��
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
	//�Զ�����boxSprite
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
	//���λ�������BoxSprite��˵�ģ�Ҫ����Ļ������ת��ΪBoxSprite��  369ΪboxSprite�Ŀ��
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
	//����ڹ�Ȧ��(��������������),����þ���λ��
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
