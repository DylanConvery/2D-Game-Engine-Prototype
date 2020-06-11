#include "PlayerInputComponent.hpp"

PlayerInputComponent::PlayerInputComponent(float speed, std::string up_key, std::string down_key, std::string left_key, std::string right_key, std::string action_key) : _speed(speed), _up_key(getSDLStringCode(up_key)), _down_key(getSDLStringCode(down_key)), _left_key(getSDLStringCode(left_key)), _right_key(getSDLStringCode(right_key)), _action_key(getSDLStringCode(action_key)) {}

//returns the SDL scancode in decimal or ascii representation
std::string PlayerInputComponent::getSDLStringCode(std::string key) const {
    if (key.compare("up") == 0) {
        return "1073741906";
    }
    if (key.compare("down") == 0) {
        return "1073741905";
    }
    if (key.compare("left") == 0) {
        return "1073741904";
    }
    if (key.compare("right") == 0) {
        return "1073741903";
    }
    if (key.compare("space") == 0) {
        return "32";
    }
    return std::to_string(static_cast<int>(key[0]));
}

void PlayerInputComponent::initialize() {
    _transform = _entity->getComponent<TransformComponent>();
    _sprite = _entity->getComponent<SpriteComponent>();
}

//translates our position
void PlayerInputComponent::update(float delta_time) {
    if (Engine::_event.type == SDL_KEYDOWN) {
        std::string key_code = std::to_string(Engine::_event.key.keysym.sym);

        if (key_code.compare(_up_key) == 0) {
            _transform->_velocity.y = -_speed;
            _transform->_velocity.x = 0;
            _sprite->play("up");
        }

        if (key_code.compare(_down_key) == 0) {
            _transform->_velocity.y = _speed;
            _transform->_velocity.x = 0;
            _sprite->play("down");
        }

        if (key_code.compare(_left_key) == 0) {
            _transform->_velocity.x = -_speed;
            _transform->_velocity.y = 0;
            _sprite->play("left");
        }

        if (key_code.compare(_right_key) == 0) {
            _transform->_velocity.x = _speed;
            _transform->_velocity.y = 0;
            _sprite->play("right");
        }

        if (key_code.compare(_action_key) == 0) {
        }
    }

    if (Engine::_event.type == SDL_KEYUP) {
        std::string key_code = std::to_string(Engine::_event.key.keysym.sym);

        if (key_code.compare(_up_key) == 0) {
            _transform->_velocity.y = 0;
        }
        if (key_code.compare(_down_key) == 0) {
            _transform->_velocity.y = 0;
        }
        if (key_code.compare(_left_key) == 0) {
            _transform->_velocity.x = 0;
        }
        if (key_code.compare(_right_key) == 0) {
            _transform->_velocity.x = 0;
        }
        if (key_code.compare(_action_key) == 0) {
        }
    }

	boundingBoxCheck();
}

//makes sure we don't go outside the bounds of the screen
void PlayerInputComponent::boundingBoxCheck(){
	if (_transform->_position.y <= 0) {
        _transform->_position.y = 0;
        if (_transform->_velocity.y < 0) {
            _transform->_velocity.y = 0;
        }
    }
    if (_transform->_position.y + _transform->_height >= WINDOW_HEIGHT) {
        _transform->_position.y = WINDOW_HEIGHT - _transform->_height;
        if (_transform->_velocity.y > 0) {
            _transform->_velocity.y = 0;
        }
    }
    if (_transform->_position.x <= 0) {
        _transform->_position.x = 0;
        if (_transform->_velocity.x < 0) {
            _transform->_velocity.x = 0;
        }
    }
    if (_transform->_position.x + _transform->_width >= WINDOW_WIDTH) {
        _transform->_position.x = WINDOW_WIDTH - _transform->_width;
        if (_transform->_velocity.x > 0) {
            _transform->_velocity.x = 0;
        }
    }
}

void PlayerInputComponent::render() {}