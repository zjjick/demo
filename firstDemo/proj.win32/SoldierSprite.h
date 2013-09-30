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


	// TODO:����������̬��������ôд��
	static SoldierSprite* soldierWithLayer(GameLayer *layer, const char *imageFile);

	void tankInit(void);
	void setLayer(GameLayer *layer);
	
	void activate(void);	
	void onFire(GameLayer *layer);

};

#endif  // __SOLDIER_SPRITE_H__

*/