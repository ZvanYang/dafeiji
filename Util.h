#ifndef __Util_H__
#define __Util_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define winSize CCDirector::sharedDirector()->getWinSize()

#define switchScene(__layer_name__, ...)  \
	CCDirector::sharedDirector()->replaceScene(Util::scene(__layer_name__::create(__VA_ARGS__)));

class Util
{
public:
	static CCScene* scene(CCLayer* layer)
	{
		CCScene* s = CCScene::create();
		s->addChild(layer);
		return s;
	}
	//static void replaceLayer(CCLayer* layer)
	//{
	//	CCScene* scene = CCScene::create();
	//	scene->addChild(layer);
	//	CCDirector::sharedDirector()->replaceScene(scene);
	//}
	static CCSprite* addBackground(const char* picFile,CCNode* parent)
	{
		CCSprite* sp = CCSprite::create(picFile);
		parent->addChild(sp);
		sp->setPosition(ccp(winSize.width/2,winSize.height/2));
		return sp;
	}

	static void modifyLabel(CCLabelAtlas* label, int change)
	{
		const char* sValue = label->getString();
		int value = atoi(sValue);
		value += change;
		label->setString(format(value));
	}

	static void moveMenuItemRB(CCMenuItem* node)
	{
		node->setPosition(
			ccp(winSize.width / 2 - node->getContentSize().width / 2,
			node->getContentSize().height / 2 - winSize.height / 2)
			);
	}

	static CCMenuItem* addMenuItemImageRB(const char* picFile1, const char* picFile2, CCNode* parent)
	{
		CCMenuItem* item = CCMenuItemImage::create(picFile1, picFile2);
		CCMenu* menu = CCMenu::createWithItem(item);    //自己这个地方出了很大的错误啊。。。气死我了啊
		parent->addChild(menu);
		moveMenuItemRB(item);
		return item;
	}

	static char* format(int value, const char* prefix = "", const char* suffix = "")
	{
		static char buf[1024];
		sprintf(buf, "%s%d%s", prefix, value, suffix);
		return buf;
	}

	static bool isClick(CCTouch* t)
	{
		return t->getLocation().getDistanceSq(t->getStartLocation()) < 25;
	}

	static void moveNode(CCNode *node, const CCPoint& delta)
	{
		node->setPosition(node->getPosition() + delta);
	}

	//判断当前的位置是不是在窗口内。
	static bool isPartOutOfWindow(CCNode* node, const CCPoint delta = ccp(0, 0))
	{
		CCRect rcNode = node->boundingBox();
		CCPoint pt[4];
		pt[0] = ccp(rcNode.getMinX(), rcNode.getMinY());
		pt[1] = ccp(rcNode.getMinX(), rcNode.getMaxY());
		pt[2] = ccp(rcNode.getMaxX(), rcNode.getMaxY());
		pt[3] = ccp(rcNode.getMaxX(), rcNode.getMinY());
		CCRect rcWin(0, 0, winSize.width, winSize.height);
		for (int i = 0; i < 4;i++)
		{
			if (!rcWin.containsPoint(pt[i]+delta))
			{
				return true;
			}
		}
		return false;
	}

	//判断结点node，通过delta的位移之后是不是整体移除了窗口
	static bool isAllOutOfWindow(CCNode* node, const CCPoint& delta = ccp(0, 0))
	{
		CCRect rcWin(0, 0, winSize.width, winSize.height);
		CCRect rcNode = node->boundingBox();
		rcNode.origin =rcNode.origin + delta;   //原点要是挪动了的话，，，矩形也就跟着挪动了。。
	
		if (rcWin.intersectsRect(node->boundingBox()))
		{

			return false;
		}
		return true;
	}
};

#endif