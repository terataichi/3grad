#include <DxLib.h>
#include "Shape.h"

Shape::Shape(Potision2 pos, Size size)
{
	pos_ = pos;
	size_ = size;
}

Shape::Shape(Potision2 pos, float radius)
{
}

Shape::Shape(Potision2 pos)
{
	pos_ = pos;
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	DxLib::DrawBox(pos_.x_, pos_.y_, pos_.x_ + size_.x_, pos_.y_ + size_.y_, 0xffff, true);
}
