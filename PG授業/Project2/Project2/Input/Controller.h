#pragma once
#include <array>
#include <map>
#include <vector>
#include "InputID.h"

/// <summary>
/// 入力装置の種類定義
/// </summary>
enum class ControllType
{
	Keybord,
	GamePad,
	Max
};

/// <summary>
/// IDに対応するtrigger情報を格納する
/// first : 現座フレームの情報
/// Second : １フレーム前の情報
/// </summary>
using TriggerMap = std::map<InputID, std::pair<bool, bool>>;


class Controller
{
public:
	// 双方向リスト
	struct RingBuffer
	{
		int id_;
		RingBuffer* next_;			// 次の要素
		RingBuffer* prev_;			// 前の要素
	};

	Controller();
	virtual ~Controller();

	/// <summary>
	/// 現在扱ってる入力装置の種類を返す
	/// </summary>
	/// <returns>入力装置の種類</returns>
	virtual ControllType GetControllType() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update(void) = 0;
	/// <summary>
	/// リングバッファー更新処理
	/// </summary>
	void UpdateRingBuf(void);
	/// <summary>
	/// 押された瞬間かどうか
	/// </summary>
	/// <param name="id">取得したいID</param>
	const bool GetPushTrigger(InputID id)const;
	/// <summary>
	/// 押され続けているかどうか
	/// </summary>
	/// <param name="id">取得したいID</param>
	const bool GetPushingTrigger(InputID id)const;
	/// <summary>
	/// 離された瞬間かどうか
	/// </summary>
	/// <param name="id">取得したいID</param>
	const bool GetReleaseTrigger(InputID id)const;
	/// <summary>
	/// 離された瞬間かどうか
	/// </summary>
	/// <param name="id">取得したいID</param>
	const bool GetReleasingTrigger(InputID id)const;
private:

protected:

	TriggerMap triggerMap_;

	std::map<InputID, int> config_;												// IDに対応したコンフィグ格納
	RingBuffer* ringBuf_;														// 入力処理保持よう双方向リスト
};

