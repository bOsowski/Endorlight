//
//  PhysicsComponent.hpp
//  ComponentBased
//
//  Created by Denis Flynn on 31/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//


#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp
#include "GameObject.hpp"

class PhysicsComponent
{
public:
    virtual ~PhysicsComponent() {}
    virtual void update(GameObject& obj, World& world) = 0;
};



class BjornPhysicsComponent : public PhysicsComponent
{
public:
    virtual void update(GameObject& obj, World& world)
    {
        // Physics code...
    }
};

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
    virtual void update(GameObject& obj, World& world)
    {
        // Physics code...
    }
};

#endif /* PhysicsComponent_hpp */
