#include <Dxlib.h>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Common/Vector2.h"

bool SysInit(void)
{
	DxLib::SetGraphMode(1280, 760, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1916025_寺崎大智");
	if (DxLib::DxLib_Init() == -1) return false;

	return true;
}


// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	if (!SysInit())return -1;

	_dbgStartDraw();

	Vector2 vec(0, 0);

	vec += Vector2(10, 0);

	//int model = MV1LoadModel("bugatti.mtl");

	while (!ProcessMessage() && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		DxLib::ClsDrawScreen();

		_dbgDraw();
		DxLib::ScreenFlip();
	}

	return 1;
}

