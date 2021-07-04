#pragma once
#include "Object.h"

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type);
	~Pawn();

protected:
	std::unique_ptr<Controller> controller_;				// コントローラーの情報保持用

	double elapsedTime_;									// 経過時間保持用
	std::string animKey_;									// 登録したアニメーションのkey保存用
	Animation_State state_;									// ステータス管理用

	friend struct RunState;
	friend struct NormalState;
};

