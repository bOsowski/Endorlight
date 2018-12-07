//
//  TextureComponent.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 07/12/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef TextureComponent_hpp
#define TextureComponent_hpp

#include <stdio.h>
#include "BasicComponent.hpp"

class GameObject;
class BasicComponent;

class TextureComponent : public BasicComponent{
public:
    TextureComponent(sf::Sprite _sprite, GameObject* delegate) :
            BasicComponent("TextureComponent", delegate),
            sprite(_sprite)
    {

    }

    void render(sf::RenderWindow& window){
        window.draw(sprite);
    }

    void update(float deltaTime){
        //todo
    }


private:
    sf::Sprite sprite;

};

#endif /* TextureComponent_hpp */
