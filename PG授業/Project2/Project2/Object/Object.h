#pragma once
#include <memory>

#include "../common/Vector2.h"
#include "../Input/Controller.h"

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
};

