#include <3ds.h>
#include <SDL.h>
#include <SDL_mixer.h>

// the 3ds has different screen width, but the same screen height.
const int TOP_SCREEN_WIDTH = 400;
const int BOTTOM_SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

bool isGamePaused;

int collisionCounter;

SDL_Rect player = {TOP_SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 32, 32};
SDL_Rect ball = {TOP_SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, 20};

const int PLAYER_SPEED = 2;

int ballVelocityX = 1;
int ballVelocityY = 1;

void quitGame()
{
}

void handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quitGame();
		}
	}
}

bool hasCollision(SDL_Rect &bounds, SDL_Rect &ball)
{
	return bounds.x < ball.x + ball.w && bounds.x + bounds.w > ball.x &&
		   bounds.y < ball.y + ball.h && bounds.y + bounds.h > ball.y;
}

void update()
{
	int keyHeld = hidKeysHeld();

	if (keyHeld & KEY_LEFT && player.x > 0)
	{
		player.x -= PLAYER_SPEED;
	}

	else if (keyHeld & KEY_RIGHT && player.x < TOP_SCREEN_WIDTH - player.w)
	{
		player.x += PLAYER_SPEED;
	}

	else if (keyHeld & KEY_UP && player.y > 0)
	{
		player.y -= PLAYER_SPEED;
	}

	else if (keyHeld & KEY_DOWN && player.y < SCREEN_HEIGHT - player.h)
	{
		player.y += PLAYER_SPEED;
	}

	// if (ball.x < 0 || ball.x > TOP_SCREEN_WIDTH - ball.w)
	// {
	// 	ballVelocityX *= -1;
	// }

	// else if (ball.y < 0 || ball.y > SCREEN_HEIGHT - ball.h)
	// {
	// 	ballVelocityY *= -1;
	// }

	// else if (hasCollision(player, ball))
	// {
	// 	ballVelocityX *= -1;
	// 	ballVelocityY *= -1;

	// 	collisionCounter++;
	// }

	// ball.x += ballVelocityX;
	// ball.y += ballVelocityY;
}

void renderTopScreen()
{
}

void renderBottomScreen()
{
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) > 0)
		return 0;

	int videoflag = SDL_SWSURFACE | SDL_HWPALETTE | SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_CONSOLEBOTTOM | SDL_TOPSCR;

	// Set up a window with 32-bit color depth
	SDL_Surface *screen = SDL_SetVideoMode(TOP_SCREEN_WIDTH, SCREEN_HEIGHT, 32, videoflag);
	if (screen == NULL)
	{
		fprintf(stderr, "Failed to set video mode: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	const Uint32 WHITE = SDL_MapRGB(screen->format, 255, 255, 255);
	const Uint32 RED = SDL_MapRGB(screen->format, 255, 0, 0);
	const Uint32 GREEN = SDL_MapRGB(screen->format, 0, 255, 0);
	const Uint32 BLUE = SDL_MapRGB(screen->format, 0, 0, 255);

	// Set the window title
	SDL_WM_SetCaption("SDL 1.2 Window", NULL);

	romfsInit();

	// Main loop
	while (aptMainLoop())
	{
		handleEvents();

		hidScanInput();

		int keyDown = hidKeysDown();

		if (keyDown & KEY_START)
		{
			isGamePaused = !isGamePaused;
		}

		if (!isGamePaused)
		{
			update();
		}

		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		// Draw the rectangle
		SDL_FillRect(screen, &player, WHITE);
		// SDL_FillRect(screen, &ball, WHITE);

		// Update the screen to display the rectangle
		SDL_Flip(screen);
	}
}
