#include "Game.h"
#include "IMap.h"
Game::Game() : m_window("Tiling", sf::Vector2u(1280, 800))

{
    
    
    ParticleSystem particleSystem(m_window.GetWindowSize());
    particleSystem.fuel(1000);
//    sf::Clock timer;
//    const sf::Uint32 UPDATE_STEP = 20;
//    const sf::Uint32 MAX_UPDATE_SKIP = 5;
//    sf::Uint32 nextUpdate = timer.getElapsedTime().asMilliseconds();
//    sf::Vector2f lastMousePos(static_cast<sf::Vector2f>(m_window.getWindowSize()));
//    
    
    //set up influencemap parameters
    m_player.setInfluence(10);
    m_ePlayer.setInfluence(-2);
    
    
    //Influence Map related
    sf::Vector2f anchorLoc(0,0);
    sf::Vector2u mapDim(32,32);//swapped x and y values due to run-time memory access error - revisit
    
    
    m_ePlayer.SetPosition(sf::Vector2f(150,200));
    int tileSize=32;
    m_imap = std::make_shared<GameIMap::InfluenceMap>(mapDim.x,mapDim.y,anchorLoc.x,anchorLoc.y,tileSize);
    
    //    m_imap->print();
    
    m_clock.restart();
    srand(time(nullptr));
    //mapSprite_ = nullptr;
    
    m_elapsed = 0.0f;
    if (!m_map.load(resourcePath()+
                    "tileset_bw.png",sf::Vector2u(tileSize, tileSize), level, 32, 32))
        return ;
    
    m_playerUiSprite = std::make_shared<sf::Sprite>();
    m_playerUiSprite->setTexture(TextureManager::GetTexture(m_playerUiTextureIDs[static_cast<int>(m_player.GetClass())]));
    m_playerUiSprite->setPosition(sf::Vector2f(45.f, 45.f));
    m_playerUiSprite->setOrigin(sf::Vector2f(30.f, 30.f));
    m_uiSprites.push_back(m_playerUiSprite);
    //  else
    // mapSprite_=new sf::Sprite(map)
    if (!m_font.loadFromFile(resourcePath()+"arial.ttf"))
    {
        // Error...
        std::cout <<"Error!!"<<std::endl;
        
    }
    
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::GetWindow(){ return &m_window; }



void Game::Update(){
    static int updateCounterIMap =0;
    static sf::Vector2i oldPlayerPosition(0,0);
    static sf::Vector2i old_E_PlayerPosition(0,0);
    ++updateCounterIMap;
    m_window.Update();
    float currentTime = m_clock.restart().asSeconds();
    float timeDelta = 0.f;
    sf::Event event;
    float newTime = m_clock.getElapsedTime().asSeconds();
    float frameTime = std::max(0.f, newTime - currentTime);
    
    
    m_player.Update(0.01);//use timeDelta, which needs to be calculated per frame
    m_ePlayer.Update(0.01);
    // Store the player position as it's used many times.
    if (updateCounterIMap%10==0){
        sf::Vector2i playerPosition = m_map.GetActualTileLocation(m_player.GetPosition());
        sf::Vector2i  ePlayerPosition = m_map.GetActualTileLocation(m_ePlayer.GetPosition());
        
        if(oldPlayerPosition!=playerPosition){
            m_imap->clear();//everytime player moves to new tile, reset influencemap calculation
            m_imap->setCellValue(playerPosition.x,playerPosition.y, 30);//m_player.getInfluence());
            
            m_imap->propValue(0.1, GameIMap::PropCurve::Linear);
            //both player and enemys need to be updated as imap has been cleared at start
            m_imap->propagateInfluence(playerPosition.x,playerPosition.y, 10, GameIMap::PropCurve::Linear);
            m_imap->propagateInfluence(ePlayerPosition.x,ePlayerPosition.y, 10, GameIMap::PropCurve::Linear);
            m_imap->propagateInfluence(playerPosition.x,playerPosition.y, 10, GameIMap::PropCurve::Linear);
            m_imap->propagateInfluence(ePlayerPosition.x,ePlayerPosition.y, 10, GameIMap::PropCurve::Linear);
        }
        
        //if enemy position changes, update influence map
        if(old_E_PlayerPosition!=ePlayerPosition){
            m_imap->clear();//if not done here,
            m_imap->setCellValue(ePlayerPosition.x,ePlayerPosition.y,m_ePlayer.getInfluence());
            m_imap->propValue(0.1, GameIMap::PropCurve::Linear);
            
            //both player and enemys need to be updated as imap has been cleared at start
            m_imap->propagateInfluence(playerPosition.x,playerPosition.y, 5, GameIMap::PropCurve::Linear);
            m_imap->propagateInfluence(ePlayerPosition.x,ePlayerPosition.y, 5, GameIMap::PropCurve::Linear);
            m_imap->propagateInfluence(playerPosition.x,playerPosition.y, 10, GameIMap::PropCurve::Linear);
            m_imap->propagateInfluence(ePlayerPosition.x,ePlayerPosition.y, 10, GameIMap::PropCurve::Linear);
            
        }
        
        
        
        if (updateCounterIMap%1000==0)
            cout << "enemy imap val at position =" << m_imap->getCellValue(ePlayerPosition.x,ePlayerPosition.y)<< endl;
        
        // m_imap->propagateInfluence(ePlayerPosition.x, ePlayerPosition.y, 3, GameIMap::PropCurve::Linear);
        oldPlayerPosition=playerPosition;
        old_E_PlayerPosition=ePlayerPosition;
        
    }
    
    // if (updateCounterIMap%100==0)
    
    
    currentTime = newTime;
    
    //    float timestep = 1.0f / m_snake.GetSpeed();
    //    if(m_elapsed >= timestep){
    //
    //
    //        m_elapsed -= timestep;
    //
    //    }
}
sf::Text Game::utilityFn(float val, sf::Vector2i pos)
{
    std::stringstream stream;
    stream << fixed <<setprecision(1) <<val;
    string s = stream.str();
    
    sf::Text sfTxt;
    
    sfTxt.setString(s);
    sfTxt.setFont(m_font);
    sfTxt.setCharacterSize(10);//magic number - change based on tilesize
    sfTxt.setFillColor(sf::Color::Black);
    
    sf::Vector2f text_pos;
    text_pos= m_map.GetActualTileLocation(pos.x,pos.y);
    
    sfTxt.setPosition(text_pos);
    return sfTxt;
}
void Game::Render(){
    sf::Color color = sf::Color::White;
    m_window.BeginDraw();
    // Render here.
    m_window.GetRenderWindow()->draw(this->m_map);
    // Draw the player.
    m_player.Draw(*m_window.GetRenderWindow(), m_player.m_timeDelta);
    
    std::stringstream stream;
    stream << fixed <<setprecision(1) <<m_player.getInfluence();
    string s = stream.str();
    std::vector<sf::Text> sfTextArr;
    sf::Vector2f location;
    for (auto j=0;j<m_imap->m_iHeight;j++ )
        for (auto i =0; i< m_imap->m_iWidth;i++){
            location=m_map.GetActualTileLocation(j,i);
            //if (m_imap->getCellValue(j, i)<0.0)
            //{
            color.r=m_imap->getCellValue(j, i)*128/3+128;
            color.g=m_imap->getCellValue(j, i)*128/3+128;
            color.b=m_imap->getCellValue(j, i)*128/3+128;
            m_map.rectangeOnTile(sf::Vector2i(i,j),color );
            // }
            sfTextArr.push_back(utilityFn(m_imap->getCellValue(j, i),sf::Vector2i(j,i)) );
        }
    //map.printOnTile(s,location);
    
    
    m_map.printOnTileArr(sfTextArr);
    m_ePlayer.setEvilState();
    m_ePlayer.Draw(*m_window.GetRenderWindow(), m_player.m_timeDelta);
    m_window.EndDraw();
}
