#include "Hero.h"

bool Hero::init(int id)
{
	//����ɻ���id�����ڷ����ӵ�����ͬ�ķɻ����䷽ʽ��ͬ��
	_id = id;

	//��ȡ����ɻ��Ļ�����Ϣ������damage��hp�������ӵ���ʱ����������ͼƬ����
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(CFG_planeinfo);
	//ս������ս����                                                                      
	const CCString* value = dict->valueForKey(Util::format(id + 1, "planedamageamount"));
	_damage = value->intValue();
	//ս������ʱ����
	value = dict->valueForKey(Util::format(id + 1, "planeshootspeedrate"));
	_shootCD = value->intValue();
	//ս������Ѫ
	value = dict->valueForKey(Util::format(id + 1, "plane","_hp"));
	_hp = value->intValue();
	//ս������ͼƬ����
	value = dict->valueForKey(Util::format(id + 1, "plane"));
	CCSprite::initWithFile(value->getCString());

	//ר�ŷ����ӵ�
	scheduleUpdate();
	_curCD = 0;
	return true;
}

bool Hero::canFire()
{
	//�ӵ��������
	_curCD++;
	if (_curCD != _shootCD)     //shootcd  ���ӵ��ķ����ٶȰɡ�����
	{
		return false;
	}
	_curCD = 0;
	return true;
}

CCSprite* Hero::genBullet()   //��
{
	//CCSprite* bullet = CCSprite::create(IMAGE_Bullet);
	//�Ż��Ľ������������Ľ��ȥ�����ӵ�

	CCSprite* bullet;// = CCSprite::createWithTexture(_bulletBatchNode->getTexture());

	//����ӵ��������ӵ����������û�еĻ�����ô��Ҫ����һ���µ��ӵ�
	if (_bulletsBox->count()>0)
	{
		bullet = (CCSprite*)_bulletsBox->lastObject();
		_bulletsBox->removeLastObject();
		_bulletFly->addObject(bullet);  //�ӵ���Ⱦ������
		bullet->setVisible(true);
		return bullet;
	}

	// ���û�У���ô��Ҫ����һ���µ��ӵ�
	bullet = CCSprite::createWithTexture(_bulletBatchNode->getTexture());
	//getParent()->addChild(bullet);    //���Ǽ��뵽��scengame����������
	_bulletBatchNode->addChild(bullet);
	_bulletFly->addObject(bullet);  //�ӵ���Ⱦ������
	return bullet;
}

void Hero::fireUp(const CCPoint& delta)
{
	//�����ӵ�
	CCSprite* bullet =genBullet();
	//getParent()->addChild(bullet);   //�Ͷ�����һ����룬�������������Ҳ�ʱ���أ�������Ϊ����ط��е��ظ���
	bullet->setPosition(getPosition() + ccp(0, getContentSize().height / 2)+delta);   //�ӵ���λ�ú�ս������λ����ͬ
	bullet->stopAllActions();
	bullet->runAction(CCMoveBy::create(4, ccp(0, winSize.height)));
	bullet->setRotation(0);
}

void Hero::fireUp(int angle,const CCPoint& delta)
{
	float x = sinf(angle*M_PI / 180)*winSize.height;
	float y = cosf(angle*M_PI / 180)*winSize.height;

	CCSprite* bullet = genBullet();
	//getParent()->addChild(bullet);
	bullet->setPosition(getPosition() + ccp(0, getContentSize().height / 2)+delta);
	bullet->stopAllActions();
	bullet->runAction(CCMoveBy::create(4, ccp(x, y)));
	bullet->setRotation(angle);
}

void Hero::fire0()
{
	fireUp();
}
void Hero::fire1()
{
	fireUp();
	fireUp(ccp(getContentSize().width / 4, -getContentSize().height/3));
	fireUp(ccp(-getContentSize().width / 4, -getContentSize().height/3));
}
void Hero::fire2()
{
	fireUp();
	fireUp(30);
	fireUp(-30);
}
void Hero::fire3()
{
	CCPoint ptDelta = ccp(0, -getContentSize().height / 2);
	float off = getContentSize().width / 2;
	fireUp(0);
	fireUp(90,ptDelta+ccp(off,0));
	fireUp(180,ptDelta+ptDelta);
	fireUp(270, ptDelta+ccp(-off,0));

}
void Hero::fire4()
{
	CCPoint ptDelta = ccp(0, -getContentSize().height / 2);
	float off = getContentSize().height / 4;
	fireUp(45,ptDelta+ccp(off,off));
	fireUp(135,ptDelta+ccp(off,-off));  //yҪ����ƫ�ƣ�x����ƫ��
	fireUp(225, ptDelta + ccp(-off, -off));
	fireUp(315, ptDelta+ccp(-off, off));
}

void Hero::fire()
{
	//�����ӵ���Ҫ���ݲ�ͬ�ķɻ���ȷ��
	switch (_id)
	{
	case 0:
		fire0();
		break;
	case 1:
		fire1();
		break;
	case 2:
		fire2();
		break;
	case 3:
		fire3();
		break;
	case 4:
		fire4();
		break;

	}
}

void Hero::update(float)
{
	if (canFire())
		fire();
	checkBullets();

}
void Hero::checkBullets()
{
	//���������ͬʱ����Ҫ��������
	int count = _bulletFly->count();
	//��һ��CCarrayҪ�ڱ����У�ɾ��һЩ����ʱ��Ӧ���������
	for (int i = count - 1; i >= 0;--i)
	{
		CCSprite* bullet = (CCSprite*)_bulletFly->objectAtIndex(i);
		//Util::isAllOutOfWindow(bullet);  //���ǿ�����ǰ�ǲ����ڴ������棬��Ȼ��delta�Ͳ�Ҫ�����ˣ�
		//�ж��ӵ��Ƿ�������˴���
		if (Util::isAllOutOfWindow(bullet))
	    {
			//ɾ���ӵ���
			_bulletFly->removeObjectAtIndex(i);
			_bulletsBox->addObject(bullet);
			//bullet->removeFromParent();
	     }
	}
}