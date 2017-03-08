#include "SceneAbout.h"
#include "SceneStart.h"
bool SceneAbout::init()
{
	CCLayer::init();

	//设置一个背景图片
	Util::addBackground(IMAGE_background, this);

	//增加一个按钮在右下角
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneAbout::Back));
	//添加about信息
	setInfo();
	return true;
}

void SceneAbout::setInfo()   //这里就是xml文件的读写
{
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(CFG_about);
	CCPoint margin(200, 100);
	float space = 80;
	for (int i = 0; i < 5;++i)
	{
		const CCString* value = dict->valueForKey(Util::format(i + 1, "people"));   //objectforkey
		CCLabelTTF* label = CCLabelTTF::create(value->getCString(), "Arial", 50);
		addChild(label);
		//label的锚点，除了影响setPosition，还指定了文字的对齐方式
		label->setAnchorPoint(ccp(0, 1));   //不设置锚点的话，，会居中显示的
		label->setPosition(ccp(0 + margin.x, winSize.height - i*space - margin.y));

		label->setColor(ccc3(255, 255, 0));
	}
}

void SceneAbout::Back(CCObject*)
{
	//Util::replaceLayer(SceneStart::create());
	//Util::replaceLayer(SceneStart::create());
	switchScene(SceneStart);
}
