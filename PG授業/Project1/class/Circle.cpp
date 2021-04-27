#include "Circle.h"
#include <DxLib.h>

Circle::Circle(Potision2 pos, float radius):Shape(pos)
{
	pos_ = pos;
	radius_ = radius;
}

void Circle::Draw(void)
{
	DrawCircle(pos_.x, pos_.y, radius_, 0xfffff, true);
}

void Circle::Draw(float radius)
{
	
}

void Circle::Draw(Vector2 offset, float rate)
{
}
