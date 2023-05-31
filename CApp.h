//==============================================================================
// Bird Dodger
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include <time.h>
#include <string>


#include <SDL.h>
#include <SDL_ttf.h>			//for fonts
#include <SDL_mixer.h>          //for sound and music


#include "CPlayer.h"
#include "CScroll_Player.h"
#include "CSpriteSheet.h"
#include "mywindow.h"


#define TICK_INTERVAL       10
#define NUM_SPRITES         6
#define NUM_SAFEZONES       5
#define MAX_SPEED           1

//====================================================================================================
class CApp
{
	private:
		bool            Running;
		TTF_Font * font;					// Pointer to font, stores the type and size of the font
		TTF_Font * font1;					// Pointer to font1, stores the type and size of the font

		SDL_Color color;					// Text Color
		SDL_Color color1;					// Text Color

		char message[100];					// Message String

		SDL_Surface * messageSurface;		// Pointer to the Surface where we display the message
		SDL_Texture * messageTexture;		// Pointer to the texture, converts the surface to texture
		SDL_Rect messageRect;				// Location
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

		//The music that will be played
		Mix_Music *gMusic = NULL;

		//Sound effects that will be used
		Mix_Chunk *gScratch = NULL;
		Mix_Chunk* gSave = NULL;
		Mix_Chunk* gGameOver = NULL;

		Uint32 next_time;
		SDL_Window *window;
		SDL_Renderer *renderer;

		CPlayer car[NUM_SPRITES];	// an array named bomb of class Cplayer to store the arrow sprites
		CPlayer log[NUM_SPRITES];
		CPlayer safeZone[NUM_SAFEZONES];	
		CPlayer cruiser; 

		//CPlayer console;
		CScroll_Player background;
		CSpriteSheet PlayerUp;
		CSpriteSheet PlayerDown;
		CSpriteSheet PlayerLeft;
		CSpriteSheet PlayerRight;
		SDL_Rect frogger;				// SDL_Rect for spritesheet

		int live, score, level;					// Variables to Store number of lives and score and level
		int direction = 0;
		bool restart = false;

	public:
		CApp();
		Uint32 time_left(void);
		int OnExecute();

	public:
		bool OnInit();

		void OnEvent(SDL_Event* Event);

		void OnLoop();

		void OnRender();

		void OnCleanup();

		// Helper functions

		bool loadMedia();

		bool check_collision(SDL_Rect A, SDL_Rect B);

		void displayGameStats(int x, int y, const char* formattedString, int number);
		void displayGameOver(int x, int y, const char* formattedString);

		int LoadSprite(const char *file, SDL_Texture **psprite, SDL_Rect *prect);
		void MoveSprites();
		void Check_Space_Collision();
		void ResetPosNVel(int level);
		void PlayerDeath();
		
};

//==============================================================================

#endif
