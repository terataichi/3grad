#include <Dxlib.h>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "class/Shape.h"

bool SysInit(void)
{
	DxLib::SetGraphMode(640, 480, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1916025_寺崎大智");
	if (DxLib::DxLib_Init() == -1) return false;

	return true;
}


// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{

	if (!SysInit())return -1;

	Shape shape;
	//shape.x_ = 300;
	//shape.y_ = 200;
	//shape.sizeX_ = 100;
	//shape.sizeY_ = 100;

	_dbgStartDraw();

	while (!ProcessMessage() && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		DxLib::ClsDrawScreen();

		shape.Draw();
		_dbgDraw();
		DxLib::ScreenFlip();
	}

	return 1;
}

