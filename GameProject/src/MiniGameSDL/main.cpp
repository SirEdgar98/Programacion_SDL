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
#define FPS 60

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
	//Backgrond Scene 1
	SDL_Texture *bgTextureS1{ IMG_LoadTexture(renderer, "../../res/img/bg.jpg") }; //Init of a texture
	if (bgTextureS1 == nullptr)throw "Can't load the background image"; // Error load throw
	SDL_Rect bgRectS1{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	//Background Scene 2
	SDL_Texture *bgTextureS2{ IMG_LoadTexture(renderer, "../../res/img/bgCastle.jpg") }; //Init of a texture
	if (bgTextureS2 == nullptr)throw "Can't load the background image"; // Error load throw
	SDL_Rect bgRectS2{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

#pragma endregion

	// ---Animated Sprites---
#pragma region "Characters"
	//Animation 
	SDL_Texture *spriteTexture{ IMG_LoadTexture(renderer, "../../res/img/spCastle.png") };
	SDL_Rect spriteRect, spritePosition;
	int textWidth, textHeigth, framewidth, frameheigth;
	SDL_QueryTexture(spriteTexture, NULL, NULL, &textWidth, &textHeigth);
	framewidth = textWidth / 12;
	frameheigth = textHeigth / 8;
	spritePosition.x = spritePosition.y = 300;
	spriteRect.x = spriteRect.y = 0;
	spritePosition.h = spriteRect.h = frameheigth;
	spritePosition.w = spriteRect.w = framewidth;
	int frameTime = 0;

#pragma endregion
	// ---Text---
#pragma region "Text"
	//Open Font
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_TTF";
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",100) }; // Crea fuente
	if (font == nullptr)throw "Can't open the saiyan font";

	// Game name text
	SDL_Surface *tmpNameSurface{ TTF_RenderText_Blended(font,"Gold Rush",SDL_Color{ 255,255,0,1 }) }; // Crea una surface
	if (tmpNameSurface == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textNameTexture{ SDL_CreateTextureFromSurface(renderer,tmpNameSurface) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textNameRect{ 225,75,tmpNameSurface->w,tmpNameSurface->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpNameSurface);

	//Play Text
	SDL_Surface *tmpPlaySurface{ TTF_RenderText_Blended(font,"Play",SDL_Color{ 0,255,0,1 }) }; // Crea una surface
	if (tmpPlaySurface == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textPlayTexture{ SDL_CreateTextureFromSurface(renderer,tmpPlaySurface) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textPlayRect{ 325,200,tmpPlaySurface->w,tmpPlaySurface->h}; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpPlaySurface);
	// Play TExt Color 2
	SDL_Surface *tmpPlaySurface2{ TTF_RenderText_Blended(font,"Play",SDL_Color{ 153,255,153,1 }) }; // Crea una surface
	if (tmpPlaySurface2 == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textPlayTexture2{ SDL_CreateTextureFromSurface(renderer,tmpPlaySurface2) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textPlayRect2{ 325,200,tmpPlaySurface2->w,tmpPlaySurface2->h}; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpPlaySurface2);

	// Exit text
	SDL_Surface *tmpStopSurface{ TTF_RenderText_Blended(font,"Exit",SDL_Color{ 255,0,0,1 }) }; // Crea una surface
	if (tmpStopSurface == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textStopTexture{ SDL_CreateTextureFromSurface(renderer,tmpStopSurface) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textStopRect{325,350,tmpStopSurface->w,tmpStopSurface->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpStopSurface);
	// Exit text 2
	SDL_Surface *tmpStopSurface2{ TTF_RenderText_Blended(font,"Exit",SDL_Color{ 255,102,102,1 }) }; // Crea una surface
	if (tmpStopSurface2 == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textStopTexture2{ SDL_CreateTextureFromSurface(renderer,tmpStopSurface2) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textStopRect2{ 325,350,tmpStopSurface2->w,tmpStopSurface2->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpStopSurface2);

	TTF_CloseFont(font);

#pragma endregion
	// ---Audio---

	enum class GameState { PLAY, EXIT, MENU };
	// --- GAME LOOP ---
	SDL_Event event;
	//bool isRunning = true;
	GameState gamestate = GameState::MENU;
	bool hoverPlay = false; 
	bool hoverExit = false; 
	bool moveUpPJ1 = false; 
	bool moveDownPJ1 = false; 
	bool moveRightPJ1 = false; 
	bool moveLeftPJ1 = false; 
	while (gamestate != GameState::EXIT) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		gamestate = GameState::EXIT; break;
			case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) gamestate = GameState::EXIT;
								if (event.key.keysym.sym == SDLK_w) moveUpPJ1 = true;
								if (event.key.keysym.sym == SDLK_s) moveDownPJ1 = true;
								if (event.key.keysym.sym == SDLK_a) moveRightPJ1 = true;
								if (event.key.keysym.sym == SDLK_d) moveLeftPJ1 = true;
								else moveUpPJ1, moveDownPJ1, moveLeftPJ1, moveRightPJ1 = false; 
								break;
			case SDL_MOUSEMOTION:
				if (event.motion.x > textPlayRect.x && event.motion.x < (textPlayRect.x + textPlayRect.h)
					&& event.motion.y > textPlayRect.y && event.motion.y < (textPlayRect.y + textPlayRect.w / 2))
				{
					std::cout << "Hover play" << std::endl; 
					hoverPlay = true; 
				}
				else hoverPlay = false; 
				if (event.motion.x > textStopRect.x && event.motion.x < (textStopRect.x + textStopRect.h)
					&& event.motion.y > textStopRect.y && event.motion.y < (textStopRect.y + textStopRect.w / 2))
				{
					std::cout << "Hover exit" << std::endl;
					hoverExit = true; 
				}
				else hoverExit = false; 
				break;
			case SDLK_w:
					spritePosition.x++;
			case SDLK_s:
					spritePosition.x--; 
					std::cout << " S presed"<< std::endl;
			default:;
			}

			// PARA MANTENER ORDEN DE ESCENAS EN EL UPDATE
			// Cada una de ellas tendra su propio control sobre si misma
			//switch (gamestate)
		
		}
		//UPDATE
		
		if (hoverPlay && event.type == SDL_MOUSEBUTTONDOWN)
		{
			std::cout << "Change Scene" << std::endl;
			gamestate = GameState::PLAY;
		}
		if (hoverExit && event.type == SDL_MOUSEBUTTONDOWN)
		{
			std::cout << "Exit Game" << std::endl;
		}

		//--- SpriteAnimation---
		//MoveUP
		if (moveUpPJ1)
		{
			spritePosition.y -= 5;
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				spriteRect.x += framewidth;
				if (spriteRect.x >= framewidth * 3)
				{
					spriteRect.x = 0;
				}
			}
			moveUpPJ1 = false;
		}
		//MoveDown 
		if (moveDownPJ1)
		{
			spritePosition.y += 5;
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				spriteRect.x += framewidth;
				if (spriteRect.x >= framewidth * 3)
				{
					spriteRect.x = 0;
				}
			}
			moveDownPJ1 = false; 
		}

		//MoveRight
		if (moveRightPJ1)
		{
			spritePosition.x = spritePosition.x - 5; 
			moveRightPJ1 = false; 
		}

		//MoveLeft
		if (moveLeftPJ1)
		{
			spritePosition.x += 5;
			moveLeftPJ1 = false; 
		}
		
		

		// DRAW
		//backgroud
		SDL_RenderClear(renderer);
		if (gamestate == GameState::MENU)
		{
			SDL_RenderCopy(renderer, bgTextureS1, nullptr, &bgRectS1); //RenderBackgrounScene1
			SDL_RenderCopy(renderer, textNameTexture, nullptr, &textNameRect); //RenderGameNameText
			SDL_RenderCopy(renderer, textPlayTexture, nullptr, &textPlayRect); // RenderPlayText
			if (hoverPlay) SDL_RenderCopy(renderer, textPlayTexture2, nullptr, &textPlayRect2); // RenderPlayTextInHover
			SDL_RenderCopy(renderer, textStopTexture, nullptr, &textStopRect); //RenderStopText
			if (hoverExit) SDL_RenderCopy(renderer, textStopTexture2, nullptr, &textStopRect2); //RenderStopTextInHover

			SDL_RenderCopy(renderer, spriteTexture,&spriteRect,&spritePosition); 
		}
		else if (gamestate == GameState::PLAY)
		{
			SDL_RenderCopy(renderer, bgTextureS2, nullptr, &bgRectS2); //RenderBackgrounScene2
		}
		SDL_RenderPresent(renderer);

		

	}


	//DESTROY
	SDL_DestroyTexture(spriteTexture); 
	SDL_DestroyTexture(textNameTexture);
	SDL_DestroyTexture(textPlayTexture);
	SDL_DestroyTexture(textStopTexture);
	SDL_DestroyTexture(textPlayTexture2);
	SDL_DestroyTexture(textStopTexture2);
	SDL_DestroyTexture(bgTextureS1);
	SDL_DestroyTexture(bgTextureS2);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//QUIT
	IMG_Quit(); // Close Image
	TTF_Quit(); //Close Text	
	Mix_Quit(); //Close Music
	SDL_Quit();




	return 0;
}