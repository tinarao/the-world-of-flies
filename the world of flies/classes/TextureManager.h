#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <raylib.h>
#include <string>
#include <map>
#include <mutex>
#include "../types.h"

class TextureManager {
private:
	static TextureManager* instance;
	static std::mutex mutex_;

	Textures textures;
	size_t loaded_textures_count;

	TextureManager();

public:
	TextureManager(TextureManager& other) = delete;
	void operator=(const TextureManager&) = delete;
	static TextureManager* GetInstance();

	Texture2D load(const char* path, std::string name);
	Textures get_textures();
};



#endif // !TEXTUREMANAGER_H