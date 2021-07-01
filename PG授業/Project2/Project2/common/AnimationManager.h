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
	AnimImageData imageData_;
	AnimDataMap animVec_;
	std::string nowState_;				// 現在のステート
	int animCount_;						// 何回再生されたか
	double startTime_;					// ステータスが変わったときに経過時間を保存しておく
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
	/// アニメーションを登録する
	/// </summary>
	/// <param name="tmxPath">登録するアニメーションの情報が入っているTMXへのパス</param>
	/// <param name="key">名前何にするか</param>
	/// <returns>登録されたキーが返ってくる(名前被りしたら別の名前で返ってくる)</returns>
	const std::string AddAnimation(const std::string& tmxPath,std::string key);
	/// <summary>
	/// アニメーションのコマ取得
	/// </summary>
	/// <param name="key">アニメーションkey</param>
	/// <param name="elapsedTime">経過時間</param>
	/// <returns>-1 : なし それ以外 : -1以外</returns>
	int GetAnimation(const std::string& key,const double& elapsedTime);
	/// <summary>
	/// 登録されているアニメーションのステータスを変える
	/// </summary>
	/// <param name="key">登録して保持しているキー</param>
	/// <param name="state">ステータス(登録されていないステータスは投げても更新されない)</param>
	/// <returns>true : 成功</returns>
	bool SetState(const std::string& key, const Animation_State& state, const double& nowElapsedTime);

	const Sizef GetChipSize(const std::string& key);

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

