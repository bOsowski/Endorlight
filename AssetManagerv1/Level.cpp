
//

#include "Level.hpp"


// Default constructor.
Level::Level() {
}

// Constructor.
Level::Level(sf::RenderWindow &window) :
        m_origin({0, 0}) {
    // Load all tiles.
    AddTile("spr_tile_floor.png", TILE::FLOOR);

    AddTile("spr_tile_wall_top.png", TILE::WALL_TOP);
    AddTile("spr_tile_wall_top_left.png", TILE::WALL_TOP_LEFT);
    AddTile("spr_tile_wall_top_right.png", TILE::WALL_TOP_RIGHT);
    AddTile("spr_tile_wall_top_t.png", TILE::WALL_TOP_T);
    AddTile("spr_tile_wall_top_end.png", TILE::WALL_TOP_END);

    AddTile("spr_tile_wall_bottom_left.png", TILE::WALL_BOTTOM_LEFT);
    AddTile("spr_tile_wall_bottom_right.png", TILE::WALL_BOTTOM_RIGHT);
    AddTile("spr_tile_wall_bottom_t.png", TILE::WALL_BOTTOM_T);
    AddTile("spr_tile_wall_bottom_end.png", TILE::WALL_BOTTOM_END);

    AddTile("spr_tile_wall_side.png", TILE::WALL_SIDE);
    AddTile("spr_tile_wall_side_left_t.png", TILE::WALL_SIDE_LEFT_T);
    AddTile("spr_tile_wall_side_left_end.png", TILE::WALL_SIDE_LEFT_END);
    AddTile("spr_tile_wall_side_right_t.png", TILE::WALL_SIDE_RIGHT_T);
    AddTile("spr_tile_wall_side_right_end.png", TILE::WALL_SIDE_RIGHT_END);

    AddTile("spr_tile_wall_intersection.png", TILE::WALL_INTERSECTION);
    AddTile("spr_tile_wall_single.png", TILE::WALL_SINGLE);

    AddTile("spr_tile_wall_entrance.png", TILE::WALL_ENTRANCE);
    AddTile("spr_tile_door_locked.png", TILE::WALL_DOOR_LOCKED);
    AddTile("spr_tile_door_unlocked.png", TILE::WALL_DOOR_UNLOCKED);

    // Calculate the top left of the grid.
    m_origin.x = (window.getSize().x - (GRID_WIDTH * TILE_SIZE));
    m_origin.x /= 2;

    m_origin.y = (window.getSize().y - (GRID_HEIGHT * TILE_SIZE));
    m_origin.y /= 2;

    // Store the column and row information for each node.
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            auto cell = &m_grid[i][j];
            cell->columnIndex = i;
            cell->rowIndex = j;
        }
    }


}

// Create and adds a tile sprite to the list of those available.
int Level::AddTile(std::string fileName, TILE tileType) {
    // Add the texture to the texture manager.
    int textureID = TextureManager::AddTexture(fileName);

    if (textureID < 0) {
        return -1; // Failed
    } else {
        m_textureIDs[static_cast<int>(tileType)] = textureID;
    }

    // Return the ID of the tile.
    return textureID;
}

// Checks if a given tile is passable
bool Level::IsSolid(int i, int j) {
    // Check that the tile is valid
    if (TileIsValid(i, j)) {
        int tileIndex = static_cast<int>(m_grid[i][j].type);
        return (((tileIndex != static_cast<int>(TILE::FLOOR)) && (tileIndex != static_cast<int>(TILE::FLOOR_ALT))) && (tileIndex != static_cast<int>(TILE::WALL_DOOR_UNLOCKED)));
    } else
        return false;
}

// Returns the position of the level relative to the application window.
sf::Vector2f Level::GetPosition() const {
    return sf::Vector2f(static_cast<float>(m_origin.x), static_cast<float>(m_origin.y));
}

// Returns the id of the given tile in the 2D level array.
TILE Level::GetTileType(int columnIndex, int rowIndex) const {
    // Check that the parameters are valid.
    if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT)) {
        return TILE::EMPTY; // failed
    }

    // Fetch the id.
    return m_grid[columnIndex][rowIndex].type;
}

// Sets the id of the given tile in the grid.
void Level::SetTile(int columnIndex, int rowIndex, TILE tileType) {
    // Check that the provided tile index is valid.
    if ((columnIndex >= GRID_WIDTH) || (rowIndex >= GRID_HEIGHT)) {
        return;
    }

    // check that the sprite index is valid
    if (tileType >= TILE::COUNT) {
        return;
    }

    // change that tiles sprite to the new index
    m_grid[columnIndex][rowIndex].type = tileType;
    m_grid[columnIndex][rowIndex].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(tileType)]));
}


// Checks if a given tile is valid.
bool Level::TileIsValid(int column, int row) {
    bool validColumn, validRow;

    validColumn = ((column >= 0) && (column < GRID_WIDTH));
    validRow = ((row >= 0) && (row < GRID_HEIGHT));

    return (validColumn && validRow);
}

// Gets the size of the level in terms of tiles.
sf::Vector2i Level::GetSize() const {
    return sf::Vector2i(GRID_WIDTH, GRID_HEIGHT);
}

