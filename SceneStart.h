#ifndef __SceneStart_H__
#define __SceneStart_H__

#include "Common.h"
class SceneStart:public CCLayer
{
public:
	CREATE_FUNC(SceneStart);
	bool init();

	void Start(CCObject* sender);
	void About(CCObject* sender);
	void Quit(CCObject* sender);

};


#endif


