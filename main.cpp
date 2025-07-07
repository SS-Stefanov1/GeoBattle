#include <SFML/Graphics.hpp>
#include "Game.hpp"

#include <iostream>

int main() {
    Game game("config.ini");
    std::cout << game.m_playerConfig.V << std::endl;
    game.run();
}