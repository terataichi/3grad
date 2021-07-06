#pragma once
#include <memory>
#include "../common/Vector2.h"

class BaseScene;
using UniqueBase = std::unique_ptr<BaseScene>;

enum class SceneName
{
	Transition,
	Title,
	Game,
	Max
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	/// <summary>
	/// BaseScene�̃R���X�g���N�^�œǂ�ł���
	/// </summary>
	virtual bool Init(void) = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="deltaTime">�P�t���[���Ԃ̎���</param>
	virtual UniqueBase Update(UniqueBase scene) = 0;
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="deltaTime">�P�t���[���Ԃ̎���</param>
	virtual void Draw();
	/// <summary>
	/// �����̎����Ă���X�N���[����`��
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void DrawOwnScreen() = 0;
	/// <summary>
	/// �������Ȃ�̃V�[���Ȃ̂�
	/// </summary>
	virtual SceneName MyName() = 0;
	/// <summary>
	/// �X�N���[��ID�擾
	/// </summary>
	/// <returns>�X�N���[��ID</returns>
	const int& GetScreenID(void);

protected:
	int screenID_;
	Size screenSize_;
};

