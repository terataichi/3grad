#pragma once
#include <map>
#include <string>
#include <list>
#include "Vector2.h"

// rappidXml
#include "../TileMap/rapidxml.hpp"
#include "../TileMap/rapidxml_utils.hpp"
#include "Collision.h"

#define TMX_VERSION "1.4"

struct LayerData
{
	std::string name;
	std::vector<int>chipData;
	int id,
		width,						// �ő剡�}�X
		heigth;						// �ő�c�}�X
};

struct MapData
{
	int width,
		height,
		tileWidth,					// �P�^�C���̑傫����
		tileHeight;					// �P�^�C���̑傫���c
};

struct ImageData
{
	std::string imageName;			// �摜�̖��O
	Size imageSize;					// �S�̂̃T�C�Y
	Size imageDivSize;				// �������
};


using LayerVec = std::vector<LayerData>;
// ���W�Ƃ�������̑傫��
using CollisionPList = std::list<std::pair<Potision2f, Sizef>>;

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
	CollisionPList GetCollisionList(void);
private:
	bool LoadTsx(std::string fileName);

	std::map<std::string, int>version_;
	//std::string version_;											// ���݂̃t�@�C����Version���`���Ċi�[���Ă���
	std::string tmxFileName_;										// Tmx�t�@�C�����ۑ�
	std::string tsxFileName_;										// Tsx�t�@�C�����ۑ�
	LayerVec layerData_;
	MapData mapData_;
	ImageData imageData_;
	unsigned int leyerGID_;
	unsigned int layerSize_;										// �ő僌�C���[��

	CollisionPList collisionVec_;										// �����蔻��p�̍��W�ƃT�C�Y�i�[

	rapidxml::xml_document<> docment;
};

