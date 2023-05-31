#include "CApp.h"
//#include "CScroll_Player.h"
//#include "CPlayer.h"

CScroll_Player::CScroll_Player()
{
    //ctor
}

//==================================================================

CScroll_Player::~CScroll_Player()
{
    //dtor
}

//==================================================================

void CScroll_Player::display(SDL_Renderer *prenderer)
{
    SDL_RenderCopy(prenderer, texture, &src, &destscr);
}

//==================================================================

int CScroll_Player::loadPlayer(SDL_Renderer *prenderer)
{
    int retval;

    retval = CPlayer::loadPlayer(prenderer);
    destscr.x = 0;
    destscr.y = 0;
    destscr.h = window_h;
    destscr.w = window_w;
    velocity.x = 1;
    velocity.y = 0;
    return (retval);
}

//==================================================================

void CScroll_Player::move()
{
    src.x += velocity.x;
    src.y += velocity.y;

    if (src.x >= position.w - window_w)   // Assuming that the backgound image is greater than window width.
    {
        src.x += velocity.x;
        src.x  = 0 ;
        scroll += 1;
    }

    if (src.x < 0)
    {
        src.x += velocity.x;
        src.x = 0 ;
    }
}


//==================================================================