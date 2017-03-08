#include "SceneMenu.h"
#include "SceneStart.h"
#include "ScrollBackground.h"
#include "SceneGame.h"
bool SceneMenu::init()
{
	//CCLayer::init();
	//增加滚动背景
	ScrollBackground* bg = ScrollBackground::create();
	addChild(bg);


	//右下角的返回按钮
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneMenu::Back));
	//增加一个滚动层，选择飞机
	initScrollMenu();


	return true;
}

void SceneMenu::initScrollMenu()
{
	CCNode* node = CCNode::create();
	_node = node;
	//增加滚动的内容
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

	//设置滚动视图
	CCScrollView* view = CCScrollView::create(winSize, node);
	addChild(view);
	view->setDirection(kCCScrollViewDirectionHorizontal);
	view->setContentSize(CCSize(winSize.width * 5, winSize.height));   //这是可以滚动的高度
	view->setBounceable(false);  //去掉弹性
	//设置触摸
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

}

void SceneMenu::adjustScrollView(float)
{
	int curPos = _node->getPositionX();
	int minOff = 10 * winSize.width;
	int i;
	for (i = 0; i < 5;++i)   //这里多一个int都不行啊
	{
		int adjustPos = -i*winSize.width;
		int offset = abs(curPos - adjustPos);
		//通过算法查找，最接近的调整位置。
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
		//点击
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
		//滑动  启动一个定时器，让定时器处理函数，矫正scrollview的位置
		scheduleOnce(schedule_selector(SceneMenu::adjustScrollView), 0.1f);

	}
}


void SceneMenu::Back(CCObject*)
{
	switchScene(SceneStart);
}

