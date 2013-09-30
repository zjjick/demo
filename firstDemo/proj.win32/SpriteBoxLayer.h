#ifndef __SPRITEBOX_LAYER_H__
#define __SPRITEBOX_LAYER_H__

#include "cocos2d.h"

class SpriteBoxLayer : public cocos2d::CCLayer
{
public:
	SpriteBoxLayer(void);
	virtual ~SpriteBoxLayer(void);

	bool init(void);

	void backCallback(CCObject* pSender);

	CREATE_FUNC(SpriteBoxLayer);

	
};

#endif  // __SPRITEBOX_LAYER_H__
