#pragma once
#include "Object.h"

#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

struct Move;
struct ModuleNode;
struct CheckKey;

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
	Anim_State state_;										// ステータス管理用

	std::vector<char> stateVec_;
	rapidxml::xml_node<char>* stateNode_;
	rapidxml::xml_document<> stateDoc;

	// --- 関数オブジェクト

	friend struct Move;
	friend struct ModuleNode;
	friend struct CheckKey;
};

