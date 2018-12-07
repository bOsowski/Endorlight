#pragma once

#include "Window.h"
#include "ResourcePath.hpp"
#include "TileMap.hpp"
#include "Player.h"
#include "evilPlayer.hpp"
#include "IMap.h"
#include "particle.hpp"


static float const FPS = 60.0;
static float const MS_PER_STEP = 1.0f / FPS;        // Roughly (0.017) @ 60fps.

class Game {
public:
    Game() : m_window("Tiling", sf::Vector2u(1280, 800)) {


        ParticleSystem particleSystem(m_window.GetWindowSize());
        particleSystem.fuel(1000);

        //set up influencemap parameters
        m_player.influenceComponent->setInfluence(10);
        m_ePlayer.influenceComponent->setInfluence(-2);


        //Influence Map related
        sf::Vector2f anchorLoc(0, 0);
        sf::Vector2u mapDim(32, 32);//swapped x and y values due to run-time memory access error - revisit


        m_ePlayer.position = (sf::Vector2f(150, 200));
        int tileSize = 32;
        m_imap = std::make_shared<GameIMap::InfluenceMap>(mapDim.x, mapDim.y, anchorLoc.x, anchorLoc.y, tileSize);

        //    m_imap->print();

        m_clock.restart();
        srand(time(0));

        m_deltaTime = 0.0f;
        if (!m_map.load(resourcePath() +
                "tileset_bw.png", sf::Vector2u(tileSize, tileSize), level, 32, 32))
            return;

        m_playerUiSprite = std::make_shared<sf::Sprite>();
        //m_playerUiSprite->setTexture(TextureManager::GetTexture(m_playerUiTextureIDs[static_cast<int>(m_player.GetClass())]));
        m_playerUiSprite->setPosition(sf::Vector2f(45.f, 45.f));
        m_playerUiSprite->setOrigin(sf::Vector2f(30.f, 30.f));
        m_uiSprites.push_back(m_playerUiSprite);
        //  else
        // mapSprite_=new sf::Sprite(map)
        if (!m_font.loadFromFile(resourcePath() + "arial.ttf")) {
            // Error...
            std::cout << "Error!!" << std::endl;

        }

    }


