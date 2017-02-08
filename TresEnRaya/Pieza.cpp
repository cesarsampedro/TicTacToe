#include "Pieza.h"
#include <iostream>
#include <SDL_image.h>

xColor::xColor(Uint8 rr, Uint8 gg, Uint8 bb, Uint8 aa)
{
	r = rr;  g = gg; b = bb; a = aa;
}


int xPieza::GetPiezaState()
{
	return state;
}



// SetPos
// --------------------------------------------
void xPieza::SetPos(int x, int y)
{
	posX = x;
	PosY = y;
}


// SetPIezas
// --------------------------------------------
void xPieza::SetPiezas(SDL_Renderer *renderer, xPlayer *player)
{
	// set surfaces
	emptySurf = IMG_Load("Assets/Art/empty.bmp");
	player1Surf = IMG_Load("Assets/Art/player_01.bmp");
	player2Surf = IMG_Load("Assets/Art/player_02.bmp");

	//set textures
	emptyTex   = SDL_CreateTextureFromSurface(renderer, emptySurf);
	player1Tex = SDL_CreateTextureFromSurface(renderer, player1Surf);
	player2Tex = SDL_CreateTextureFromSurface(renderer, player2Surf);

	piezaTex   = emptyTex;

	// freeding surface.
	SDL_FreeSurface(emptySurf);		//una vez tenemos la texuta de render ya no necesitamos la surface y esto la quita de memoria.
	SDL_FreeSurface(player1Surf); 
	SDL_FreeSurface(player2Surf);

}


// DRAW
// --------------------------------------------
void xPieza::Draw(SDL_Renderer *renderer)
{
	rect.x = posX;
	rect.y = PosY;
	rect.h = height;
	rect.w = width;

	// Assign texture to rectangle.
	SDL_RenderCopy(renderer, piezaTex, NULL, &rect);
}


// Check if the pieze CONTAINS a point XY
// --------------------------------------------
bool xPieza::ContainsPoint(int x, int y)
{
	if (x > rect.x && x < (rect.x + rect.w) && y > rect.y && y < (rect.y + rect.h))
	{
		return true;
	}
	else
	{
		return false;
	}

}


// ChangePieceTexture()
void  xPieza::ChangePieceTexture(int player)
{
	switch (player)
	{
	case 0:
		piezaTex = emptyTex;
		break;
	case 1:
		piezaTex = player1Tex;
		break;
	case 2:
		piezaTex = player2Tex;
		break;
	}
}

// ChangePiezaSTATE
// --------------------------------------------
void  xPieza::ChangePiezaState(xPieza *pieza, xPlayer *player)
{
	// estaba intentando cambiar el estado de cada pieza
	if (pieza)
	{
		if (pieza->state == 0)
		{
			switch (player->GetPlayer())
			{
			case 0:
				pieza->ChangePieceTexture(0);
				break;
			case 1:
				pieza->ChangePieceTexture(1);
				pieza->state = 1;
				allowPlayerChange = true;
				break;
			case 2:
				pieza->ChangePieceTexture(2);
				pieza->state = 2;
				allowPlayerChange = true;
				break;

			}
		}
		else
		{
			allowPlayerChange = false;
			std::cout << "the pieze ins't empty" << std::endl;
		}
	}

}


// ResetPiece
// --------------------------------------------
void xPieza::ResetPiece()
{
	state      = 0;
	ChangePieceTexture(0);
}


