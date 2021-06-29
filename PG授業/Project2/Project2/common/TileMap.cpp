#include "TileMap.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <DxLib.h>
#include "Vector2.h"
#include "ImageManager.h"

// rappidXml
#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"

TileMap::TileMap()
{
	Init();
}

TileMap::TileMap(std::string fileName)
{
	Init();
	LoadTmx(fileName);
}

TileMap::~TileMap()
{
}

bool TileMap::LoadTmx(std::string fileName)
{
	if (!loader_.LoadTmx(fileName))
	{
		assert(!"é∏îs\n");
		return false;
	}

	layerVec_ = loader_.GetLayerData();
	mapData_ = loader_.GetMapData();
	imageData_ = loader_.GetImageData();
	collisionList_ = loader_.GetCollisionList();
	return true;
}

const LayerVec& TileMap::GetLayerVec(void) const
{
	return layerVec_;
}

const LayerData& TileMap::GetLayerData(Map_Layer&& name)const
{
	for (auto& data : layerVec_)
	{
		if (data.name == accessLayer_.at(name))
		{
			return data;
		}
	}
	assert(!"GetLayerData : Not found ");
	LayerData tmp{};
	return tmp;
}

const int TileMap::GetChipData(Map_Layer&& layer, const Potision2& pos)
{
	return GetChipData(layer, pos.x_ / mapData_.tileWidth, pos.y_ / mapData_.tileHeight);
}

const int TileMap::GetChipData(Map_Layer layer, const int x, const int y)
{
	for (auto& data : layerVec_)
	{
		if (data.name == accessLayer_.at(layer))
		{
			auto tmpwidth = x + y * data.width;
			if (data.chipData.size() > tmpwidth && x + y * data.width >= 0)
			{
				return data.chipData[tmpwidth];
			}
			return -1;
		}
	}
	return -1;
}

const MapData& TileMap::GetMapData(void) const
{
	return mapData_;
}

bool TileMap::CheckHitCollision(Potision2f pos, Sizef size)
{
	Sizef tmpSize = { size.x_ / 2 ,size.y_ / 2 };
	for (auto& data : collisionList_)
	{
		if (data.first.x_ < pos.x_ - tmpSize.x_ &&
			data.first.x_ + data.second.x_ > pos.x_ + tmpSize.x_ &&
			data.first.y_ < pos.y_ - tmpSize.y_ &&
			data.first.y_ + data.second.y_ > pos.y_ + tmpSize.y_)
		{
			return true;
		}
	}

	return false;
}

void TileMap::DrawMap(LayerData layerData)
{
	// í∑Ç¢ÇÃÇ≈ÉçÅ[ÉJÉãïœêîÇ…äiî[
	Vector2 div{ layerData.width ,layerData.heigth };
	Vector2 size{ loader_.GetMapData().tileWidth,loader_.GetMapData().tileHeight };

	int i = 0;
	for (auto chip : layerData.chipData)
	{
		//int chip = data.second.chipData[i];
		Vector2 chipPos{ size.x_ * (i % div.x_),size.y_ * (i / div.x_)};
		if (chip != 0)
		{
			auto num = chip - 1;
			auto image = lpImageManager.GetImageHandle(imageData_.imageName, imageData_.imageDivSize, size)[num];
			DrawGraph(chipPos.x_, chipPos.y_, image, true);
		}
		i++;
	}
}

void TileMap::DrawMap()
{
	for (auto layerData : layerVec_)
	{
		// í∑Ç¢ÇÃÇ≈ÉçÅ[ÉJÉãïœêîÇ…äiî[
		Vector2 div{ layerData.width ,layerData.heigth };
		Vector2 size{ loader_.GetMapData().tileWidth,loader_.GetMapData().tileHeight };

		int i = 0;
		for (auto chip : layerData.chipData)
		{
			//int chip = data.second.chipData[i];
			Vector2 chipPos{ size.x_ * (i % div.x_),size.y_ * (i / div.x_) };
			if (chip != 0)
			{
				auto num = chip - 1;
				auto image = lpImageManager.GetImageHandle(imageData_.imageName, imageData_.imageDivSize, size)[num];
				DrawGraph(chipPos.x_, chipPos.y_, image, true);
			}
			i++;
		}
	}
}

void TileMap::Init(void)
{
	mapData_ = MapData{};
	layerVec_ = LayerVec{};
	imageData_ = ImageData{};
	accessLayer_.try_emplace(Map_Layer::Block, "block");
	accessLayer_.try_emplace(Map_Layer::Line, "line");
	accessLayer_.try_emplace(Map_Layer::Pipe, "pipe");
}
