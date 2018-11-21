//
//  HealthComponent.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 21/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef HealthComponent_hpp
#define HealthComponent_hpp

#include <stdio.h>

class HealthComponent {
public:
    void setMaxHealth(float newMaxHealth);

    float getMaxHealth();

    void adjustCurrentHealth(float value);

    float getCurrenthealth();


private:
    float _maxHealth;
    float _currentHealth;
};

#endif /* HealthComponent_hpp */
