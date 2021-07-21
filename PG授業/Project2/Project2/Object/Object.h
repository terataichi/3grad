#pragma once
#include <memory>
#include <string>
#include <list>

#include "../common/Vector2.h"
#include "../Input/Controller.h"
#include "../Status/Animation_State.h"

enum class ObjectType
{
	Non,
	Pawn,
	Actor,
};

class Object
{
public:
	Object(Potision2f& pos, Vector2f& speed, ObjectType&& objtype);
	virtual ~Object();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="type">�R���X�g���N�^�œ��͋@��̑I�������󂯎��</param>
	virtual void Init() = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta">�P�t���[��������̎��Ԃ����炤</param>
	/// <returns></returns>
	virtual bool Update() = 0;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="delta"></param>
	virtual void Draw() = 0;

	const ObjectType& GetObjectType(void)const;
protected:
	Potision2f pos_;										// �����̍��W
	Vector2f vel_;											// ���x
	Size size_;												// �傫��
	float radius_;											// ���a
	bool turn_;												// �������Ă邩�E�����Ă邩(�摜���E�����Ă���false�ŉE)
	const ObjectType objType_;
};

