//
//  Component.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 07/12/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef BasicComponent_hpp
#define BasicComponent_hpp

#include <stdio.h>
#include "Window.h"
#include <string>
#include "GameObject.hpp"

class GameObject;

class BasicComponent{

public:
    BasicComponent(std::string __name, GameObject* _delegate):
            _name(__name),
            delegate(_delegate)
    {

    }
    
    virtual void update(float deltaTime);

    GameObject* delegate;

    std::string name(){
        return _name;
    }

private:
    std::string _name;
};

#endif /* BasicComponent_hpp */
