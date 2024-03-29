#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL_ttf.h>
#include "./TextureManager.h"
#include "./EntityManager.h"



class AssetManager {
private:
    EntityManager* manager;
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, TTF_Font*> fonts;

public:
    AssetManager(EntityManager* manager);
    ~AssetManager();
    void ClearData();

    //passing const char* as this is what SDL expects (otherwise would be std::string )
    void AddTexture(std::string textureId, const char* filePath, SDL_Renderer* renderer);
    SDL_Texture* GetTexture(std::string textureId);

    void AddFont(std::string fontId,  const char* filePath, int fontSize);
    TTF_Font* GetFont(std::string fontId);

};

#endif