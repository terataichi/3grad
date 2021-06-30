#pragma once
#include <memory>

#include "Object.h"
#include "../common/Raycast.h"

class Controller;
class TmxAnimation;
class TileMap;

class Player:
	public Object
{
public:
	Player(Potision2f&& pos, Vector2f&& speed, std::shared_ptr<TileMap>& tileMap,ControllType type = ControllType::Keybord);
	~Player();

	void Init(ControllType type)override;
	bool Update(const double& delta) override;
	void Draw(const double& delta) override;
private:
	Sizef GetOffSet(Vector2f vel);
	Raycast raycast_;
	std::shared_ptr<TileMap> tileMap_;						// ÉQÅ[ÉÄÉVÅ[ÉìÇ©ÇÁÇ‡ÇÁÇ¡ÇƒÇ≠ÇÈ
};

