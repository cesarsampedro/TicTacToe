#pragma once

#include <SDL.h>
#include <string>
#include "Player.h"

using namespace std;

class xColor
{
public:
	xColor(Uint8 rr, Uint8 gg, Uint8 bb, Uint8 aa);

	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
	Uint8 a = 255;
};

//-----------
class xPieza
{
public:
	void			SetPos(int x, int y);
	void			Draw(SDL_Renderer *renderer);
	void			ChangePiezaState(xPieza *pieza, xPlayer *player);
	int				GetPiezaState();

	void			SetPiezas(SDL_Renderer *renderer, xPlayer *player);
	void			ResetPiece();
	void			ChangePieceTexture(int player);


	string			name = "none";
	bool			ContainsPoint(int x, int y);
	bool			allowPlayerChange = true;

private:

	int posX   = 0;
	int PosY   = 0;
	int width  = 100;
	int height = 100;

	SDL_Rect    rect;

	SDL_Texture  *piezaTex    = NULL;
	SDL_Texture	 *emptyTex    = NULL;
	SDL_Texture	   *player1Tex  = NULL;
	SDL_Texture    *player2Tex  = NULL;

	SDL_Surface  *emptySurf   = NULL;
	SDL_Surface  *player1Surf = NULL;
	SDL_Surface  *player2Surf = NULL;

	
	int state  = 0; // 0 = empty, 1 = x, 2 = 0;
	xColor		FichaColor{ 122,122,122,255 };
	
};

