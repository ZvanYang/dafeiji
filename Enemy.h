//#pragma once
#ifndef __Enemy_H__
#define __Enemy_H__
#include "Common.h"
#include "Bullet.h"

class Enemy:public CCSprite
{
public:
	enum TYPE{ SMALL, MIDDLE, BIG };
	int _hp;
	TYPE _type;
	int _speed;
	int _damage;
	int _shootCD;
	int _curCD;
	int _score;

	static Enemy* create(TYPE type)
	{
		Enemy* enemy = new Enemy;
		enemy->init(type);
		enemy->autorelease();
		return enemy;

	}
	bool init(TYPE type)
	{
		CCSprite::initWithFile(Util::format(type+1,"Enemy",".png"));
		_type = type;
		int hp[] = { 10, 50, 200 };
		_hp = hp[type];
		//设置小飞机256是让小飞机在4秒内从窗口上方落下
		int speed[] = { 256, 128, 50 };
		_speed = speed[type];

		int damage[] = { 20, 40, 100 };
		_damage = damage[type];

		_curCD = 0;
		int shootCD[] = { 60, 120, 250 };
		_shootCD = shootCD[type];

		int score[] = { 100, 2000, 3000 };
		_score = score[type];
		//运动敌机
		scheduleUpdate();

		return true;
	}
	void update(float dt)
	{
		setPositionY(getPositionY() - dt*_speed);
	}

	bool canFire()
	{
		_curCD++;
		if (_curCD != _shootCD)
		{
			return false;
		}
		_curCD=0;
		return true;
	}

	void fire(CCArray* bulletsFly, CCArray* bulletsBox, CCSpriteBatchNode* batchNode)
	{
		//Bullet* b = Bullet::create(_damage);
		//b->setColor(ccc3(255, 255, 0));
		//bullets->addObject(b);
		//getParent()->addChild(b);

		Bullet* b;
		if (bulletsBox->count() > 0)
		{
			b = (Bullet*)bulletsBox->lastObject();
			bulletsBox->removeLastObject();
			b->setVisible(true);
		}
		else
		{
			b = Bullet::create(_damage, batchNode);
			b->setColor(ccc3(255, 0, 0));

			//getParent()->addChild(b);
			// 优化
			batchNode->addChild(b);
		}


		bulletsFly->addObject(b);



		float off = this->boundingBox().size.width / 2;
		b->setPosition(this->getPosition() + ccp(off, 0));
		b->runAction(
			CCMoveBy::create(winSize.height / (_speed * 2), ccp(0, -winSize.height))
			);
	}

	//敌机发射子弹的接口
	void shoot(CCArray* bulletsFly,CCArray* bulletsBox,CCSpriteBatchNode* batchNode)
	{
		//如果敌机已经死亡，就不用再发射子弹了
		if (_hp<=0)
		{
			return;
		}
		if (canFire())
		{
			fire(bulletsFly, bulletsBox, batchNode);
		}
	}

	void killed()
	{
		//enemys->removeAllObjects();  //执行一个爆炸动画,然后删除对象
		//CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
		//cache->addSpriteFramesWithFile(ANI_PLIST_PFBoom);
		//CCArray* frames = CCArray::create();
		//for (int i = 0; i < 18;++i)
		//{
		//	char* frameName = Util::format(i + 1, "Boom_", ".png");
		//	CCSpriteFrame* frame = cache->spriteFrameByName(frameName);
		//	frames->addObject(frame);

		//}
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(ANI_ENEMY_BOOM);
		CCAnimate* animate = CCAnimate::create(animation);
		
		CCRemoveSelf* remove = CCRemoveSelf::create();   //自杀
		this->runAction(CCSequence::create(animate,remove,NULL));
	}
};


#endif

