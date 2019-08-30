#pragma once

void InitGame();
void DibujaMapa();
char GetMap(int Y, int X);
int FindHollow();
bool IsThereAHollow(int Y, int X);
bool SetMap(int Y, int X, char caracter);