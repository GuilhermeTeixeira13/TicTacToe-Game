#include <stdio.h>
#include <string.h>
#include"functions.h"
#define N 3

int main(void)
{
    char grid[N][N], sym, userPlayAgain[257], *pos;
    int x, y, n, counter, player, reciveCoordinate, coordinateLetter, draw, gameEnds=0, invalidPlay, changeFirstPlayer=0, repiteQuestion, playAgain;

    /*   ↓ The ganme starts ↓   */
    welcomeMSG();

    do
    {
        importantStuffMSG();
        startingGameMSG();

        inicializeGrid(grid);
        printGrid(grid);
        counter=1;

        while(counter <=9 || gameEnds != 1)
        {
        /*   ↓ Players order ↓   */
            if(changeFirstPlayer == 1)
            {
                if (counter % 2 == 0)
                {   
                    sym = 'X';
                    player = 1;
                }
                else if (counter % 2 != 0)
                {
                    sym = 'O';
                    player = 0;
                }
            }
            else
            {
                if (counter % 2 == 0)
                {   
                    sym = 'O';
                    player = 0;
                }
                else if (counter % 2 != 0)
                {
                    sym = 'X';
                    player = 1;
                }
            }

            printChar(64, '-');
            printf("\n");
            printf("\t\t       |--  PLAYER %d  --|\n", player);
            printf("\n");

            /*   ↓ Start of the move ↓   */
            do
            {
                /*   ↓ Asks for a valid input ↓   */
                if(invalidPlay == 1 || invalidPlay == 2 || coordinateLetter == 1)
                {
                    invalidCoordinatesMSG();
                }
                printf("COORDINATES TO PUT THE '%c':\n", sym);
                printf(" --> Line number (0 a 2): ");

                /*   ↓ Check if the input is a letter ↓   */
                reciveCoordinate = scanf("%d", &x);

                if(reciveCoordinate != 1) 
                {
                    getchar();
                    coordinateLetter = 1;
                }
                else
                    coordinateLetter = 0;
                printf(" --> Column number (0 a 2): ");

                /*   ↓ Check if the input is a letter ↓   */
                reciveCoordinate = scanf("%d", &y);

                if(reciveCoordinate != 1) 
                {
                    getchar();
                    coordinateLetter = 1;
                }
                else
                    coordinateLetter = 0;

                invalidPlay = play(grid, x, y, player);

            }while(invalidPlay == 1 || invalidPlay == 2 || coordinateLetter == 1); 


            play(grid, x, y, player);
            printf("\n");
            printGrid(grid);

            /*   ↓ If the number of moves is above 4, checks if there is any 3 in a row ↓   */
            if(counter>4)
                gameEnds = threeInRow(grid, x, y);

            /*   ↓ If he finds a 3 in a row, the game is done ↓   */
            if(gameEnds == 1)
                break;
            if(gameEnds == -1)
                printf("Invalid coordinates!!\n");
            if(counter == 9) 
            {
                /*   ↓ If the number of moves is 8, then no one wins - Draw ↓   */
                draw = 1; 
                break;
            }
            counter++;
        }

        /*   ↓ End of the game ↓   */
        printf("\n");
        printChar(64, '*');
        printf("\n");
        printChar(20, ' ');

        /*   ↓ Draw message ↓   */
        if(draw == 1) 
        {
            printf("**  GAME DRAW  **\n");
            printf("     None of the players placed 3 symbols in a row. \n");
        }

        /*   ↓ Winning message ↓   */
        else 
        {
            printf("** PLAYER %d WON !! **\n", player);
            printf("\n");
            printf("   PLAYER %d lined 3 symbols and won the game! \n", player);
        }
        
        printf("\n");
        printGrid(grid);
        printf("\n");
        limpaInput();

        do
        {
            printf("Do you want to play again? [YES/NO] --> ");
            fgets(userPlayAgain, 257, stdin);
            pos = strchr(userPlayAgain, '\n');
            *pos = '\0';

            if((strcmp(userPlayAgain, "YES") == 0) || (strcmp(userPlayAgain, "yes") == 0))
            {
                playAgain = 1;
                repiteQuestion = 0;
            }
            else if((strcmp(userPlayAgain, "NO") == 0) || (strcmp(userPlayAgain, "no") == 0))
            {
                playAgain = 0;
                repiteQuestion = 0;
            }
            else 
                repiteQuestion = 1;
        }while(repiteQuestion == 1);

        if(playAgain == 1)
        {
            printChar(64, '*');
            printf("\n\n");
            changeFirstPlayer = !changeFirstPlayer;
            gameEnds = 0;
        }

    }while(playAgain == 1);

    /*   ↓ The program ends ↓   */
    endingMSG();
    return 0;
}