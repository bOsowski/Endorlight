//
// Created by Bartosz Osowski on 21/11/2018.
// Copyright (c) 2018 Denis Flynn. All rights reserved.
//

#include "Creature.hpp"

Creature::Creature()
        : physicsComponent(new PhysicsComponent(this)),
          graphicsComponent(new GraphicsComponent(this)),
          healthComponent(new HealthComponent()),
          influenceComponent(new InfluenceComponent()),
          damageComponent(new DamageComponent(this)) {
}