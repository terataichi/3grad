#pragma once
#include <memory>
#include <string>

#include "../common/Vector2.h"
#include "../Input/Controller.h"
#include "../common/AnimationManager.h"


class Object
{
public:
	Object(Potision2f& pos, Vector2f& speed);
	~Object();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="type">�R���X�g���N�^�œ��͋@��̑I�������󂯎��</param>
	virtual void Init(ControllType type) = 0;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta">�P�t���[��������̎��Ԃ����炤</param>
	/// <returns></returns>
	virtual bool Update(const double& delta) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="delta"></param>
	virtual void Draw(const double& delta) = 0;
protected:
	std::unique_ptr<Controller> controller_;				// �R���g���[���[�̏��ێ��p

	Potision2f pos_;										// �����̍��W
	Vector2f speed_;										// ���x
	Size size_;												// �傫��
	float radius_;											// ���a
	bool turn_;												// �������Ă邩�E�����Ă邩(�摜���E�����Ă���false�ŉE)
	double elapsedTime_;									// �o�ߎ��ԕێ��p
	std::string animKey_;									// �o�^�����A�j���[�V������key�ۑ��p
	Animation_State state_;									// �X�e�[�^�X�Ǘ��p
};

