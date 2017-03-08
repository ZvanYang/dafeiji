#include "SceneMenu.h"
#include "SceneStart.h"
#include "ScrollBackground.h"
#include "SceneGame.h"
bool SceneMenu::init()
{
	//CCLayer::init();
	//���ӹ�������
	ScrollBackground* bg = ScrollBackground::create();
	addChild(bg);


	//���½ǵķ��ذ�ť
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneMenu::Back));
	//����һ�������㣬ѡ��ɻ�
	initScrollMenu();


	return true;
}

void SceneMenu::initScrollMenu()
{
	CCNode* node = CCNode::create();
	_node = node;
	//���ӹ���������
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("chooselevel.plist");
	for (int i = 0; i < 5;i++)
	{
		CCSprite* sprite = CCSprite::createWithSpriteFrameName(
			Util::format(i+1,"ChooseLevel",".png"));
		node->addChild(sprite);
		sprite->setPosition(ccp(winSize.width / 2+i*winSize.width, winSize.height / 2));
		sprite->setTag(i);
	}

	//���ù�����ͼ
	CCScrollView* view = CCScrollView::create(winSize, node);
	addChild(view);
	view->setDirection(kCCScrollViewDirectionHorizontal);
	view->setContentSize(CCSize(winSize.width * 5, winSize.height));   //���ǿ��Թ����ĸ߶�
	view->setBounceable(false);  //ȥ������
	//���ô���
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

}

void SceneMenu::adjustScrollView(float)
{
	int curPos = _node->getPositionX();
	int minOff = 10 * winSize.width;
	int i;
	for (i = 0; i < 5;++i)   //�����һ��int�����а�
	{
		int adjustPos = -i*winSize.width;
		int offset = abs(curPos - adjustPos);
		//ͨ���㷨���ң���ӽ��ĵ���λ�á�
		if (offset<minOff)
		{
			minOff = offset;
		}
		else
		{
			break;
		}
	}
	int adjustPos = -(i - 1)*winSize.width;
	CCAction* action = CCMoveTo::create(0.1f, ccp(adjustPos, _node->getPositionY()));
	_node->stopAllActions();
	_node->runAction(action);
}


void SceneMenu::ccTouchEnded(CCTouch *t, CCEvent *)
{
	if (Util::isClick(t))
	{
		//���
		CCPoint ptInNode = _node->convertTouchToNodeSpace(t);
		for (int i = 0; i < 5;++i)
		{
			CCNode* sprite = _node->getChildByTag(i);
			if (sprite->boundingBox().containsPoint(ptInNode))
			{
				switchScene(SceneGame,i);
				break;
			}
		}
	}
	else
	{
		//����  ����һ����ʱ�����ö�ʱ��������������scrollview��λ��
		scheduleOnce(schedule_selector(SceneMenu::adjustScrollView), 0.1f);

	}
}


void SceneMenu::Back(CCObject*)
{
	switchScene(SceneStart);
}

