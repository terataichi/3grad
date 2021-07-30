#pragma once
#include <memory>
#include <string>
#include <list>

#include "../common/Vector2.h"
#include "../Input/Controller.h"
#include "../Status/Animation_State.h"

enum class ObjectType
{
	Non,
	Pawn,
	Actor,
};

enum class TeamTag
{
	Non,
	Red,
	Green,
	Bule,
	Yellow,
	Max
};

class Object
{
public:
	Object(Potision2f& pos, Vector2f& speed, ObjectType&& objtype, TeamTag tag = TeamTag::Non);
	virtual ~Object();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="type">コンストラクタで入力機器の選択情報を受け取る</param>
	virtual void Init(void) = 0;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta">１フレーム当たりの時間をもらう</param>
	/// <returns></returns>
	virtual bool Update(void) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="delta"></param>
	virtual void Draw(void) = 0;
	/// <summary>
	/// オブジェクト同士で当たったときに呼び出す
	/// </summary>
	/// <param name="obj">当たった相手のポインタ</param>
	virtual void Hit(std::shared_ptr<Object> target) = 0;
	/// <summary>
	/// UIの仕組みを作ってなかったので仮
	/// </summary>
	virtual void DrawStatus() {};

	const Potision2f& GetPotision(void)const;
	const Sizef& GetSize(void)const;
	const ObjectType& GetObjectType(void)const;
	const int& GetObjID(void)const;
	void ResetObjID(void);
	const TeamTag GetTeamTag(void)const;
	const Anim_State GetAnimState(void)const;
	virtual const bool IsActive(void);
protected:
	Potision2f pos_;										// 自分の座標
	Vector2f vel_;											// 速度
	Sizef size_;											// 大きさ
	float radius_;											// 半径
	bool turn_;												// 左向いてるか右向いてるか(画像が右向いてたらfalseで右)
	const ObjectType objType_;

	std::string animKey_;									// 登録したアニメーションのkey保存用
	Anim_State animState_;									// ステータス管理用

	bool active_;

	TeamTag teamTag_;
	int objID_;											    // 自分の番号
private:
	static int instanceCount_;								// 生成されるたびに+１
};

