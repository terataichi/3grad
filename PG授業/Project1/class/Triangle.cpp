#include "Triangle.h"
#include "System/SystemManager.h"
#include "../common/Vector2.h"
#include <DxLib.h>

Triangle::Triangle(Vector2f&& point1, Vector2f&& point2, Vector2f&& point3, Vector2f&& speed, int&& color) :Shape(point1, point2, point3, speed, color)
{
	shapeType_ = ShapeType::Triangle;
	pos_ = { 0,0 };
}

Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	auto tmpPoint = point_;

	DrawTriangle(point_[0].x_, point_[0].y_, point_[1].x_, point_[1].y_, point_[2].x_, point_[2].y_, color_, true);
}

void Triangle::Draw(float rate)
{
	auto color = 0x00ff00;
	auto ratePoint = point_;

	for (int i = 0; i < ratePoint.size(); i++)
	{
		ratePoint[i] *= static_cast<int>(rate);
	}

	DrawTriangle(ratePoint[0].x_, ratePoint[0].y_, ratePoint[1].x_, ratePoint[1].y_, ratePoint[2].x_, ratePoint[2].y_, color, true);
}

bool Triangle::Update(const float& delta, const ShapeVec& vec)
{
	auto refSpeed = CheckHitWall(vec);
	if (refSpeed != Vector2f{ 0.0f,0.0f })
	{
		speed_ = refSpeed;
	}
	for (auto& shape : vec)
	{
		HitShape(shape);
	}
	// “®‚«
	for (auto& p : point_)
	{
		p += speed_ * delta;
	}

	return false;
}

Vector2f Triangle::CheckHitWall(const ShapeVec& vec)
{
	for (auto p : point_)
	{
		if (p.x_ >= static_cast<float>(lpSysMng.GetScreenSize("x")) ||
			p.x_ <= 0.0f)
		{
			Vector2f n1 = { 0.0f,static_cast<float>(lpSysMng.GetScreenSize("y")) };
			color_ = rand() % 0xff0000;
			return Reflection(Normal(n1).Normalized());
		}
		if (p.y_ >= static_cast<float>(lpSysMng.GetScreenSize("y")) ||
			p.y_ <= 0.0f)
		{
			Vector2f n1 = { static_cast<float>(lpSysMng.GetScreenSize("x")),0.0f };
			color_ = rand() % 0x00ff00;
			return Reflection(Normal(n1).Normalized());
		}
	}
	return { 0.0f,0.0f };
}

void Triangle::HitShape(const SharedShape& shape)
{
	if (myNamber_ == shape->GeyMyNamber())
	{
		return;
	}

	if (shape->GetType() == ShapeType::Triangle)
	{
		CheckHitTriangle(shape);
	}
	if (shape->GetType() == ShapeType::Square || shape->GetType() == ShapeType::Circle)
	{
		CheckHitShapeTriangle(shape->GetHitPoint(), point_);
	}
}
