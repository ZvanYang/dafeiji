//#pragma once
#ifndef __AI_H__
#define __AI_H__
#include "Common.h"
#include "Enemy.h"
//控制敌机的 产生和消失，但是不负责碰撞。
class AI:public CCNode
{
public:
	CREATE_FUNC(AI);
	bool init();

	//保存所有敌机的数组
	CCArray* _enemys;
	//保存所有敌机的子弹
	CCArray* _bulletFly;
	CCArray* _bulletBox;

	// 敌机子弹的批处理精灵
	CCSpriteBatchNode* _bulletBatchNode;
	//产生一个敌机,检测敌机是否飞到窗口外
	void update(float);
	void onEnter()
	{
		CCNode::onEnter();
		_enemys = CCArray::create();
		_enemys->retain();

		_bulletFly = CCArray::create();
		_bulletFly->retain();

		_bulletBox = CCArray::create();
		_bulletBox->retain();
	}
	void onExit()
	{
		CCNode::onExit();
		_enemys->release();
		_bulletFly->release();
		_bulletBox->release();
	}

	void genSmall(float);
	void genMiddle(float);
	void genBig(float);

	void genEnemy(Enemy::TYPE type);

};


#endif


