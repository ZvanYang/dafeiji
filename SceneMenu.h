
#ifndef __SceneMenu_H__
#define __SceneMenu_H__

#include "Common.h"
class SceneMenu :public CCLayer
{
public:
	CREATE_FUNC(SceneMenu);
	bool init();
	void initScrollMenu();
	void Back(CCObject*);

	bool ccTouchBegan(CCTouch *, CCEvent *){ return true; }
	void ccTouchEnded(CCTouch *t, CCEvent *);
	CCNode* _node;
	void adjustScrollView(float);
};

#endif