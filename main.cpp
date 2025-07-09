#include <SFML/Graphics.hpp>
#include "Game.hpp"

#include <iostream>

int main() {
    Game game("config.ini");
    game.run();
}