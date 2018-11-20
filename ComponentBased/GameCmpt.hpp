#ifndef GameCMPT_hpp
#define GameCMPT_hpp
#include "Window.h"
#include "ResourcePath.hpp"
#include "TileMap.hpp"
#include "Player.h"
#include "evilPlayer.hpp"
#include "IMap.h"

static float const FPS = 60.0;
static float const MS_PER_STEP = 1.0f / FPS;        // Roughly (0.017) @ 60fps.

class Game{
public:
	Game();
	~Game();

	void Update();
	void Render();
    bool IsRunning()
    {
        return m_isRunning;
    }

	sf::Time GetElapsed();
	void RestartClock();

	Window* GetWindow();
    sf::Text utilityFn(float , sf::Vector2i );
    
private:
	Window m_window;
     const int numTiles=512;
    
    std::shared_ptr<GameIMap::InfluenceMap> m_imap;
    
    sf::Font m_font;
    
    /**
     * An array of texture for the player in the UI.
     */
    int m_playerUiTextureIDs[static_cast<int>(PLAYER_CLASS::COUNT)];
    
    
    
    /**
     * The sprite that shows the player class in the UI.
     */
    std::shared_ptr<sf::Sprite> m_playerUiSprite;
    
    /**
     * A vector of all ui sprites.
     */
    std::vector<std::shared_ptr<sf::Sprite>> m_uiSprites;
    
    /**
     * The main player object. Only one instance of this object should be created at any one time.
     */
    Player m_player;
    evilPlayer m_ePlayer;
    
    bool m_isRunning; //want to be able to quit gameloop
    
	sf::Clock m_clock;
	float m_elapsed;
    TileMap m_map;
    sf::Sprite mapSprite_;
    std::vector<int> level=
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1
        
    };;
    
    



};
#endif  