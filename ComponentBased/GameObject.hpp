//
//  GameObject.hpp
//  AssetManagerv1
//
//  Created by Denis Flynn on 09/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//


#ifndef GameObject_hpp
#define GameObject_hpp
#include "GraphicsComponent.hpp"
#include "PhysicsComponent.hpp"
#include "HealthComponent.hpp"
#include "AIComponent.hpp"
#include "InputComponent.hpp"



class GameObject
{
public:
    int velocity;
    int x, y;
    
    GameObject(InputComponent* input,
               PhysicsComponent* physics,
               GraphicsComponent* graphics)
    : input_(input),
    physics_(physics),
    graphics_(graphics)
    {}
    
    void update(World& world, GraphicsComponent& graphics)
    {   
        input_->update(*this);
        physics_->update(*this, world);
        graphics_->update(*this, graphics);
    }
    
private:
    InputComponent* input_;
    PhysicsComponent* physics_;
    GraphicsComponent* graphics_;
};
//the following must follow definition of gameobject, forward declaration won't suffice!!



//
//GameObject* createPlayer()
//{
//    return new GameObject(new PlayerInputComponent(),
//                          new BjornPhysicsComponent(),
//                          new BjornGraphicsComponent());
//}




//GameObject* createBjorn()
//{
//    return new GameObject(new PlayerInputComponent(),
//                          new BjornPhysicsComponent(),
//                          new BjornGraphicsComponent());
//}

#endif /* GameObject_hpp */
