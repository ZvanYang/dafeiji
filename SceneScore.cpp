#include "SceneScore.h"

#include "SceneMenu.h"
bool SceneScore::init(int score)
{
	CCLayer::init();

	//设置一个背景图片
	Util::addBackground(IMAGE_background, this);

	//增加一个按钮在右下角
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneScore::Back));
	//要把分数上传到服务器，并且从服务器，获得前十名

	uploadScore(score, Util::format(CCRANDOM_0_1()*100,"user"));

	return true;
}

void SceneScore::uploadScore(int score, const char* username)
{
	//先暂停到这里
}

void SceneScore::Back(CCObject*)
{
	//Util::replaceLayer(SceneStart::create());
	//Util::replaceLayer(SceneStart::create());
	switchScene(SceneMenu);
}
