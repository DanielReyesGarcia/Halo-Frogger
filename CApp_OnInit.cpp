//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit()
{

    int i;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK)<0)
    {
        return false;
    }

	//TTF Initialization
    TTF_Init( );	

    //Loads font with font size
    font = TTF_OpenFont("Halo.ttf", 20);
    color = {0,255,255};

    font1 = TTF_OpenFont("Halo Outline.ttf", 40);
    color1 = {255,0,0};

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        Running = false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        Running = false;
    }

    //Plays Music in Background while GAMEPLAY
    loadMedia();
    Mix_PlayMusic( gMusic, -1 );
    Mix_VolumeMusic(5);

    window = SDL_CreateWindow("Halo Frogger",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window)
        return false;
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        return false;

    srand(time(NULL));

    // Initialization of cars and logs
    for (i = 0; i < NUM_SPRITES; ++i) {
        strncpy_s(car[i].imagename,"banshee.bmp",255);
        car[i].loadPlayer(renderer);

        strncpy_s(log[i].imagename, "pelican.bmp", 255);
        log[i].loadPlayer(renderer);
        
            switch (i)
            {
            case 0:
                car[i].position.x = (rand() % 3 + 1) * 100;
                car[i].position.y = window_h - 200;
                car[i].velocity.x = (rand() % 3 + 1)*-1;
                car[i].velocity.y = 0;

                log[i].position.x = (rand() % 3 + 1) * 100;
                log[i].position.y = 200;
                log[i].velocity.x = (rand() % 3 + 1);
                log[i].velocity.y = 0;
                break;
            case 1:
                car[i].position.x = car[0].position.x + 500;
                car[i].position.y = car[0].position.y;
                car[i].velocity.x = car[0].velocity.x;
                car[i].velocity.y = 0;

                log[i].position.x = log[0].position.x + 600;
                log[i].position.y = log[0].position.y;
                log[i].velocity.x = log[0].velocity.x;
                log[i].velocity.y = 0;
                break;
            }       

            switch (i)
            {
            case 2:
                car[i].position.x = (rand() % 3 + 1) * 100;
                car[i].position.y = window_h - 300;
                car[i].velocity.x = rand() % 3 + 1;
                car[i].velocity.y = 0;
                

                log[i].position.x = (rand() % 3 + 1) * 100;
                log[i].position.y = 300;
                log[i].velocity.x = (rand() % 3 + 1) * -1;
                log[i].velocity.y = 0;
                break;
            case 3:
                car[i].position.x = car[2].position.x + 500;
                car[i].position.y = car[2].position.y;
                car[i].velocity.x = car[2].velocity.x;
                car[i].velocity.y = 0;

                log[i].position.x = log[2].position.x + 600;
                log[i].position.y = log[2].position.y;
                log[i].velocity.x = log[2].velocity.x;
                log[i].velocity.y = 0;
                break;
            }
               
            switch (i)
            {
            case 4:
                car[i].position.x = (rand() % 3 + 1) * 100;
                car[i].position.y = window_h - 400;
                car[i].velocity.x = (rand() % 3 + 1) * -1;
                car[i].velocity.y = 0;

                log[i].position.x = (rand() % 3 + 1) * 100;
                log[i].position.y = 400;
                log[i].velocity.x = (rand() % 3 + 1);
                log[i].velocity.y = 0;
                break;
            case 5:
                car[i].position.x = car[4].position.x + 500;
                car[i].position.y = car[4].position.y;
                car[i].velocity.x = car[4].velocity.x;
                car[i].velocity.y = 0;

                log[i].position.x = log[4].position.x + 600;
                log[i].position.y = log[4].position.y;
                log[i].velocity.x = log[4].velocity.x;
                log[i].velocity.y = 0;
                break;
            }
        
    }

    // Inizialization of SafeZones
    for (i = 0; i < NUM_SAFEZONES; i++)
    {
        strncpy_s(safeZone[i].imagename, "sabre.bmp", 255);
        safeZone[i].loadPlayer(renderer);
        safeZone[i].position.w = 100;
        safeZone[i].position.h = 100;
        safeZone[i].position.y = 100;
        safeZone[i].velocity.x = 0;
        safeZone[i].velocity.y = 0;
    }

    safeZone[0].position.x = 0;
    safeZone[1].position.x = 200;
    safeZone[2].position.x = 400;
    safeZone[3].position.x = 600;
    safeZone[4].position.x = 800;


    //Up sprite
    PlayerUp.set_sheet("Chief_SpriteSheet.bmp");
    if (PlayerUp.load_sheet(renderer) != 0)
    {
        printf("Bad load of runner animation file\n");
    }
    PlayerUp.config_sheet(4, 4, 149, 25, 41, 4, 1, 7);

    //Down sprite
    PlayerDown.set_sheet("Chief_SpriteSheet.bmp");
    if (PlayerDown.load_sheet(renderer) != 0)
    {
        printf("Bad load of runner animation file\n");
    }
    PlayerDown.config_sheet(4, 4, 5, 25, 41, 4, 1, 7);

    //Left sprite
    PlayerLeft.set_sheet("Chief_SpriteSheet.bmp");
    if (PlayerLeft.load_sheet(renderer) != 0)
    {
        printf("Bad load of runner animation file\n");
    }
    PlayerLeft.config_sheet(4, 6, 53, 20, 41, 4, 1, 12);

    //Right sprite
    PlayerRight.set_sheet("Chief_SpriteSheet.bmp");
    if (PlayerRight.load_sheet(renderer) != 0)
    {
        printf("Bad load of runner animation file\n");
    }
    PlayerRight.config_sheet(4, 6, 101, 20, 41, 4, 1, 12);

    frogger.h = 100;
    frogger.w = 100;
    frogger.x = window_w/2 - 50;
    frogger.y = window_h - 100;

    // Press 'p' to reset lives and score value to default.
    live = 0012;
    score = 0000;
    level = 0001;

    //Background IMAGE DECLARATION
    strncpy_s(background.imagename,"starfield.bmp",255);
    background.loadPlayer(renderer);
    background.set_scroll_loc(0,0,window_w,CONSOLE_START_Y);
    

    //Cruiser background declaration
    strncpy_s(cruiser.imagename, "cruiser.bmp", 255);
    cruiser.loadPlayer(renderer);
    cruiser.position.x = 0;
    cruiser.position.y = 500;
    cruiser.velocity.x = 0;
    cruiser.velocity.y = 0;

    return true;
}

//==============================================================================
