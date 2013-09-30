#ifndef __HELP_LAYER_H__
#define __HELP_LAYER_H__

#include "cocos2d.h"

class HelpLayer : public cocos2d::CCLayer
{
public:
	HelpLayer(void);
	virtual ~HelpLayer(void);

	bool init(void);

	void backCallback(CCObject* pSender);

	CREATE_FUNC(HelpLayer);

	
};

#endif  // __HELP_LAYER_H__
