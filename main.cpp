#include <SFML/Graphics.hpp>
#include "./Game.hpp"

int main() {
    Game game("config.ini");
    game.run();
}