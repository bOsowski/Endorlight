//
// Created by Bartosz Osowski on 21/11/2018.
// Copyright (c) 2018 Denis Flynn. All rights reserved.
//

#ifndef ASSETMANAGERV1_CREATURE_H
#define ASSETMANAGERV1_CREATURE_H

#include "GraphicsComponent.hpp"
#include "PhysicsComponent.hpp"
#include "HealthComponent.hpp"
#include "InfluenceCoponent.hpp"
#include "DamageComponent.hpp"

class DamageComponent;

class Creature : public GameObject {
public:
    Creature();

    GraphicsComponent *graphicsComponent;
    PhysicsComponent *physicsComponent;
    HealthComponent *healthComponent;
    InfluenceComponent *influenceComponent;
    DamageComponent *damageComponent;

private:
};


#endif //ASSETMANAGERV1_CREATURE_H
