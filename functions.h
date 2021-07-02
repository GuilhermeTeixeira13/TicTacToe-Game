#include<stdio.h>
#define N 3

void inicializeGrid(char grid[N][N]);

void printGrid(char grid[N][N]);

int play(char grid[N][N], int x, int y, int player);

int threeInRow(char grid[N][N], int x, int y);

void printChar(int numberOfspaces, char charac);

void limpaInput();