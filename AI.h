//#pragma once
#ifndef __AI_H__
#define __AI_H__
#include "Common.h"
#include "Enemy.h"
//���Ƶл��� ��������ʧ�����ǲ�������ײ��
class AI:public CCNode
{
public:
	CREATE_FUNC(AI);
	bool init();

	//�������ел�������
	CCArray* _enemys;
	//�������ел����ӵ�
	CCArray* _bulletFly;
	CCArray* _bulletBox;

	// �л��ӵ�����������
	CCSpriteBatchNode* _bulletBatchNode;
	//����һ���л�,���л��Ƿ�ɵ�������
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


