#include "BrightRotationScene.h"
#include "../../common/SceneManager.h"
#include "../../TimeManager.h"

#include <DxLib.h>

BrightRotationScene::BrightRotationScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit)
	:TransitionScene(std::move(beforScene), std::move(afterScene))
{
	limit_ = limit;
	time_ = 0;
	fadeCount_ = 0;
	angle_ = 0.0;
}

BrightRotationScene::~BrightRotationScene()
{
}

bool BrightRotationScene::TransitionUpdate()
{
	time_ += lpTimeManager.GetDeltaTime();
	fadeCount_ = 510.0 * time_ / limit_;
	angle_ = angleCount_ * DX_PI_F / 180.0f;

	angleCount_ += 10.0f;
	if (fadeCount_ >= 510.0)
	{
		return true;
	}
	else if (fadeCount_ >= 255.0)
	{
		angleCount_ -= 20.0f;
		if (angleCount_ < 0)
		{
			angleCount_ = 0;
		}
	}

	return false;
}

void BrightRotationScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);

	if (fadeCount_ > 255.0)
	{
		ClsDrawScreen();
		SetDrawBlendMode(DX_BLENDMODE_ADD, fadeCount_ - 255);
		DrawRotaGraph(lpSceneManager.screenSize_.x_ / 2, lpSceneManager.screenSize_.y_ / 2, 1.0, angle_, afterScene_->GetScreenID(), true);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - fadeCount_);
		DrawRotaGraph(lpSceneManager.screenSize_.x_ / 2, lpSceneManager.screenSize_.y_ / 2, 1.0, angle_, beforScene_->GetScreenID(), true);
	}
}
