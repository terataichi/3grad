#include "Bulled.h"
#include "../TimeManager.h"
#include "../common/ImageManager.h"

#include<DxLib.h>

Bulled::Bulled(Potision2f&& pos, Vector2f&& vel) :Object(pos, vel,ObjectType::Actor)
{
	Init();
}

Bulled::~Bulled()
{
}

void Bulled::Init()
{
}

bool Bulled::Update()
{
	pos_.x_ += vel_.x_ * lpTimeManager.GetDeltaTimeF();
	return true;
}

void Bulled::Draw()
{
	DrawRotaGraphF(pos_.x_, pos_.y_, 1.0, 0.0, lpImageManager.GetImageHandle("test01.png")[0], true);
}
