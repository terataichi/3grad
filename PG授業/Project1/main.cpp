#include <Dxlib.h>
#include <memory>
#include <utility>
#include <vector>
#include <algorithm>

#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "common/Vector2.h"
#include "class/Shape.h"
#include "class/Square.h"
#include "class/Circle.h"
#include "class/Triangle.h"
#include "class/Carrot.h"
#include "class/System/TimeManager.h"
#include "class/System/SystemManager.h"

bool SysInit(void)
{
	DxLib::SetGraphMode(lpSysMng.GetScreenSize("x"), lpSysMng.GetScreenSize("y"), 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1916025_寺崎大智");
	if (DxLib::DxLib_Init() == -1) return false;

	_dbgSetup(lpSysMng.GetScreenSize("x"), lpSysMng.GetScreenSize("y"), 255);

	return true;
}


// エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow)
{

	if (!SysInit())return -1;
		
	ShapeVec shape;
	shape.reserve(100);
	shape.push_back(std::make_shared<Square>(Potision2f{ 600,200 }, Size{ 50,50 }, Vector2f{ 100,-50 }, 0xffff00));
	shape.push_back(std::make_shared<Square>(Potision2f{ 300,200 }, Size{ 100,100 }, Vector2f{ 100,-50 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 200,300 }, 50.0f, Vector2f{ 100,50}, 0xff0000));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 500,300 }, 50.0f, Vector2f{ 100,50 }, 0xff0000));

	shape.push_back(std::make_shared<Triangle>(Potision2f{ 300,400 }, Potision2f{ 200,200 }, Potision2f{ 100,300 }, Vector2f{ 300,100 }, 0x0000ff));
	shape.push_back(std::make_shared<Triangle>(Potision2f{ 300,100 }, Potision2f{ 200,50 }, Potision2f{ 100,30 }, Vector2f{ 200,-300 }, 0xff00ff));

	//shape.push_back(std::make_shared<Carrot>(Potision2f{ 400,200 }, Vector2f{ 30,-70 }, 0xff00));

	std::unique_ptr<TimeManager>timeManager_;
	timeManager_ = std::make_unique<TimeManager>();

	while (!ProcessMessage() && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		DxLib::ClsDrawScreen();
		timeManager_->Update();


		for (auto& obj : shape)
		{
			(*obj).Update(timeManager_->GetDeltaTime(), shape);
			(*obj).Draw();
		}

		shape.erase(std::remove_if(shape.begin(), shape.end(), [&](SharedShape& s) {return !s->GetAlive(); }), shape.end());
		DrawFormatString(0, 10, 0xff, "%f", timeManager_->GetDeltaTime());

		_dbgDraw();
		DxLib::ScreenFlip();
	}
	return 1;
}

