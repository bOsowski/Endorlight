//-------------------------------------------------------------------------------------
// Player.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "GraphicsComponent.hpp"
#include "PhysicsComponent.hpp"
#include "HealthComponent.hpp"
#include "InfluenceCoponent.hpp"
#include "Input.h"

//#include "Projectile.h"

class Player : public GameObject {
public:
    /**
     * Default constructor.
     */
    Player();

    /**
     * Updates the player object.
     * The main purpose of this function is to update the players position.
     * @param timeDelta The time, in MS, since the last game tick.
     * @param level A reference to the level object.
     */
    void Update(float timeDelta);//, Level& level);

    /**
     * Gets the player's class.
     * @return The player's class.
     */
    PLAYER_CLASS GetClass() const;

    /**
     * Gets the player's aim sprite.
     * return The player's aim sprite.
     */
    GraphicsComponent *graphicsComponent;
    PhysicsComponent *physicsComponent;
    HealthComponent *healthComponent;
    InfluenceComponent *influenceComponent;

private:

    /**
     * Checks if the given movement will result in a collision.
     * @param movement The movement to check.
     * @param level A reference to the level object.
     * @return True if the given movement will result in a collision.
     */
    bool CausesCollision(sf::Vector2f movement);

private:

    float speed = 200;
    /**
    * The number of stat points the entities has to distribute.
    */
    int m_statPoints;

    /**
     * The player's class.
     */
    PLAYER_CLASS m_class;

};

#endif
