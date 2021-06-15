#pragma once
#include "TransitionScene.h"

class CrossOverScene:
	public TransitionScene
{
public:
	/// <summary>
	/// 引数に前のシーンと次のシーンを渡す
	/// </summary>
	/// <param name="prev">現在のシーン</param>
	/// <param name="next">移行させたいシーン</param>
	/// <param name="limit">何秒で完了してほしいか</param>
	CrossOverScene(UniqueBase beforScene, UniqueBase afterScene,double&& limit);
	~CrossOverScene();

private:
	bool TransitionUpdate(const double& deltaTime)override;
	void DrawOwnScreen(const double& deltaTime)override;

	double limit_;													// 何秒で完了してほしいか
	double time_;													// 経過時間
	double fadeCount_;												// 画面効果用
};

