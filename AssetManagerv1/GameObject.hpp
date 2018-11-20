//
//  GameObject.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 20/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "GraphicsComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Components.hpp"

class GraphicsComponent;
class PhysicsComponent;
class InputComponent;

class GameObject
{
public:
    int velocity;
    int x, y;

    void update(World& world, GraphicsComponent& graphics){};
};
#endif /* GameObject_hpp */
