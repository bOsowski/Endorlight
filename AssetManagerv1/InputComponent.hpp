//
//  InputComponent.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 20/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp

#include "GameObject.hpp"
#include "Window.h"

class GameObject;

class InputComponent {
public:
    void update(GameObject &GameObject) {
    }

    /**
     * Checks if a given key is currently pressed.
     * @param keycode The key to check.
     * @return True if the given key is currently pressed.
     */
    static bool IsKeyPressed(sf::Keyboard keycode);
};

#endif /* InputComponent_hpp */
