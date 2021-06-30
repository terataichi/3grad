#pragma once
#include "Vector2.h"

class Raycast
{
public:
	struct Ray
	{
		Vector2f p1;		// �n�_
		Vector2f p2;		// �I�_
		Vector2f v;			// �����x�N�g��
	};

	struct Line
	{
		Vector2f p1;		// �n�_
		Vector2f p2;		// �I�_
		Vector2f vec() 
		{ 
			return p2 - p1; 
		};
	};

	bool CheckCollision(Ray ray, std::pair<Potision2f, Sizef> col);
	bool CheckRay(Ray ray, Line line);
private:
};

