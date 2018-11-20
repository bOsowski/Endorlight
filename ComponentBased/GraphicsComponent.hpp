//
//  GraphicsComponent.hpp
//  ComponentBased
//
//  Created by Denis Flynn on 31/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//


#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp

#include "GameObject.hpp"

class GraphicsComponent
{
public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject& obj, Graphics& graphics) = 0;
};





class BjornGraphicsComponent : public GraphicsComponent
{
public:
    virtual void update(GameObject& obj, Graphics& graphics)
    {
        // Graphics code...
    }
};

class PlayerGraphicsComponent : public GraphicsComponent
{
public:
    virtual void update(GameObject& obj, Graphics& graphics)
    {
        // Graphics code...
    }
};

#endif /* GraphicsComponent_hpp */
