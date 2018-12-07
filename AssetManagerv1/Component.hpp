//
//  Component.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 07/12/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>
#include "Window.h"
#include "GameObject.hpp"

class GameObject;

class Component{
    
public:
    Component();
    virtual void update(float deltaTime);
    virtual void render(sf::Window& window);
    
private:
    GameObject* delegate;
    
};

#endif /* Component_hpp */
