#pragma once
#include <memory>
#include <string>

#include "../common/Vector2.h"
#include "../Input/Controller.h"
#include "../common/AnimationManager.h"


class Object
{
public:
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
	bool turn_;						// 左向いてるか右向いてるか(画像が右向いてたらfalseで右)
	double elapsedTime_;			// 経過時間保持用
	std::string animKey_;			// 登録したアニメーションのkey保存用
	Animation_State state_;			// ステータス管理用
};

