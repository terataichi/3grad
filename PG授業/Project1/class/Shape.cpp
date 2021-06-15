#include <DxLib.h>
#include "Shape.h"
#include "../class/System/SystemManager.h"

int Shape::objectNumber_ = 0;

Shape::Shape()
{
	Init();
}

Shape::Shape(Potision2f& pos, Size& size, Vector2f& speed, int& color)
	:pos_(pos), size_(size), speed_(speed), color_(color), defSpeed_(speed)
{
	Init();
}

Shape::Shape(Potision2f& pos, float& radius, Vector2f& speed, int& color)
	:pos_(pos), radius_(radius), speed_(speed), color_(color), defSpeed_(speed)
{
	Init();
}

Shape::Shape(Potision2f& pos, Vector2f& speed, int& color)
	: pos_(pos), speed_(speed), color_(color), defSpeed_(speed)
{
	Init();
}

Shape::Shape(Vector2f& point1, Vector2f& point2, Vector2f& point3, Vector2f& speed, int& color)
{
	speed_ = speed;
	defSpeed_ = speed;
	color_ = color;
	point_.push_back(point1);
	point_.push_back(point2);
	point_.push_back(point3);
	Init();
}

Shape::~Shape()
{
}

const bool Shape::GetAlive(void)const
{
	return alive_;
}

const Potision2f& Shape::GetPotision(void)const
{
	return pos_;
}

const int& Shape::GeyMyNamber(void) const
{
	return myNamber_;
}

const int& Shape::GetColor(void) const
{
	return color_;
}

const Vector2f& Shape::GetSpeed(void) const
{
	return speed_;
}

ShapeType Shape::GetType(void) const
{
	return shapeType_;
}

const float Shape::GetRadius(void) const
{
	return radius_;
}

const Size Shape::GetSize(void) const
{
	return size_;
}

const std::vector<Vector2f> Shape::GetPoint(void) const
{
	return point_;
}

const std::vector<Potision2f> Shape::GetHitPoint(void) const
{
	return hitPoint_;
}

const bool Shape::GetHit() const
{
	return hit_;
}

bool Shape::Update(const float& delta, const ShapeVec& shapeVec)
{
	if (!alive_)
	{
		return false;
	}

	//if (speed_ >= defSpeed_)
	//{
	//	speed_ -= Vector2f{5, 5} * delta;
	//}

	auto refSpeed = CheckHitWall(shapeVec);
	if (refSpeed != Vector2f{ 0.0f,0.0f })
	{
		speed_ = refSpeed;
	}
	for (auto& shape : shapeVec)
	{
		HitShape(shape);
	}
	pos_ += speed_ * delta;
	for (auto& hitp : hitPoint_)
	{
		hitp += speed_ * delta;
	}
	return true;
}

void Shape::Draw()
{
	auto pos = Vector2(pos_);
	DxLib::DrawBox(pos.x_, pos.y_, pos.x_ + size_.x_, pos.y_ + size_.y_, 0xffff, true);
}

bool Shape::CheckHitSquare(const SharedShape& shape)
{
	auto tmpPos = shape->GetPotision();
	auto tmpSize = shape->GetSize();

	if (pos_.x_ <= tmpPos.x_ + tmpSize.x_ &&
		tmpPos.x_ <= pos_.x_ + size_.x_ &&
		pos_.y_ <= tmpPos.y_ + tmpSize.y_ &&
		tmpPos.y_ <= pos_.y_ + size_.y_)
	{
		return true;
	}
	return false;
}

bool Shape::CheckHitCircle(const SharedShape& shape)
{
	float a = pos_.x_ - shape->pos_.x_;
	float b = pos_.y_ - shape->pos_.y_;

	float c = a * a + b * b;
	float r = (radius_ + shape->GetRadius()) * (radius_ + shape->GetRadius());

	if (c <= r)
	{
		return true;
	}

	return false;
}

bool Shape::CheckHitTriangle(const SharedShape& shape)
{

	for (auto& p : shape->GetPoint())
	{
		Vector2f AB = point_[1] - point_[0];
		Vector2f BP = p - point_[1];
		float c1 = Cross(AB, BP);

		Vector2f BC = point_[2] - point_[1];
		Vector2f CP = p - point_[2];
		float c2 = Cross(BC, CP);

		Vector2f CA = point_[0] - point_[2];
		Vector2f AP = p - point_[0];
		float c3 = Cross(CA, AP);

		if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) 
		{
			return true;
		}
	}

	return false;
}

