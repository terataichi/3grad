#include <DxLib.h>
#include "common/Vector2.h"

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

	while (DxLib::ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		DxLib::ClsDrawScreen();

		DxLib::ScreenFlip();
	}
	DxLib_End();
	return 0;
}