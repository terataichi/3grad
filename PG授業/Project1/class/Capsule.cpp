#include "Capsule.h"
#include "Circle.h"
#include "Square.h"

Capsule::Capsule(Potision2f&& pos, Vector2f&& speed, int&& color)
{
	shapeType_ = ShapeType::Carrot;
	size_ = { 100,100 };
	radius_ = size_.x_ / 2;
	refcnt_ = 0;

	shapeVec_.emplace_back(std::make_shared<Circle>(Potision2f{ pos.x_ + size_.x_ / 2 ,pos.y_ }, std::move(radius_), Vector2f{ speed }, 0x00ff00));
	shapeVec_.emplace_back(std::make_shared<Circle>(Potision2f{ pos.x_ + size_.x_ / 2 ,pos.y_ + size_.y_ }, std::move(radius_), Vector2f{ speed }, 0x00ff00));
	shapeVec_.emplace_back(std::make_shared<Square>(Potision2{ pos }, Size{ size_ + 1 }, Vector2f{ speed }, 0x00ff00));
}

void Capsule::Draw()
{
	for (auto& shape : shapeVec_)
	{
		shape->Draw();
	}
}

void Capsule::Draw(float rate)
{
	for (auto& shape : shapeVec_)
	{
		shape->Draw();
	}
}

bool Capsule::Update(const float& delta, const ShapeVec& vec)
{
	int cnt = 0;
	for (auto& shape : shapeVec_)
	{
		shape->Update(delta, vec);
		if (shape->GetType() == ShapeType::Circle)
		{
			if (radius_ > shape->GetRadius())
			{
				radius_ = shape->GetRadius();
			}
			else
			{
				shape->SetRadius(radius_);
			}
			Sizef sizef = size_ - 1;
			Potision2f pos = Potision2f{ pos_.x_ + sizef.x_ / 2, pos_.y_ + sizef.y_ * cnt };
			cnt++;
			shape->SetPotision(pos);
		}
		else
		{
			auto iRadius = static_cast<int>(radius_);
			size_ = Size{ iRadius ,iRadius } * 2 + 1;
			shape->SetSize(size_);
			pos_ = shape->GetPotision();
		}
	}


	if (refcnt_ < 0)
	{
		auto refSpeed = CheckHitWall(vec);
		if (refSpeed != Vector2f{ 0.0f,0.0f })
		{
			speed_ = refSpeed;
			for (auto& shape : shapeVec_)
			{
				shape->SetSpeed(speed_);
				refcnt_ = 0.2;
			}
		}
	}
	else
	{
		refcnt_ -= delta;
	}

	return false;
}

void Capsule::HitShape(const SharedShape& shape)
{
}

Vector2f Capsule::CheckHitWall(const ShapeVec& shapeVec)
{
	auto vec = shapeVec_.front()->GetSpeed();

	if (vec != nowSpeed_)
	{
		nowSpeed_ = vec;
		return vec;
	}

	for (auto shape : shapeVec_)
	{
		if (vec != shape->GetSpeed())
		{
			nowSpeed_ = shape->GetSpeed();
			return nowSpeed_;
		}
	}

	return { 0.0f,0.0f };
}
