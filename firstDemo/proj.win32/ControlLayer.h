#ifndef __CONTROL_LAYER_H__
#define __CONTROL_LAYER_H__

#include "cocos2d.h"

class ControlLayer : public cocos2d::CCLayer
{
public:
	ControlLayer(void);
	virtual ~ControlLayer(void);

	bool init(void);

	void backCallback(CCObject* pSender);
	void onGoBack(CCObject* pSender);
	void onReStart(CCObject * pSender);
	void onPause(CCObject * pSender);
	void onFire(CCObject *pSender);

	CREATE_FUNC(ControlLayer);

	
};

#endif  // __CONTROL_LAYER_H__
