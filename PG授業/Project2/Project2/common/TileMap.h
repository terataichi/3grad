#pragma once
#include <vector>
#include <list>
#include <map>
#include <string>
#include "Vector2.h"

#include "TmxLoader.h"

#define TMX_VERSION "1.4"

enum class Map_Layer
{
	Block,
	Line,
	Pipe,
	Max
};

class TileMap;

class TileMap
{
public:
	TileMap();
	/// <summary>
	/// LoadTmxをしてくれる
	/// </summary>
	/// <param name="fileName">tmxファイルのパス</param>
	TileMap(std::string fileName);
	~TileMap();

	/// <summary>
	/// TMXファイル読み込み
	/// コンストラクタでも可能
	/// </summary>
	/// <param name="fileName">tmxファイルのパス</param>
	/// <returns>失敗：false</returns>
	bool LoadTmx(std::string fileName);
	/// <summary>
	/// 全レイヤーの情報の取得
	/// </summary>
	const LayerVec& GetLayerVec(void) const;
	/// <summary>
	/// 個別レイヤーの情報の取得
	/// </summary>
	/// <param name="name">レイヤー名</param>
	const LayerData& GetLayerData(Map_Layer&& name) const;
	/// <summary>
	/// 座標からチップの場所を特定
	/// </summary>
	/// <param name="layer">レイヤー名</param>
	/// <param name="pos">座標</param>
	/// <returns>失敗-1</returns>
	const int GetChipData(Map_Layer&& layer, const Potision2& pos);
	/// <summary>
	/// チップデータの取得
	/// </summary>
	/// <param name="layer">レイヤー名</param>
	/// <param name="x">横の番号</param>
	/// <param name="y">縦の番号</param>
	/// <returns>失敗：-1</returns>
	const int GetChipData(Map_Layer layer,const int x,const int y);
	/// <summary>
	/// マップデータの情報取得
	/// </summary>
	const MapData& GetMapData(void) const;

	/// <summary>
	/// 指定したレイヤー情報の描画
	/// </summary>
	/// <param name="layerData"></param>
	/// <returns></returns>
	void DrawMap(LayerData layerData);
	void DrawMap();

private:
	void Init(void);

	/// 読み込んだTMXファイルの情報保存用
	TmxLoader loader_;
	LayerVec layerVec_;
	MapData mapData_;
	ImageData imageData_;
	std::map<Map_Layer, std::string> accessLayer_;			// レイヤー名がstringなので変換器
};

