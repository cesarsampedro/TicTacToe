#pragma once
#include <SDL.h>

class xPlayer
{
public:
	xPlayer();
	~xPlayer();
	void Draw (SDL_Renderer *renderer, int WIN_H, int WIN_D);
	int  ChangePlayer();
	int  GetPlayer();
	void SetPlayer(int player);
	void ResetPlayer();
	void ChangePlayerTexture( int player);
	void GetPiezasTexture(SDL_Texture *texture);
	void SetPlayerTextures(SDL_Renderer *renderer);

private:
	SDL_Texture  *textureMiniplayer = NULL;
	SDL_Texture  *piezaTex = NULL;
	SDL_Texture	 *emptyTex = NULL;
	SDL_Texture	 *player1Tex = NULL;
	SDL_Texture  *player2Tex = NULL;

	SDL_Surface  *emptySurf = NULL;
	SDL_Surface  *player1Surf = NULL;
	SDL_Surface  *player2Surf = NULL;

	int			  Cr, Cg, Cb, Ca;
	SDL_Rect	  rectPlayer;
	int			  player = 1; // 1 = player 1, 2 = player 2;
};
