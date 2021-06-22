#pragma once
#include <memory>
#include <map>
#include <string>

#include "TmxAnimation.h"

#define lpAnimManager AnimationManager::GetInstance()

enum class Animation_State
{
	Non,
	Normal,
	Walk,
	Run,
	Max,
};

struct Animation
{
	AnimImageData imageData;
	AnimDataMap animVec;
	std::string nowState_;				// 現在のステート
	int animCount_;						// 何回再生されたか
	double time_;						// アニメーション再生時間管理用
};

class AnimationManager
{
public:
	/// <summary>
	/// 実体の取得
	/// </summary>
	/// <returns>実体が返る</returns>
	static AnimationManager& GetInstance()
	{
		return *sInstance_;
	}

	/// <summary>
	/// アニメーション登録
	/// 登録するアニメーション名とアニメーションの情報
	/// </summary>
	bool AddAnimation(const std::string key, const AnimDataMap& animData, const AnimImageData& animImageData);
	/// <summary>
	/// アニメーションのコマ取得
	/// </summary>
	/// <param name="key">アニメーションkey</param>
	/// <param name="elapsedTime">経過時間</param>
	/// <returns>-1 : なし それ以外 : -1以外</returns>
	int GetAnimation(const std::string key, double elapsedTime);
	/// <summary>
	/// 登録されているアニメーションのステータスを変える
	/// </summary>
	/// <param name="key"></param>
	/// <param name="state"></param>
	/// <returns></returns>
	bool SetState(const std::string& key, const Animation_State& state);
private:
	AnimationManager();
	~AnimationManager();

	/// <summary>
	/// カスタムデリーター
	/// </summary>
	struct AnimationManagerDeleter
	{
		void operator()(AnimationManager* manager)
		{
			delete manager;
		}
	};


	std::map<Animation_State, std::string> stateMap_;									// ステータス別アニメーションにアクセスするためのマップ
	std::map<std::string, Animation> animMap_;											// AddAnimationで登録するkeyを使う

	static std::unique_ptr<AnimationManager, AnimationManagerDeleter> sInstance_;		// 実態
};

