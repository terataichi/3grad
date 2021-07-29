#include "TitleScene.h"
#include <DxLib.h>
#include <memory>

#include "../common/TileMap.h"

#include "GameScene.h"
#include "Transition/CrossOverScene.h"
#include "Transition/Fade_InOutScene.h"
#include "Transition/BrightRotationScene.h"
#include "Transition/BlockDropScene.h"
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
	DrawOwnScreen();
	return true;
}

UniqueBase TitleScene::Update(UniqueBase scene)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return std::make_unique<BrightRotationScene>(std::move(scene), std::make_unique<GameScene>(), 5.0);
	}
	return scene;
}

void TitleScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageManager.GetImageHandle("BackGround/bg04.png")[0], true);
}
