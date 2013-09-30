#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class MySprite;
class GameLayer : public cocos2d::CCLayer
{
	/*
	struct POINTXY
	{
		float fx;
		float fy;
		POINTXY()
		{
			::memset(this, 0L, sizeof(POINTXY));
		}
	};
	*/

public:
	GameLayer(void);
	virtual ~GameLayer(void);
	virtual bool init(void);
	CREATE_FUNC(GameLayer);

	float gameWorldWidth(void);
	float gameWorldHeight(void);
	void onBoxMoveOut(CCObject* pSender);
	void spriteCallback(CCObject* pSender);

	void update(float dt);
	cocos2d::CCPoint findNextTilePoint(float x, float y);
	void findLoad(cocos2d::CCArray* array);
	bool isLoadMaterial(cocos2d::CCPoint step);
	void OnBoxAutoOut(MySprite * sprite);
	void addMySpriteManager(MySprite * sprite,cocos2d::CCPoint point);
	void doActionAuto(MySprite * sprite);
	void onFire(CCObject* pSender);
	bool isSpriteRunning();

public:
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void touchUpdate(float dt);
	void touchUpdateOnce(float dt);

public:
	cocos2d::CCTMXTiledMap *gameWorld;

private:
	float screenWidth, screenHeight, tileSize;
	float viewOrgX, viewOrgY, viewOrgZ;
	float mapX, mapY;
	cocos2d::CCSprite *boxSprite;
	cocos2d::CCSprite *line;
	cocos2d::CCSprite *mySprite;
	bool isMoveOut;
	
	bool isTouchMoving;
	cocos2d::CCArray *soldierList;
	cocos2d::CCPoint m_tBeginPos;
	//以下测试 临时处理
//	cocos2d::CCSprite * mySprite;
	cocos2d::CCPoint m_tLastPos;

	cocos2d::CCMenuItemFont *summit;
	cocos2d::CCSpriteBatchNode *manager;
	cocos2d::CCFiniteTimeAction * seqAction;
	bool canDoActionNext;
};

#endif  // __GAME_LAYER_H__
