#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>	//For Images
#include <SDL_ttf.h>	//For TextFonts
#include <SDL_mixer.h> // For Music & sounds (Audio)

//StarUML para diagramas de estado

//Game general information

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

int main(int, char*[]) {

	// --- INIT ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "No es pot inicialitzar SDL subsystems";
	


	// --- WINDOW ---
	SDL_Window *window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (window == nullptr) throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *renderer{ SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (renderer == nullptr) throw "No es pot inicialitzar SDL_Renderer";
# pragma region "Sprites"

	// --- SPRITES ---
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG }; // Init of an image
	if (!(IMG_Init(imgFlags)& imgFlags)) throw "Error : SDL_Image init"; // Error load throw 

	SDL_Texture *bgTexture{ IMG_LoadTexture(renderer, "../../res/img/bg.jpg") }; //Init of a texture
	if (bgTexture == nullptr)throw "Can't load the background image"; // Error load throw
	SDL_Rect bgRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_Texture*playerTexture{ IMG_LoadTexture(renderer, "../../res/img/kintoun.png") }; //Init of a texture
	if (playerTexture == nullptr) throw "Can't load playerTexture"; // Error load throw
	SDL_Rect playerRect{ 0,0,350,189 };

	SDL_Rect playerTarget{ 0,0,100,100 };
	// --- Animated Sprite ---
	SDL_Texture *spriteTexture{ IMG_LoadTexture(renderer, "../../res/img/sp01.png") };
	SDL_Rect spriteRect, spritePosition;
	int textWidth, textHeigth, framewidth, frameheigth;
	SDL_QueryTexture(spriteTexture, NULL, NULL, &textWidth, &textHeigth);
	framewidth = textWidth / 6;
	frameheigth = textHeigth / 1;
	spritePosition.x = spritePosition.y = 0;
	spriteRect.x = spriteRect.y = 0;
	spritePosition.h = spriteRect.h = frameheigth;
	spritePosition.w = spriteRect.w = framewidth;
	int frameTime = 0;
#pragma endregion 

#pragma region "Text and fonts "

	// --- TEXT ---
	if (TTF_Init() != 0) throw "No es pot inicialitzar SDL_TTF";
	TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",100) }; 
	TTF_Font *font2{ TTF_OpenFont("../../res/ttf/saiyan.ttf",100) }; // Crea fuente														// Crea fuente
	if (font == nullptr )throw "Can't open the saiyan font";
	// ---MY SDL GAME---
	SDL_Surface *tmpSurface{ TTF_RenderText_Blended(font,"My SDL Game",SDL_Color{255,150,0,1}) }; // Crea una surface
	if (tmpSurface == nullptr) TTF_CloseFont(font),throw "Can't create the surface";
	SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(renderer,tmpSurface) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textRect{ 150,50,tmpSurface->w,tmpSurface->h }; // El rectangulo de la textura con el w y h de la surface

	//---PLay music---
	SDL_Surface *tmpPlaySurface{ TTF_RenderText_Blended(font,"Play Music",SDL_Color{ 0,255,0,1 }) }; // Crea una surface
	if (tmpPlaySurface == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textPlayTexture{ SDL_CreateTextureFromSurface(renderer,tmpPlaySurface) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textPlayRect{ 200,150,tmpPlaySurface->w,tmpPlaySurface->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpPlaySurface);
	

	//---Stop music---
	SDL_Surface *tmpSSurface{ TTF_RenderText_Blended(font,"Stop Music",SDL_Color{ 255,0,0,1 }) }; // Crea una surface
	if (tmpSSurface == nullptr) TTF_CloseFont(font), throw "Can't create the surface";
	SDL_Texture *textStopTexture{ SDL_CreateTextureFromSurface(renderer,tmpSSurface) }; //Crea una textura apartir de la surface con el texto
	SDL_Rect textStopRect{ 200,250,tmpSSurface->w,tmpSSurface->h }; // El rectangulo de la textura con el w y h de la surface
	SDL_FreeSurface(tmpSSurface);

	TTF_CloseFont(font);

#pragma endregion 

#pragma region "Audio"
	// --- AUDIO ---
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw "Unable SDL_mixer";
	}
	Mix_Music *soundTrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
	if (!soundTrack)throw "Can't load soundTrack";
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(soundTrack, -1);
#pragma endregion 


	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:		isRunning = false; break;
			case SDL_KEYDOWN:	if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
			case SDL_MOUSEMOTION:
				playerTarget.x = event.motion.x - 50;
				playerTarget.y = event.motion.y - 50; 
				break;
			default:;
			}
		}

		// UPDATE
		//playerRect.x += (playerTarget.x - playerRect.x) / 10; // For smoth efect in the movement of the kintoun
		//playerRect.y += (playerTarget.y - playerRect.y) / 10; // Idem 

		frameTime++;
		if (FPS / frameTime <= 9)
		{
			frameTime = 0;
			spriteRect.x += framewidth;
			if (spriteRect.x >= textWidth)
			{
				spriteRect.x = 0;
			}
		}

		// DRAW
		//---Sprite---
		SDL_RenderCopy(renderer, spriteTexture, &spriteRect, &spritePosition);
		//Background
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
		//SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
		SDL_RenderCopy(renderer, textPlayTexture, nullptr, &textPlayRect);
		SDL_RenderCopy(renderer, textStopTexture, nullptr, &textStopRect);
		SDL_RenderCopy(renderer, spriteTexture, &spriteRect, &spritePosition);

		//Animated Sprite
		SDL_RenderPresent(renderer);

	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(textPlayTexture);
	SDL_DestroyTexture(textStopTexture);
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// --- QUIT ---
	IMG_Quit(); // Close Image
	TTF_Quit(); //Close Text	
	Mix_Quit(); //Close Music
	SDL_Quit();
	return 0;
}