    void Update() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
            showInfluenceValues = !showInfluenceValues;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
            showInfluenceMapColours = !showInfluenceMapColours;
        }
        static int updateCounterIMap = 0;
        static sf::Vector2i oldPlayerPosition(0, 0);
        static sf::Vector2i old_E_PlayerPosition(0, 0);
        ++updateCounterIMap;
        m_window.Update();
        float currentTime = m_clock.restart().asSeconds();
        float newTime = m_clock.getElapsedTime().asSeconds();


        m_player.Update(0.01);//use timeDelta, which needs to be calculated per frame
        m_ePlayer.Update(0.01);
        // Store the player position as it's used many times.
        if (updateCounterIMap % 10 == 0) {
            sf::Vector2i playerPosition = m_map.GetActualTileLocation(m_player.position);
            sf::Vector2i ePlayerPosition = m_map.GetActualTileLocation(m_ePlayer.position);

            m_imap->clear();//if not done here,
            if (oldPlayerPosition != playerPosition) {
                m_imap->setCellValue(playerPosition.x, playerPosition.y, 30);//m_player.getInfluence());
            }
            //if enemy position changes, update influence map
            if (old_E_PlayerPosition != ePlayerPosition) {
                m_imap->setCellValue(ePlayerPosition.x, ePlayerPosition.y, m_ePlayer.influenceComponent->getInfluence());
            }
            //both player and enemys need to be updated as imap has been cleared at start
            for (int i = 0; i < 2; i++) {
                m_imap->propagateInfluence(ePlayerPosition.x, ePlayerPosition.y, 10, GameIMap::PropCurve::Linear, -1);
                m_imap->propagateInfluence(playerPosition.x, playerPosition.y, 10, GameIMap::PropCurve::Linear, 1);
            }


            if (updateCounterIMap % 1000 == 0)
                cout << "enemy imap val at position =" << m_imap->getCellValue(ePlayerPosition.x, ePlayerPosition.y)
                     << endl;

            oldPlayerPosition = playerPosition;
            old_E_PlayerPosition = ePlayerPosition;

        }

        currentTime = newTime;

    }

    void Render() {
        sf::Color color = sf::Color::Black;
        m_window.BeginDraw();
        // Render here.
        m_window.GetRenderWindow()->draw(this->m_map);
        // Draw the player.

        // todo: fix this.
        //m_player.graphicsComponent->draw(*m_window.GetRenderWindow());
        m_window.Draw(*m_player.graphicsComponent);

        std::stringstream stream;
        stream << fixed << setprecision(1) << m_player.influenceComponent->getInfluence();
        string s = stream.str();
        std::vector<sf::Text> sfTextArr;
        for (auto j = 0; j < m_imap->m_iHeight; j++)
            for (auto i = 0; i < m_imap->m_iWidth; i++) {
                if (showInfluenceMapColours) {
                    if (m_imap->getCellValue(j, i) < 0) {
                        color.b = (m_imap->getCellValue(j, i) * 128 / 2.5 + 128);
                        color.r = -1 * (m_imap->getCellValue(j, i) * 128 / 2.5 + 128);
                    }
                    if (m_imap->getCellValue(j, i) > 0) {
                        color.r = -1 * m_imap->getCellValue(j, i) * 128 / 2.5 + 128;
                        color.b = m_imap->getCellValue(j, i) * 128 / 2.5 + 128;
                    }
                    if (m_imap->getCellValue(j, i) == 0) {
                        color.b = (m_imap->getCellValue(j, i) * 128 / 2.5 + 128);
                        color.r = (m_imap->getCellValue(j, i) * 128 / 2.5 + 128);
                    }
                }

                m_map.rectangeOnTile(sf::Vector2i(i, j), color);
                sfTextArr.push_back(utilityFn(m_imap->getCellValue(j, i), sf::Vector2i(j, i)));
            }

        if (!showInfluenceValues) {
            sfTextArr.clear();
        }
        m_map.printOnTileArr(sfTextArr);
        // todo: fix this
        m_window.Draw(*m_ePlayer.graphicsComponent);
        //m_ePlayer.graphicsComponent->draw(*m_window.GetRenderWindow());
        m_window.EndDraw();
    }


    bool IsRunning() {
        return m_isRunning;
    }

    float deltaTime(){
        return m_deltaTime;
    }

    void RestartClock() {
        m_deltaTime += m_clock.restart().asSeconds();
    }

    Window* GetWindow() {
        return &m_window;
    }

    sf::Text utilityFn(float val, sf::Vector2i pos) {
        std::stringstream stream;
        stream << fixed << setprecision(1) << val;
        string s = stream.str();

        sf::Text sfTxt;

        sfTxt.setString(s);
        sfTxt.setFont(m_font);
        sfTxt.setCharacterSize(10);//magic number - change based on tilesize
        sfTxt.setFillColor(sf::Color::White);

        sf::Vector2f text_pos;
        text_pos = m_map.GetActualTileLocation(pos.x, pos.y);

        sfTxt.setPosition(text_pos);
        return sfTxt;
    }


private:
    Window m_window;
    const int numTiles = 1024;
    bool showInfluenceMapColours = true;
    bool showInfluenceValues = true;

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
    float m_deltaTime;
    
    TileMap m_map;
    sf::Sprite mapSprite_;
    std::vector<int> level =
            {
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
                    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
                    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
                    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
                    2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
                    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
                    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
                    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
                    2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
                    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
                    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
                    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
                    2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
                    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
                    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
                    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
                    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
                    2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 2, 0, 1, 10, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1

            };;


};
