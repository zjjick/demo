#ifndef __LOADGAME_LAYER_H__
#define __LOADGAME_LAYER_H__

#include "cocos2d.h"

class LoadGameLayer : public cocos2d::CCLayer
{
public:
	LoadGameLayer(void);
	virtual ~LoadGameLayer(void);

	bool init(void);

	void backCallback(CCObject* pSender);

	CREATE_FUNC(LoadGameLayer);

	
};

#endif  // __LOADGAME_LAYER_H__