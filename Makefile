CC = gcc
CFLAGS = -I/opt/homebrew/Cellar/sdl2/2.30.0/include/SDL2 -I/opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2
LDFLAGS = -L/opt/homebrew/Cellar/sdl2/2.30.0/lib -lSDL2 -L/opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib -lSDL2_ttf

simple_tennis_game: simple_tennis_game.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f simple_tennis_game 


