#pragma once
#include "Object.h"
#include <map>
#include <list>

#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

#include "../common/Vector2.h"
#include "../common/Raycast.h"

class Controller;
class TmxAnimation;
class TileMap;

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type);
	~Pawn();

protected:
	std::unique_ptr<Controller> controller_;				// コントローラーの情報保持用

	double deltaTime_;										// １フレーム間の時間保存
	double elapsedTime_;									// 経過時間保持用
	std::string animKey_;									// 登録したアニメーションのkey保存用
	Anim_State state_;										// ステータス管理用

	std::vector<char> stateVec_;
	rapidxml::xml_node<char>* stateNode_;
	rapidxml::xml_document<> stateDoc;

	std::shared_ptr<TileMap> tileMap_;						// ゲームシーンからもらってくる

	Raycast raycast_;
	std::map<InputID, std::list<Sizef>> offset_;			// レイを飛ばすためのやつ

	bool isGround_;											// true:地面
	bool isJump_;											// true:ジャンプ中
	// --- 関数オブジェクト
	friend struct Move;
	friend struct CheckKey;
	friend struct CheckState;
	friend struct SetAnimation;
	friend struct SetTurn;
	friend struct CheckCollision;
	friend struct Gravity;
	friend struct Jump;
	friend struct SetJump;
};

