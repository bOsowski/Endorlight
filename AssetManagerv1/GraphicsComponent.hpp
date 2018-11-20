//
//  GraphicsComponent.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 20/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include <iostream>

class GameObject;
class Graphics;

class GraphicsComponent
{
public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject& obj, GraphicsComponent& graphics) = 0;
};


class BjornGraphicsComponent : public GraphicsComponent
{
public:
    virtual void update(GameObject& obj, GraphicsComponent& graphics)
    {
        // Graphics code...
    }
};

class PlayerGraphicsComponent : public GraphicsComponent
{
public:
    virtual void update(GameObject& obj, GraphicsComponent& graphics)
    {
        // Graphics code...
    }
};

#endif /* GraphicsComponent_hpp */
