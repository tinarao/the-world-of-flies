#include "TextureManager.h"

TextureManager* TextureManager::instance{ nullptr };
std::mutex TextureManager::mutex_;

TextureManager::TextureManager() {
    this->loaded_textures_count = 0;
}

Texture2D TextureManager::load(const char* path, std::string name) {
	Texture2D tex = LoadTexture(path);
	this->loaded_textures_count += 1;

	this->textures.insert({ name, tex });

	return tex;
}

Textures TextureManager::get_textures() {
    return this->textures;
}

TextureManager* TextureManager::GetInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }

    return instance;
}