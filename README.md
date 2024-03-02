# Simple Tennis Game

This is a simple tennis game implemented using the SDL (Simple DirectMedia Layer) and SDL_ttf (SDL TrueType Fonts) libraries in C.

## Prerequisites

Before running the game, ensure you have SDL and SDL_ttf installed on your system. You can install them using a package manager or by downloading the libraries from their official websites.

- SDL: [https://libsdl.org/](https://libsdl.org/)
- SDL_ttf: [https://www.libsdl.org/projects/SDL_ttf/](https://www.libsdl.org/projects/SDL_ttf/)

## Compilation

Compile the game using the provided Makefile. Make sure to adjust the paths in the Makefile according to your SDL and SDL_ttf installations.

```bash
make
```

*NOTE:* Make sure you correct the path to the SDLs libraries in `Makefile`

## Running the Game

To run the compiled executable and start the simple tennis game, use the following command in your terminal:

```bash
./simple_tennis_game
```

## Game Controls

- **Left Arrow:** Move the racket to the left
- **Right Arrow:** Move the racket to the right
- **Close the window:** Exit the game

## Gameplay

- A ball bounces around the screen, and the player controls a racket to prevent the ball from hitting the bottom of the screen.
- The game ends when the ball reaches the bottom of the screen, and a "Game Over" message is displayed.

## Acknowledgments

- **SDL:** [https://libsdl.org/](https://libsdl.org/)
- **SDL_ttf:** [https://www.libsdl.org/projects/SDL_ttf/](https://www.libsdl.org/projects/SDL_ttf/)
