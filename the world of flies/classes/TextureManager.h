#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <raylib.h>
#include <string>
#include <map>
#include <mutex>

class TextureManager
{
private:
	static TextureManager* instance;
	static std::mutex mutex_;

	std::map<std::string, Texture2D> textures;
	size_t loaded_textures_count;

	TextureManager();

public:
	TextureManager(TextureManager& other) = delete;
	void operator=(const TextureManager&) = delete;
	static TextureManager* GetInstance();

	Texture2D load(const char* path, std::string name);
};



#endif // !TEXTUREMANAGER_H