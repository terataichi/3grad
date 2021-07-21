#include "GameScene.h"

#include <DxLib.h>

#include "../common/ImageManager.h"
#include "../common/TileMap.h"
#include "../Object/Player.h"
#include "../Object/Pawn.h"

GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
	map_ = std::make_shared<TileMap>("Resource/TileMap/testStage01.tmx");
	objList_.emplace_back(std::make_shared<Player>(Potision2f{ 300.0f,100.0f }, Vector2f{ 80.0f,50.0f },map_, ControllType::GamePad));
	objList_.emplace_back(std::make_shared<Player>(Potision2f{ 300.0f,100.0f }, Vector2f{ 80.0f,50.0f },map_,ControllType::Keybord));

	DrawOwnScreen();
	return true;
}

UniqueBase GameScene::Update(UniqueBase scene)
{
	for (auto& obj : objList_)
	{
		obj->Update();

		// 技が出てたらインスタンスリストに追加する
		if (obj->GetObjectType() == ObjectType::Actor)
		{
			auto pawn = std::dynamic_pointer_cast<Pawn>(obj);
			AddInstanceList(pawn);
		}
	}
	// リストに追加
	for (auto& ins : instanceList_)
	{
		objList_.push_back(ins);
	}
	instanceList_.clear();

	return scene;
}

void GameScene::DrawOwnScreen()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	map_->DrawMap();

	for (auto& obj : objList_)
	{
		obj->Draw();
	}
}

bool GameScene::AddInstanceList(std::shared_ptr<Pawn>& pawn)
{
	for (auto& attack : pawn->GetAttackList())
	{
		if (pawn->GetInstanceFuncMap().count(attack))
		{
			instanceList_.push_back(pawn->GetInstanceFuncMap().at(attack)());
		}
	}
	return true;
}
