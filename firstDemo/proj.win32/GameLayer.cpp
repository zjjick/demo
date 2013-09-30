#include "GameLayer.h"
#include "MySprite.h"

USING_NS_CC;

enum {
    kTagGameWorld = 1,
    kTagMenu0 = 0,                       
    kTagMenu1 = 1,
};


GameLayer::GameLayer():boxSprite(NULL),isMoveOut(false),m_tBeginPos(CCPointZero),m_tLastPos(CCPointZero),
	summit(NULL),seqAction(NULL),manager(NULL),line(NULL),mySprite(NULL),isTouchMoving(false)
{
	canDoActionNext=false;
}

GameLayer::~GameLayer(void)
{
}

bool GameLayer::init(void)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());



		// Load level map
		gameWorld = CCTMXTiledMap::create("level/Level4.tmx");
		CCPoint pt12 = gameWorld->getAnchorPoint();
		CC_BREAK_IF(! gameWorld);
		this->addChild(gameWorld, 0, 9);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		screenWidth = size.width;
		screenHeight = size.height;
		tileSize = gameWorld->getTileSize().width;
		
		/*
		mySprite = CCSprite::create("me48.png",CCRectMake(0,0,48,48));
		CC_BREAK_IF(! mySprite);
		mySprite->setPosition(ccp(10,10));
		gameWorld->addChild(mySprite);
		*/

		this->setTouchEnabled(true);

		boxSprite = CCSprite::create("box.png");
		CCSize boxSize = boxSprite->getContentSize();
		boxSprite->setPosition(ccp(screenWidth/2,-boxSize.height/2));
		this->addChild(boxSprite);
		scheduleUpdate();	

		manager = CCSpriteBatchNode::create("me48.png", 10);
		boxSprite->addChild(manager);
		for(int i=0;i<4;i++)
		{
			MySprite * sprite = MySprite::MySpriteWithBatchNode(manager,CCRectMake(0,0,48,48));
			CC_BREAK_IF(! sprite);
			sprite->initGameLayer(this);
			manager->addChild(sprite);
			sprite->setPosition(ccp(i*80+60,180));
		}


		CCRect boxRect = boxSprite->getTextureRect();
		CCMenuItemFont *summit = CCMenuItemFont::create("Sumit",this,menu_selector(GameLayer::onBoxMoveOut));
		CC_BREAK_IF(!summit);
		summit->setFontSizeObj(30);
		CCMenu *menu = CCMenu::create(summit,NULL);
		boxSprite->addChild(menu);
		menu->setPosition(ccp(boxRect.getMidX(),boxRect.getMaxY()));
		//设置抗锯齿
		CCObject* pObj = NULL;
		CCARRAY_FOREACH(gameWorld->getChildren(), pObj)
		{
			CCSpriteBatchNode* child = (CCSpriteBatchNode*)pObj;
			if(!child)
				break;
			child->getTexture()->setAntiAliasTexParameters();
		}
		CCArray * array = CCArray::create();
		findLoad(array);
		CCArray * arrayActions = CCArray::create();
		CCObject* obj=NULL;
		CCARRAY_FOREACH(array,obj)
		{
			CCPoint* point = (CCPoint*)obj;
			CCActionInterval* move = CCMoveTo::create(1,*point);
			arrayActions->addObject((CCObject*)move);
		}
		//CCActionInterval* move
		CCFiniteTimeAction *action2= CCBlink::actionWithDuration(3.0f, 5);
		arrayActions->addObject(action2);		
		seqAction = CCSequence::create(arrayActions);
		//CCBlink::actionWithDuration(3.0f, 5)
	
		seqAction->setTag(1);
		seqAction->retain();


		CCMenuItemFont *fire = CCMenuItemFont::create("Fire",this,menu_selector(GameLayer::onFire));
		CC_BREAK_IF(!fire);
		fire->setFontSizeObj(20);
		CCMenu * menuFire = CCMenu::create(fire, NULL);
		menuFire->alignItemsVerticallyWithPadding(10);
		menuFire->setColor(ccc3(255,100,0));
		menuFire->setPosition(screenWidth-30,50);
		this->addChild(menuFire);
	

		bRet = true;
	} while (0);

	return bRet;
}

