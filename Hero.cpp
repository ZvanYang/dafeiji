#include "Hero.h"

bool Hero::init(int id)
{
	//保存飞机的id，用于发射子弹，不同的飞机发射方式不同。
	_id = id;

	//获取这个飞机的基础信息，包括damage，hp，产生子弹的时间间隔，还有图片纹理
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(CFG_planeinfo);
	//战斗机的战斗力                                                                      
	const CCString* value = dict->valueForKey(Util::format(id + 1, "planedamageamount"));
	_damage = value->intValue();
	//战斗机的时间间隔
	value = dict->valueForKey(Util::format(id + 1, "planeshootspeedrate"));
	_shootCD = value->intValue();
	//战斗机的血
	value = dict->valueForKey(Util::format(id + 1, "plane","_hp"));
	_hp = value->intValue();
	//战斗机的图片纹理
	value = dict->valueForKey(Util::format(id + 1, "plane"));
	CCSprite::initWithFile(value->getCString());

	//专门发射子弹
	scheduleUpdate();
	_curCD = 0;
	return true;
}

bool Hero::canFire()
{
	//子弹发射控制
	_curCD++;
	if (_curCD != _shootCD)     //shootcd  是子弹的发射速度吧。。。
	{
		return false;
	}
	_curCD = 0;
	return true;
}

CCSprite* Hero::genBullet()   //就
{
	//CCSprite* bullet = CCSprite::create(IMAGE_Bullet);
	//优化的结果，用批处理的结点去创建子弹

	CCSprite* bullet;// = CCSprite::createWithTexture(_bulletBatchNode->getTexture());

	//如果子弹里面有子弹，，，如果没有的话，那么需要创建一个新的子弹
	if (_bulletsBox->count()>0)
	{
		bullet = (CCSprite*)_bulletsBox->lastObject();
		_bulletsBox->removeLastObject();
		_bulletFly->addObject(bullet);  //加到渲染树里面
		bullet->setVisible(true);
		return bullet;
	}

	// 如果没有，那么需要创建一个新的子弹
	bullet = CCSprite::createWithTexture(_bulletBatchNode->getTexture());
	//getParent()->addChild(bullet);    //就是加入到了scengame层里面离了
	_bulletBatchNode->addChild(bullet);
	_bulletFly->addObject(bullet);  //加到渲染树里面
	return bullet;
}

void Hero::fireUp(const CCPoint& delta)
{
	//发射子弹
	CCSprite* bullet =genBullet();
	//getParent()->addChild(bullet);   //就多了这一句代码，，，，耽误了我不时间呢，，，因为这个地方有点重复了
	bullet->setPosition(getPosition() + ccp(0, getContentSize().height / 2)+delta);   //子弹的位置和战斗机的位置相同
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
	fireUp(135,ptDelta+ccp(off,-off));  //y要向下偏移，x向右偏移
	fireUp(225, ptDelta + ccp(-off, -off));
	fireUp(315, ptDelta+ccp(-off, off));
}

void Hero::fire()
{
	//发射子弹，要根据不同的飞机来确定
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
	//遍历数组的同时，又要回收数组
	int count = _bulletFly->count();
	//当一个CCarray要在便利中，删除一些对象时，应该逆序遍历
	for (int i = count - 1; i >= 0;--i)
	{
		CCSprite* bullet = (CCSprite*)_bulletFly->objectAtIndex(i);
		//Util::isAllOutOfWindow(bullet);  //就是看看当前是不是在窗口里面，，然后delta就不要考虑了，
		//判断子弹是否整体除了窗口
		if (Util::isAllOutOfWindow(bullet))
	    {
			//删除子弹。
			_bulletFly->removeObjectAtIndex(i);
			_bulletsBox->addObject(bullet);
			//bullet->removeFromParent();
	     }
	}
}