#include "Laberinto.h"
#include <time.h>
#include <iostream>

extern int playerPoints;
extern const int INIT_POINTS;
extern const char playerSkin;
extern unsigned short int playerX, playerY;
extern unsigned short int *phantomX, *phantomY;
extern const int FILAS, COLS;
extern char **laberinto;


void InitGame()
{
	srand(time(NULL));

	playerPoints = INIT_POINTS;
	playerX = 1;
	playerY = FILAS - 2;
	laberinto[playerY][playerX] = playerSkin;

	for (int fantasma = 0; fantasma < 4; fantasma++)
	{
		int hueco = FindHollow();
		phantomX[fantasma] = hueco % COLS;
		phantomY[fantasma] = hueco / COLS;

		phantomLastMovement[fantasma] == EDirectionMovement::Up;
	}
}

int FindHollow()
{
	int startX = rand() % COLS;
	int startY = rand() % FILAS;

	int fila = startY;
	int columna = startX;
	do
	{
		if (GetMap(fila, columna) == ' ')
			return fila * COLS + columna;

		columna++;
		if (columna == COLS)
		{
			columna = 0;
			fila++;
			if (fila == FILAS)
				fila = 0;
		}
	} while ((columna != startX) || (fila != startY));

	return -1;
}

bool IsThereAHollow(int Y, int X)
{
	char celda = GetMap(Y, X);
	if ((celda != 'X') && (celda != '\0'))
		return true;

	return false;
}
void DibujaMapa()
{
	for (int filas = 0; filas < FILAS; filas++)
	{
		for (int columnas = 0; columnas < COLS; columnas++)
			std::cout << laberinto[filas][columnas];

		std::cout << "\n";
	}
}
char GetMap(int Y, int X)
{
	if ((Y >= FILAS) || (X >= COLS) || (Y < 0) || (X < 0))
		return '\0';

	return laberinto[Y][X];
}