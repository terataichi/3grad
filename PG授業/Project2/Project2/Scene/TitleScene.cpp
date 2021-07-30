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
#include "../Object/Player.h"
#include "../common/TileMap.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{
	map_ = std::make_shared<TileMap>("Resource/TileMap/titleMap.tmx");
	object_ = std::make_unique<Player>(Potision2f{ 100.0f,100.0f }, Vector2f{ 100.0f,100.0f }, map_, ControllType::Keybord);
	DrawOwnScreen();
	return true;
}

UniqueBase TitleScene::Update(UniqueBase scene)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		object_->ResetObjID();
		return std::make_unique<BrightRotationScene>(std::move(scene), std::make_unique<GameScene>(), 5.0);
	}
	object_->Update();
	return scene;
}

void TitleScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageManager.GetImageHandle("BackGround/bg04.png")[0], true);
	object_->Draw();
	map_->DrawMap();
}