bool Shape::CheckHitSquareCircle(const Potision2f& sPos, const Size& sSize,const Potision2f& cPos,const float& cRadius)
{
	// “ñæ
	auto squared = [](float num) 
	{
		return num * num;
	};

	// Šp‚Ì”»’è
	bool check1 = squared(sPos.x_ - cPos.x_) + squared(sPos.y_ - cPos.y_) < squared(cRadius);
	bool check2 = squared((sPos.x_ + sSize.x_) - cPos.x_) + squared(sPos.y_ - cPos.y_) < squared(cRadius);
	bool check3 = squared((sPos.x_ + sSize.x_) - cPos.x_) + squared((sPos.y_ + sSize.y_) - cPos.y_) < squared(cRadius);
	bool check4 = squared(sPos.x_ - cPos.x_) + squared((sPos.y_ + sSize.y_) - cPos.y_) < squared(cRadius);

	// c‚Æ‰¡‚Å”¼Œa‚ª’†‚É“ü‚Á‚Ä‚«‚Ä‚é‚©‚Ç‚¤‚©
	bool check5 = (sPos.x_ < cPos.x_) && (sPos.x_ + sSize.x_ > cPos.x_) &&
				(sPos.y_ - cRadius < cPos.y_) && (sPos.y_ + sSize.y_ + cRadius > cPos.y_);

	bool check6 = (sPos.x_ - cRadius < cPos.x_) && (sPos.x_ + sSize.x_ + cRadius > cPos.x_)&&
				(sPos.y_ < cPos.y_) && (sPos.y_ + sSize.y_ > cPos.y_);

	// ƒfƒoƒbƒO—p
	if (check1 || check2 || check3 || check4 || check5 || check6)
	{
		return true;
	}
	return false;
}

bool Shape::CheckHitShapeTriangle(const std::vector<Potision2f>& sPoint, const std::vector<Vector2f>& tpoint)
{
	for (auto& p : sPoint)
	{
		Vector2f AB = tpoint[1] - tpoint[0];
		Vector2f BP = p - tpoint[1];
		float c1 = Cross(AB, BP);

		Vector2f BC = tpoint[2] - tpoint[1];
		Vector2f CP = p - tpoint[2];
		float c2 = Cross(BC, CP);

		Vector2f CA = tpoint[0] - tpoint[2];
		Vector2f AP = p - tpoint[0];
		float c3 = Cross(CA, AP);

		if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0))
		{
			return true;
		}
	}
	return false;
}

void Shape::SetAlive(bool alive)
{

	if (muteki_ > 0)
		return;
	alive_ = alive;
}

void Shape::SetPotision(Potision2f& pos)
{
	pos_ = pos;
}

void Shape::SetColor(int c)
{
	color_ = c;
}

void Shape::SetSpeed(Vector2f vec)
{
	speed_ = vec;
}

void Shape::MultiplySpeed(Vector2f vec)
{
	if (mutekiCount_ <= 0.0)
	{
		if (multiplyCount_ <= 2)
		{
			speed_ *= vec;
			multiplyCount_++;
		}
	}
}

void Shape::SetHit(bool hit)
{
	hit_ = hit;
}

void Shape::SetRadius(float radius)
{
	radius_ = radius;
}

void Shape::SetSize(Size size)
{
	size_ = size;
}

Vector2f Shape::Reflection(Vector2f N)
{
	auto a = Dot(-speed_, N);
	return speed_ + (N * (a * 2));
}

void Shape::NewShape()
{
	Vector2f n1 = { 0.0f,static_cast<float>(lpSysMng.GetScreenSize("y")) };
	Reflection(Normal(n1).Normalized());
}

void Shape::Init(void)
{
	myNamber_ = objectNumber_;
	objectNumber_++;
	alive_ = true;
	hit_ = false;
	radius_ = 0;
	muteki_ = 0;
	mutekiCount_ = 0;
	multiplyCount_ = 0;
}
