#include "Carrot.h"
#include "Triangle.h"
#include "Square.h"
void Carrot::Draw()
{
	for (auto& shape : shapeVec_)
	{
		shape->Draw();
	}
}

void Carrot::Draw(float rate)
{
}

Vector2f Carrot::CheckHitWall(const ShapeVec& shapeVec)
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


void Carrot::HitShape(const SharedShape& shape)
{
	if (shape->GetHit())
	{
		alive_ = false;
	}
}

Carrot::Carrot(Potision2f&& pos, Vector2f&& speed, int&& color) :Shape(pos, speed, color)
{
	float offset = -50;
	nowSpeed_ = speed;
	green_ = 0x00ff00;
	orange_ = 0xff9211;
	defSize_ = Size{ 10,50 };
	shapeType_ = ShapeType::Carrot;
	shapeVec_.emplace_back(std::make_shared<Square>(Potision2f{ 15,offset } + pos, Size{ 10,50 }, Vector2f{ speed.x_,speed.y_ }, 0x00ff00));
	shapeVec_.emplace_back(std::make_shared<Square>(Potision2f{ 35,offset } + pos, Size{ 10,50 }, Vector2f{ speed.x_,speed.y_ }, 0x00ff00));
	shapeVec_.emplace_back(std::make_shared<Square>(Potision2f{ 55,offset } + pos, Size{ 10,50 }, Vector2f{ speed.x_,speed.y_ }, 0x00ff00));
	shapeVec_.emplace_back(std::make_shared<Triangle>(Potision2f{ pos }, Potision2f{ 80,0 } + pos, Potision2f{ 40,100 } + pos, Vector2f{ speed.x_,speed.y_ }, 0xff9211));
}

bool Carrot::Update(const float& delta, const ShapeVec& vec)
{
	for (auto& shape : shapeVec_)
	{
		shape->Update(delta, vec);

		if (shape->GetType() == ShapeType::Square)
		{
			if (shape->GetSize().x_ < defSize_.x_ || shape->GetSize().y_ < defSize_.y_)
			{
				shape->SetAlive(false);
			}
		}

		if (shape->GetType() == ShapeType::Square)
		{
			shape->SetColor(green_);
		}
		else if (shape->GetType() == ShapeType::Triangle)
		{
			shape->SetColor(orange_);
		}
	}

	shapeVec_.erase(std::remove_if(shapeVec_.begin(), shapeVec_.end(), [&](SharedShape& s) {return !s->GetAlive(); }), shapeVec_.end());

	auto refSpeed = CheckHitWall(vec);
	if (refSpeed != Vector2f{ 0.0f,0.0f })
	{
		speed_ = refSpeed;
		for (auto& shape : shapeVec_)
		{
			shape->SetSpeed(speed_);
		}
	}
	return false;
}
