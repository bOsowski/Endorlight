//
//  PhysicsComponent.cpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 20/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(GameObject *gameObject)
        : _gameObject(gameObject) {
}

void PhysicsComponent::move(Direction dir, float velocity) {
    switch (dir) {
        case LEFT:
            _gameObject->position.x -= velocity;
            break;
        case RIGHT:
            _gameObject->position.x += velocity;
            break;
        case DOWN:
            _gameObject->position.y += velocity;
            break;
        case UP:
            _gameObject->position.y -= velocity;
            break;
    }
    moving = true;
}
