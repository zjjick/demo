#ifndef __MYSPRITE_H__
#define __MYSPRITE_H__

#include "cocos2d.h"
#include "GameLayer.h"

class MySprite : public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate
{
public:
	MySprite(void);
	virtual ~MySprite(void);
	virtual void onEnter(void);
	virtual void onExit(void);
	void initGameLayer(GameLayer* layer);
	cocos2d::CCRect rect(void);
	bool containsTouchLocation(cocos2d::CCTouch *touch);

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	static MySprite* MySpriteWithBatchNode(cocos2d::CCSpriteBatchNode *batchNode, const cocos2d::CCRect& rect);

private:
	cocos2d::CCPoint oldPoint;
	GameLayer *glayer;
	bool canBoxMove;
	bool isFatherGW;
	bool isDoMove;
	bool reMoveTouch;
};

#endif  // __MYSPRITE_H__
