#include "Circle.h"
#include <DxLib.h>
#include <cmath>
#include "System/SystemManager.h"

Circle::Circle(Potision2f&& pos, float&& radius, Vector2f&& speed, int&& color) :Shape(pos, radius, speed,color)
{
	shapeType_ = ShapeType::Circle;
	radius_ = radius;

	for (int i = 0; i < 360; i++)
	{
		if (i % 30 == 0)
		{
			hitPoint_.emplace_back(Vector2f{ pos.x_ + radius_ * cosf(DX_PI_F / 180.0f * i),pos.x_ + radius_ * sinf(DX_PI_F / 180.0f * i) });
		}
	}
}

void Circle::Draw(void)
{
	Vector2 pos = Vector2(pos_);
	DrawCircle(pos.x_, pos.y_, static_cast<int>(radius_), color_, true);
}

void Circle::Draw(float rate)
{
	Vector2 pos = Vector2(pos_);
	DrawCircle(pos.x_, pos.y_, static_cast<int>(radius_ * rate), color_, true);
}

bool Circle::Update(const float& delta, const ShapeVec& vec)
{
	Shape::Update(delta, vec);
	return false;
}

Vector2f Circle::CheckHitWall(const ShapeVec& vec)
{
	if (pos_.x_ + radius_ >= static_cast<float>(lpSysMng.GetScreenSize("x"))||
		pos_.x_ - radius_ <= 0.0f)
	{
		Vector2f n1 = { 0.0f,static_cast<float>(lpSysMng.GetScreenSize("y")) };
		return Reflection(Normal(n1).Normalized());

	}
	if (pos_.y_ + radius_ >= static_cast<float>(lpSysMng.GetScreenSize("y")) ||
		pos_.y_ - radius_ <= 0.0f)
	{
		Vector2f n2 = { static_cast<float>(lpSysMng.GetScreenSize("x")),0.0f };
		return Reflection(Normal(n2).Normalized());
	}
	return { 0.0f,0.0f };
}

void Circle::HitShape(const SharedShape& shape)
{
	if (myNamber_ == shape->GeyMyNamber())
	{
		return;
	}

	if (shape->GetType() == ShapeType::Circle)
	{
		CheckHitCircle(shape);
	}
	else if(shape->GetType() == ShapeType::Square)
	{
		CheckHitSquareCircle(shape->GetPotision(), shape->GetSize(), pos_, radius_);
	}
	else if (shape->GetType() == ShapeType::Triangle)
	{
		CheckHitShapeTriangle(hitPoint_, shape->GetPoint());
	}
}
