//==============================================================================
#include "CApp.h"


using namespace std;

void
CApp::MoveSprites()
{
    int i;
    /* Draw a gray background */
    /* Move the sprite, bounce at the wall, and draw */
    for (i = 0; i < NUM_SPRITES; ++i)
    {
        car[i].move();
        log[i].move();

        if (i == 2 || i == 3)
        {
            car[i].display(renderer, flip);
            log[i].display(renderer, flip);
        }
        else
        {
            car[i].display(renderer);
            log[i].display(renderer);
        }

        // DEATH BY CAR
        if (check_collision(car[i].position, frogger)== true)
        {
            PlayerDeath();													
        }

        // STEP ON LOG
        if (check_collision(log[i].position, frogger) == true)
        {
            if (log[i].position.x + 200<= frogger.x)
            {
                frogger.x = log[i].position.x + 200 + 2 + level;
            }
            else if (log[i].position.x + 100 <= frogger.x && log[i].position.x + 200> frogger.x)
            {
                frogger.x = log[i].position.x + 100 + 2 + level;
            }
            else if (log[i].position.x + 100 > frogger.x)
            {
                frogger.x = log[i].position.x + 2 + level;
            }
        }

        printf(" LIVES: %d   LEVEL: %d   SCORE: %d   SCROLLS: %d  \r", live, car[0].velocity.y, score, background.scroll);
    }

    

    for (int i = 0; i < NUM_SAFEZONES; i++)
    {
        safeZone[i].move();
        safeZone[i].display(renderer);

        // REACHED END GOAL
        if (check_collision(safeZone[i].position, frogger) == true)
        {
            loadMedia();
            Mix_PlayChannel(-1, gSave, 0);

            frogger.x = window_w / 2 - 50;
            frogger.y = window_h - 100;
            safeZone[i].velocity.y = -1;
            live += 2;                                                  // gain 2 lives
            score++;                                                    // increse spartans saved
            level++;                                                    // increase difficulty level
            if (level > 5)
            {
                level--;
            }
            ResetPosNVel(level);
        }
    }


}

// CHECK COLLISION WITH SPACE AREA
void CApp::Check_Space_Collision()
{
    if (frogger.y <= 400 && frogger.y > 300)
    {       
            if (!check_collision(log[4].position, frogger) && !check_collision(log[5].position, frogger))
            {
                PlayerDeath();
            }            
    }  

    if (frogger.y <= 300 && frogger.y > 200)
    {
        if (!check_collision(log[2].position, frogger) && !check_collision(log[3].position, frogger))
        {
            PlayerDeath();
        }
    }

    if (frogger.y <= 200)
    {
        if (!check_collision(log[0].position, frogger) && !check_collision(log[1].position, frogger))
        {
            PlayerDeath();
        }
    }
}

// RESET POSITIONS AND VELOCITIES
void CApp::ResetPosNVel(int level)
{
    for (int i = 0; i < NUM_SPRITES; i++)
    {
        if (i % 2 == 0)
        {
            car[i].position.x = (rand() % 3 + 1) * 100;
            log[i].position.x = (rand() % 3 + 1) * 100;

            if (car[i].velocity.x < 0)
            {
                car[i].velocity.x = (rand() % 3 + level) * -1;
            }
            else
            {
                car[i].velocity.x = (rand() % 3 + level);
            }

            if (log[i].velocity.x < 0)
            {
                log[i].velocity.x = (rand() % 3 + level) * -1;
            }
            else
            {
                log[i].velocity.x = (rand() % 3 + level);
            }
        }

        if (i % 2 == 1)
        {
            car[i].position.x = car[i - 1].position.x + 500;
            log[i].position.x = log[i - 1].position.x + 600;

            car[i].velocity.x = car[i - 1].velocity.x;
            log[i].velocity.x = log[i - 1].velocity.x;
        }
    }
}

// PLAY EVENTS FOR PLAYER DEATH
void CApp::PlayerDeath()
{
    loadMedia();
    Mix_PlayChannel(-1, gScratch, 0);
    Mix_VolumeChunk(gScratch, 10);

    frogger.x = window_w / 2 - 50;
    frogger.y = window_h - 100;
    live--;
}


//==============================================================================
void CApp::OnLoop()
{
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);

    static Uint32 count = 0;
    restart = false;
    
    // CREATE COUNTER FOR TIME
    if (live > 0 && score < 5)
    {
        count++;
    }

    // DISPLAY SPRITES AND MOVEMENT
    background.move();
    background.display(renderer);

    cruiser.display(renderer, flip);

    MoveSprites();
    Check_Space_Collision();

    // CHANGE PLAYER SPRITE DIRECTION
    if (direction == 0)
    {
        PlayerUp.play(renderer, &frogger, false);
    }

    if (direction == 1)
    {
        PlayerDown.play(renderer, &frogger, false);
    }

    if (direction == 2)
    {
        PlayerLeft.play(renderer, &frogger, false);
    }

    if (direction == 3)
    {
        PlayerRight.play(renderer, &frogger, false);
    }
    
    // DISPLAY INTERFACE
    displayGameStats(25, 25, "Spartans Saved   : %3d", score);
    displayGameStats(window_w - 390, 25, "Time  : %d", count / 100);
    displayGameStats(25, 70, "Lives    : %3d", live);
    displayGameStats(window_w - 390, 70, "Level   : %d", level);

    // GAME OVER EVENTS
    if (live <= 0 || score == 5)

    {
        background.velocity.x = 0;

        frogger.y = window_h + 500;
        for (int i = 0; i < NUM_SPRITES; ++i)
        {
            car[i].velocity.y = 0;					
            car[i].position.y = -500;				
                                                    
            log[i].velocity.y = 0;
            log[i].position.y = -500;


        }

        for (int i = 0; i < NUM_SAFEZONES; ++i)
        {
            safeZone[i].velocity.y = 0;
            safeZone[i].position.y = -500;
        }

        // GAME OVER SOUND EFFECT
        // not working properly it loops infinietly
        /*loadMedia();
        Mix_PlayChannel(-1, gScratch, 0);
        Mix_VolumeChunk(gScratch, 5);*/

        displayGameOver(250, 250, "GAME OVER");
        if (live <= 0)
        {
            displayGameOver(275, 300, "YOU LOSE");
        }
        if (score == 5)
        {
            displayGameOver(325, 300, "YOU WIN");
        }
        
        displayGameStats(300, 350, "Press 'P' to Play Again", NULL);
        displayGameStats(300, 400, "Press 'ESC' to EXIT", NULL);
        Mix_FreeMusic(gMusic);
        gMusic = NULL;
    }
            
}


//==============================================================================
