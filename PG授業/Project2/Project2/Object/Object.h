#pragma once
#include <memory>
#include <string>

#include "../common/Vector2.h"
#include "../Input/Controller.h"
#include "../common/AnimationManager.h"


class Object
{
public:
	Object();
	Object(Potision2f& pos, Vector2f& speed, Size& size);
	~Object();

	virtual void Init(ControllType type) = 0;
	virtual bool Update(const double& delta) = 0;
	virtual void Draw(const double& delta) = 0;
protected:
	std::unique_ptr<Controller> controller_;

	Potision2f pos_;
	Vector2f speed_;
	Size size_;
	float radius_;
	double elapsedTime_;			// �o�ߎ��ԕێ��p
	std::string animKey_;			// �o�^�����A�j���[�V������key�ۑ��p
	Animation_State state_;			// �X�e�[�^�X�Ǘ��p
};

