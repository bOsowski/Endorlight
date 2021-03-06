//
//  Level.hpp


#ifndef Level_hpp
#define Level_hpp

#include "enums.h"
#include "utils.h"
#include "TileMap.hpp"


// Constants for the game grid size.
static int const GRID_WIDTH = 19;
static int const GRID_HEIGHT = 19;

// The width and height of each tile in pixels.
static int const TILE_SIZE = 32;

//
//// The level tile type.
//struct Tile {
//    TILE type;                            // The type of tile this is.
//    int columnIndex;                    // The column index of the tile.
//    int rowIndex;                        // The row index of the tile.
//    sf::Sprite sprite;                    // The tile sprite.
//    int H;                                // Heuristic / movement cost to goal.
//    int G;                                // Movement cost. (Total of entire path)
//    int F;                                // Estimated cost for full path. (G + H)
//    Tile* parentNode;                    // Node to reach this node.
//};

class Level {
public:
    /**
     * Default constructor.
     */
    Level();


    Level(sf::RenderWindow &window);


    bool IsSolid(int columnIndex, int rowIndex);


    void SetTile(int columnIndex, int rowIndex, TILE tileType);


    void Draw(sf::RenderWindow &window, float timeDelta);

    /**
     * Gets the index of the given tile.
     * @param columnIndex The column index of the tile to check.
     * @param rowIndex The row index of the tile to check.
     * @return The index of the given tile.
     */
    TILE GetTileType(int columnIndex, int rowIndex) const;

    /**
     * Gets the tile at the given position.
     * @param position The coordinates of the position to check.
     * @return A pointer to the tile at the given location.
     */
    Tile *GetTile(sf::Vector2f position);

    /**
     * Gets the tile at the given position in the level array.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The row that the tile is in.
     * @return A pointer to the tile if valid.
     */
    Tile *GetTile(int columnIndex, int rowIndex);

    /**
     * Gets the position of the level grid relative to the window.
     * @return The position of the top-left of the level grid.
     */
    sf::Vector2f GetPosition() const;


    /**
     * Checks if a given tile is valid.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The column that the row is in.
     * @return True if the tile is valid.
     */
    bool TileIsValid(int columnIndex, int rowIndex);


    /**
     * Gets the size of the level in terms of tiles.
     * @return The size of the level grid.
     */
    sf::Vector2i GetSize() const;

    /**
     * Gets the actual position of a tile in the game.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The column that the row is in.
     * @return The position of the tile if valid.
     */
    sf::Vector2f GetActualTileLocation(int columnIndex, int rowIndex);


    /**
     * Resets the A* data of all level tiles.
     */
    void ResetNodes();


    /**
     * Return true if the given tile is a floor tile.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The column that the row is in.
     * @return True if the given tile is a floor tile.
     */
    bool IsFloor(int columnIndex, int rowIndex);

    /**
     * Return true if the given tile is a floor tile.
     * @param tile The tile to check
     * @return True if the given tile is a floor tile.
     */
    bool IsFloor(const Tile &tile);

    /**
     * Returns the size of the tiles in the level.
     * @return The size of the tiles in the level.
     */
    int GetTileSize() const;

    /**
     * Adds a tile to the level.
     * These tiles are essentially sprites with a unique index. Once added, they can be loaded via the LoadLevelFromFile() function by including its index in the level data.
     * @param fileName The path to the sprite resource, relative to the project directory.
     * @param tileType The type of tile that is being added.
     * @return The index of the tile. This is used when building levels.
     */
    int AddTile(std::string fileName, TILE tileType);

private:

    /**
     * Creates a path between two nodes in the recursive backtracker algorithm.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The column that the row is in.
     */
    void CreatePath(int columnIndex, int rowIndex);


    /**
     * Calculates the correct texture for each tile in the level.
     */
    void CalculateTextures();


    /**
     * Checks if a given tile is a wall block.
     * @param columnIndex The column that the tile is in.
     * @param rowIndex The column that the row is in.
     * @return True if the given tile is a wall tile.
     */
    bool IsWall(int columnIndex, int rowIndex);

private:
    /**
     * A 2D array that describes the level data.
     * The type is Tile, which holds a sprite and an index.
     */
    Tile m_grid[GRID_WIDTH][GRID_HEIGHT];

    /**
     * A vector off all the sprites in the level.
     */
    std::vector<sf::Sprite> m_tileSprites;

    /**
     * The position of the level relative to the window.
     * This is to the top-left of the level grid.
     */
    sf::Vector2i m_origin;


    /**
     * A 2D array that contains the room layout for the current floor.
     */
    int m_roomLayout[3][10];

    /**
     * An array containing all texture IDs of the level tiles.
     */
    int m_textureIDs[static_cast<int>(TILE::COUNT)];


};

#endif /* Level_hpp */