void GameLayer::findLoad(cocos2d::CCArray * arrayPoint)
{
	//CCPoint p = mySprite->getPosition();
	CCPoint p = ccp(10,10);
	int indexx = p.x/gameWorld->getTileSize().width;
	int indexy = gameWorld->getMapSize().height - p.y/gameWorld->getTileSize().height;
	CCPoint playerindex = ccp(indexx,indexy);
	bool findNext = true;
	int deadline = 0;
	while(findNext)
	{
		++deadline;
		CC_BREAK_IF(deadline==1000);		
		CCPoint nextPos = this->findNextTilePoint(indexx,indexy);
		if(nextPos.x>0 && nextPos.y>0)
		{
			m_tLastPos = ccp(indexx,indexy);
			indexx = nextPos.x;
			indexy = nextPos.y;
			cocos2d::CCPoint *point = new CCPoint(indexx*gameWorld->getTileSize().width,
				(gameWorld->getMapSize().height-indexy)*gameWorld->getTileSize().height);
			arrayPoint->addObject((cocos2d::CCObject*)point);
		}
		else
			break;
	}
}


float GameLayer::gameWorldWidth(void)
{
	return gameWorld->getMapSize().width * tileSize;
}

float GameLayer::gameWorldHeight(void)
{
	return gameWorld->getMapSize().height * tileSize;
}




void GameLayer::registerWithTouchDispatcher(void)
{
	//为了只响应按钮，
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-100,false);
	//CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,INT_MIN+1);
}



void GameLayer::update(float dt)
{
	/*
	return;
	static float temp =0;
	static float  all = 0;
	all += dt;
	if( ( ( (int)all )/10) > ( ( (int)temp )/10))
	{
		temp = all;
	}
	*/

	//碰撞
    //if ( CCRect::CCRectIntersectsRect(a->boundingBox(), b->boundingBox()) )
	//CCRect::CCRectIntersectsRect(mySprite->boundingBox(),	
	//CCRect mySpriteRect = mySprite->boundingBox();
	if(mySprite)
	{
		CCPoint p = mySprite->getPosition();
		if(p.x<0 || p.x>gameWorldWidth() || p.y<0 || p.y>gameWorldHeight())
		{
			//执行某个动作
			gameWorld->removeChild(mySprite,true);
			mySprite = NULL;
		}
	}
}



cocos2d::CCPoint GameLayer::findNextTilePoint(float x, float y)
{
	//理论要八个点 现在只取四个试验
	//以当前这个点来推断下一个点
	cocos2d::CCPoint step = ccp(x-1,y);  //左
	if(isLoadMaterial(step))
		return step;
	step = ccp(x+1,y); //右
	if(isLoadMaterial(step))
		return step;
	step = ccp(x,y-1); //上
	if(isLoadMaterial(step))
		return step;
	step = ccp(x,y+1); //下
	if(isLoadMaterial(step))
		return step;
	return ccp(-1,-1);
}

