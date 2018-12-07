//
//  TransformComponent.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 07/12/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include <stdio.h>
#include "BasicComponent.hpp"
#include "Box2D/Box2D.h"

class TransformComponent: BasicComponent{
public:
    TransformComponent(b2Body* _body, GameObject* delegate) :
            BasicComponent("TransformComponent", delegate),
            body(_body)
    {}
    b2Body* body;

};

#endif /* TransformComponent_hpp */
