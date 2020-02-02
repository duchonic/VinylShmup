//
//  MoveShip.cpp
//  VinylShmup
//
//  Created by duchonic on 02.02.20.
//

#include "MoveShip.hpp"

USING_NS_CC;

Scene* MoveShip::createScene()
{
    auto scene = Scene::create();
    auto layer = MoveShip::create();
    scene->addChild(layer);
    
    return scene;
}

bool MoveShip::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto sprite = Sprite::create("missile.png");
    sprite->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);

    this->addChild(sprite, 0);

    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event){

        log("%u", keyCode);
        
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch(keyCode){
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
                event->getCurrentTarget()->setPosition(--loc.x,loc.y);
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                event->getCurrentTarget()->setPosition(++loc.x,loc.y);
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_W:
                event->getCurrentTarget()->setPosition(loc.x,++loc.y);
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                event->getCurrentTarget()->setPosition(loc.x,--loc.y);
                break;
        }
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,sprite);

    return true;
    
    return true;
}
