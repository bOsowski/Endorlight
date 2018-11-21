
//
// Created by Bartosz Osowski on 21/11/2018.
// Copyright (c) 2018 Denis Flynn. All rights reserved.
//

#ifndef ASSETMANAGERV1_DAMAGECOMPONENT_H
#define ASSETMANAGERV1_DAMAGECOMPONENT_H


#include "Creature.hpp"

class Creature;

class DamageComponent {
public:
    float damage;

    DamageComponent(Creature* creature);

private:
    Creature *_creature;
};


#endif //ASSETMANAGERV1_DAMAGECOMPONENT_H
