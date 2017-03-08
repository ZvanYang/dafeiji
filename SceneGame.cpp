#include "SceneGame.h"
#include "ScrollBackground.h"
#include "SceneMenu.h"
#include "SceneScore.h"
#include "SimpleAudioEngine.h"
//#include "Enemy.h"
bool SceneGame::init(int planeID)
{
	//CCLayer::init();

	//加入一个滚动背景
	ScrollBackground* bg = ScrollBackground::create();
	addChild(bg);
	
	//右下角的返回按钮
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneGame::Back));

	//创建一个英雄飞机
	addHeroPlane(planeID);
	//使能touch
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	//创建敌机AI
	creatEnemyAI();

	//碰撞检测
	scheduleUpdate();

	//增加label显示信息
	// 增加Label显示信息
	addLabels();
	return true;
}

void SceneGame::preLoadResource()
{
	//执行爆炸动画，然后删除对象
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(ANI_PLIST_PFBoom);
	CCArray* frames = CCArray::create();
	for (int i = 0; i < 18;++i)
	{
		char* frameName = Util::format(i + 1, "Boom_", ".png");
		CCSpriteFrame* frame = cache->spriteFrameByName(frameName);
		frames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, 0.05f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, ANI_ENEMY_BOOM);
	//预加载声音
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(...);
}


void SceneGame::addLabels()
{
	_hp = CCLabelAtlas::create(Util::format(_hero->_hp),IMAGE_Font_labelatlasimg,24,32,'0');
	_score = CCLabelAtlas::create("0", IMAGE_Font_labelatlasimg, 24, 32, '0');
	addChild(_hp);
	addChild(_score);

	_hp->setAnchorPoint(ccp(1, 1));
	_hp->setPosition(ccp(winSize.width, winSize.height));

	_score->setAnchorPoint(ccp(0, 1));
	_score->setPosition(ccp(0, winSize.height));

}


void SceneGame::update(float)
{
	//碰撞检测
	//敌机的循环
	int count = _ai->_enemys->count();
	for (int i = count - 1; i >= 0;--i)
	{
		Enemy* e = (Enemy*)_ai->_enemys->objectAtIndex(i);
		//敌机和英雄战机，是否有交集
		if (e->boundingBox().intersectsRect(_hero->boundingBox()))
		{
			//英雄战机少血
			_hero->_hp -= e->_hp;

			if (_hero->_hp <= 0)
			{
				gameOver();
				//_hero->killed();
				return;
			}
			Util::modifyLabel(_hp, -e->_hp);
			//敌机从数组中删除，从数组删除意味着不再进行碰撞检测
			_ai->_enemys->removeObjectAtIndex(i);
			//敌机死亡的动画，以及敌机从渲染树种删除
			e->killed();
			//_score->getString();
			Util::modifyLabel(_score, e->_score);

			//执行continue
			continue;
		}
		//敌机和子弹做碰撞检测
		int bulletCount = _hero->_bulletFly->count();
		for (int j = bulletCount - 1; j >= 0;--j)
		{
			CCSprite* sprite = (CCSprite*)_hero->_bulletFly->objectAtIndex(j);
			if (sprite->boundingBox().intersectsRect(e->boundingBox()))
			{
				//敌机的血药减少
				e->_hp -= _hero->_damage;   //这里少写了一个减号，无论如何也不能好使啊

				//如果敌军吃了子弹，，，那么这个子弹就要消，，，就不合另外的子弹做碰撞检测了。
				//子弹要消失  
				//sprite->removeFromParent();
				sprite->setVisible(false);
				_hero->_bulletsBox->addObject(sprite);
				_hero->_bulletFly->removeObject(sprite);
				//判断敌机是否已经死亡。
				if (e->_hp<=0)
				{
					// 敌机从数组里删除，从数组删除意味着这个敌机不再参与碰撞检测
					_ai->_enemys->removeObjectAtIndex(i);
					Util::modifyLabel(_score, e->_score);
					e->killed();
					break;
				}

			}
		}
	}
	//敌机子弹的碰撞检测
	count = _ai->_bulletFly->count();
	for (int i = count-1; i >=0; --i)
	{
		Bullet* eb = (Bullet*)_ai->_bulletFly->objectAtIndex(i);
		if (eb->boundingBox().intersectsRect(_hero->boundingBox()))
		{
			_hero->_hp -= eb->_damage;

			if (_hero->_hp <= 0)
			{
				gameOver();
				//_hero->killed();
				return;
			}

			Util::modifyLabel(_hp, -eb->_damage);   //这里是原因？？。。。

			//eb->removeFromParent();
			eb->setVisible(false);
			_ai->_bulletBox->addObject(eb);
			_ai->_bulletFly->removeObject(eb);
			continue;   //去找下一个子弹，注意检测完成了，就不执行后边的代码了。
		}
		//敌机子弹和我方子弹的碰撞检测
		int bulletCount = _hero->_bulletFly->count();
		for (int j = bulletCount - 1; j >= 0; --j)
		{
			CCSprite* sprite = (CCSprite*)_hero->_bulletFly->objectAtIndex(j);
			CCRect rc1 = sprite->boundingBox();
			CCLog("......%d", _ai->_bulletFly->count());
			CCRect rc2 = eb->boundingBox();
			if (rc1.intersectsRect(rc2))
			{
				//敌方子弹消失
				//eb->removeFromParent();
				_ai->_bulletFly->removeObject(eb);
				_ai->_bulletBox->addObject(eb);
				eb->setVisible(false);
				//我方子弹消失
				//sprite->removeFromParent();

				_hero->_bulletsBox->addObject(sprite);
				_hero->_bulletFly->removeObject(sprite);
				sprite->setVisible(false);
				break;   //去找下一个子弹，注意检测完成了，就不执行后边的代码了。
			}
		}
	}
}



void SceneGame::gameOver()
{
	//switchScene(SceneScore,atoi(this->_score.getString()));   //atoi把字符串转换为整型
	switchScene(SceneScore, atoi(this->_score->getString()));
}


void SceneGame::creatEnemyAI()
{
	_ai = AI::create();
	addChild(_ai);
}

void SceneGame::addHeroPlane(int id)
{
	_hero= Hero::create(id);
	addChild(_hero);
	_hero->setPosition(ccp(winSize.width/2,_hero->getContentSize().height));

	//为一个英雄飞机的子弹建立一个batchNode
	_hero->_bulletBatchNode = CCSpriteBatchNode::create(IMAGE_Bullet);
	addChild(_hero->_bulletBatchNode);
}

void SceneGame::Back(CCObject*)
{
	switchScene(SceneMenu);
}
//其实每一帧，都会被调用的。
void SceneGame::ccTouchMoved(CCTouch *t, CCEvent*)
{
	if (Util::isPartOutOfWindow(_hero, t->getDelta()))
		return;
	Util::moveNode(_hero, t->getDelta());
	//_hero->setPosition(_hero->getPosition() + t->getDelta());
}