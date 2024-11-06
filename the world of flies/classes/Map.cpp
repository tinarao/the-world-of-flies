#include "Map.h"
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace tinyxml2;

Map* Map::instance{ nullptr };
std::mutex Map::mutex_;

Map::Map() {
    TileMap tilemap(20, std::vector<int>(30, 0));
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
        std::cout << "Dropped a temp str_data_vec vector" << std::endl;
        temp_str_data_vec.clear();
    }

    int y_axis = 0;
    for (int tile_idx = 0; tile_idx < int_vec_map.size(); tile_idx++) {
        if (tile_idx % 30 == 0 && tile_idx != 0) {
            y_axis++;
        }

        this->tilemap[y_axis].push_back(int_vec_map[tile_idx]);
    }
}

void Map::draw() {
    // Get parsed data
    // Draw on screen
    // Done!
}

void Map::init() {
    this->parse_tmx();
    this->draw();
}