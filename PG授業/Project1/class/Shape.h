#pragma once
#include "../common/Vector2.h"

// �}�`�N���X
class Shape
{
public:
	Shape(Potision2 pos, Size size);
	~Shape();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();
protected:
	Potision2 pos_;
	Size size_;
	int col_;

private:
};

