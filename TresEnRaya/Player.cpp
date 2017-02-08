#include "Player.h"
#include <iostream>
#include <SDL_image.h>


xPlayer::xPlayer()
{
	 Cr = 0;
	 Cg = 0;
	 Cb = 128;
	 Ca = 255;
}
xPlayer::~xPlayer()
{

}


void xPlayer::Draw(SDL_Renderer *renderer, int WIN_H, int WIN_D)
{
	rectPlayer.w = 50;
	rectPlayer.h = 50;
	rectPlayer.x = (int)(WIN_D - (rectPlayer.w * 2)) ;
	rectPlayer.y = (int)(WIN_H / 2) - rectPlayer.h / 2 ;


	switch (player)
	{
		case 1:
			textureMiniplayer = player1Tex;
			break;

		case 2:
			textureMiniplayer = player2Tex;
			break;
	}
	//SDL_RenderDrawRect(renderer, &rectPlayer);
	SDL_RenderCopy(renderer, textureMiniplayer, NULL, &rectPlayer);
}


// SWAPS between PLAYERS
//------------------------------
int xPlayer::ChangePlayer()
{
	if (player == 1)
	{
		player = 2;
		ChangePlayerTexture(player);
		return player;
	}
	else if (player == 2)
	{
		player = 1;
		ChangePlayerTexture(player);
		return player;
	}
	else
	{
		return -1; // null
	}
	
}

int xPlayer::GetPlayer()
{
	return player;
}

void xPlayer::SetPlayer(int playerN)
{
	player = playerN;
}

void xPlayer::ResetPlayer()
{
	player = 2;
}


// CHANGE PLAYER TEXTURE 
//------------------------------
void xPlayer::ChangePlayerTexture( int player)
{
	if (player == 1)
	{

	}
	if (player == 2)
	{

	}
}


void xPlayer::SetPlayerTextures(SDL_Renderer *renderer)
{
	// set surfaces
	emptySurf = IMG_Load("Assets/Art/empty.bmp");
	player1Surf = IMG_Load("Assets/Art/player_01.bmp");
	player2Surf = IMG_Load("Assets/Art/player_02.bmp");

	//set textures
	emptyTex = SDL_CreateTextureFromSurface(renderer, emptySurf);
	player1Tex = SDL_CreateTextureFromSurface(renderer, player1Surf);
	player2Tex = SDL_CreateTextureFromSurface(renderer, player2Surf);

	piezaTex = emptyTex;

	// freeding surface.
	SDL_FreeSurface(emptySurf);		//una vez tenemos la texuta de render ya no necesitamos la surface y esto la quita de memoria.
	SDL_FreeSurface(player1Surf);
	SDL_FreeSurface(player2Surf);
}