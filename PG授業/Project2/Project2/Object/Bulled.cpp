#include "Bulled.h"
#include "../TimeManager.h"
#include "../common/ImageManager.h"

#include<DxLib.h>

Bulled::Bulled(Potision2f&& pos, Vector2f&& vel, TeamTag tag) :Object(pos, vel,ObjectType::Actor,tag)
{
	Init();
}

Bulled::~Bulled()
{
}

void Bulled::Init()
{
	auto tmp = (lpImageManager.GetImageSize("test01.png"));
	size_ = static_cast<Sizef>(tmp);
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

void Bulled::Hit(std::shared_ptr<Object> target)
{
}
