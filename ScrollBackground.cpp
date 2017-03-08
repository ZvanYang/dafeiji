#include "ScrollBackground.h"

bool ScrollBackground::init()
{
	//CCLayer::init();   //不加的话，，看看会出什么问题
	CCSprite*bg = Util::addBackground(IMAGE_background, this);
	//让背景图片和窗口下边对其。
	bg->setPositionY(bg->getPositionY() + winSize.height / 2);

	CCMoveBy* move = CCMoveBy::create(4, ccp(0, -winSize.height));
	//ccplace相当于setposition的action版本
	CCPlace* place = CCPlace::create(bg->getPosition());
	bg->runAction(
		CCRepeatForever::create(CCSequence::create(move, place, NULL))
		);

	return true;
}