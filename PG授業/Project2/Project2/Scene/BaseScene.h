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
	virtual UniqueBase Update(UniqueBase scene) = 0;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="deltaTime">１フレーム間の時間</param>
	virtual void Draw();
	/// <summary>
	/// 自分の持っているスクリーンを描画
	/// </summary>
	/// <param name="deltaTime"></param>
	virtual void DrawOwnScreen() = 0;
	/// <summary>
	/// 自分がなんのシーンなのか
	/// </summary>
	virtual SceneName MyName() = 0;
	/// <summary>
	/// スクリーンID取得
	/// </summary>
	/// <returns>スクリーンID</returns>
	const int& GetScreenID(void);

protected:
	int screenID_;
	Size screenSize_;
};

