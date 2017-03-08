#include "SceneGame.h"
#include "ScrollBackground.h"
#include "SceneMenu.h"
#include "SceneScore.h"
#include "SimpleAudioEngine.h"
//#include "Enemy.h"
bool SceneGame::init(int planeID)
{
	//CCLayer::init();

	//����һ����������
	ScrollBackground* bg = ScrollBackground::create();
	addChild(bg);
	
	//���½ǵķ��ذ�ť
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneGame::Back));

	//����һ��Ӣ�۷ɻ�
	addHeroPlane(planeID);
	//ʹ��touch
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	//�����л�AI
	creatEnemyAI();

	//��ײ���
	scheduleUpdate();

	//����label��ʾ��Ϣ
	// ����Label��ʾ��Ϣ
	addLabels();
	return true;
}

void SceneGame::preLoadResource()
{
	//ִ�б�ը������Ȼ��ɾ������
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
	//Ԥ��������
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
	//��ײ���
	//�л���ѭ��
	int count = _ai->_enemys->count();
	for (int i = count - 1; i >= 0;--i)
	{
		Enemy* e = (Enemy*)_ai->_enemys->objectAtIndex(i);
		//�л���Ӣ��ս�����Ƿ��н���
		if (e->boundingBox().intersectsRect(_hero->boundingBox()))
		{
			//Ӣ��ս����Ѫ
			_hero->_hp -= e->_hp;

			if (_hero->_hp <= 0)
			{
				gameOver();
				//_hero->killed();
				return;
			}
			Util::modifyLabel(_hp, -e->_hp);
			//�л���������ɾ����������ɾ����ζ�Ų��ٽ�����ײ���
			_ai->_enemys->removeObjectAtIndex(i);
			//�л������Ķ������Լ��л�����Ⱦ����ɾ��
			e->killed();
			//_score->getString();
			Util::modifyLabel(_score, e->_score);

			//ִ��continue
			continue;
		}
		//�л����ӵ�����ײ���
		int bulletCount = _hero->_bulletFly->count();
		for (int j = bulletCount - 1; j >= 0;--j)
		{
			CCSprite* sprite = (CCSprite*)_hero->_bulletFly->objectAtIndex(j);
			if (sprite->boundingBox().intersectsRect(e->boundingBox()))
			{
				//�л���Ѫҩ����
				e->_hp -= _hero->_damage;   //������д��һ�����ţ��������Ҳ���ܺ�ʹ��

				//����о������ӵ���������ô����ӵ���Ҫ���������Ͳ���������ӵ�����ײ����ˡ�
				//�ӵ�Ҫ��ʧ  
				//sprite->removeFromParent();
				sprite->setVisible(false);
				_hero->_bulletsBox->addObject(sprite);
				_hero->_bulletFly->removeObject(sprite);
				//�жϵл��Ƿ��Ѿ�������
				if (e->_hp<=0)
				{
					// �л���������ɾ����������ɾ����ζ������л����ٲ�����ײ���
					_ai->_enemys->removeObjectAtIndex(i);
					Util::modifyLabel(_score, e->_score);
					e->killed();
					break;
				}

			}
		}
	}
	//�л��ӵ�����ײ���
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

			Util::modifyLabel(_hp, -eb->_damage);   //������ԭ�򣿣�������

			//eb->removeFromParent();
			eb->setVisible(false);
			_ai->_bulletBox->addObject(eb);
			_ai->_bulletFly->removeObject(eb);
			continue;   //ȥ����һ���ӵ���ע��������ˣ��Ͳ�ִ�к�ߵĴ����ˡ�
		}
		//�л��ӵ����ҷ��ӵ�����ײ���
		int bulletCount = _hero->_bulletFly->count();
		for (int j = bulletCount - 1; j >= 0; --j)
		{
			CCSprite* sprite = (CCSprite*)_hero->_bulletFly->objectAtIndex(j);
			CCRect rc1 = sprite->boundingBox();
			CCLog("......%d", _ai->_bulletFly->count());
			CCRect rc2 = eb->boundingBox();
			if (rc1.intersectsRect(rc2))
			{
				//�з��ӵ���ʧ
				//eb->removeFromParent();
				_ai->_bulletFly->removeObject(eb);
				_ai->_bulletBox->addObject(eb);
				eb->setVisible(false);
				//�ҷ��ӵ���ʧ
				//sprite->removeFromParent();

				_hero->_bulletsBox->addObject(sprite);
				_hero->_bulletFly->removeObject(sprite);
				sprite->setVisible(false);
				break;   //ȥ����һ���ӵ���ע��������ˣ��Ͳ�ִ�к�ߵĴ����ˡ�
			}
		}
	}
}



void SceneGame::gameOver()
{
	//switchScene(SceneScore,atoi(this->_score.getString()));   //atoi���ַ���ת��Ϊ����
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

	//Ϊһ��Ӣ�۷ɻ����ӵ�����һ��batchNode
	_hero->_bulletBatchNode = CCSpriteBatchNode::create(IMAGE_Bullet);
	addChild(_hero->_bulletBatchNode);
}

void SceneGame::Back(CCObject*)
{
	switchScene(SceneMenu);
}
//��ʵÿһ֡�����ᱻ���õġ�
void SceneGame::ccTouchMoved(CCTouch *t, CCEvent*)
{
	if (Util::isPartOutOfWindow(_hero, t->getDelta()))
		return;
	Util::moveNode(_hero, t->getDelta());
	//_hero->setPosition(_hero->getPosition() + t->getDelta());
}