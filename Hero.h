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

	CCSprite* genBullet();   //������������������bullet

	void checkBullets();

	CCArray* _bulletFly;  //������ɵ��ӵ�
	CCArray* _bulletsBox;   //�ӵ�ϻ������ӵ�
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
		_bulletFly->release();   //�ͷ��ڴ棬�����ͷ��ӵ�
		_bulletsBox->release();
	}
	//void killed()
	//{

	//}
};
#endif


