#include "Square.h"
#include <DxLib.h>
#include "System/SystemManager.h"

Square::Square(Potision2f&& pos, Size&& size, Vector2f&& speed, int&& color) :Shape(pos, size, speed, color)
{
	shapeType_ = ShapeType::Square;

	hitPoint_.emplace_back(pos);
	hitPoint_.emplace_back(Vector2f{ pos + Potision2f(size) });
	hitPoint_.emplace_back(Vector2f{ pos.x_ + size.x_,pos.y_ });
	hitPoint_.emplace_back(Vector2f{ pos.x_ ,pos.y_ + size.y_ });

	hitPoint_.emplace_back(Vector2f{ pos.x_ + size.x_ / 2,pos.y_ + size.y_ });
	hitPoint_.emplace_back(Vector2f{ pos.x_ + size.x_, pos.y_ + size.y_ / 2 });
	hitPoint_.emplace_back(Vector2f{ pos.x_ + size.x_ / 2,pos.y_ });
	hitPoint_.emplace_back(Vector2f{ pos.x_ ,pos.y_ + size.y_ / 2 });

}

Square::~Square()
{
}

void Square::Draw()
{
	auto pos = Potision2(pos_);
	DxLib::DrawBox(pos.x_, pos.y_, pos.x_ + size_.x_, pos.y_ + size_.y_, color_, true);
}

void Square::Draw(float rate)
{
	auto pos = Potision2(pos_);
	DxLib::DrawBox(pos.x_, pos.y_, pos.x_ + size_.x_ * static_cast<int>(rate), pos.y_ + size_.y_ * static_cast<int>(rate), color_, true);
}

void Square::Draw(Vector2 offset, float rate)
{
	
	Vector2 pos{ pos_ + Vector2f(offset) - Vector2f(size_) * rate * (Vector2f(offset) / Vector2f(size_)) };

	DxLib::DrawBox(
		pos.x_,
		pos.y_,
		pos.x_ + size_.x_ * static_cast<int>(rate),
		pos.y_ + size_.y_ * static_cast<int>(rate),
		color_, true);

	Draw();
}

bool Square::Update(const float& delta, const ShapeVec& vec)
{
	Shape::Update(delta, vec);
	return false;
}

Vector2f Square::CheckHitWall(const ShapeVec& vec)
{
	if (pos_.x_ + size_.x_ >= static_cast<float>(lpSysMng.GetScreenSize("x")) ||
		pos_.x_ <= 0.0f)
	{
		Vector2f n1 = { 0.0f,static_cast<float>(lpSysMng.GetScreenSize("y")) };

		auto ref = Reflection(Normal(n1).Normalized());
		color_ = rand() % 0xffffff;
		return Reflection(Normal(n1).Normalized());
	}
	if (pos_.y_ + size_.y_ >= static_cast<float>(lpSysMng.GetScreenSize("y")) ||
		pos_.y_ <= 0.0f)
	{
		Vector2f n1 = { static_cast<float>(lpSysMng.GetScreenSize("x")),0.0f };
		color_ = rand() % 0xffffff;
		return Reflection(Normal(n1).Normalized());
	}
	return { 0.0f,0.0f };
}

void Square::HitShape(const SharedShape& shape)
{
	if (myNamber_ == shape->GeyMyNamber())
	{
		return;
	}

	if (shape->GetType() == ShapeType::Square)
	{
		CheckHitSquare(shape);
	}
	if (shape->GetType() == ShapeType::Circle)
	{
		CheckHitSquareCircle(pos_, size_, shape->GetPotision(), shape->GetRadius());
	}
	if (shape->GetType() == ShapeType::Triangle)
	{
		CheckHitShapeTriangle(hitPoint_, shape->GetPoint());
	}
}
