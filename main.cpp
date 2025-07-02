#include <SFML/Graphics.hpp>
#include "./Game.hpp"
#include "main.hpp"

int main() {
    Game game("config.ini");
    game.run();
}