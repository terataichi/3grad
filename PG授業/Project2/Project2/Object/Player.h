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

	void Init(void)override;
	bool Update(void) override;
	void Draw(void) override;
	void InitFunction(void) override;
private:

	ModuleNode moduleNode;
};