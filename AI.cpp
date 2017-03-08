#include "AI.h"

bool AI::init()
{
	CCNode::init();
	scheduleUpdate();
	//�����л���ʱ�䣬���Խ�д�������ļ��������Ժ��޸���Ϸ�߼�
	schedule(schedule_selector(AI::genSmall), 1);
	schedule(schedule_selector(AI::genMiddle), 5);
	schedule(schedule_selector(AI::genBig), 30);

	_bulletBatchNode = CCSpriteBatchNode::create(IMAGE_Bullet);
	addChild(_bulletBatchNode);
	return true;
}
void AI::update(float)
{
	//���л�
	int count = _enemys-> count();
	for (int i = count - 1; i >= 0;--i)
	{
		Enemy* e = (Enemy*)_enemys->objectAtIndex(i);
		if (Util::isAllOutOfWindow(e))
		{
			e->removeFromParent();
			_enemys->removeObject(e);

		}
		else
		{
			e->shoot(_bulletFly,_bulletBox,_bulletBatchNode);
		}
	}
	count = _bulletFly->count();
	for (int i = count - 1; i >= 0;--i)
	{
		Bullet* b = (Bullet*)_bulletFly->objectAtIndex(i);
		if (Util::isAllOutOfWindow(b))
		{
			//b->removeFromParent();
			_bulletBox->addObject(b);
			_bulletFly->removeObject(b);
		}
	}
}

void AI::genEnemy(Enemy::TYPE type)
{
	Enemy* e = Enemy::create(type);
	addChild(e);
	//����ê���Ŀ����Ϊ�˷����������λ��
	e->setAnchorPoint(ccp(0, 0));
	//����λ��
	//Ϊ�л�����һ�����λ��
	float x = CCRANDOM_0_1()*(winSize.width-e->boundingBox().size.width);
	float y = winSize.height;
	e->setPosition(ccp(x, y));

	_enemys->addObject(e);   //����Ҫ���뵽��������
}

void AI::genSmall(float)
{
	genEnemy(Enemy::SMALL);
}
void AI::genMiddle(float)
{
	genEnemy(Enemy::MIDDLE);
}
void AI::genBig(float)
{
	genEnemy(Enemy::BIG);
}