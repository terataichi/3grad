#pragma once
#include "Object.h"
#include <map>
#include <list>
#include <functional>
#include <memory>
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
	std::string name_;											// コマンド名
	double allTime_;											// このコマンド全体に対しての許容時間
	bool reset_;												// リセットをするかどうか
	std::list<std::pair<unsigned int, double>> input_;			// CommandIDとIDに対しての許容時間
};


using CommandList = std::list<CommandData>;

// using InstanceFunc = std::function<std::shared_ptr<Object>(void)>;
using InstanceMap = std::map<std::string, std::function<std::shared_ptr<Object>(void)>>;

class Pawn :
    public Object
{
public:
	Pawn(Potision2f& pos, Vector2f& speed ,ControllType& type,TeamTag& tag);
	virtual ~Pawn();

	/// <summary>
	/// インスタンスする攻撃のリスト
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::list<std::string>& GetAttackList(void);
	/// <summary>
	/// アタックリストに対応したインスタンスマップ取得
	/// </summary>
	/// <returns></returns>
	const InstanceMap& GetInstanceFuncMap()const;

	void Damage(int&& value);
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
	/// <summary>
	/// 初期化してね
	/// instanceMap_
	/// </summary>
	virtual void InitFunction(void) = 0;

	std::unique_ptr<Controller> controller_;				// コントローラーの情報保持用

	std::vector<char> stateVec_;
	rapidxml::xml_node<char>* stateNode_;
	rapidxml::xml_document<> stateDoc;

	std::shared_ptr<TileMap> tileMap_;						// ゲームシーンからもらってくる

	Raycast raycast_;
	std::map<InputID, std::list<Sizef>> offset_;			// レイを飛ばすためのやつ

	bool isGround_;											// true:地面
	bool isJump_;											// true:ジャンプ中

	CommandList commandList_;								// コマンドを保存

	float hp_;												// 体力

	std::list<std::string> attackList_;						// 弾とか打つ
	InstanceMap instanceMap_;								// アタックリストに対応したインスタンスマップ

	// stringに対応したID
	static std::map<std::string, InputID>keyMap_;
private:
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
	friend struct InstanceBulled;
};

