#ifndef __NOTOUCH_LAYER_H__
#define __NOTOUCH_LAYER_H__

#include "cocos2d.h"

class NoTouchLayer : public cocos2d::CCLayer
{
public:

	NoTouchLayer(void);
	virtual ~NoTouchLayer(void);
	bool init(void);
	CREATE_FUNC(NoTouchLayer);
	
	virtual void registerWithTouchDispatcher();

    virtual bool ccTouchBegan (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded (cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
};

#endif  // __NOTOUCH_LAYER_H__