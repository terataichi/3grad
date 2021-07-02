#pragma once
#include <memory>
#include <list>

#include "Pawn.h"
#include "../common/Raycast.h"

class Controller;
class TmxAnimation;
class TileMap;

class Player:
	public Pawn
{
public:
	Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap,ControllType type = ControllType::Keybord);
	~Player();

	void Init()override;
	bool Update(const double& delta) override;
	void Draw(const double& delta) override;
private:
	Sizef GetOffSet(Vector2f vel);
	Raycast raycast_;
	std::shared_ptr<TileMap> tileMap_;							// ゲームシーンからもらってくる
	std::map<InputID, std::list<Sizef>> offset_;				// レイを飛ばすためのやつ

	float displacement_;										// 変化量
	double g_elapsedTime_;										// 重力の経過時間計測用
	bool jump_;													// ジャンプするためのトリガー
};

