#pragma once
#include "../common/Vector2.h"

// �}�`�N���X
class Shape
{
public:
	Shape(Potision2 pos, Size size);
	Shape(Potision2 pos);
	~Shape();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;
	virtual void Draw(float rate) = 0;
	virtual void Draw(Vector2 offset, float rate = 1) = 0;
protected:
	Potision2 pos_;
	Size size_;
private:
};

