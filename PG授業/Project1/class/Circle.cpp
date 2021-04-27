#include "Circle.h"
#include <DxLib.h>

Circle::Circle(Potision2 pos, int radius):Shape(pos)
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