// Gets the tile that the position lies on.
Tile *Level::GetTile(sf::Vector2f position) {
    // Convert the position to relative to the level grid.
    position.x -= m_origin.x;
    position.y -= m_origin.y;

    // Convert to a tile position.
    int tileColumn, tileRow;

    tileColumn = static_cast<int>(position.x) / TILE_SIZE;
    tileRow = static_cast<int>(position.y) / TILE_SIZE;

    return &m_grid[tileColumn][tileRow];
}

// Returns a pointer to the tile at the given index.
Tile *Level::GetTile(int columnIndex, int rowIndex) {
    if (TileIsValid(columnIndex, rowIndex)) {
        return &m_grid[columnIndex][rowIndex];
    } else {
        return nullptr;
    }
}

// Gets the actual location of a tile in the level.
sf::Vector2f Level::GetActualTileLocation(int columnIndex, int rowIndex) {
    sf::Vector2f location;

    location.x = static_cast<float>(m_origin.x + (columnIndex * TILE_SIZE) + (TILE_SIZE / 2));
    location.y = static_cast<float>(m_origin.y + (rowIndex * TILE_SIZE) + (TILE_SIZE / 2));

    return location;
}


// Resets the A* data of all tiles.
void Level::ResetNodes() {
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            auto cell = &m_grid[i][j];
            cell->parentNode = nullptr;
            cell->H = 0;
            cell->G = 0;
            cell->F = 0;
        }
    }
}

// Create a path between two tiles in the level grid.
void Level::CreatePath(int columnIndex, int rowIndex) {
    // Store the current tile.
    Tile *currentTile = &m_grid[columnIndex][rowIndex];

    // Create a list of possible directions and sort randomly.
    sf::Vector2i directions[] = {{0, -2}, {2, 0}, {0, 2}, {-2, 0}};
    std::random_shuffle(std::begin(directions), std::end(directions));

    // For each direction.
    for (int i = 0; i < 4; i++) {
        // Get the new tile position.
        int dx = currentTile->columnIndex + directions[i].x;
        int dy = currentTile->rowIndex + directions[i].y;

        // If the tile is valid.
        if (TileIsValid(dx, dy)) {
            // Store the tile.
            Tile *tile = &m_grid[dx][dy];

            // If the tile has not yet been visited.
            if (tile->type == TILE::EMPTY) {
                // Mark the tile as floor.
                tile->type = TILE::FLOOR;
                tile->sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

                // Knock that wall down.
                int ddx = currentTile->columnIndex + (directions[i].x / 2);
                int ddy = currentTile->rowIndex + (directions[i].y / 2);

                Tile *wall = &m_grid[ddx][ddy];
                wall->type = TILE::FLOOR;
                wall->sprite.setTexture(TextureManager::GetTexture(m_textureIDs[static_cast<int>(TILE::FLOOR)]));

                // Recursively call the function with the new tile.
                CreatePath(dx, dy);
            }
        }
    }
}

// Adds a given number of randomly sized rooms to the level to create some open space.

// Calculates the correct texture for each tile in the level.
void Level::CalculateTextures() {
    // For each tile in the grid.
    for (int i = 0; i < GRID_WIDTH; ++i) {
        for (int j = 0; j < GRID_HEIGHT; ++j) {
            // Check that the tile is a wall block.
            if (IsWall(i, j)) {
                // Calculate bit mask.
                int value = 0;

                // Store the current type as default.
                TILE type = m_grid[i][j].type;

                // Top.
                if (IsWall(i, j - 1)) {
                    value += 1;
                }

                // Right.
                if (IsWall(i + 1, j)) {
                    value += 2;
                }

                // Bottom.
                if (IsWall(i, j + 1)) {
                    value += 4;
                }

                // Left.
                if (IsWall(i - 1, j)) {
                    value += 8;
                }

                // Set the new type.
                m_grid[i][j].type = (TILE) value;
                m_grid[i][j].sprite.setTexture(TextureManager::GetTexture(m_textureIDs[value]));
            }
        }
    }
}


// Checks if a given tile is a wall block.
bool Level::IsWall(int i, int j) {
    if (TileIsValid(i, j))
        return m_grid[i][j].type <= TILE::WALL_INTERSECTION;
    else
        return false;
}


// Return true if the given tile is a floor tile.
bool Level::IsFloor(int columnIndex, int rowIndex) {
    Tile *tile = &m_grid[columnIndex][rowIndex];

    return ((tile->type == TILE::FLOOR) || (tile->type == TILE::FLOOR_ALT));
}

// Return true if the given tile is a floor tile.
bool Level::IsFloor(const Tile &tile) {
    return ((tile.type == TILE::FLOOR) || (tile.type == TILE::FLOOR_ALT));
}

// Gets the size of the tiles in the level.
int Level::GetTileSize() const {
    return TILE_SIZE;
}


// Draws the level grid to the given render window.
void Level::Draw(sf::RenderWindow &window, float timeDelta) {
    // Draw the level tiles.
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            window.draw(m_grid[i][j].sprite);
        }
    }


}
