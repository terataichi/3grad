#pragma once

enum class InputID
{
	Up = 1,
	Down = 2,
	Left = 4,
	Right = 8,
	Button_1 = 16,
	Button_2 = 32,
	Button_3 = 64,
	Button_4 = 128,
	Max = 256,
};

enum class CommandID
{
	Up = 1,
	Down = 2,
	Left = 4,
	Right = 8,
	LowerLeft = Down + Left,
	LowerRight = Down + Right,
	UpperLeft = Up + Left,
	UpperRight = Up + Right,
	Button_1 = 16,
	Button_2 = 32,
	Button_3 = 64,
	Button_4 = 128,
	Max = 256,
};

InputID begin(InputID);
InputID end(InputID);
InputID operator++(InputID& key);
InputID operator* (InputID key);
