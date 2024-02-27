#include "../inc/minilibmx.h"


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *playerTexture = NULL;
SDL_Texture *enemyTexture = NULL;

Player player;
Enemy enemies[MAX_ENEMIES]; 
int numEnemies = 0;

void initGame() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Vampire Survivor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Ініціалізуємо гравця у центрі екрану
    initPlayer(&player, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    // Ініціалізуємо ворогів
    for (int i = 0; i < numEnemies; i++) {
        // Генеруємо випадкові позиції для ворогів
        int x = rand() % SCREEN_WIDTH;
        int y = rand() % SCREEN_HEIGHT;
        int type = rand() % NUM_ENEMY_TYPES + 1; 
        initEnemy(&enemies[i], x, y, type);
    }
}

void loadAssets() {
  // Додаємо текстури
    playerTexture = loadTexture("../resource/images/squere.png");
    enemyTexture = loadTexture("../resource/images/squere2.png");
}

void update() {
    // Оновлення руху гравця та ворогів
    movePlayer(&player, playerSpeedX, playerSpeedY);
    for (int i = 0; i < numEnemies; i++) {
        moveEnemy(&enemies[i], &player);
    }

    // Логіка взаємодії гравця та ворогів, наприклад, перевірка колізій
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Відображення гравця
    renderPlayer(renderer, &player, playerTexture);

    // Відображення ворогів
    for (int i = 0; i < numEnemies; i++) {
        renderEnemy(renderer, &enemies[i], enemyTexture);
    }

    SDL_RenderPresent(renderer);
}

void handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        playerSpeedY = -PLAYER_SPEED;
                        break;
                    case SDLK_DOWN:
                        playerSpeedY = PLAYER_SPEED;
                        break;
                    case SDLK_LEFT:
                        playerSpeedX = -PLAYER_SPEED;
                        break;
                    case SDLK_RIGHT:
                        playerSpeedX = PLAYER_SPEED;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN:
                        playerSpeedY = 0;
                        break;
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        playerSpeedX = 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}
