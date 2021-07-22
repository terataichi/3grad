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
	Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap, ControllType type, TeamTag tag = TeamTag::Non);
	~Player();

	void Init(void)override;
	bool Update(void) override;
	void Draw(void) override;
	void InitFunction(void) override;
	void Hit(std::shared_ptr<Object> target)override;
private:

	ModuleNode moduleNode;
};