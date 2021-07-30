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

enum class TeamTag
{
	Non,
	Red,
	Green,
	Bule,
	Yellow,
	Max
};

class Object
{
public:
	Object(Potision2f& pos, Vector2f& speed, ObjectType&& objtype, TeamTag tag = TeamTag::Non);
	virtual ~Object();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="type">�R���X�g���N�^�œ��͋@��̑I�������󂯎��</param>
	virtual void Init(void) = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta">�P�t���[��������̎��Ԃ����炤</param>
	/// <returns></returns>
	virtual bool Update(void) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="delta"></param>
	virtual void Draw(void) = 0;
	/// <summary>
	/// �I�u�W�F�N�g���m�œ��������Ƃ��ɌĂяo��
	/// </summary>
	/// <param name="obj">������������̃|�C���^</param>
	virtual void Hit(std::shared_ptr<Object> target) = 0;
	/// <summary>
	/// UI�̎d�g�݂�����ĂȂ������̂ŉ�
	/// </summary>
	virtual void DrawStatus() {};

	const Potision2f& GetPotision(void)const;
	const Sizef& GetSize(void)const;
	const ObjectType& GetObjectType(void)const;
	const int& GetObjID(void)const;
	void ResetObjID(void);
	const TeamTag GetTeamTag(void)const;
	const Anim_State GetAnimState(void)const;
	virtual const bool IsActive(void);
protected:
	Potision2f pos_;										// �����̍��W
	Vector2f vel_;											// ���x
	Sizef size_;											// �傫��
	float radius_;											// ���a
	bool turn_;												// �������Ă邩�E�����Ă邩(�摜���E�����Ă���false�ŉE)
	const ObjectType objType_;

	std::string animKey_;									// �o�^�����A�j���[�V������key�ۑ��p
	Anim_State animState_;									// �X�e�[�^�X�Ǘ��p

	bool active_;

	TeamTag teamTag_;
	int objID_;											    // �����̔ԍ�
private:
	static int instanceCount_;								// ��������邽�т�+�P
};

