#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>	//For Images
#include <SDL_ttf.h>	//For TextFonts
#include <SDL_mixer.h> // For Music & sounds (Audio)

#include <time.h> //para los deltaTime
#include<iostream>

// GENERAL STUFF
#pragma region "Staff"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#pragma endregion

int main(int, char*[])
{
	// --- INIT ---

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";

	// ---Sprites---
#pragma region "Sprites"

	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG }; // Init of image
	if (!(IMG_Init(imgFlags)& imgFlags)) throw "Error : SDL_Image init"; // Error load throw 

	//PLAY SCENE IMAGES
	//Backgrond
	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../GameProject/res/img/bg.jpg") }; //Init of a texture
	if (bgTexture == nullptr)throw "Can't load the background image"; // Error load throw
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


#pragma endregion

	// ---Animated Sprites---
	// ---Text---
	// ---Audio---

	enum class GameState { PLAY, EXIT, MENU };
	// --- GAME LOOP ---
	SDL_Event event;
	//bool isRunning = true;
	GameState gamestate = GameState::MENU;
	while (gamestate != GameState::EXIT) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		gamestate = GameState::EXIT; break;
			case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) gamestate = GameState::EXIT; break;
			case SDL_MOUSEMOTION:
				break;
			default:;
			}

			// PARA MANTENER ORDEN DE ESCENAS EN EL UPDATE
			// Cada una de ellas tendra su propio control sobre si misma
			//switch (gamestate)
			
		}
		// DRAW
		//backgroud
		
		SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);

		SDL_RenderClear(renderer);

	}


	//DESTROY
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//QUIT
	IMG_Quit(); // Close Image
	TTF_Quit(); //Close Text	
	Mix_Quit(); //Close Music
	SDL_Quit();




	return 0;
}