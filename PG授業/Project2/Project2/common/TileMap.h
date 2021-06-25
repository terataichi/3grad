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
	/// LoadTmx�����Ă����
	/// </summary>
	/// <param name="fileName">tmx�t�@�C���̃p�X</param>
	TileMap(std::string fileName);
	~TileMap();

	/// <summary>
	/// TMX�t�@�C���ǂݍ���
	/// �R���X�g���N�^�ł��\
	/// </summary>
	/// <param name="fileName">tmx�t�@�C���̃p�X</param>
	/// <returns>���s�Ffalse</returns>
	bool LoadTmx(std::string fileName);
	/// <summary>
	/// �S���C���[�̏��̎擾
	/// </summary>
	const LayerVec& GetLayerVec(void) const;
	/// <summary>
	/// �ʃ��C���[�̏��̎擾
	/// </summary>
	/// <param name="name">���C���[��</param>
	const LayerData& GetLayerData(Map_Layer&& name) const;
	/// <summary>
	/// ���W����`�b�v�̏ꏊ�����
	/// </summary>
	/// <param name="layer">���C���[��</param>
	/// <param name="pos">���W</param>
	/// <returns>���s-1</returns>
	const int GetChipData(Map_Layer&& layer, const Potision2& pos);
	/// <summary>
	/// �`�b�v�f�[�^�̎擾
	/// </summary>
	/// <param name="layer">���C���[��</param>
	/// <param name="x">���̔ԍ�</param>
	/// <param name="y">�c�̔ԍ�</param>
	/// <returns>���s�F-1</returns>
	const int GetChipData(Map_Layer layer,const int x,const int y);
	/// <summary>
	/// �}�b�v�f�[�^�̏��擾
	/// </summary>
	const MapData& GetMapData(void) const;

	/// <summary>
	/// �w�肵�����C���[���̕`��
	/// </summary>
	/// <param name="layerData"></param>
	/// <returns></returns>
	void DrawMap(LayerData layerData);
	void DrawMap();

private:
	void Init(void);

	/// �ǂݍ���TMX�t�@�C���̏��ۑ��p
	TmxLoader loader_;
	LayerVec layerVec_;
	MapData mapData_;
	ImageData imageData_;
	std::map<Map_Layer, std::string> accessLayer_;			// ���C���[����string�Ȃ̂ŕϊ���
};

