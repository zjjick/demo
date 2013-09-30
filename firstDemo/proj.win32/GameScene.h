#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	virtual ~GameScene(void);

	virtual bool init(void);

	CREATE_FUNC(GameScene);
};

#endif  // __GAME_SCENE_H__
