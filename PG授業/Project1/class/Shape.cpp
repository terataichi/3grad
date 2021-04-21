#include <DxLib.h>
#include "Shape.h"

Shape::Shape(Potision2 pos, Size size)
{
	pos_ = pos;
	size_ = size;
	col_ = 0xff;
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	DxLib::DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, col_, true);
}
