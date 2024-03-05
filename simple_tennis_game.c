#include <SDL.h>
#include <SDL_ttf.h>

typedef struct {
    int x;
    int y;
} Point;

Point move(Point *point, Point velocity) {
    point->x += velocity.x;
    point->y += velocity.y;

    return *point;
}

int main() 
{
    int screenWidth = 800;
    int screenHeight = 600;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow(
        "Simple tennis game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight,
        SDL_WINDOW_RESIZABLE
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("/Users/gneves/Downloads/ComicMono.ttf", 24);

    int quit = 0;
    SDL_Event event;

    // Initializing parameters
    int racketWidth = 100;
    int racketHeight = 30;
    int squareSize = 30;
    int racket_speed = 40;

    Point ball = {screenWidth/2, screenHeight/10};
    Point racket = {screenWidth/2 - racketWidth/2, screenHeight*4/5};
    Point ball_velocity = {5, 5};

    int gameOver = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (racket.x > 0) {
                            racket.x -= racket_speed;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (racket.x + racketWidth < screenWidth) {
                            racket.x += racket_speed;
                        }
                        break;
                }
            }
        }

        // Do not allow racket to go beyond screen
        if (racket.x < 0) {
            racket.x = 0;
        }
        if (racket.x + racketWidth > screenWidth) {
            racket.x = screenWidth - racketWidth;
        }

        // Renewing "ball" position
        ball = move(&ball, ball_velocity);

        // When the ball hits the corners of the screen
        if ((ball.x == screenWidth - squareSize) || (ball.x == 0)) {
            ball_velocity.x = -ball_velocity.x;
        }
        if ((ball.y ==  screenHeight - squareSize) || (ball.y == 0)) {
            ball_velocity.y = -ball_velocity.y;
        }

        // Checks if ball hit the racket
        if ((ball.x < racket.x + racketWidth) &&
            (ball.x + squareSize > racket.x) &&
            (ball.y + squareSize >= racket.y) &&
            (ball.y <= racket.y + racketHeight)) {
            ball_velocity.y = -ball_velocity.y;
        }
        else if (ball.y + squareSize >= screenHeight) {
            gameOver = 1;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        SDL_RenderClear(renderer);

        if (gameOver == 0) {
            // Rendering the "ball"
            SDL_Rect squareRect = { ball.x, ball.y, squareSize, squareSize};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &squareRect);

            // Rendering the "racket"
            SDL_Rect racketRect = { racket.x, racket.y, racketWidth, racketHeight};
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &racketRect);
        }
        else {
            SDL_Color textColor = {255, 0, 0, 255};
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game over!", textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            SDL_Rect textRect = {screenWidth/2 - 100, screenHeight/2, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }
            
        SDL_RenderPresent(renderer);

        SDL_Delay(10);  // Add a small delay to reduce CPU usage
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
