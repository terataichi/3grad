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

// コマンドの情報
struct CommandData 
{
	std::string name_;
	std::list<int> input_;
};

using CommandList = std::list<CommandData>;

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type);
	virtual ~Pawn();

protected:
	/// <summary>
	/// コマンドのバッファーにためる処理
	/// </summary>
	void CommandBufUpdate(void);
	/// <summary>
	/// ステータスUpdate用のTmx読み込み
	/// </summary>
	void LoadStateModule(std::string&& fileName);
	/// <summary>
	/// コマンドを読み込む
	/// </summary>
	/// <param name="fileName">ファイルまでのパス</param>
	/// <returns>読み込んだコマンドリスト</returns>
	void LoadCommandList(std::string&& fileName);

	std::unique_ptr<Controller> controller_;				// コントローラーの情報保持用
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

	CommandList commandList_;								// コマンドを保存

	// stringに対応したID
	static std::map<std::string, InputID>keyMap_;

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
	friend struct CheckCommand;
};

