#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>
#include "Pieza.h"
#include "Player.h"

// variables
static const int NUMBER_PIEZES = 9;
static const int SPACE_BETWEEN_PIECES = 50;
static const int WIN_HEIGHT = 600;
static const int WIN_WIDTH  = 600;

int				 mouseX, mouseY;
bool			 allowChangePlayer = true;

//loading game elements.
xPlayer   Player;
xPieza    Piezas[NUMBER_PIEZES];
SDL_Rect *rects = new SDL_Rect[4];

void GenerateBoard();
void CheckForWinner();
void ResetBoardPiezes();

// --------------------------------------------
xPieza *GetPiezaUnderMouse(int mPosX, int mPosY)
{
	for (int i = 0; i < NUMBER_PIEZES; i++)
	{
		if (Piezas[i].ContainsPoint(mPosX, mPosY))
		{
			return &Piezas[i];
		}
	}
	return nullptr;
}

// Draw Grid
// --------------------------------------------
void DrawGrid(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderFillRect(renderer, &rects[0]);
	SDL_RenderFillRect(renderer, &rects[1]);
	SDL_RenderFillRect(renderer, &rects[2]);
	SDL_RenderFillRect(renderer, &rects[3]);
}


// DoRender
// --------------------------------------------
void DoRender(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	
	// Draw Grid
	DrawGrid(renderer);

	// Drawing piezes
	for (int i = 0; i < 9; i++)
	{
		Piezas[i].Draw(renderer);
	}

	Player.Draw(renderer, WIN_HEIGHT, WIN_HEIGHT);

	SDL_RenderPresent(renderer);
}


// SettingGamePlayElements
// --------------------------------------------
void SettingGameplayElements(SDL_Renderer *renderer)
{

	// Setting grid
	rects[0].h = 5; rects[0].w = 430; rects[0].x = 20; rects[0].y = 212;
	rects[1].h = 5; rects[1].w = 430; rects[1].x = 20; rects[1].y = 342;
	rects[2].h = 430; rects[2].w = 5; rects[2].x = 162; rects[2].y = 68;
	rects[3].h = 430; rects[3].w = 5; rects[3].x = 291; rects[3].y = 68;

	// Setting piezes
	for (int i = 0; i < 9; i++)
	{
		Piezas[i].SetPiezas(renderer, &Player);
	}

	// player
	Player.SetPlayerTextures(renderer);
}



// MAIN LOOP
// --------------------------------------------
int main(int, int, char*, int)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window	 *window     = SDL_CreateWindow("Tres en Raya", 310, 200, WIN_HEIGHT, WIN_WIDTH, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer   = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	SDL_Surface  *winsurface = SDL_GetWindowSurface(window);
	SDL_Event    e;
	bool running = true;

	// Generte board with piezes.
	GenerateBoard();

	// Setting Elements.
	SettingGameplayElements(renderer);


	while (running)
	{
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE )	running = !running;
			
			if (e.key.keysym.sym == SDLK_a)
			{
				//td::cout << "Presionada" << std::endl;
				//std::cout << Piezas[4].name << std::endl;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					xPieza *temp = GetPiezaUnderMouse(mouseX, mouseY);
					temp->ChangePiezaState(temp, &Player);

					allowChangePlayer = false;
					if (temp != nullptr)
						allowChangePlayer = temp->allowPlayerChange;

					CheckForWinner();

					if (allowChangePlayer)
					{
						Player.ChangePlayer();
					}
				}
			}

			//Getting Mouse	
			SDL_GetMouseState(&mouseX, &mouseY);// std::cout << mouseX <<  " " << mouseY  << std::endl;
		}

		//Renderer
		DoRender(renderer);
	}

	//Destroying window on exit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}



// GenerateBoard
// --------------------------------------------
void GenerateBoard()
{
	for (int i = 0; i < 3; i++)
	{
		Piezas[i].SetPos(((i * 130) + SPACE_BETWEEN_PIECES), 100);
		Piezas[i].name = "Pieza_" + std::to_string(i);
	}

	int a = 0;
	for (int i = 3; i < 6; i++)
	{
		Piezas[i].SetPos(((a * 130) + SPACE_BETWEEN_PIECES), 230);
		Piezas[i].name = "Pieza_" + std::to_string(i);
		a++;
	}

	int b = 0;
	for (int i = 6; i < 9; i++)
	{
		Piezas[i].SetPos(((b * 130) + SPACE_BETWEEN_PIECES), 360);
		Piezas[i].name = "Pieza_" + std::to_string(i);
		b++;
	}
}

