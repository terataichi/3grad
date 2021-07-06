#include "Fade_InOutScene.h"
#include "../../TimeManager.h"

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

bool Fade_InOutScene::TransitionUpdate()
{
	time_ += lpTimeManager.GetDeltaTime();
	fadeCount_ = 510.0 * time_ / limit_;

	if (fadeCount_ >= 510.0)
	{
		return true;
	}

	return false;
}

void Fade_InOutScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeCount_ < 255 ? 255 - fadeCount_ : 0));
	beforScene_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeCount_ > 255 ? fadeCount_ - 255 : 0));
	afterScene_->Draw();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
