

#pragma once

#include "cocos2d.h"
#include <map>

USING_NS_CC;

class KeyboardScene : public Layer
{
public:

    KeyboardScene() : speed(4){
        log("constructor");
    };
    
    static Scene* createScene();
    virtual bool init();

    bool isKeyPressed(EventKeyboard::KeyCode);
    double keyPressedDuration(EventKeyboard::KeyCode);

    CREATE_FUNC(KeyboardScene);

private:
    static std::map<EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> keys;
    cocos2d::Label * label;
    cocos2d::Sprite * sprite;
    cocos2d::Sprite3D * ship3d;
    
    int speed;
    
public:
    virtual void update(float delta) override;
};

