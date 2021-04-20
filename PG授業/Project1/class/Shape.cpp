#include <DxLib.h>
#include "Shape.h"

Shape::Shape()
{
	x_ = 100;
	y_ = 100;
	sizeX_ = 50;
	sizeY_ = 50;
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	DxLib::DrawBox(x_, y_, x_ + sizeX_, y_ + sizeY_, 0xfff, true);
}
