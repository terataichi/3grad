#pragma once
#include "../common/Vector2.h"

// ê}å`ÉNÉâÉX
class Shape
{
public:
	Shape(Potision2 pos, Size size);
	~Shape();

	/// <summary>
	/// ï`âÊ
	/// </summary>
	virtual void Draw();
protected:
	Potision2 pos_;
	Size size_;
	int col_;

private:
};

