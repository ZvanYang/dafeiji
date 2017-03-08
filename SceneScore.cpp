#include "SceneScore.h"

#include "SceneMenu.h"
bool SceneScore::init(int score)
{
	CCLayer::init();

	//����һ������ͼƬ
	Util::addBackground(IMAGE_background, this);

	//����һ����ť�����½�
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneScore::Back));
	//Ҫ�ѷ����ϴ��������������Ҵӷ����������ǰʮ��

	uploadScore(score, Util::format(CCRANDOM_0_1()*100,"user"));

	return true;
}

void SceneScore::uploadScore(int score, const char* username)
{
	//����ͣ������
}

void SceneScore::Back(CCObject*)
{
	//Util::replaceLayer(SceneStart::create());
	//Util::replaceLayer(SceneStart::create());
	switchScene(SceneMenu);
}
