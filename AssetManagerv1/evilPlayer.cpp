//
//  evilPlayer.cpp
//  AssetManagerv1
//
//  Created by Denis Flynn on 16/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#include "evilPlayer.hpp"

void evilPlayer::Update(float timeDelta) {
    // Calculate where the current movement will put us.
    if (Input::IsKeyPressed(Input::KEY::KEY_E_LEFT)) {
        physicsComponent->move(LEFT, speed * timeDelta);
        graphicsComponent->animState = ANIMATION_STATE::WALK_LEFT;
    } else if (Input::IsKeyPressed(Input::KEY::KEY_E_RIGHT)) {
        physicsComponent->move(RIGHT, speed * timeDelta);
        graphicsComponent->animState = ANIMATION_STATE::WALK_RIGHT;
    }

    if (Input::IsKeyPressed(Input::KEY::KEY_E_UP)) {
        physicsComponent->move(UP, speed * timeDelta);
        graphicsComponent->animState = ANIMATION_STATE::WALK_UP;
    } else if (Input::IsKeyPressed(Input::KEY::KEY_E_DOWN)) {
        physicsComponent->move(DOWN, speed * timeDelta);
        graphicsComponent->animState = ANIMATION_STATE::WALK_DOWN;
    }


    // update the sprite position
    graphicsComponent->updatePosition(position);


    // set animation speed
    if (!physicsComponent->moving) {
        // the character is still
        if (graphicsComponent->IsAnimated()) {
            graphicsComponent->setToIdle();
        }
    } else {
        // the character is moving
        if (!graphicsComponent->IsAnimated()) {
            graphicsComponent->setToWalking();
        }
    }
    physicsComponent->moving = false;

}
