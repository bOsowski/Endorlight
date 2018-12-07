//
//  GameObject.cpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 20/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#include "GameObject.hpp"

void GameObject::update(float deltaTime){
    for(BasicComponent* component : components){
        component->update(deltaTime);
    }
}

void GameObject::render(sf::RenderWindow& window){
    for(BasicComponent* component : components){
        component->render(window);
    }
}

void GameObject::addComponent(BasicComponent* component){
    components.push_back(component);
}
