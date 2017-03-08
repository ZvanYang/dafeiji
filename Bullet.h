//#pragma once
#ifndef __Bullet_H__
#define __Bullet_H__

#include "Common.h"
class Bullet :public CCSprite
{
public:
	int _damage;
	static Bullet* create(int damage, CCSpriteBatchNode* batchNode)
	{
		Bullet* bullet = new Bullet;
		bullet->init(damage, batchNode);
		bullet->autorelease();
		return bullet;
	}
	bool init(int damage, CCSpriteBatchNode* batchNode)
	{
		//CCSprite::initWithFile(IMAGE_Bullet);
		CCSprite::initWithTexture(batchNode->getTexture());
		_damage = damage;
		return true;
	}
};
#endif

