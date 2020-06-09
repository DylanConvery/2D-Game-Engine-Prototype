#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "string"
#include "../Component.hpp"
#include "../AssetManager.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"

class SpriteComponent;

class PlayerInputComponent : public Component{
   public:
    PlayerInputComponent();
    PlayerInputComponent(std::string up_key, std::string down_key, std::string left_key, std::string right_key, std::string action_key);
    std::string getSDLStringCode(std::string key);

    void initialize() override;
    void update(float delta_time) override;
    void render() override;

    std::string _up_key;
    std::string _down_key;
    std::string _left_key;
    std::string _right_key;
    std::string _action_key;

    TransformComponent* _transform;
    SpriteComponent* _sprite;
};

#endif  // !PLAYERINPUTCOMPONENT_H