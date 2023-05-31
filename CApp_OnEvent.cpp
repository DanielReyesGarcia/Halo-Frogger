//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {


    switch(Event->type)
    {
		case SDL_QUIT:

            Running = false;
            break;

   //     case SDL_MOUSEMOTION:

			//runnerspot.x = Event->motion.x ;						//Player.x location = mouse current x location 
   //         runnerspot.y = Event->motion.y ;						//Player.y location = mouse current y location 

			//// Checks if the runnerspot sprite is going out of window (right side)
   //         if (runnerspot.x >= (window_w - runnerspot.w))
   //         {
			//	runnerspot.x = (window_w - runnerspot.w);			// stops the sprite at the border
			//}

			//// Checks if the runnerspot spritesheet is going out of window (left side)
   //         if (runnerspot.x < 0)
   //         {
			//	runnerspot.x = 0;									// stops the sprite at the border
			//}

			//// Checks if the runnerspot spritesheet is going out of window (Top)
   //         if (runnerspot.y < 0)
   //         {
			//	runnerspot.y = 0;									// stops the sprite at the border
   //         }

			//// Checks if the runnerspot sprite is going out of window (Bottom)
			//if (runnerspot.y >= (window_h - runnerspot.h))
   //         {
			//	runnerspot.y = (window_h - runnerspot.h);			// stops the sprite at the border
   //         }

   //         break;

        case SDL_KEYDOWN:

            switch(Event->key.keysym.sym)
            {
				// UP Arrow key
                case SDLK_UP:
					
                    if (live > 0 && score < 5)
                    {
                        frogger.y -= 100;								// change the y location by -100
                        if (frogger.y < 0)
                        {
                            frogger.y = 0;
                        }

                        PlayerUp.play(renderer, &frogger, true);
                        direction = 0;                                // Change to up sprite
                    }
					
                    break;

				// DOWN Arrow key
				case SDLK_DOWN:

                    if (live > 0 && score < 5)
                    {
                        frogger.y += 100;								// change the y location by +100
                        if (frogger.y >= (window_h - frogger.h))
                        {
                            frogger.y = (window_h - frogger.h);
                        }

                        PlayerDown.play(renderer, &frogger, true);
                        direction = 1;                                // Change to down sprite  
                    }
                    
					break;

				// LEFT Arrow key
				case SDLK_LEFT:
					
                    if (live > 0 && score < 5)
                    {
                        frogger.x -= 100;								// change the x location by -100
                        if (frogger.x < 0)
                        {
                            frogger.x = 0;
                        }

                        PlayerLeft.play(renderer, &frogger, true);
                        direction = 2;                                  // Change to left sprite
                    }   
					
                    break;

				// RIGHT Arrow key
                case SDLK_RIGHT:

                    if (live > 0 && score < 5)
                    {
                        frogger.x += 100;								// change the x location by +10
                        if (frogger.x >= (window_w - frogger.w))
                        {
                            frogger.x = (window_w - frogger.w);
                        }

                        PlayerRight.play(renderer, &frogger, true);
                        direction = 3;                                  // Change to right sprite
                    }
                    
                    break;

				// When a is pressed speed of arrows falling down and scrolling background is increased by 1
                case SDLK_a:
					/*background.velocity.x+=1;
                    for(int i = 0; i < NUM_SPRITES ; ++i)
					{
                           car[i].velocity.y += 1;
                    }*/
                    break;

				// When z is pressed speed of arrows falling down and scrolling background is decreased by 1
				case SDLK_z:
					/*if (background.velocity.x > 0)
					{
						background.velocity.x--;	
					}

					for(int i = 0 ; i < NUM_SPRITES ; ++i)
					{
                            car[i].velocity.y -= 1;
                    }*/
                             break;
				// 'p' To play the Game again
                case SDLK_p:
					SDL_DestroyRenderer( renderer );
                    SDL_DestroyWindow( window );
                    window = NULL;
                    renderer = NULL;
                    restart = true;
                    SDL_QUIT;

                    OnInit();
                    break;
				
				// 'Esc' to exit 
                case SDLK_ESCAPE:

                    Running=false;
                    break;
                    }
    }
}

//==============================================================================
