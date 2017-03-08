#include "SceneAbout.h"
#include "SceneStart.h"
bool SceneAbout::init()
{
	CCLayer::init();

	//����һ������ͼƬ
	Util::addBackground(IMAGE_background, this);

	//����һ����ť�����½�
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneAbout::Back));
	//���about��Ϣ
	setInfo();
	return true;
}

void SceneAbout::setInfo()   //�������xml�ļ��Ķ�д
{
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(CFG_about);
	CCPoint margin(200, 100);
	float space = 80;
	for (int i = 0; i < 5;++i)
	{
		const CCString* value = dict->valueForKey(Util::format(i + 1, "people"));   //objectforkey
		CCLabelTTF* label = CCLabelTTF::create(value->getCString(), "Arial", 50);
		addChild(label);
		//label��ê�㣬����Ӱ��setPosition����ָ�������ֵĶ��뷽ʽ
		label->setAnchorPoint(ccp(0, 1));   //������ê��Ļ������������ʾ��
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
