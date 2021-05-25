#include <DxLib.h>
#include <memory>
#include "common/Vector2.h"
#include "Scene/BaseScene.h"
#include "Scene/TitleScene.h"
#include "TimeManager.h"
#include "common/SceneManager.h"
constexpr int ScreenSizeX = 1024;
constexpr int ScreenSizeY = 768;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxLib::SetGraphMode(1024, 768, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText(L"1916025_éõçËëÂíq");
	if (DxLib_Init())
	{
		return false;
	}

	std::unique_ptr<BaseScene> scene;
	scene = std::make_unique<TitleScene>();

	std::unique_ptr<TimeManager> time;
	time = std::make_unique<TimeManager>();

	SceneManager::GetInstance();

	int handle = LoadGraph(L"Resource/Image/test01.png");

	while (DxLib::ProcessMessage() == 0 && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		DxLib::ClsDrawScreen();

		time->Update();

		scene->Draw(time->GetDeltaTime());

		DxLib::ScreenFlip();
	}
	DxLib_End();
	return 0;
}