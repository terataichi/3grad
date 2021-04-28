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
	DxLib::DrawBox(pos_.x_, pos_.y_, pos_.x_ + size_.x_, pos_.y_ + size_.y_, 0xffff, true);
}

void Square::Draw(float rate)
{
	DxLib::DrawBox(pos_.x_, pos_.y_, pos_.x_ + size_.x_ * static_cast<int>(rate), pos_.y_ + size_.y_ * static_cast<int>(rate), 0xffff, true);
}

void Square::Draw(Vector2 offset, float rate)
{
	
	Vector2 pos{ pos_ + offset - size_ * static_cast<int>(rate) * (offset / size_) };

	DxLib::DrawBox(
		pos.x_,
		pos.y_,
		pos.x_ + size_.x_ * static_cast<int>(rate),
		pos.y_ + size_.y_ * static_cast<int>(rate),
		0xff, true);

	Draw();
}
