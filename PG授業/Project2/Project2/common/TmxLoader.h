#pragma once
#include <map>
#include <string>
#include "Vector2.h"

// rappidXml
#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

#define TMX_VERSION "1.4"

struct LayerData
{
	std::string name;
	std::vector<int>chipData;
	int id,
		width,						// 最大横マス
		heigth;						// 最大縦マス
};

struct MapData
{
	int width,
		height,
		tileWidth,					// １タイルの大きさ横
		tileHeight;					// １タイルの大きさ縦
};

struct ImageData
{
	std::string imageName;			// 画像の名前
	Size imageSize;					// 全体のサイズ
	Size imageDivSize;				// 分割情報
};


using LayerVec = std::vector<LayerData>;

class TmxLoader
{
public:
	TmxLoader();
	~TmxLoader();

	bool LoadTmx(std::string fileName);
	//rapidxml::xml_node<>& GetNode(std::string nodeName);
	LayerVec GetLayerData(void);
	MapData GetMapData(void);
	ImageData GetImageData(void);
	std::string GetTmxFileName(void);
private:
	bool LoadTsx(std::string fileName);

	std::map<std::string, int>version_;
	//std::string version_;											// 現在のファイルのVersionを定義して格納しておく
	std::string tmxFileName_;										// Tmxファイル名保存
	std::string tsxFileName_;										// Tsxファイル名保存
	LayerVec layerData_;
	MapData mapData_;
	ImageData imageData_;
	unsigned int leyerGID_;
	unsigned int layerSize_;										// 最大レイヤー数

	rapidxml::xml_document<> docment;
};

