#pragma once
#include "Vector2.h"

class Raycast
{
public:
	struct Ray
	{
		Vector2f p1;		// 始点
		Vector2f p2;		// 終点
		Vector2f v;			// 方向ベクトル
	};

	struct Line
	{
		Vector2f p1;		// 始点
		Vector2f p2;		// 終点
		Vector2f vec() 
		{ 
			return p2 - p1; 
		};
	};

	bool CheckCollision(Ray ray, std::pair<Potision2f, Sizef> col);
	bool CheckRay(Ray ray, Line line);
private:
};

