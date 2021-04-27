#include "Square.h"
#include <DxLib.h>

Square::Square(Potision2 pos, Size size) :Shape(pos, size)
{
}

Square::~Square()
{
}

void Square::Draw()
{
	DxLib::DrawBox(pos_.x, pos_.y, pos_.x + size_.x, pos_.y + size_.y, 0xffff, true);
}

void Square::Draw(float rate)
{
	DxLib::DrawBox(pos_.x, pos_.y, pos_.x + size_.x * rate, pos_.y + size_.y * rate, 0xffff, true);
}

void Square::Draw(Vector2 offset, float rate)
{


	Vector2 pos{ (int)(pos_ + offset - (size_ * static_cast<int>(rate)) * (offset.x / (float)size_.x)),
				 (pos_.y + offset.y - size_.y * rate * (offset.y / (float)size_.y)) };



	DxLib::DrawBox(
		pos.x,
		pos.y,
		pos.x + (size_.x * rate),
		pos.y + (size_.x * rate),
		0xff, true);

	//Draw();
}
