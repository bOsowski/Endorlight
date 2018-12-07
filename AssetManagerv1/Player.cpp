#include "utils.h"
#include "Player.h"
#include <iostream>

// Constructor.
Player::Player() :
        m_statPoints(0) {
    std::string className;
    className = "mage";
    // Load textures.
    graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("spr_" + className + "_walk_up.png");
    graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("spr_" + className + "_walk_down.png");
    graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("spr_" + className + "_walk_right.png");
    graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("spr_" + className + "_walk_left.png");
    graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("spr_" + className + "_idle_up.png");
    graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("spr_" + className + "_idle_down.png");
    graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("spr_" + className + "_idle_right.png");
    graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("spr_" + className + "_idle_left.png");

    // Set initial sprite.
    graphicsComponent->SetSprite(TextureManager::GetTexture(graphicsComponent->m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
    graphicsComponent->m_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
    graphicsComponent->m_sprite.setOrigin(sf::Vector2f(13.f, 18.f));

}

// Updates the player object.
void Player::Update(float timeDelta) {
    // Calculate movement speed based on the timeDelta since the last update.

    // Calculate where the current movement will put us.
    if (Input::IsKeyPressed(Input::KEY::KEY_LEFT)) {
        physicsComponent->move(LEFT, speed * timeDelta);
        graphicsComponent->animState = ANIMATION_STATE::WALK_LEFT;
    } else if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT)) {
        physicsComponent->move(RIGHT, speed * timeDelta);
        graphicsComponent->animState = ANIMATION_STATE::WALK_RIGHT;
    }

    if (Input::IsKeyPressed(Input::KEY::KEY_UP)) {
        physicsComponent->move(UP, speed * timeDelta);
        graphicsComponent->animState = ANIMATION_STATE::WALK_UP;
    } else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN)) {
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

// Returns the player's class.
PLAYER_CLASS Player::GetClass() const {
    return m_class;
}
