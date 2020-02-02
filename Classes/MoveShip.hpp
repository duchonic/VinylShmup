//
//  MoveShip.hpp
//  VinylShmup
//
//  Created by duchonic on 02.02.20.
//

#ifndef MoveShip_hpp
#define MoveShip_hpp

#include <stdio.h>
#include "cocos2d.h"


class MoveShip : public cocos2d::Layer
{
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(MoveShip);
private:
    
};



#endif /* MoveShip_hpp */
