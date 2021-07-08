#include "Pawn.h"
#include "../Input/Keyboard.h"
#include "../Input/Gamepad.h"

Pawn::Pawn(Potision2f& pos, Vector2f& speed, ControllType& type) :Object(pos, speed)
{
	state_ = Anim_State::Normal;

	// コントローラーの設定
	if (type == ControllType::GamePad)
	{
		controller_ = std::make_unique<Gamepad>();
		return;
	}
	controller_ = std::make_unique<Keyboard>();
}

Pawn::~Pawn()
{
}
