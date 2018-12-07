//
// Created by Bartosz Osowski on 07/12/2018.
// Copyright (c) 2018 Denis Flynn. All rights reserved.
//

#ifndef ASSETMANAGERV1_ASSETMANAGER_HPP
#define ASSETMANAGERV1_ASSETMANAGER_HPP

#include <map>
#include <string>
#include <SFML/Graphics/Sprite.hpp>


class AssetManager {

public:
    static AssetManager& instance()
    {
        static AssetManager *instance = new AssetManager();
        return *instance;
    }

    std::map<std::string, sf::Sprite> textures;
    std::map<std::string, std::vector<sf::Sprite>> animations;

private:
    AssetManager();

};


#endif //ASSETMANAGERV1_ASSETMANAGER_HPP
