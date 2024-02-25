#include "../inc/minilibmx.h"

int main(int argc, char* argv[]) {
    initGame();
    loadAssets();

    while (1) {
        handleInput();
        update();
        render();
    }

    return 0;
}
