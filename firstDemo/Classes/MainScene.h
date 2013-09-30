#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class MainScene : public cocos2d::CCLayer
{
public:

    virtual bool init();  
    static cocos2d::CCScene* scene();

	void onNewGame(CCObject* pSender);
	void onLoadGame(CCObject* pSender);
	void onSettings(CCObject* pSender);
	void onHelp(CCObject* pSender);
	void onQuit(CCObject* pSender);


    // implement the "static node()" method manually
    CREATE_FUNC(MainScene);
};

#endif  // __MAIN_SCENE_H__