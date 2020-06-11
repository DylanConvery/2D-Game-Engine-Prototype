#ifndef PLAYERINPUTCOMPONENT_H
#define PLAYERINPUTCOMPONENT_H

#include "../AssetManager.hpp"
#include "../Component.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include "string"

class SpriteComponent;

class PlayerInputComponent : public Component {
   public:
    PlayerInputComponent();
    PlayerInputComponent(float speed, std::string up_key, std::string down_key, std::string left_key, std::string right_key, std::string action_key);
    std::string getSDLStringCode(std::string key) const;

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
    float _speed;

   private:
    void boundingBoxCheck();
};

#endif  // !PLAYERINPUTCOMPONENT_H