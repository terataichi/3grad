#include <DxLib.h>

#include "BlockDropScene.h"
#include "../../TimeManager.h"
#include "../../common/SceneManager.h"

BlockDropScene::BlockDropScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit)
:TransitionScene(std::move(beforScene), std::move(afterScene))
{
	limit_ = limit;
	time_ = 0;
	fadeCount_ = 0;
	size_ = 32;
	division_ = { lpSceneManager.screenSize_ / size_ };
	speed_ = 0;
}

BlockDropScene::~BlockDropScene()
{
}

bool BlockDropScene::TransitionUpdate()
{
	//time_ += lpTimeManager.GetDeltaTime();
	fadeCount_ = 510.0 * time_ / limit_;

	if (fadeCount_ >= 510.0)
	{
		return true;
	}

	return false;
}

void BlockDropScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();

	float cy = 0;
	for (float y = 0; y < division_.y_; y++)
	{
		for (float x = 0; x < division_.x_; x++)
		{
			Potision2f pos{ x * size_,y * size_ };
			Potision2 imagePos = static_cast<Potision2>(pos);

			cy += 10 * sinf((pos.x_ + count_) / 180.0f * DX_PI_F);
			//speed_ += 1 * lpTimeManager.GetDeltaTime();
			//pos.y_ += cy;

			//SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeCount_ < 255 ? 255 - fadeCount_ : 0));
			DrawRectGraph(pos.x_, pos.y_ + cy, imagePos.x_, imagePos.y_, size_, size_, beforScene_->GetScreenID(), true);
			count_+= 0.1f;
		}
	}


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeCount_ > 255 ? fadeCount_ - 255 : 0));
	afterScene_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
