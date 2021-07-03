#include<stdio.h>
#include"functions.h"
#define N 3

void inicializeGrid(char grid[N][N])
{
    /*
    * Goal: Inicialize empy grid, with the size of NxN
    * 
    * grid: Name of the grid that we want to inicialize
    */
    int line, column;

    for(line=0; line<N; line++)
    {
        for(column=0; column<N; column++)
            grid[line][column] = ' '; 
    }
}


void printGrid(char grid[N][N])
{
    /*
    * Goal: Print Nxn grid, with the 'symbols' in the respective coordinates
    * 
    * grid: Name of the grid that we want to print
    */
    int line, column, square;

    for(line=0; line<N; line++)
    {
        for(column=0; column<N; column++)
        {
            if(column<N-1)
                printf(" %c |", grid[line][column]);
            else
                printf(" %c \n", grid[line][column]);
        }
        for(square=0; square<N; square++)
        {
            if(line<(N-1))
                printf("--- ");
        }
        if(line<(N-1))
            printf("\n");
    }
}


int play(char grid[N][N], int x, int y, int player)
{
    /*
    * Goal: Put the player symbol in the coordinates that he wants of the grid NxN
    * 
    * grid: Name of the grid that we want to insert the move
    * x: line number (0, 1 or 2)
    * y: column number (0, 1 ou 2)
    * player: number of the player that is making the move
    * 
    * returns:
    *       0: If the coordinates are empty
    *       1: If the coordinates doesnt exists
    *       2: If the coorsinates are taken
    */
    char sym;

        /*   ↓  Giving symbols to the players ↓   */
    if(player == 0)
        sym = 'O';
    else 
        sym = 'X';

    /*   ↓ Returns conditions ↓   */
    if (x < 0 || x > 2 || y < 0 || y > 2)
        return 1;
    else if (grid[x][y] != ' ')
        return 2;
    else
    {
        grid[x][y] = sym;

        return 0;
    }
}


int threeInRow(char grid[N][N], int x, int y)
{
    /*
    * Goal: Check if there are three symbols in a row in the NxN grid, in relation to the desired position
    * 
    * grid: Name of the grid that we want to insert the move
    * x: line number (0, 1 or 2)
    * y: column number (0, 1 ou 2)
    * 
    * returns:
    *       -1: If the coordinates (x,y) are empty
    *       0: If there isnt a 3 in a row and the coordinates are valid
    *       1: If there is a 3 in a row
    */

    int line, column;
    char lineElements[N], columnElements[N], MainDiaElements[N] = {' ', ' ', ' '}, SecDiaElements[N] = {' ', ' ', ' '};


    /*   ↓ Collects all elements of the move line ↓   */
    for(column=0; column<N; column++)
        lineElements[column] = grid[x][column];

    /*   ↓ Collects all elements of the move collumn ↓   */
    for(line=0; line<N; line++)
        columnElements[line] = grid[line][y];

    /*   ↓ Collects all elements of the main diagonal, if (x,y) belongs to it ↓   */
    int MDcoordinate = 0;
    if(x==y)
    {
        MDcoordinate = 1;
        for(line=0; line<N; line++)
        {
            for(column=0; column<N; column++)
            {
                if(line==column)
                    MainDiaElements[column] = grid[line][column];
            }
        }
    }

    /*   ↓ Collects all elements of the secundary diagonal, if (x,y) belongs to it ↓   */
    line=0;
    int SDcoordinate = 0;
    for(column=(N-1);column>=0;column--)
    {
        if(line==x && column==y)
            SDcoordinate = 1;
        line++;
    }
    line = 0;
    if(SDcoordinate == 1)
    {
        for(column=(N-1);column>=0;column--)
        {
            SecDiaElements[column] = grid[line][column];
            line++;
        }
    }

    /*   ↓ Returns conditions ↓   */
    if(columnElements[0] == columnElements[1] && columnElements[0] == columnElements[2])
        return 1;
    else if(lineElements[0] == lineElements[1] && lineElements[0] == lineElements[2])
        return 1;
    else if(MDcoordinate==1 && (MainDiaElements[0]==MainDiaElements[1] && MainDiaElements[0]==MainDiaElements[2]))
        return 1;
    else if(SDcoordinate==1 && (SecDiaElements[0]==SecDiaElements[1] && SecDiaElements[0]==SecDiaElements[2]))
        return 1;
    else if(grid[x][y] == ' ')
        return -1;
    else
        return 0; 
}

void printChar(int numberOfChars, char charac)
{
    /*
    * Goal: Print a certain character, as many times as the user wants (numberOfChara)
    *
    * numberOfChars: Number of chars that the user wants to be printed
    * charac: The char that will be printed numberOfChars times
    * 
    */
    int n;

    for(n=1; n<numberOfChars; n++)
        printf("%c", charac);
}

/* Simply clean the input */
void limpaInput()
{
    while (getchar() != '\n');
}