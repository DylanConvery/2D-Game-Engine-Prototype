#include <iostream>

#include "Constants.hpp"
#include "Engine.hpp"

int main(int argc, char* args[]) {
    Engine game;
    if (game.init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        while (game.loop()) {
            game.processInput();
            game.update();
            game.render();
        }
        game.destroy();
    }
    return 0;
}