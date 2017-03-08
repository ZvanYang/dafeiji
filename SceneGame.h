
#ifndef __SceneGame_H__
#define __SceneGame_H__

#include "Common.h"
#include "Hero.h"
#include "AI.h"
class SceneGame :public CCLayer
{
public:
	//CREATE_FUNC(SceneGame);
	//bool init();
	static SceneGame* create(int planeID)   //因为需要一个ID，所以吧，不能用系统的create函数
	{
		SceneGame* game = new SceneGame();
		game->init(planeID);
		game->autorelease();
		return game;
	}

	void preLoadResource();

	bool init(int planeID);
	void Back(CCObject*);
	void addHeroPlane(int id);
	void creatEnemyAI();
	void addLabels();
	Hero* _hero;
	AI* _ai;

	CCLabelAtlas* _score;
	CCLabelAtlas* _hp;

	bool ccTouchBegan(CCTouch *t, CCEvent*)
	{ 
		//return _hero->boundingBox().containsPoint(t->getLocation());
		return true;   //这种情况的话，是点到哪里，也都能动啊。
	}
	void ccTouchMoved(CCTouch *t, CCEvent*);
	void update(float dt);
	void gameOver();



	void onEnter()
	{
		CCLayer::onEnter();
		//预先加载资源
		preLoadResource();

	}
	void onExit()
	{
		CCLayer::onExit();
		//如果资源在下一个场景不用，那么要清除这些不用的资源，一面占用过多的内存
		CCAnimationCache::sharedAnimationCache()->removeAnimationByName(ANI_ENEMY_BOOM);

		//或者清空缓存中的所有资源
		CCAnimationCache::sharedAnimationCache()->purgeSharedAnimationCache();
		//分数，北京音乐什么的就不用了
		CCTextureCache::sharedTextureCache()->purgeSharedTextureCache();
		CCSpriteFrameCache::sharedSpriteFrameCache()->purgeSharedSpriteFrameCache();
	}
};


#endif


