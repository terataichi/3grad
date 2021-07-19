#pragma once
#include <memory>
#include <string>
#include <list>

#include "../common/Vector2.h"
#include "../Input/Controller.h"
#include "../Status/Animation_State.h"

class Object
{
public:
	Object(Potision2f& pos, Vector2f& speed);
	virtual ~Object();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="type">コンストラクタで入力機器の選択情報を受け取る</param>
	virtual void Init() = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta">１フレーム当たりの時間をもらう</param>
	/// <returns></returns>
	virtual bool Update() = 0;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="delta"></param>
	virtual void Draw() = 0;
protected:
	Potision2f pos_;										// 自分の座標
	Vector2f vel_;											// 速度
	Size size_;												// 大きさ
	float radius_;											// 半径
	bool turn_;												// 左向いてるか右向いてるか(画像が右向いてたらfalseで右)
};

