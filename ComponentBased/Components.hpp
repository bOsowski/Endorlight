//
//  Components.hpp
//  AssetManagerv1
//

//



#ifndef COMPONENTS_hpp
#define COMPONENTS_hpp

class Bjorn;
class GameObject;
class PlayerInputComponent;

enum class Joystick
{
    DIR_NONE,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
    
};

 enum class Keyboard
{
    DIR_NONE,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_ATTACK,
    KEY_ESC
    
};


class Controller
{
public:
    static Joystick getJoystickDirection()
    {
        // Determine which direction the user is currently
        // pressing on the joystick...
        return Joystick::DIR_NONE;
    }
    static Keyboard getKeyboardDirection()
    {
        // Determine which direction the user is currently
        // pressing on the joystick...
        return Keyboard::DIR_NONE;
    }
};

class Sprite
{
};

class Graphics
{
public:
    void draw(Sprite& sprite, int x, int y)
    {
        // Draw the sprite at the given position...
    }
};

class Volume
{
};

class World
{
public:
    void resolveCollision(Volume& volume, int& x, int& y, int& velocity)
    {
        // Determine what the hero is colliding with and
        // modify position and velocity if needed...
    }
};




#endif











