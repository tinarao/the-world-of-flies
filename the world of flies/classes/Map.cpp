#include "Map.h"
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Tile.h"
#include "TextureManager.h"
#include "../config.h"

using namespace tinyxml2;

Map* Map::instance{ nullptr };
std::mutex Map::mutex_;

Map::Map() {
	this->tileset = TextureManager::GetInstance()->load("assets/tileset.png", "tileset");
	if (this->tileset.height == 0 || this->tileset.width == 0) {
		std::cerr << "Failed to load tileset.png" << std::endl;
		exit(1);
	}

	this->map_h = 20;
	this->map_w = 30;
	// TODO: Read the XML attr "width" and "height"

	TileMap tilemap(this->map_h, std::vector<int>());
	this->tilemap = tilemap;
	this->tiles = {};

	this->parse_tmx();
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

void Map::load_tiles() {
	for (int y = 0; y < this->map_h; y++) {
		for (int x = 0; x < this->map_w; x++) {
			if (this->tilemap[y][x] == TileVariant::Air) {
				continue;
			}

			Rectangle dst = {
				x * RENDERED_TILE_SIZE,
				y * RENDERED_TILE_SIZE,
				RENDERED_TILE_SIZE,
				RENDERED_TILE_SIZE
			};

			int tile_type = this->tilemap[y][x];
			printf("Tile type: %d\n", tile_type);

			if (tile_type == DIRT_TILE) {
				std::cout << "Rendered a dirt tile." << std::endl;
				Rectangle src = {
					32,
					32,
					BASE_TILE_SIZE,
					BASE_TILE_SIZE
				};

				Tile dirtTile = Tile(src, dst, this->tileset, true);
				this->tiles.push_back(dirtTile);
			}
			else if (tile_type == GRASS_TILE) {
				std::cout << "Rendered a grass tile." << std::endl;
				Rectangle src = {
					32,
					0,
					BASE_TILE_SIZE,
					BASE_TILE_SIZE
				};

				Tile grassTile = Tile(src, dst, this->tileset, true);
				this->tiles.push_back(grassTile);
			}
		}
	}
}

void Map::draw() {
	for (const auto& tile : this->tiles) {
		tile.draw();
	}
}

Rectangle Map::GetCollisionsWithPlayer(Player* player) {
	Rectangle collisionRect = { 0, 0, 0, 0 };

	for (const auto& tile : this->tiles) {
		if (CheckCollisionRecs(player->getCollisionChecker(), tile.getDstRect())) {
			collisionRect = GetCollisionRec(player->getCollisionChecker(), tile.getDstRect());
			break;
		}
	}

	return collisionRect;
}