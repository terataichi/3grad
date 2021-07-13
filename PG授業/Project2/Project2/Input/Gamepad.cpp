#include "Gamepad.h"
#include <DxLib.h>

Gamepad::Gamepad() :Controller()
{

	// êlêîÇ™ëùÇ¶ÇÈÇ∆ëΩÇ≠Ç»ÇÈÇÊÇ§Ç…ÇµÇΩÇ¢
	padID_ = DX_INPUT_PAD1;
	// ìoò^
	config_ =
	{
		{InputID::Left,PAD_INPUT_LEFT},
		{InputID::Up,PAD_INPUT_UP},
		{InputID::Right,PAD_INPUT_RIGHT},
		{InputID::Down,PAD_INPUT_DOWN},
		{InputID::Button_1,PAD_INPUT_1},
		{InputID::Button_2,PAD_INPUT_2},
		{InputID::Button_3,PAD_INPUT_3},
		{InputID::Button_4,PAD_INPUT_4},
	};
}

Gamepad::~Gamepad()
{
}

ControllType Gamepad::GetControllType(void)
{
	return ControllType::GamePad;
}

void Gamepad::Update(void)
{
	// OldèÓïÒÇ∆NowèÓïÒÇÃçXêV
	for (auto id : InputID())
	{
		triggerMap_[id].second = triggerMap_[id].first;
		triggerMap_[id].first = (GetJoypadInputState(padID_) & config_[id]);
	}
	UpdateRingBuf();
}
