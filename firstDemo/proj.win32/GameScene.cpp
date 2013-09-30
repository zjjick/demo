#include "GameScene.h"
#include "ControlLayer.h"
#include "GameLayer.h"

USING_NS_CC;

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

bool GameScene::init(void)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCScene::init());

		/*
		GameLayer *game_layer = GameLayer::create();
		CC_BREAK_IF(! game_layer);
		ControlLayer *control_layer = ControlLayer::create();
		CC_BREAK_IF(! control_layer);
		control_layer->game_layer = game_layer;

		this->addChild(game_layer);
		this->addChild(control_layer);
		*/
		GameLayer *gameLayer = GameLayer::create();
		CC_BREAK_IF(! gameLayer);
		this->addChild(gameLayer,10);
		
		ControlLayer *controlLayer = ControlLayer::create();
		CC_BREAK_IF(! controlLayer);
		//control_layer->game_layer = game_layer;
		this->addChild(controlLayer,11);

		bRet = true;
	} while (0);

	return bRet;
}
