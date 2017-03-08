#ifndef __SceneAbout_H__
#define __SceneAbout_H__

#include "Common.h"
class SceneAbout :public CCLayer
{
public:
	CREATE_FUNC(SceneAbout);
	bool init();

	void Back(CCObject*);
	void setInfo();

};

#endif



