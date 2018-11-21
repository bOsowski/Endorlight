//
//  GraphicsComponent.cpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 20/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#include "GraphicsComponent.hpp"

// Advances the sprite forward a frame.
void GraphicsComponent::NextFrame()
{
    // check if we reached the last frame
    if (m_currentFrame == (m_frameCount - 1))
        m_currentFrame = 0;
    else
        m_currentFrame++;
    
    // update the texture rect
    m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}


// Draws the object to the given render window.
void GraphicsComponent::draw(sf::RenderWindow &window, float timeDelta)
{
    // check if the sprite is animated
    if (m_isAnimated)
    {
        // add the elapsed time since the last draw call to the aggregate
        m_timeDelta += timeDelta;
        
        // check if the frame should be updated
        if (m_timeDelta >= (1.f / m_animationSpeed))
        {
            NextFrame();
            m_timeDelta = 0;
        }
    }
    
    window.draw(m_sprite);
}

void GraphicsComponent::setToIdle(){
    // Update sprite to idle version.
    // In our enum we have 4 walking sprites followed by 4 idle sprites.
    // Given this, we can simply add 4 to a walking sprite to get its idle counterpart.
    m_currentTextureIndex += 4;
    m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
    // Stop movement animations.
    SetAnimated(false);
}

void GraphicsComponent::setToWalking(){
    // Update sprite to walking version.
    m_currentTextureIndex -= 4;
    m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
    
    // Start movement animations.
    SetAnimated(true);
}

void GraphicsComponent::updatePosition(sf::Vector2f position){
    m_sprite.setPosition(position);
    
    // Set the sprite.
    if (m_currentTextureIndex != static_cast<int>(animState))
    {
        m_currentTextureIndex = static_cast<int>(animState);
        m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
        //m_sprite.setColor(sf::Color::Red); //"evil" version
    }
}

GraphicsComponent::GraphicsComponent(GameObject* gameObject)
:_gameObject(gameObject)
{
    animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);
}

// Gives the object the given sprite.
bool GraphicsComponent::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed)
{
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
    if (frames > 1)
    {
        // Set sprite as animated.
        m_isAnimated = true;
        
        // Set the texture rect of the first frame.
        m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    }
    else
    {
        // Set sprite as non animated.
        m_isAnimated = false;
    }
    
    // Set the origin of the sprite.
    m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);
    
    return true;
}

// Returns the object's sprite.
sf::Sprite& GraphicsComponent::GetSprite()
{
    return m_sprite;
}


// Gets the current animation state of the object.
bool GraphicsComponent::IsAnimated()
{
    return m_isAnimated;
}

// Sets the animation state of the object.
void GraphicsComponent::SetAnimated(bool isAnimated)
{
    m_isAnimated = isAnimated;
    
    if (isAnimated)
    {
        m_currentFrame = 0;
    }
    else
    {
        // set the texture rect of the first frame
        m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    }
}
