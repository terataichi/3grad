#include "TransitionScene.h"
#include <DxLib.h>


TransitionScene::TransitionScene(UniqueBase beforScene, UniqueBase afterScene)
{
	beforScene_ = std::move(beforScene);
	afterScene_ = std::move(afterScene);
}

TransitionScene::~TransitionScene()
{
}

bool TransitionScene::Init(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	beforScene_->Draw();
	return false;
}

UniqueBase TransitionScene::Update(UniqueBase scene)
{
	if (TransitionUpdate())
	{
		return std::move(afterScene_);
	}
	return scene;
}
