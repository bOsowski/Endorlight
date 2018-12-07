//
//  GraphicsComponent.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 20/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef GraphicsComponent_hpp
#define GraphicsComponent_hpp

#include <stdio.h>
#include "enums.h"
#include "Window.h"
#include "TextureManager.h"
#include "BasicComponent.hpp"

class BasicComponent;

class GraphicsComponent : public sf::Drawable {
public:
//    GraphicsComponent(GameObject *gameObject);

    ~GraphicsComponent(){};

    int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
    ANIMATION_STATE animState;

    GraphicsComponent(GameObject *_delegate) {
        animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);
    }

    void update(float deltaTime){

    }


    bool SetSprite(sf::Texture &texture, bool isSmooth, int frames, int frameSpeed) {
        // Create a sprite from the loaded texture.
        m_sprite.setTexture(texture);

        // Set animation speed.
        m_animationSpeed = frameSpeed;

        // Store the number of frames.
        m_frameCount = frames;

        // Calculate frame dimensions.
        sf::Vector2u texSize = m_sprite.getTexture()->getSize();
        m_frameWidth = texSize.x / m_frameCount;
        m_frameHeight = texSize.y;

        // Check if animated or static.
        if (frames > 1) {
            // Set sprite as animated.
            m_isAnimated = true;

            // Set the texture rect of the first frame.
            m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
        } else {
            // Set sprite as non animated.
            m_isAnimated = false;
        }

        // Set the origin of the sprite.
        m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

        return true;
    }


    void Update(float timeDelta) {
    };

    sf::Sprite &GetSprite() {
        return m_sprite;
    }

    int GetFrameCount() const;

    bool IsAnimated() {
        return m_isAnimated;
    }

    void SetAnimated(bool isAnimated) {
        m_isAnimated = isAnimated;

        if (isAnimated) {
            m_currentFrame = 0;
        } else {
            // set the texture rect of the first frame
            m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
        }
    }

    void updatePosition(sf::Vector2f position) {
        m_sprite.setPosition(position);

        // Set the sprite.
        if (m_currentTextureIndex != static_cast<int>(animState)) {
            m_currentTextureIndex = static_cast<int>(animState);
            m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
            //m_sprite.setColor(sf::Color::Red); //"evil" version
        }
    }

    void setToIdle() {
        // Update sprite to idle version.
        // In our enum we have 4 walking sprites followed by 4 idle sprites.
        // Given this, we can simply add 4 to a walking sprite to get its idle counterpart.
        m_currentTextureIndex += 4;
        m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
        // Stop movement animations.
        SetAnimated(false);
    }

    void setToWalking() {
        // Update sprite to walking version.
        m_currentTextureIndex -= 4;
        m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

        // Start movement animations.
        SetAnimated(true);
    }

// Draws the object to the given render window.
    void draw(sf::RenderWindow &window) {
        window.draw(m_sprite);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(m_sprite);
    }

    void NextFrame() {
        // check if we reached the last frame
        if (m_currentFrame == (m_frameCount - 1))
            m_currentFrame = 0;
        else
            m_currentFrame++;

        // update the texture rect
        m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
    }
//    sf::Sprite& GetAimSprite();

    sf::Sprite m_sprite;
    int m_animationSpeed;
    bool m_isAnimated;
    int m_frameCount;
    int m_currentFrame;
    int m_currentTextureIndex;
    int m_frameWidth;
    int m_frameHeight;

private:
    GameObject *_gameObject;
};

#endif /* GraphicsComponent_hpp */
