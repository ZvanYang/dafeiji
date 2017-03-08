#include "SceneStart.h"
#include "SceneAbout.h"
#include "SceneMenu.h"
bool SceneStart::init()
{
	CCLayer::init();

	//设置一个北京图片

	Util::addBackground(IMAGE_background,this);
	//加上三个菜单按钮
	CCMenuItem* start = CCMenuItemImage::create(IMAGE_start_1,IMAGE_start_2);
	//CCMenuItem* start = CCMenuItemImage::create(IMAGE_start_1, IMAGE_start_2,menu_selector(SceneStart::Start));
	CCMenuItem* about = CCMenuItemImage::create(IMAGE_about_1,IMAGE_about_2);
	CCMenuItem* quit = CCMenuItemImage::create(IMAGE_quit_1,IMAGE_quit_2);

	CCMenu* menu = CCMenu::create(start, about, quit, NULL);
	addChild(menu);
	//自定义空格的对其
	menu->alignItemsVerticallyWithPadding(50);

	//三个按钮加上处理函数
	start->setTarget(this, menu_selector(SceneStart::Start));
	about->setTarget(this, menu_selector(SceneStart::About));
	quit->setTarget(this, menu_selector(SceneStart::Quit));
	return true;
}


void SceneStart::Start(CCObject*)
{
	switchScene(SceneMenu);
}
void SceneStart::About(CCObject*)
{
	switchScene(SceneAbout);
	//CCDirector::sharedDirector()->replaceScene(Util::scene(SceneAbout::create()));
}
void SceneStart::Quit(CCObject*)
{

}