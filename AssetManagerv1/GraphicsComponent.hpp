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
#include "GameObject.hpp"
#include "enums.h"
#include "Window.h"
#include "TextureManager.h"

class GameObject;

class Graphics;

class GraphicsComponent {
public:
    GraphicsComponent(GameObject *gameObject);

    int m_textureIDs[static_cast<int>(ANIMATION_STATE::COUNT)];
    ANIMATION_STATE animState;

    bool SetSprite(sf::Texture &texture, bool isSmooth, int frames, int frameSpeed);

    void Update(float timeDelta) {
    };

    void Draw(sf::RenderWindow &window, float timeDelta);

    sf::Sprite &GetSprite();

    int GetFrameCount() const;

    bool IsAnimated();

    void SetAnimated(bool isAnimated);

    void updatePosition(sf::Vector2f position);

    void setToIdle();

    void setToWalking();

    void draw(sf::RenderWindow &window, float timeDelta);

    void NextFrame();
//    sf::Sprite& GetAimSprite();

    sf::Sprite m_sprite;
    int m_animationSpeed;
    bool m_isAnimated;
    int m_frameCount;
    int m_currentFrame;
    int m_currentTextureIndex;
    int m_frameWidth;
    int m_frameHeight;
    float m_timeDelta;

private:
    GameObject *_gameObject;
};

#endif /* GraphicsComponent_hpp */
