#include "GameScene.h"

#include <DxLib.h>

#include "../common/ImageManager.h"
#include "../common/TileMap.h"
#include "../Object/Player.h"

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
	objList_.emplace_back(std::make_unique<Player>(Potision2f{ 300.0f,100.0f }, Vector2f{ 50.0f,50.0f }, ControllType::GamePad));
	objList_.emplace_back(std::make_unique<Player>(Potision2f{ 300.0f,100.0f }, Vector2f{ 50.0f,50.0f }, ControllType::Keybord));

	DrawOwnScreen(0.0);
	return true;
}

UniqueBase GameScene::Update(UniqueBase scene, const double& deltaTime)
{
	for (auto& obj : objList_)
	{
		obj->Update(deltaTime);
	}
	return scene;
}

void GameScene::DrawOwnScreen(const double& deltaTime)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	map_->DrawMap();

	for (auto& obj : objList_)
	{
		obj->Draw(deltaTime);
	}
}
