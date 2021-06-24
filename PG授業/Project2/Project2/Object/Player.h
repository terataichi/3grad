#pragma once
#include <memory>

#include "Object.h"

class Controller;
class TmxAnimation;

class Player:
	public Object
{
public:
	Player(Potision2f&& pos, Vector2f&& speed, ControllType type = ControllType::Keybord);
	~Player();

	void Init(ControllType type)override;
	bool Update(const double& delta) override;
	void Draw(const double& delta) override;
private:
};

