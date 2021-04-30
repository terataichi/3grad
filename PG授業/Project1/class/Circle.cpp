#include "Circle.h"
#include <DxLib.h>

Circle::Circle(Potision2 pos, float radius):Shape(pos)
{
	pos_ = pos;
	radius_ = radius;
}

void Circle::Draw(void)
{
	DrawCircle(pos_.x_, pos_.y_, static_cast<int>(radius_), 0xf54242, true);
}

void Circle::Draw(float rate)
{
	DrawCircle(pos_.x_, pos_.y_, static_cast<int>(radius_ * rate), 0xf54242, true);
}

void Circle::Draw(Vector2 offset, float rate)
{
	DrawCircle(pos_.x_ + offset.x_, pos_.y_ + offset.y_, static_cast<int>(radius_ * rate), 0xf54242, true);
}
