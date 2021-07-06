#include "CrossOverScene.h"
#include "../../TimeManager.h"

#include <DxLib.h>

CrossOverScene::CrossOverScene(UniqueBase beforScene, UniqueBase afterScene,double&& limit)
	:TransitionScene(std::move(beforScene), std::move(afterScene))
{
	limit_ = limit;
	time_ = 0;
	fadeCount_ = 0;
}

CrossOverScene::~CrossOverScene()
{
}

bool CrossOverScene::TransitionUpdate()
{
	time_ += lpTimeManager.GetDeltaTime();
	fadeCount_ = 255.0 * time_ / limit_;

	if (fadeCount_ >= 255)
	{
		return true;
	}

	return false;
}

void CrossOverScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeCount_));
	afterScene_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 - fadeCount_));
	beforScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
