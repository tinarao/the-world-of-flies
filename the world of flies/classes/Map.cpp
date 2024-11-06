#include "Map.h"
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace tinyxml2;

Map* Map::instance{ nullptr };
std::mutex Map::mutex_;

Map::Map() {
    this->map_h = 20;
    this->map_w = 30;
    // TODO: Read the XML attr "width" and "height"

    TileMap tilemap(this->map_h, std::vector<int>());
    this->tilemap = tilemap;
}

Map* Map::GetInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance == nullptr) {
        instance = new Map();
    }

    return instance;
}

void Map::parse_tmx() {
    XMLDocument doc;
    doc.LoadFile("map.tmx");
    XMLElement* layer = doc.FirstChildElement("map")->FirstChildElement("layer");
    XMLElement* body = layer->FirstChildElement("data");

    int map_w = std::stoi(layer->Attribute("width"));
    int map_h = std::stoi(layer->Attribute("height"));

    std::string body_data = body->GetText();

    std::vector<std::string> temp_str_data_vec;
    boost::split(temp_str_data_vec, body_data, boost::is_any_of(","), boost::token_compress_on);

    std::vector<int> int_vec_map;
    for (const std::string& elem : temp_str_data_vec) {
        int_vec_map.push_back(std::stoi(elem));
    }
    
    if (int_vec_map.size() == map_w * map_h) {
        temp_str_data_vec.clear();
    }

    int y_axis = 0;
    for (int tile_idx = 0; tile_idx < int_vec_map.size(); tile_idx++) {
        if (tile_idx % this->map_w == 0 && tile_idx != 0) {
            y_axis++;
        }

        this->tilemap[y_axis].push_back(int_vec_map[tile_idx]);
    }

}

void Map::draw() {
    for (int y = 0; y < this->map_h; y++) {
        for (int x = 0; x < this->map_w; x++) {
            std::cout << this->tilemap[y][x];
        }
        
        std::cout << '\n';
    }
}

void Map::init() {
    this->parse_tmx();
    this->draw();
}