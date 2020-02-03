

#include "KeyboardScene.hpp"



Scene* KeyboardScene::createScene()
{
    auto scene = Scene::create();
    
    KeyboardScene* layer = KeyboardScene::create();
    scene->addChild(layer);
    return scene;
}

bool KeyboardScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    sprite = Sprite::create("ship.png");
    sprite->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    this->addChild(sprite, 0);
    
    ship3d = Sprite3D::create("boss.c3b"); //c3b file, created with the FBX-converter
    ship3d->setScale(5.f); //sets the object scale in float
    ship3d->setPosition(Vec2(100,200)); //sets sprite position
    ship3d->setRotation(180);
    
    this->addChild(ship3d, 1); //adds sprite to scene, z-index: 1
    
    
    //rotate around the X axis
    auto rotation = RotateBy::create(1, Vec3(0, 360, 0));
    //our sprite object runs the action
    ship3d->runAction(RepeatForever::create(rotation));
    
    
    
    
    auto light = DirectionLight::create(Vec3(-1.0f, -1.0f, 0.0f), Color3B::RED);
    addChild(light);
    
    label = cocos2d::Label::createWithSystemFont("Press the CTRL Key","Arial",11);
    label->setPosition(this->getBoundingBox().getMidX(),this->getBoundingBox().getMidY());
    addChild(label);
    auto eventListener = EventListenerKeyboard::create();

    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if(keys.find(keyCode) == keys.end()){
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);

    // Let cocos know we have an update function to be called.
    // No worries, ill cover this in more detail later on
    this->scheduleUpdate();
    return true;
}

bool KeyboardScene::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

double KeyboardScene::keyPressedDuration(EventKeyboard::KeyCode code) {
    if(!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
        return 0;  // Not pressed, so no duration obviously

    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void KeyboardScene::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    Node::update(delta);

    Vec2 pos = sprite->getPosition();
    Vec2 shipPos3d = ship3d->getPosition();
    
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL)) {
        std::stringstream ss;
        ss << "Control key has been pressed for " <<
            keyPressedDuration(EventKeyboard::KeyCode::KEY_CTRL) << " ms";
        label->setString(ss.str().c_str());
    }
    else{
        label->setString("Press the CTRL Key");
    }

    if(isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)){
        sprite->setPosition(pos.x-=speed, pos.y);
        ship3d->setPosition(shipPos3d.x-=speed, shipPos3d.y);
    }
    
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)){
        sprite->setPosition(pos.x+=speed, pos.y);
        ship3d->setPosition(shipPos3d.x+=speed, shipPos3d.y);
    }
    
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)){
        sprite->setPosition(pos.x, pos.y+=speed);
        ship3d->setPosition(shipPos3d.x, shipPos3d.y+=speed);
    }
    
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)){
        sprite->setPosition(pos.x, pos.y-=speed);
        ship3d->setPosition(shipPos3d.x, shipPos3d.y-=speed);
    }
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode,
        std::chrono::high_resolution_clock::time_point> KeyboardScene::keys;

