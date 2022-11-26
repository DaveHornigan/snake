#include "main.h"

Game game = Game();

using namespace std;

int main() {
    while (!game.gameOver) {
        game.update();
    }

    return 0;
}
