#pragma once
#include "TransitionScene.h"

class BrightRotationScene :
    public TransitionScene
{
public:
	/// <summary>
	/// 引数に前のシーンと次のシーンを渡す
	/// </summary>
	/// <param name="prev">現在のシーン</param>
	/// <param name="next">移行させたいシーン</param>
	/// <param name="limit">何秒で完了してほしいか</param>
	BrightRotationScene(UniqueBase beforScene, UniqueBase afterScene, double&& limit);
	~BrightRotationScene();

private:
	bool TransitionUpdate()override;
	void DrawOwnScreen()override;

	double angle_;													// 角度
	float angleCount_;												
	double limit_;													// 何秒で完了してほしいか
	double time_;													// 経過時間
	double fadeCount_;												// 画面効果用
};

