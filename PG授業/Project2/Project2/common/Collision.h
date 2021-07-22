#pragma once
#include <list>
#include <memory>
#include "Vector2.h"

class Object;

class Collision
{
public:
	Collision();
	~Collision();

	/// <summary>
	/// 矩形判定
	/// </summary>
	/// <returns>当たったかどうか</returns>
	bool IsHitAABB(std::shared_ptr<Object> myself, std::shared_ptr<Object> target);
	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="myself">当たり判定したいオブジェクト</param>
	/// <param name="objList">判定に使うオブジェクトたち</param>
	void CheckCollision(std::shared_ptr<Object> myself, std::list<std::shared_ptr<Object>> objList);
private:
};


