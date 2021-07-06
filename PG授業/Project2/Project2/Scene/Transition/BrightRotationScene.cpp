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
	fadeCount_ = 255.0 * time_ / limit_;
	angle_ = atan(fadeCount_);
	if (fadeCount_ >= 255)
	{
		return true;
	}
	return false;
}

void BrightRotationScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	//ClsDrawScreen();
	//SetDrawBlendMode(DX_BLENDMODE_PMA_ADD, static_cast<int>(fadeCount_));
	//DrawRotaGraph(lpSceneManager.screenSize_.x_ / 2, lpSceneManager.screenSize_.y_ / 2, 1.0, angle_, afterScene_->GetScreenID(), true);
	SetDrawBlendMode(DX_BLENDMODE_PMA_ADD, static_cast<int>(255.0 - fadeCount_));
	DrawRotaGraph(lpSceneManager.screenSize_.x_ / 2, lpSceneManager.screenSize_.y_ / 2, 1.0, angle_, beforScene_->GetScreenID(), true);
	//beforScene_->Draw(deltaTime);

}
