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

//enum class Command_ID
//{
//	neutral,
//	left,
//	right,
//	up,
//	down,
//	LowerRight,
//	LowerLeft,
//	UpperRight,
//	UpperLeft,
//	Button1,
//	Button2,
//	Button3,
//	Button4,
//};

/// <summary>
/// IDに対応するtrigger情報を格納する
/// first : 現座フレームの情報
/// Second : １フレーム前の情報
/// </summary>
using TriggerMap = std::map<InputID, std::pair<bool, bool>>;

class Controller
{
public:
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

	std::vector<std::pair<int,double>> commandBuf_;								// 入力されたコマンドと許容時間を保存する
	int commandCnt_ = 0;
};

