// PacMan.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <conio.h>
#include <time.h>

#include "Laberinto.h"
#include "DirectionMovement.h"
#include "Player.h"
#include "Fantasmas.h"

//Puntos iniciales
extern const int INIT_POINTS = 100;
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


