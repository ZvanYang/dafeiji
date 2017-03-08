
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
	static SceneGame* create(int planeID)   //��Ϊ��Ҫһ��ID�����԰ɣ�������ϵͳ��create����
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
		return true;   //��������Ļ����ǵ㵽���Ҳ���ܶ�����
	}
	void ccTouchMoved(CCTouch *t, CCEvent*);
	void update(float dt);
	void gameOver();



	void onEnter()
	{
		CCLayer::onEnter();
		//Ԥ�ȼ�����Դ
		preLoadResource();

	}
	void onExit()
	{
		CCLayer::onExit();
		//�����Դ����һ���������ã���ôҪ�����Щ���õ���Դ��һ��ռ�ù�����ڴ�
		CCAnimationCache::sharedAnimationCache()->removeAnimationByName(ANI_ENEMY_BOOM);

		//������ջ����е�������Դ
		CCAnimationCache::sharedAnimationCache()->purgeSharedAnimationCache();
		//��������������ʲô�ľͲ�����
		CCTextureCache::sharedTextureCache()->purgeSharedTextureCache();
		CCSpriteFrameCache::sharedSpriteFrameCache()->purgeSharedSpriteFrameCache();
	}
};


#endif


