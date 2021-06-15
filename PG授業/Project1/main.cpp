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
#include "class/Capsule.h"
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
	shape.push_back(std::make_shared<Square>(Potision2f{ 600,500 }, Size{ 50,50 }, Vector2f{ 100,-50 }, 0xff0000));
	shape.push_back(std::make_shared<Square>(Potision2f{ 700,500 }, Size{ 30,30 }, Vector2f{ 50,-100 }, 0xff0000));
	shape.push_back(std::make_shared<Square>(Potision2f{ 700,500 }, Size{ 30,30 }, Vector2f{ 100,50 }, 0xff0000));
	shape.push_back(std::make_shared<Square>(Potision2f{ 700,500 }, Size{ 30,30 }, Vector2f{ 300,-50 }, 0xff0000));
	shape.push_back(std::make_shared<Square>(Potision2f{ 700,500 }, Size{ 30,30 }, Vector2f{ 50,50 }, 0xff0000));
	shape.push_back(std::make_shared<Square>(Potision2f{ 700,500 }, Size{ 30,30 }, Vector2f{ 60,-75 }, 0xff0000));
	shape.push_back(std::make_shared<Square>(Potision2f{ 700,500 }, Size{ 30,30 }, Vector2f{ 90,-30 }, 0xff0000));

	shape.push_back(std::make_shared<Circle>(Potision2f{ 200,300 }, 50.0f, Vector2f{ 100,50}, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 50,500 }, 50.0f, Vector2f{ 100,50 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 50,500 }, 50.0f, Vector2f{ 100,-50 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 50,500 }, 50.0f, Vector2f{ -100,50 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 50,500 }, 50.0f, Vector2f{ 200,50 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 50,500 }, 50.0f, Vector2f{ 100,200 }, 0xffff00));

	shape.push_back(std::make_shared<Circle>(Potision2f{ 600,200 }, 50.0f, Vector2f{ -100,50 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 900,500 }, 50.0f, Vector2f{ 300,-50 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 900,500 }, 50.0f, Vector2f{ 100,-200 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 900,500 }, 50.0f, Vector2f{ 50,-50 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 900,500 }, 50.0f, Vector2f{ 70,-10 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 900,500 }, 50.0f, Vector2f{ 90,90 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 900,500 }, 50.0f, Vector2f{ 10,-100 }, 0xffff00));
	shape.push_back(std::make_shared<Circle>(Potision2f{ 900,500 }, 50.0f, Vector2f{ 30,200 }, 0xffff00));

	shape.push_back(std::make_shared<Triangle>(Potision2f{ 300,330 }, Potision2f{ 250,300 }, Potision2f{ 200,320 }, Vector2f{ 300,100 }, 0x0000ff));
	shape.push_back(std::make_shared<Triangle>(Potision2f{ 250,100 }, Potision2f{ 230,50 }, Potision2f{ 210,30 }, Vector2f{ 200,-300 }, 0xff00ff));

	shape.push_back(std::make_shared<Carrot>(Potision2f{ 400,200 }, Vector2f{ 30,-70 }, 0xff00));
	shape.push_back(std::make_shared<Carrot>(Potision2f{ 870,200 }, Vector2f{ 30,20 }, 0xff00));

	shape.push_back(std::make_shared<Capsule>(Potision2f{ 800,200 }, Vector2f{ 30,-70 }, 0xff00));
	shape.push_back(std::make_shared<Capsule>(Potision2f{ 200,500 }, Vector2f{ -30,-70 }, 0xff00));
	shape.push_back(std::make_shared<Capsule>(Potision2f{ 400,600 }, Vector2f{ -30,70 }, 0xff00));

	std::unique_ptr<TimeManager>timeManager_;
	timeManager_ = std::make_unique<TimeManager>();

	while (!ProcessMessage() && !DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_dbgStartDraw();
		DxLib::ClsDrawScreen();
		timeManager_->Update();

		DrawBox(0, 0, lpSysMng.GetScreenSize("x"), lpSysMng.GetScreenSize("y"),0xffffff, true);
		for (auto& obj : shape)
		{
			(*obj).Update(timeManager_->GetDeltaTime(), shape);
			(*obj).Draw();
		}

		shape.erase(std::remove_if(shape.begin(), shape.end(), [&](SharedShape& s) {return !s->GetAlive(); }), shape.end());
		DrawFormatString(0, 10, 0xff, "%f", timeManager_->GetDeltaTime());

		DxLib::ScreenFlip();
	}
	return 1;
}

