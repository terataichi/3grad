#include "Fade_InOutScene.h"
#include <DxLib.h>

Fade_InOutScene::Fade_InOutScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit)
	:TransitionScene(std::move(beforScene), std::move(afterScene))
{
	limit_ = limit;
	time_ = 0;
	fadeCount_ = 0;
}

Fade_InOutScene::~Fade_InOutScene()
{
}

bool Fade_InOutScene::TransitionUpdate(const double& deltaTime)
{
	time_ += deltaTime;
	fadeCount_ = 510.0 * time_ / limit_;

	if (fadeCount_ >= 510.0)
	{
		return true;
	}

	return false;
}

void Fade_InOutScene::DrawOwnScreen(const double& deltaTime)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeCount_ < 255 ? 255 - fadeCount_ : 0));
	beforScene_->Draw(deltaTime);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeCount_ > 255 ? fadeCount_ - 255 : 0));
	afterScene_->Draw(deltaTime);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
