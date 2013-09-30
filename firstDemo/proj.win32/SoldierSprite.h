/*
#ifndef __SOLDIER_SPRITE_H__
#define __SOLDIER_SPRITE_H__

#include "cocos2d.h"

class GameLayer;


class SoldierSprite : public cocos2d::CCSprite
{
public:
	SoldierSprite(void);
	virtual ~SoldierSprite(void);


	// TODO:看看其他静态函数是怎么写的
	static SoldierSprite* soldierWithLayer(GameLayer *layer, const char *imageFile);

	void tankInit(void);
	void setLayer(GameLayer *layer);
	
	void activate(void);	
	void onFire(GameLayer *layer);

};

#endif  // __SOLDIER_SPRITE_H__

*/