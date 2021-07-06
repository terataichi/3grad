#pragma once
#include <memory>
#include <list>
#include <vector>

#include "Pawn.h"
#include "State.h"

class Player:
	public Pawn
{
public:
	Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap,ControllType type = ControllType::Keybord);
	~Player();

	void Init()override;
	bool Update() override;
	void Draw() override;
private:

	ModuleNode moduleNode;


	bool jump_;													// ジャンプするためのトリガー

};

