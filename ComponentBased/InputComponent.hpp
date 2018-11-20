//
//  InputComponent.hpp
//  ComponentBased
//
//  Created by Denis Flynn on 31/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp

#include "GameObject.hpp"

class GameObject;

class InputComponent
{
public:
    void update(GameObject& GameObject) {}
    
    /**
     * Checks if a given key is currently pressed.
     * @param keycode The key to check.
     * @return True if the given key is currently pressed.
     */
    static bool IsKeyPressed(Keyboard keycode);
};

class PlayerInputComponent : public InputComponent
{
public:
    virtual void update(GameObject& GameObject)
    {
        switch (Controller::getJoystickDirection())
        {
            case Joystick::DIR_LEFT:
                GameObject.velocity -= WALK_ACCELERATION;
                break;
                
            case Joystick::DIR_RIGHT:
                GameObject.velocity += WALK_ACCELERATION;
                break;
                //^omit
            case Joystick::DIR_NONE: break; // Do nothing.
                //^omit
            case Joystick::DIR_UP:  break; //do something later
            case Joystick::DIR_DOWN: break; //do something later
        }
    }
    
private:
    static const int WALK_ACCELERATION = 1;
};


#endif /* InputComponent_hpp */
