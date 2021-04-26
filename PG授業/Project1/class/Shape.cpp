#include <DxLib.h>
#include "Shape.h"

Shape::Shape(Potision2 pos, Size size)
{
	pos_ = pos;
	size_ = size;
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	DxLib::DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xffff, true);
}
