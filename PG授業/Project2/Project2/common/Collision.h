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
	/// ��`����
	/// </summary>
	/// <returns>�����������ǂ���</returns>
	bool IsHitAABB(std::shared_ptr<Object> myself, std::shared_ptr<Object> target);
	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="myself">�����蔻�肵�����I�u�W�F�N�g</param>
	/// <param name="objList">����Ɏg���I�u�W�F�N�g����</param>
	void CheckCollision(std::shared_ptr<Object> myself, std::list<std::shared_ptr<Object>> objList);
private:
};


