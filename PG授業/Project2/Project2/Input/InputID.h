#pragma once

enum class InputID
{
	Up,
	Down,
	Left,
	Right,
	Button_1,
	Button_2,
	Button_3,
	Max
};

InputID begin(InputID);
InputID end(InputID);
InputID operator++(InputID& key);
InputID operator* (InputID key);
