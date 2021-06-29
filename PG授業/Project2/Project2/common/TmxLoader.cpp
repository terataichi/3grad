#include "TmxLoader.h"
#include <iostream>
#include <sstream>
#include <cassert>

TmxLoader::TmxLoader()
{
    version_.try_emplace("1.4", 1);
    version_.try_emplace("1.4.1", 1);
    version_.try_emplace("1.4.2", 1);
    version_.try_emplace("1.4.3", 1);
    version_.try_emplace("1.5", 1);

    mapData_ = {};
    layerData_ = {};
}

TmxLoader::~TmxLoader()
{
}

bool TmxLoader::LoadTmx(std::string fileName)
{
    rapidxml::file<> file(fileName.c_str());
    docment.parse<0>(file.data());

    rapidxml::xml_node<>* root_node;
    root_node = docment.first_node("map");

    // バージョンチェック
    auto ver = root_node->first_attribute("version")->value();
    if (version_.count(ver) == 0) {
        assert(!"バージョンが対応していません");
        return false;
    }

    tmxFileName_ = fileName;
    //  ﾏｯﾌﾟの中身を保存
    for (rapidxml::xml_attribute<>* data = root_node->first_attribute();
        data != nullptr;
        data = data->next_attribute())
    {
        std::cout << data->name() << "[" << data->value() << "]" << std::endl;
    }
    //  欲しいマップ情報の格納
    mapData_.width = atoi(root_node->first_attribute("width")->value());
    mapData_.height = atoi(root_node->first_attribute("height")->value());
    mapData_.tileWidth = atoi(root_node->first_attribute("tilewidth")->value());
    mapData_.tileHeight = atoi(root_node->first_attribute("tileheight")->value());
    layerSize_ = atoi(root_node->first_attribute("nextlayerid")->value()) - 1;
    //  各レイヤー情報の取り出し
    for (rapidxml::xml_node<>* layer_node = root_node->first_node("layer");
        layer_node != nullptr;
        layer_node = layer_node->next_sibling("layer"))
    {
        LayerData layer;

        // 基本情報の格納
        layer.name = layer_node->first_attribute("name")->value();
        layer.id = atoi(layer_node->first_attribute("id")->value());
        layer.width = atoi(layer_node->first_attribute("width")->value());
        layer.heigth = atoi(layer_node->first_attribute("height")->value());

        // チップデータの格納
        rapidxml::xml_node<>* data_node = layer_node->first_node("data");
        std::string data = data_node->value();

        std::istringstream iss{ data };
        std::string num;

        auto size = layer.width * layer.heigth;
        layer.chipData.resize(size);
        //for (int i = 0; i <= layer.width * layer.heigth; i++)
        for (auto& data : layer.chipData)
        {
            getline(iss, num, ',');
            data = atoi(num.c_str());
            //std::cout << num;
        }

        // 情報の追加
        layerData_.emplace_back(layer);
    }

    // 当たり判定用のデータがあったらそれを格納しておく
    rapidxml::xml_node<>* col_node = root_node->first_node("objectgroup");
    if (col_node)
    {
        for (rapidxml::xml_node<>* object = col_node->first_node("object");
            object != nullptr;
            object = object->next_sibling("object"))
        {
            float x = static_cast<float>(atof(object->first_attribute("x")->value()));
            float y = static_cast<float>(atof(object->first_attribute("y")->value()));
            float width = static_cast<float>(atof(object->first_attribute("width")->value()));
            float height = static_cast<float>(atof(object->first_attribute("height")->value()));

            collisionVec_.emplace_back(
                Potision2f{ x,y },
                Sizef{ width,height });
        }
    }

    //  Tsxファイル名を保存
    rapidxml::xml_node<>* tileset_node = root_node->first_node("tileset");
    tsxFileName_ = tileset_node->first_attribute("source")->value();
    leyerGID_ = atoi(tileset_node->first_attribute("firstgid")->value());

    // Tsxファイルの読み込み
    std::string pass = fileName.substr(0, fileName.find_last_of("/") + 1);
    LoadTsx(pass + tsxFileName_);


    return true;
}

bool TmxLoader::LoadTsx(std::string fileName)
{
    std::string tsxFile = fileName;
    rapidxml::file<> file(tsxFile.c_str());
    docment.parse<0>(file.data());

    rapidxml::xml_node<>* root_node = docment.first_node("tileset");

    // バージョンチェック
    if (version_.count(root_node->first_attribute("version")->value()) == 0) {
        assert(!"バージョンが対応していません");
        return false;
    }

    // イメージ情報の格納
    rapidxml::xml_node<>* tileset_node = root_node->first_node("image");
    imageData_.imageDivSize.x_ = atoi(root_node->first_attribute("columns")->value());
    imageData_.imageDivSize.y_ = atoi(root_node->first_attribute("tilecount")->value()) / imageData_.imageDivSize.x_;

    imageData_.imageSize.x_ = atoi(tileset_node->first_attribute("width")->value());
    imageData_.imageSize.y_ = atoi(tileset_node->first_attribute("height")->value());

    std::string str = tileset_node->first_attribute("source")->value();
    imageData_.imageName = str.substr(str.find_first_of("T"));

    return true;
}

LayerVec TmxLoader::GetLayerData(void)
{
    return layerData_;
}

MapData TmxLoader::GetMapData(void)
{
    return mapData_;
}

ImageData TmxLoader::GetImageData(void)
{
	return imageData_;
}

std::string TmxLoader::GetTmxFileName(void)
{
    return tmxFileName_;
}

CollisionPList TmxLoader::GetCollisionList(void)
{
    return collisionVec_;
}
