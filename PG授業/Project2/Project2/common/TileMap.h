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
	std::map<Map_Layer, std::string> accessLayer_;
};

