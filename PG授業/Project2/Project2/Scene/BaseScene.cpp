#include "BaseScene.h"
#include <DxLib.h>

BaseScene::BaseScene()
{
	//RECT rect;
	//GetClientRect(GetMainWindowHandle(), &rect);
	//screenSize_ = { rect.right, rect.bottom };

	SetDrawScreen(DX_SCREEN_BACK);
	GetDrawScreenSize(&screenSize_.x_, &screenSize_.y_);
	screenID_ = MakeScreen(screenSize_.x_, screenSize_.y_, true);
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw(const double& deltaTime)
{
	DrawGraph(0, 0, screenID_,true);
}

const int& BaseScene::GetScreenID(void)
{
	return screenID_;
}
