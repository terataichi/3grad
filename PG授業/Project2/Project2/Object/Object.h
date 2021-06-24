#pragma once
#include <memory>
#include <string>

#include "../common/Vector2.h"
#include "../Input/Controller.h"
#include "../common/AnimationManager.h"


class Object
{
public:
	Object(Potision2f& pos, Vector2f& speed);
	~Object();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="type">コンストラクタで入力機器の選択情報を受け取る</param>
	virtual void Init(ControllType type) = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta">１フレーム当たりの時間をもらう</param>
	/// <returns></returns>
	virtual bool Update(const double& delta) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="delta"></param>
	virtual void Draw(const double& delta) = 0;
protected:
	std::unique_ptr<Controller> controller_;				// コントローラーの情報保持用

	Potision2f pos_;										// 自分の座標
	Vector2f speed_;										// 速度
	Size size_;												// 大きさ
	float radius_;											// 半径
	bool turn_;												// 左向いてるか右向いてるか(画像が右向いてたらfalseで右)
	double elapsedTime_;									// 経過時間保持用
	std::string animKey_;									// 登録したアニメーションのkey保存用
	Animation_State state_;									// ステータス管理用
};

