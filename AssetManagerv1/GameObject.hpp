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
#include "Window.h"
#include "Components.hpp"
#include "BasicComponent.hpp"
#include <string>

class BasicComponent;

class GameObject {
public:
    sf::Vector2f position;
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void addComponent(BasicComponent* component);
    
private:
    std::vector<BasicComponent*> components;
};

#endif /* GameObject_hpp */
