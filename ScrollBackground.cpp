#include "ScrollBackground.h"

bool ScrollBackground::init()
{
	//CCLayer::init();   //���ӵĻ������������ʲô����
	CCSprite*bg = Util::addBackground(IMAGE_background, this);
	//�ñ���ͼƬ�ʹ����±߶��䡣
	bg->setPositionY(bg->getPositionY() + winSize.height / 2);

	CCMoveBy* move = CCMoveBy::create(4, ccp(0, -winSize.height));
	//ccplace�൱��setposition��action�汾
	CCPlace* place = CCPlace::create(bg->getPosition());
	bg->runAction(
		CCRepeatForever::create(CCSequence::create(move, place, NULL))
		);

	return true;
}