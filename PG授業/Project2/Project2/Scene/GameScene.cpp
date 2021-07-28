#include "GameScene.h"

#include <DxLib.h>

#include "../common/ImageManager.h"
#include "../common/SceneManager.h"
#include "../common/TileMap.h"
#include "../Object/Player.h"
#include "../Object/Pawn.h"
#include "../common/Collision.h"
#include <algorithm>

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
	objList_.emplace_back(std::make_shared<Player>(Potision2f{ 600.0f,100.0f }, Vector2f{ 80.0f,50.0f }, map_, ControllType::GamePad, TeamTag::Bule));
	objList_.emplace_back(std::make_shared<Player>(Potision2f{ 300.0f,100.0f }, Vector2f{ 80.0f,50.0f }, map_, ControllType::Keybord, TeamTag::Red));

	collision_.reset(new Collision());

	DrawOwnScreen();

	deathScreen_ = MakeScreen(lpSceneManager.screenSize_.x_, lpSceneManager.screenSize_.y_, true);

	return true;
}

UniqueBase GameScene::Update(UniqueBase scene)
{
	for (auto& obj : objList_)
	{
		obj->Update();

		collision_->CheckCollision(obj, objList_);

		if (obj->GetObjectType() == ObjectType::Pawn)
		{
			auto pawn = std::dynamic_pointer_cast<Pawn>(obj);
			if (obj->IsActive())
			{
				// 技が出てたらインスタンスリストに追加する
				AddInstanceList(pawn);
			}

			if (obj->GetAnimState() == Anim_State::Death)
			{
				// スクショ
				SetDrawScreen(deathScreen_);
				obj->Draw();
				pawn->Continue();					// 復活
			}
		}
	}

	objList_.erase(std::remove_if(objList_.begin(), objList_.end(), [&](std::shared_ptr<Object>& s) {return !s->IsActive(); }), objList_.end());

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
	DrawGraph(0, 0, deathScreen_, true);
	for (auto& obj : objList_)
	{
		obj->Draw();
		obj->DrawStatus();
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
	pawn->GetAttackList().clear();
	return true;
}
