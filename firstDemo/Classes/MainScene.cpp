#include "MainScene.h"
#include "SettingsLayer.h"
#include "LoadGameLayer.h"
#include  "HelpLayer.h"
#include "GameScene.h"

using namespace cocos2d;

CCScene* MainScene::scene()
{
    CCScene * scene = NULL;
    do 
    {     
        scene = CCScene::create();
        CC_BREAK_IF(! scene); 
        MainScene *layer = MainScene::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);

    return scene;
}

bool MainScene::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());	

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		CC_BREAK_IF(!pSprite);
		pSprite->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(pSprite,0);		
		//pSprite->runAction(CCBlink::actionWithDuration(3.0f, 2));
		pSprite->runAction(CCTintTo::create(1.2f, 0, 128, 255));	


		CCMenuItemFont *newGame = CCMenuItemFont::create("New Game", this, menu_selector(MainScene::onNewGame));
		CC_BREAK_IF(! newGame);
		CCMenuItemFont *loadGame = CCMenuItemFont::create("Load",this,menu_selector(MainScene::onLoadGame));
		CC_BREAK_IF(! loadGame);
		CCMenuItemFont *gameSettings = CCMenuItemFont::create("Option", this, menu_selector(MainScene::onSettings));
		CC_BREAK_IF(! gameSettings);
		CCMenuItemFont *help = CCMenuItemFont::create("Help",this,menu_selector(MainScene::onHelp));
		CC_BREAK_IF(! help);
		CCMenuItemFont *quit = CCMenuItemFont::create("Quit", this, menu_selector(MainScene::onQuit));

		CCMenu *menu = CCMenu::create(newGame, loadGame, gameSettings, help, quit, NULL);
		CC_BREAK_IF(! menu);	
		menu->alignItemsVertically();
		this->addChild(menu, 1, 2);

        bRet = true;
    } while (0);

    return bRet;
}

void MainScene::onNewGame(CCObject* pSender)
{
	//CCScene *scene = CCScene::create();
	//GameLayer* layer = GameLayer::create();
	//scene->addChild(layer);
	static int i = 1;
	i = (i+1)%5;
	CCScene *scene = GameScene::create();
	switch(i)
	{
		case 0:
			CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1.2f, scene));
			break;
		case 1:
			//ZoomFlipYUpOver:
			CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipY::create(1.2f, scene, kCCTransitionOrientationUpOver));
			break;
		case 2:
			CCDirector::sharedDirector()->replaceScene(CCTransitionSplitRows::create(1.2f, scene));
			break;
		case 3:
			//ZoomFlipAngularRightOver
			CCDirector::sharedDirector()->replaceScene(CCTransitionZoomFlipAngular::create
				(1.2f,scene,kCCTransitionOrientationRightOver));
			break;
		case 4:
			CCDirector::sharedDirector()->replaceScene(CCTransitionRotoZoom::create(1.2f, scene));
			break;
	}
	
}

void MainScene::onLoadGame(CCObject* pSender)
{
	CCScene *scene = CCScene::create();
	LoadGameLayer * layer = LoadGameLayer::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2f, scene));	
}

void MainScene::onSettings(CCObject* pSender)
{
	/*
	CCScene *scene = CCScene::create();
	SettingsLayer * layer = SettingsLayer::getInstance();
	layer->create();
	//SettingsLayer * layer = SettingsLayer::create();
	scene->addChild(layer);
	*/
	/*
	CCScene * scene = this->getScene();
	scene->removeChild(this);
	SettingsLayer * layer = SettingsLayer::create();
	scene->addChild(layer);
	*/
	CCScene *scene = CCScene::create();
	SettingsLayer * layer = SettingsLayer::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2f, scene));
}


void MainScene::onHelp(CCObject* pSender)
{
	CCScene *scene = CCScene::create();
	HelpLayer * layer = HelpLayer::create();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(CCTransitionShrinkGrow::create(1.2f, scene));
}

void MainScene::onQuit(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}