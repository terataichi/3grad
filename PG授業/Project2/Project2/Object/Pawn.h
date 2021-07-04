#pragma once
#include "Object.h"

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type);
	~Pawn();

protected:
	std::unique_ptr<Controller> controller_;				// �R���g���[���[�̏��ێ��p

	double elapsedTime_;									// �o�ߎ��ԕێ��p
	std::string animKey_;									// �o�^�����A�j���[�V������key�ۑ��p
	Animation_State state_;									// �X�e�[�^�X�Ǘ��p

	friend struct RunState;
	friend struct NormalState;
};

