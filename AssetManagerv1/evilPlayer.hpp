//
//  evilPlayer.hpp
//  AssetManagerv1
//
//  Created by Denis Flynn on 16/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef evilPlayer_hpp
#define evilPlayer_hpp

#include "utils.h"
#include "Player.h"
#include "GameObject.hpp"
#include "GraphicsComponent.hpp"
#include "PhysicsComponent.hpp"
#include "HealthComponent.hpp"
#include "InfluenceCoponent.hpp"
#include "Input.h"

class evilPlayer : public GameObject {
public:
    /**
     * Default constructor.
     */
    evilPlayer()
            : physicsComponent(new PhysicsComponent(this)),
              graphicsComponent(new GraphicsComponent(this)),
              healthComponent(new HealthComponent()),
              influenceComponent(new InfluenceComponent()) {
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

        graphicsComponent->m_sprite.setColor(sf::Color::Red); //"evil" version
    }


    void Update(float timeDelta);

    // Recalculates the enemies path finding.
//    void UpdatePathfinding(Level &level, sf::Vector2f playerPosition) {
//        // Create all variables.
//        std::vector<Tile *> openList;
//        std::vector<Tile *> closedList;
//        std::vector<Tile *> pathList;
//        std::vector<Tile *>::iterator position;
//        Tile *currentNode;
//
//        // Reset all nodes.
//        level.ResetNodes();
//
//        // Store the start and goal nodes.
//        Tile *startNode = level.GetTile(m_position);
//        Tile *goalNode = level.GetTile(playerPosition);
//
//        // Check we have a valid path to find. If not we can just end the function as there's no path to find.
//        if (startNode == goalNode) {
//            // Clear the vector of target positions.
//            m_targetPositions.clear();
//
//            // Exit the function.
//            return;
//        }
//
//        // Pre-compute our H cost (estimated cost to goal) for each node.
//        for (int i = 0; i < level.GetSize().x; i++) {
//            for (int j = 0; j < level.GetSize().y; j++) {
//                int rowOffset, heightOffset;
//                Tile *node = level.GetTile(i, j);
//
//                heightOffset = abs(node->rowIndex - goalNode->rowIndex);
//                rowOffset = abs(node->columnIndex - goalNode->columnIndex);
//
//                node->H = heightOffset + rowOffset;
//            }
//        }
//
//        // Add the start node to the open list.
//        openList.push_back(startNode);
//
//        // While we have values to check in the open list.
//        while (!openList.empty()) {
//            // Find the node in the open list with the lowest F value and mark it as current.
//            int lowestF = INT_MAX;
//
//            for (Tile *tile : openList) {
//                if (tile->F < lowestF) {
//                    lowestF = tile->F;
//                    currentNode = tile;
//                }
//            }
//
//            // Remove the current node from the open list and add it to the closed list.
//            position = std::find(openList.begin(), openList.end(), currentNode);
//            if (position != openList.end())
//                openList.erase(position);
//
//            closedList.push_back(currentNode);
//
//            // Find all valid adjacent nodes.
//            std::vector<Tile *> adjacentTiles;
//            Tile *node;
//
//            // Top.
//            node = level.GetTile(currentNode->columnIndex, currentNode->rowIndex - 1);
//            if ((node != nullptr) && (level.IsFloor(*node))) {
//                adjacentTiles.push_back(level.GetTile(currentNode->columnIndex, currentNode->rowIndex - 1));
//            }
//
//            // Right.
//            node = level.GetTile(currentNode->columnIndex + 1, currentNode->rowIndex);
//            if ((node != nullptr) && (level.IsFloor(*node))) {
//                adjacentTiles.push_back(level.GetTile(currentNode->columnIndex + 1, currentNode->rowIndex));
//            }
//
//            // Bottom.
//            node = level.GetTile(currentNode->columnIndex, currentNode->rowIndex + 1);
//            if ((node != nullptr) && (level.IsFloor(*node))) {
//                adjacentTiles.push_back(level.GetTile(currentNode->columnIndex, currentNode->rowIndex + 1));
//            }
//
//            // Left.
//            node = level.GetTile(currentNode->columnIndex - 1, currentNode->rowIndex);
//            if ((node != nullptr) && (level.IsFloor(*node))) {
//                adjacentTiles.push_back(level.GetTile(currentNode->columnIndex - 1, currentNode->rowIndex));
//            }
//
//            // For all adjacent nodes.
//            for (Tile *node : adjacentTiles) {
//                // If the node is our goal node.
//                if (node == goalNode) {
//                    // Parent the goal node to current.
//                    node->parentNode = currentNode;
//
//                    // Store the current path.
//                    while (node->parentNode != nullptr) {
//                        pathList.push_back(node);
//                        node = node->parentNode;
//                    }
//
//                    // Empty the open list and break out of our for loop.
//                    openList.clear();
//                    break;
//                } else {
//                    // If the node is not in the closed list.
//                    position = std::find(closedList.begin(), closedList.end(), node);
//                    if (position == closedList.end()) {
//                        // If the node is not in the open list.
//                        position = std::find(openList.begin(), openList.end(), node);
//                        if (position == openList.end()) {
//                            // Add the node to the open list.
//                            openList.push_back(node);
//
//                            // Set the parent of the node to the current node.
//                            node->parentNode = currentNode;
//
//                            // Calculate G (total movement cost so far) cost.
//                            node->G = currentNode->G + 10;
//
//                            // Calculate the F (total movement cost + heuristic) cost.
//                            node->F = node->G + node->H;
//                        } else {
//                            // Check if this path is quicker that the other.
//                            int tempG = currentNode->G + 10;
//
//                            // Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
//                            if (tempG < node->G) {
//                                // Re-parent node to this one.
//                                node->parentNode = currentNode;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//
//        // Clear the vector of target positions.
//        m_targetPositions.clear();
//
//        // Store the node locations as the enemies target locations.
//        for (Tile *tile : pathList) {
//            m_targetPositions.push_back(level.GetActualTileLocation(tile->columnIndex, tile->rowIndex));
//        }
//
//        // Reverse the target position as we read them from goal to origin and we need them the other way around.
//        std::reverse(m_targetPositions.begin(), m_targetPositions.end());
//    }

    GraphicsComponent *graphicsComponent;
    PhysicsComponent *physicsComponent;
    HealthComponent *healthComponent;
    InfluenceComponent *influenceComponent;

protected:
//    /**
//     * The target position of the enemy.
//     */
//    std::vector<sf::Vector2f> m_targetPositions;
//
//    /**
//     * The current target of the enemy.
//     */
//    sf::Vector2f m_currentTarget;

private:
    float speed = 200;
};

#endif /* evilPlayer_hpp */
