#include "CrossOverScene.h"
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

bool CrossOverScene::TransitionUpdate(const double& deltaTime)
{
	time_ += deltaTime;
	fadeCount_ = 255.0 * time_ / limit_;

	if (fadeCount_ >= 255)
	{
		return true;
	}

	return false;
}

void CrossOverScene::DrawOwnScreen(const double& deltaTime)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeCount_));
	afterScene_->Draw(deltaTime);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 - fadeCount_));
	beforScene_->Draw(deltaTime);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
