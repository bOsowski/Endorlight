//
//  HealthComponent.cpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 21/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#include "HealthComponent.hpp"

void HealthComponent::setMaxHealth(float newMaxHealth){
    _maxHealth = newMaxHealth;
}

float HealthComponent::getMaxHealth(){
    return _maxHealth;
}

void HealthComponent::adjustCurrentHealth(float value){
    if(_currentHealth + value < 0){
        _currentHealth = 0;
    }
    else if(_currentHealth + value > _maxHealth){
        _currentHealth = _maxHealth;
    }
    else{
        _currentHealth += value;
    }
}

float HealthComponent::getCurrenthealth(){
    return _currentHealth;
}
