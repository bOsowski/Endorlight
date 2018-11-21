//
//  PhysicsComponent.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 20/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//
#pragma once
#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "Direction.hpp"

class GameObject;

class PhysicsComponent {
public:
    PhysicsComponent(GameObject *gameObject);

    ~PhysicsComponent();

    void move(Direction dir, float velocity);

    bool moving;

private:
    GameObject *_gameObject;
};


#endif /* PhysicsComponent_hpp */
