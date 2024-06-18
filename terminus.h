#ifndef TERMINUS_H
#define TERMINUS_H

#include <windows.h>

HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);

// Função para determinar as coordenadas que será imprimido no terminal.
void gotoxy(int x, int y) {
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para randomizar a cor dentro de um padrão específico.
int randomColor() {
    int color = rand() % 7 + 9;
    // Assegurando que o valor da cor seja entre 9 e 15.
    if (color > 15 || color < 9) { return randomColor(); }
    return color;
}

#endif