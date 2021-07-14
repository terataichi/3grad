#pragma once

enum class InputID
{
	Up = 2,
	Down = 4,
	Left = 8,
	Right = 16,
	LowerLeft = Down + Left,
	LowerRight = Down + Right,
	UpperLeft = Up + Left,
	UpperRight = Up + Right,
	Button_1 = 32,
	Button_2 = 64,
	Button_3 = 128,
	Button_4 = 256,
	Max = 512,
};

InputID begin(InputID);
InputID end(InputID);
InputID operator++(InputID& key);
InputID operator* (InputID key);
