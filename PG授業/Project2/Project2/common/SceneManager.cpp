#include "SceneManager.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../TimeManager.h"
#include "../_debug/_DebugDispOut.h"
#include <DxLib.h>

void SceneManager::Run(void)
{
	if (!initFlag_)
	{
		return;
	}

	scene_ = std::make_unique<GameScene>();
	time_ = std::make_unique<TimeManager>();

	while (DxLib::ProcessMessage() == 0 && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		time_->Update();

		scene_ = scene_->Update(std::move(scene_), time_->GetDeltaTime());
		scene_->DrawOwnScreen(time_->GetDeltaTime());

		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		DxLib::ClsDrawScreen();
		scene_->Draw(time_->GetDeltaTime());
		_dbgAddDraw();
		DxLib::ScreenFlip();
	}
	DxLib_End();
}

void SceneManager::Update(void)
{
}

void SceneManager::Draw(void)
{
}

bool SceneManager::SystemInit(void)
{
	DxLib::SetGraphMode(screenSize_.x_, screenSize_.y_, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1916025_éõçËëÂíq");
	if (DxLib::DxLib_Init() == -1) return false;
	_dbgSetup(screenSize_.x_, screenSize_.y_, 255);

	return true;
}

SceneManager::SceneManager():screenSize_(1024, 768)
{
	initFlag_ = SystemInit();
}

SceneManager::~SceneManager()
{
}
