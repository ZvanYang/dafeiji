#ifndef __SceneScore_H__
#define __SceneScore_H__

#include "Common.h"
class SceneScore :public CCLayer
{
public:
	//CREATE_FUNC(SceneScore);
	static SceneScore* create(int score)
	{
		SceneScore* s = new SceneScore();
		s -> init(score);
		s->autorelease();
		return s;
	}
	bool init(int score);

	void Back(CCObject*);
	void uploadScore(int score, const char* username);
};

#endif