bool GameLayer::isLoadMaterial(cocos2d::CCPoint step)
{
	if(step.x>0 && step.y>0 && (step.x < gameWorld->getMapSize().width) && (step.y < gameWorld->getMapSize().height)
		&& !(step.x==m_tLastPos.x && step.y == m_tLastPos.y))
	{
		cocos2d::CCTMXLayer * layer = gameWorld->layerNamed("layer1");
		int tilegid = layer->tileGIDAt(step);
		if(tilegid<=0)
			return false;
		const CCString * mvalue = gameWorld->propertiesForGID(tilegid)->valueForKey("material");
		int mv =mvalue->intValue();
		if(mv==1)
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_tBeginPos = pTouch->getLocation();
	schedule(schedule_selector(GameLayer::touchUpdateOnce), 0.2f);
	return true;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(isMoveOut)
		return;
	isTouchMoving = true;

	CCPoint beginPos = pTouch->getPreviousLocation();
    CCPoint touchLocation = pTouch->getLocation();    
    float nMoveY = touchLocation.y - beginPos.y;
	float nMoveX = touchLocation.x - beginPos.x;

	CCPoint oldPos  = gameWorld->getPosition();
	float PosX = oldPos.x + nMoveX;
	float PosY = oldPos.y + nMoveY;
	if(PosX >0)
		PosX = 0;
	if(PosY > 0)
		PosY = 0;
	if(PosX <-(this->gameWorldWidth()-screenWidth))
		PosX = -(this->gameWorldWidth() - screenWidth);
	if (PosY < -(this->gameWorldHeight() - screenHeight))
		PosY = -(this->gameWorldHeight() - screenHeight);
	if(PosX == oldPos.x && PosY == oldPos.y)
	{
		this->unscheduleAllSelectors();
	}
	else
		gameWorld->setPosition(PosX, PosY);

}


void GameLayer::ccTouchEnded(CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(isMoveOut)
		return;
	isTouchMoving = false;
	CCPoint endPos = pTouch->getLocation();
	
	if( (endPos.x == m_tBeginPos.x) && (endPos.y == m_tBeginPos.y) )
	{
	}
	//this->unschedule(schedule_selector(GameLayer::touchUpdate));
	this->unscheduleAllSelectors(); 
	scheduleUpdate();
}


void GameLayer::ccTouchCancelled(CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	//执行暂停操作
	//NoTouchLayer * layer = NoTouchLayer::create();
	//this->addChild(layer);
}

void GameLayer::touchUpdateOnce(float dt)
{
	this->unschedule(schedule_selector(GameLayer::touchUpdateOnce));
	schedule(schedule_selector(GameLayer::touchUpdate), 0.03f);
}

void GameLayer::touchUpdate(float dt)
{
	if(isTouchMoving)
		return;
	if(line!=NULL)
	{
		float rotation = line->getRotation();
		//左屏-2,右屏+2
		if(m_tBeginPos.x<screenWidth/2)
			line->setRotation(rotation-1);
		else
			line->setRotation(rotation+1);
	}
}


void GameLayer::onBoxMoveOut(CCObject* pSender)
{
	if(isSpriteRunning())
		return;
	CCSize  s = boxSprite->getContentSize();
	if(isMoveOut)
	{
		boxSprite->runAction(cocos2d::CCMoveTo::create(0.3f, ccp(screenWidth/2, -s.height/2)));
		isMoveOut = false;
	}
	else
	{
		boxSprite->runAction(cocos2d::CCMoveTo::create(0.3f, ccp(screenWidth/2, s.height/2)));
		isMoveOut =true;
	}
}

//给MySprite用
void GameLayer::OnBoxAutoOut(MySprite * sprite)
{
	onBoxMoveOut(summit);
	if(sprite->getParent()==manager)
		manager->removeChild(sprite,true);
	if(sprite->getParent() == NULL)
	{
		gameWorld->addChild(sprite);
		mySprite = sprite;
	}
}

//给MySprite用
void GameLayer::addMySpriteManager(MySprite * sprite,cocos2d::CCPoint point)
{
	if(sprite->getParent() == gameWorld)
	{
		gameWorld->removeChild(sprite,true);
		mySprite = NULL;
	}
	if(sprite->getParent() == NULL)
		manager->addChild(sprite);
	sprite->setPosition(point);
}

//给MySprite用
void GameLayer::doActionAuto(MySprite * sprite)
{
	line = CCSprite::create("line1.png");
	//CCAnimation *animation = CCAnimation::create();
	//animation->setDelayPerUnit(0.1f);
	//animation->addSpriteFrameWithFileName("line1.png");
	//animation->addSpriteFrameWithFileName("line2.png");
	//CCAnimate *animate = CCAnimate::create(animation);
	//line->runAction(CCRepeatForever::create(animate));
	sprite->addChild(line,0,1);
	line->setAnchorPoint(ccp(0.5,0.05));
	line->setPosition(ccp(20,20));
	sprite->runAction(seqAction);
}

void GameLayer::onFire(CCObject* pSender)
{
	if(line && mySprite)
	{
		int rotation = (int)(line->getRotation())%360;
		float x =0;
		if(rotation>=0 && rotation<=180)
			x = 1000;
		else
			x= -1000;
		rotation=90-rotation; //转换为四象上
		float y = x*std::tan(float(rotation*M_PI/180)); 
		mySprite->stopActionByTag(1);
		CCPoint p = mySprite->getPosition();
		p = ccp(x+p.x,y+p.y);
		float duration = std::sqrt(std::pow(p.x,2)+std::pow(p.y,2));
		mySprite->removeChildByTag(1,true);
		line = NULL;
		mySprite->runAction(CCMoveTo::create(duration/300,p));
	}
}

bool GameLayer::isSpriteRunning()
{
	if(line || mySprite)
		return true;
	else
		return false;
}