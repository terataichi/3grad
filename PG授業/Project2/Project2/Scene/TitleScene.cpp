#include "TitleScene.h"
#include <DxLib.h>
#include <list>
#include "../common/TileMap.h"

#include "GameScene.h"
#include "Transition/CrossOverScene.h"
#include "Transition/Fade_InOutScene.h"
#include "Transition/BrightRotationScene.h"
#include "Transition/BlockDropScene.h"
#include "../common/ImageManager.h"
#include "../common/SceneManager.h"
#include "../Object/Player.h"
#include "../Object/StartObj.h"
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
	player_ = std::make_shared<Player>(Potision2f{ 100.0f,500.0f }, Vector2f{ 100.0f,100.0f }, map_, ControllType::Keybord);
	startObj_ = std::make_shared<StartObj>(Potision2f{ 510.0f,670.0f }, Vector2f{ 100.0f,100.0f }, Size{ 30,30 }, TeamTag::Non);
	DrawOwnScreen();
	return true;
}

UniqueBase TitleScene::Update(UniqueBase scene)
{
	if (!player_->IsActive())
	{
		player_->ResetObjID();
		return std::make_unique<BrightRotationScene>(std::move(scene), std::make_unique<GameScene>(), 5.0);
	}
	player_->Update();

	col_.CheckCollision(startObj_, std::list<std::shared_ptr<Object>>{player_});

	return scene;
}

void TitleScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	// bg
	DrawGraph(0, 0, lpImageManager.GetImageHandle("BackGround/bg04.png")[0], true);

	player_->Draw();
	// 1P •\Ž¦
	auto& pos = player_->GetPotision();
	auto offset = Vector2f{ player_->GetSize().x_ / 3 ,player_->GetSize().y_ + 5 };
	DrawFormatStringF(pos.x_ - offset.x_, pos.y_ - offset.y_, 0xffffff, "1P");

	// start‚ÌŠÅ”Â
	auto size = lpImageManager.GetImageSize("start.png");
	auto startPos = Potision2{ 450,470 };
	DrawExtendGraph(startPos.x_, startPos.y_,
		startPos.x_ + size.x_ * 3, startPos.y_ + size.y_ * 3,
		lpImageManager.GetImageHandle("start.png")[0], true);

	map_->DrawMap();
}
