//
//  InfluenceCoponent.hpp
//  AssetManagerv1
//
//  Created by Bartosz Osowski on 21/11/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#ifndef InfluenceCoponent_hpp
#define InfluenceCoponent_hpp

#include <stdio.h>

class InfluenceComponent{
public:
    void setInfluence(float influence){m_influenceValue=influence;};
    float getInfluence(){ return(m_influenceValue);};
    
private:
    float m_influenceValue = 1;
};
#endif /* InfluenceCoponent_hpp */
