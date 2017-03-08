//#pragma once
#ifndef __Hero_H__
#define __Hero_H__
#include "Common.h"
class Hero:public CCSprite
{
public:
	static Hero* create(int id)
	{
		Hero* h = new Hero;
		h->init(id);
		h->autorelease();
		return h;
	}
	bool init(int id);
	int _damage;
	int _shootCD;
	int _curCD;
	int _hp;
	int _id;

	CCSpriteBatchNode* _bulletBatchNode;

	void update(float);



	bool canFire();
	void fire();
	void fire0();
	void fire1();
	void fire2();
	void fire3();
	void fire4();

	void fireUp(const CCPoint& deltaStartPosition = ccp(0,0));
	void fireUp(int angle,const CCPoint& delta = ccp(0,0));

	CCSprite* genBullet();   //这个对象就是用来产生bullet

	void checkBullets();

	CCArray* _bulletFly;  //在外面飞的子弹
	CCArray* _bulletsBox;   //子弹匣里面的子弹
	void onEnter()
	{
		CCSprite::onEnter();
	   _bulletFly = CCArray::create();
	   _bulletFly->retain();

	   _bulletsBox=CCArray::create();
	   _bulletsBox->retain();

	}
	void onExit()
	{
		CCSprite::onExit();
		_bulletFly->release();   //释放内存，就是释放子弹
		_bulletsBox->release();
	}
	//void killed()
	//{

	//}
};
#endif


