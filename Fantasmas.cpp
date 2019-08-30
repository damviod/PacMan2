#include "Fantasmas.h"
#include "Laberinto.h"
#include "DirectionMovement.h"

/*
	VARIABLES DE LOS FANTASMAS
*/
const char phantomSkinCHASE = '"';
const char phantomSkinFLIGHT = '^';
unsigned short int phantomX[4], phantomY[4];

EDirectionMovement phantomLastMovement[4];

void MueveFantasmas()
{
	for (int i = 0; i < 4; i++)
	{
		SetMap(phantomY[i], phantomX[i], ' ');
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
			if (IsThereAHollow(currentY, currentX - 1))
			{
				phantomX[i] = --currentX;
				phantomLastMovement[i] = EDirectionMovement::Left;
				break;
			}
		case EDirectionMovement::Right:
			//buscar en celda Up
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
			//Buscar en celda Down
			if (IsThereAHollow(currentY + 1, currentX))
			{
				phantomY[i] = ++currentY;
				phantomLastMovement[i] = EDirectionMovement::Down;
				break;
			}
			//Buscar en celda Left
			if (IsThereAHollow(currentY, currentX - 1))
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

		SetMap(phantomY[i], phantomX[i], phantomSkinFLIGHT);
	}
}