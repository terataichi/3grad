#include <Dxlib.h>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "class/Shape.h"
#include "class/Square.h"
#include "class/Circle.h"

bool SysInit(void)
{
	DxLib::SetGraphMode(640, 480, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1916025_寺崎大智");
	if (DxLib::DxLib_Init() == -1) return false;

	_dbgSetup(640, 480, 32);

	return true;
}


// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{

	if (!SysInit())return -1;

	//Shape shape();

	Potision2 pos{ 200,200 };
	Size size{ 50,50 };

	Square shape1{ pos, size };
	//Shape* shape2 = new Shape{ pos * 2, size };
	//Shape* shape3 = new Square{ pos * 3 , size };
	Shape* circle = new Circle{ pos,20.0f };

	while (!ProcessMessage() && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		DxLib::ClsDrawScreen();

		shape1.Draw(Vector2{25,25}, 2);
		circle->Draw(3.0f);
		//shape2->Draw();
		//shape3->Draw();

		_dbgDraw();
		DxLib::ScreenFlip();
	}

	return 1;
}

