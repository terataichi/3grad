#include "TitleScene.h"
#include <DxLib.h>
#include <memory>

#include "../common/TileMap.h"

#include "GameScene.h"
#include "Transition/CrossOverScene.h"
#include "Transition/Fade_InOutScene.h"
#include "Transition/BrightRotationScene.h"
#include "../common/ImageManager.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{

	DrawOwnScreen(0.0);
	return true;
}

UniqueBase TitleScene::Update(UniqueBase scene, const double& deltaTime)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return std::make_unique<BrightRotationScene>(std::move(scene), std::make_unique<GameScene>(), 5.0);
	}
	return scene;
}

void TitleScene::DrawOwnScreen(const double& deltaTime)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(300, 100, lpImageManager.GetImageHandle("test01.png")[0], true);
}
