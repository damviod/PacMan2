#include <iostream>
#include <conio.h>

#include "Player.h"
#include "Laberinto.h"

/*
	VARIABLES DEL PLAYER
*/
extern const char playerSkin = 'O';
unsigned short int playerX, playerY;
int playerPoints;

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

	SetMap(playerY, playerX, ' ');

	switch (tipoMovimiento)
	{
	case EDirectionMovement::Up:
		celda = GetMap(playerY - 1, playerX);
		if ((celda != 'X') && (celda != '\0'))
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

	SetMap(playerY, playerX, playerSkin);
}