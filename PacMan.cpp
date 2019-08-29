// PacMan.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <conio.h>
#include <time.h>

#include "Laberinto.h"

//Puntos iniciales
const int INIT_POINTS = 100;
//Puntos perdidos por paso
const int STEP_DROP_POINTS = 1;
//Puntos por comer miga
const int CRUMB_POINTS = 5;
//Puntos perdidos al ser alcanzado por fantasma
const int PHANTOM_DROP_POINTS = 50;
//Puntos por comer fantasma
const int PHANTOM_UP_POINTS = 40;


//PASOS NECESARIOS PARA LA VICTORIA
const int VICTORY_STEPS = 100;
//Duración en pasos del estado favorable "persecución"
const int CHASE_STEPS = 25;
//intervalo de pasos para spawn de gema
const int GEM_STEPS = 10;

/*
	VARIABLES DEL PLAYER
*/
const char playerSkin = 'O';
unsigned short int playerX, playerY;
int playerPoints;
/*
	VARIABLES DE LOS FANTASMAS
*/
const char phantomSkinCHASE = '"';
const char phantomSkinFLIGHT = '^';
unsigned short int phantomX[4], phantomY[4];


enum EDirectionMovement
{
	Up, Down, Left, Right
};

EDirectionMovement phantomLastMovement[4];

const int FILAS = 11, COLS = 21;

char laberinto[FILAS][COLS] = {
	{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
	{'X',' ',' ',' ',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
	{'X',' ','X','X','X','X',' ','X',' ','X','X','X','X',' ','X',' ',' ','X',' ',' ','X'},
	{'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ','X',' ',' ','X'},
	{'X','X','X','X','X','X',' ','X','X','X','X','X','X',' ','X',' ',' ',' ',' ',' ','X'},
	{'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ','X','X','X','X','X'},
	{'X',' ','X','X',' ','X','X','X','X','X','X','X',' ','X',' ',' ',' ',' ',' ',' ','X'},
	{'X',' ','X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ','X','X','X','X',' ','X'},
	{'X',' ','X','X','X','X','X','X','X','X','X','X',' ','X',' ',' ',' ',' ','X',' ','X'},
	{'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
	{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}
};


void PlayerInput();
void MuevePlayer(EDirectionMovement tipoMovimiento);
void MueveFantasmas();




void PlayerInput()
{
	char tecla = toupper(_getch());
	switch (tecla)
	{
		case 'W':
			MuevePlayer(EDirectionMovement::Up);
			break;
		case 'A':
			MuevePlayer(EDirectionMovement::Left);
			break;
		case 'D':
			MuevePlayer(EDirectionMovement::Right);
			break;
		case 'S':
			MuevePlayer(EDirectionMovement::Down);
			break;
	}
}

void MuevePlayer(EDirectionMovement tipoMovimiento)
{
	char celda;

	laberinto[playerY][playerX] = ' ';
	switch (tipoMovimiento)
	{
		case EDirectionMovement::Up:
			celda = GetMap(playerY - 1, playerX);
			if ((celda!= 'X') && (celda!='\0'))
			{
				playerY--;
			}
			break;
		case EDirectionMovement::Down:
			celda = GetMap(playerY + 1, playerX);
			if ((celda != 'X') && (celda != '\0'))
			{
				playerY++;
			}
			break;
		case EDirectionMovement::Left:
			celda = GetMap(playerY, playerX - 1);
			if ((celda != 'X') && (celda != '\0'))
			{
				playerX--;
			}
			break;
		case EDirectionMovement::Right:
			celda = GetMap(playerY, playerX + 1);
			if ((celda != 'X') && (celda != '\0'))
			{
				playerX++;
			}
			break;
	}

	laberinto[playerY][playerX] = playerSkin;
}



void MueveFantasmas()
{
	for (int i = 0; i < 4; i++)
	{
		laberinto[phantomY[i]][phantomX[i]] = ' ';
	}
	for (int i = 0; i < 4; i++)
	{
		EDirectionMovement lastMov = phantomLastMovement[i];
		int currentX = phantomX[i];
		int currentY = phantomY[i];

		switch (lastMov)
		{
		case EDirectionMovement::Up:
			//buscar en celda Left
			if (IsThereAHollow(currentY, currentX-1))
			{
				phantomX[i] = --currentX;
				phantomLastMovement[i] = EDirectionMovement::Left;
				break;
			}
		case EDirectionMovement::Right:
			//buscar en celda Up
			if (IsThereAHollow(currentY-1, currentX))
			{
				phantomY[i] = --currentY;
				phantomLastMovement[i] = EDirectionMovement::Up;
				break;
			}
			//Buscar en celda Right
			if (IsThereAHollow(currentY, currentX+1))
			{
				phantomX[i] = ++currentX;
				phantomLastMovement[i] = EDirectionMovement::Right;
				break;
			}
			//Buscar en celda Down
			if (IsThereAHollow(currentY + 1, currentX))
			{
				phantomY[i] = ++currentY;
				phantomLastMovement[i] = EDirectionMovement::Down;
				break;
			}
			//Buscar en celda Left
			if (IsThereAHollow(currentY, currentX-1))
			{
				phantomX[i] = --currentX;
				phantomLastMovement[i] = EDirectionMovement::Left;
				break;
			}
			break;
		case EDirectionMovement::Down:
			//buscar en celda Right
			if (IsThereAHollow(currentY, currentX + 1))
			{
				phantomX[i] = ++currentX;
				phantomLastMovement[i] = EDirectionMovement::Right;
				break;
			}
		case EDirectionMovement::Left:
			//Buscar en celda Down
			if (IsThereAHollow(currentY + 1, currentX))
			{
				phantomY[i] = ++currentY;
				phantomLastMovement[i] = EDirectionMovement::Down;
				break;
			}
			//buscar en celda Left
			if (IsThereAHollow(currentY, currentX - 1))
			{
				phantomX[i] = --currentX;
				phantomLastMovement[i] = EDirectionMovement::Left;
				break;
			}
			//Buscar en celda Up
			if (IsThereAHollow(currentY - 1, currentX))
			{
				phantomY[i] = --currentY;
				phantomLastMovement[i] = EDirectionMovement::Up;
				break;
			}
			//Buscar en celda Right
			if (IsThereAHollow(currentY, currentX + 1))
			{
				phantomX[i] = ++currentX;
				phantomLastMovement[i] = EDirectionMovement::Right;
				break;
			}
		}

		laberinto[phantomY[i]][phantomX[i]] = phantomSkinFLIGHT;
	}
}

int main()
{
	bool gameOver = false;

	std::cout << "Presione cualquier tecla para iniciar el juego";
	_getch();

	InitGame();

	while (!gameOver)
	{
		PlayerInput();
		MueveFantasmas();

		system("cls");
		DibujaMapa();
	}
}


