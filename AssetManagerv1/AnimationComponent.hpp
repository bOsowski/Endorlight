//
// Created by Bartosz Osowski on 07/12/2018.
// Copyright (c) 2018 Denis Flynn. All rights reserved.
//

#ifndef ASSETMANAGERV1_ANIMATIONCOMPONENT_H
#define ASSETMANAGERV1_ANIMATIONCOMPONENT_H


#include "TextureComponent.hpp"

class AnimationComponent : TextureComponent{
public:
    AnimationComponent(const sf::Sprite &_sprite, GameObject *delegate)
            : TextureComponent(_sprite, delegate) {
    }


};


#endif //ASSETMANAGERV1_ANIMATIONCOMPONENT_H