// CHECK WINNER
// --------------------------------
void CheckForWinner()
{
	// Horizontal
	if (Piezas[0].GetPiezaState() == Player.GetPlayer()
		&& Piezas[1].GetPiezaState() == Player.GetPlayer()
		&& Piezas[2].GetPiezaState() == Player.GetPlayer())
	{
		std::cout << "winner player = " + std::to_string(Player.GetPlayer()) << std::endl;
		ResetBoardPiezes();
	}

	if (   Piezas[3].GetPiezaState() == Player.GetPlayer()
		&& Piezas[4].GetPiezaState() == Player.GetPlayer()
		&& Piezas[5].GetPiezaState() == Player.GetPlayer())
	{
		std::cout << "winner player = " + std::to_string(Player.GetPlayer()) << std::endl;
		ResetBoardPiezes();
	}

	if (   Piezas[6].GetPiezaState() == Player.GetPlayer()
		&& Piezas[7].GetPiezaState() == Player.GetPlayer()
		&& Piezas[8].GetPiezaState() == Player.GetPlayer())
	{
		std::cout << "winner player = " + std::to_string(Player.GetPlayer()) << std::endl;
		ResetBoardPiezes();
	}

	// Vertical
	if (   Piezas[0].GetPiezaState() == Player.GetPlayer()
		&& Piezas[3].GetPiezaState() == Player.GetPlayer()
		&& Piezas[6].GetPiezaState() == Player.GetPlayer())
	{
		std::cout << "winner player = " + std::to_string(Player.GetPlayer()) << std::endl;
		ResetBoardPiezes();
	}

	if (   Piezas[1].GetPiezaState() == Player.GetPlayer()
		&& Piezas[4].GetPiezaState() == Player.GetPlayer()
		&& Piezas[7].GetPiezaState() == Player.GetPlayer())
	{
		std::cout << "winner player = " + std::to_string(Player.GetPlayer()) << std::endl;
		ResetBoardPiezes();
	}

	if (   Piezas[2].GetPiezaState() == Player.GetPlayer()
		&& Piezas[5].GetPiezaState() == Player.GetPlayer()
		&& Piezas[8].GetPiezaState() == Player.GetPlayer())
	{
		std::cout << "winner player = " + std::to_string(Player.GetPlayer()) << std::endl;
		ResetBoardPiezes();
	}

	// Diagonal
	if (   Piezas[0].GetPiezaState() == Player.GetPlayer()
		&& Piezas[4].GetPiezaState() == Player.GetPlayer()
		&& Piezas[8].GetPiezaState() == Player.GetPlayer())
	{
		std::cout << "winner player = " + std::to_string(Player.GetPlayer()) << std::endl;
		ResetBoardPiezes();
	}

	if (   Piezas[2].GetPiezaState() == Player.GetPlayer()
		&& Piezas[4].GetPiezaState() == Player.GetPlayer()
		&& Piezas[6].GetPiezaState() == Player.GetPlayer())
	{
		std::cout << "winner player = " + std::to_string(Player.GetPlayer()) << std::endl;
		ResetBoardPiezes();
	}

	// check if the board is full of pieces and no winner
	int c = 0;
	for (int i = 0; i < NUMBER_PIEZES; i++)
	{
		if (Piezas[i].GetPiezaState() != 0) { c++; }
	}
	if (c == NUMBER_PIEZES) {
		std::cout << "Empates" << std::endl;
		ResetBoardPiezes();
	}
}

// Reset board piezes
// --------------------------------
void ResetBoardPiezes()
{
	for (int i = 0; i < NUMBER_PIEZES; i++)
	{
		Piezas[i].ResetPiece();
	}

	//std::cout << "Reset Board Completed" << std::endl;
	Player.ResetPlayer(); // starting with player 1 (default);
}



