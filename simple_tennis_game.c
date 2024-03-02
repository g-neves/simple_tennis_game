#include <SDL.h>
#include <SDL_ttf.h>

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
    int squareX = screenWidth/2;
    int squareY = screenHeight/10;
    int squareSize = 30;
    int squareVX = 5;
    int squareVY = 5;
    int racketWidth = 100;
    int racketHeight = 30;
    int racketX = screenWidth/2 - racketWidth/2;
    int racketY = screenHeight*4/5;
    int racketSpeed = 40;
    
    int gameOver = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (racketX > 0) {
                            racketX -= racketSpeed;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (racketX + racketWidth < screenWidth) {
                            racketX += racketSpeed;
                        }
                        break;
                }
            }
        }

        // Do not allow racket to go beyond screen
        if (racketX < 0) {
            racketX = 0;
        }
        if (racketX + racketWidth > screenWidth) {
            racketX = screenWidth - racketWidth;
        }

        // Renewing "ball" position
        squareX = squareX + squareVX; 
        squareY = squareY + squareVY; 

        // When the ball hits the corners of the screen
        if ((squareX == screenWidth - squareSize) || (squareX == 0)) {
            squareVX = -squareVX;
        }
        if ((squareY ==  screenHeight - squareSize) || (squareY == 0)) {
            squareVY = -squareVY;
        }

        // Checks if ball hit the racket
        if ((squareX < racketX + racketWidth) &&
            (squareX + squareSize > racketX) &&
            (squareY + squareSize >= racketY) &&
            (squareY <= racketY + racketHeight)) {
            squareVY = -squareVY;
        }
        else if (squareY + squareSize >= screenHeight) {
            gameOver = 1;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        SDL_RenderClear(renderer);

        if (gameOver == 0) {
            // Rendering the "ball"
            SDL_Rect squareRect = { squareX, squareY, squareSize, squareSize};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &squareRect);

            // Rendering the "racket"
            SDL_Rect racketRect = { racketX, racketY, racketWidth, racketHeight};
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
