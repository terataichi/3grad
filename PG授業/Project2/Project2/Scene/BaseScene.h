#pragma once
#include <memory>
#include "../common/Vector2.h"

class BaseScene;
using UniqueBase = std::unique_ptr<BaseScene>;

enum class SceneName
{
	Transition,
	Title,
	Game,
	Max
};

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	/// <summary>
	/// BaseSceneのコンストラクタで読んである
	/// </summary>
	virtual bool Init(void) = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">１フレーム間の時間</param>
	virtual UniqueBase Update(UniqueBase scene,const double& deltaTime) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="deltaTime">１フレーム間の時間</param>
	virtual void Draw(const double& deltaTime);
	/// <summary>
	/// 自分の持っているスクリーンを描画
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void DrawOwnScreen(const double& deltaTime) = 0;
	/// <summary>
	/// 自分がなんのシーンなのか
	/// </summary>
	virtual SceneName MyName() = 0;

protected:
	int screenID_;
	Size screenSize_;
};

