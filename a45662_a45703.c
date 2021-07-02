#include <stdio.h>
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
        {
            grid[line][column] = ' '; 
        }
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
            {
                printf(" %c |", grid[line][column]);
            }
            else
            {
                printf(" %c \n", grid[line][column]);
            }
        }
        for(square=0; square<N; square++)
        {
            if(line<(N-1))
            {
                printf("--- ");
            }
        }
        if(line<(N-1))
        {
            printf("\n");
        }
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
    {
        sym = 'O';
    }
    else
    {   
        sym = 'X';
    }

    /*   ↓ Returns conditions ↓   */
    if (x < 0 || x > 2 || y < 0 || y > 2)
    {
        return 1;
    }
    else if (grid[x][y] != ' ')
    {
        return 2;
    }
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
    {
        lineElements[column] = grid[x][column];
    }

    /*   ↓ Collects all elements of the move collumn ↓   */
    for(line=0; line<N; line++)
    {
        columnElements[line] = grid[line][y];
    }

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
                {
                    MainDiaElements[column] = grid[line][column];
                }
            }
        }
    }

    /*   ↓ Collects all elements of the secundary diagonal, if (x,y) belongs to it ↓   */
    line=0;
    int SDcoordinate = 0;
    for(column=(N-1);column>=0;column--)
    {
        if(line==x && column==y)
        {
            SDcoordinate = 1;
        }
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
    {
        return 1;
    }
    else if(lineElements[0] == lineElements[1] && lineElements[0] == lineElements[2])
    {
        return 1;
    }
    else if(MDcoordinate==1 && (MainDiaElements[0]==MainDiaElements[1] && MainDiaElements[0]==MainDiaElements[2]))
    {
        return 1;
    }
    else if(SDcoordinate==1 && (SecDiaElements[0]==SecDiaElements[1] && SecDiaElements[0]==SecDiaElements[2]))
    {
        return 1;
    }
    else if(grid[x][y] == ' ')
    {
        return -1;
    }
    else
    {
        return 0; 
    }
}

int main(void)
{
    char grid[N][N], sym;
    int x, y, n, counter, player, reciveCoordinate, coordinateLetter, draw, gameEnds=0, invalidPlay;

    /*   ↓ The ganme starts ↓   */
    for(n=0; n<65; n++)
    {
        printf("-");
    }
    printf(" \n");
    printf(" \n");
    for(n=0; n<17; n++)
    {
        printf(" ");
    }

    printf("Welcome to Tic Tac Toe game!!!\n");

    printf(" \n");
    for(n=0; n<65; n++)
    {
        printf("-");
    }
    printf("\n");

    printf("IMPORTANT STUFF:\n");
    printf(" . player 0: Uses the 'O' symbol.\n");
    printf(" . player 1: Uses the 'X' symbol.\n");
    printf(" . In the 3x3 grid, lines and columns starts in 0 and ends at 2.\n");

    for(n=0; n<65; n++)
    {
        printf("-");
    }
    printf("\n");

    printf("\t\t  |--  STARTING THE GAME --|\n");
    printf("\n");
    inicializeGrid(grid);
    printGrid(grid);
    counter=0;

    while(counter <=9 || gameEnds != 1)
    {
    /*   ↓ Players order ↓   */
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

        for(n=0; n<65; n++)
        {
            printf("-");
        }
        printf("\n");
        printf("\t\t       |--  PLAYER %d  --|\n", player);
        printf("\n");

        /*   ↓ Start of the move ↓   */
        do
        {
            /*   ↓ Asks for a valid input ↓   */
            if(invalidPlay == 1 || invalidPlay == 2 || coordinateLetter == 1)
            {
                printf("\n");
                printf("-> Error!! Write valid coordinates (0 to 2). <-\n");
                printf("-> Please verify if the call that you want is empty. <-\n");
                printf("\n");
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
            {
                coordinateLetter = 0;
            }
            printf(" --> Column number (0 a 2): ");

            /*   ↓ Check if the input is a letter ↓   */
            reciveCoordinate = scanf("%d", &y);

            if(reciveCoordinate != 1) 
            {
                getchar();
                coordinateLetter = 1;
            }
            else
            {
                coordinateLetter = 0;
            }

            invalidPlay = play(grid, x, y, player);

        }while(invalidPlay == 1 || invalidPlay == 2 || coordinateLetter == 1); 


        play(grid, x, y, player);
        printf("\n");
        printGrid(grid);

        /*   ↓ If the number of moves is above 3, checks if there is any 3 in a row ↓   */
        if(counter>3)
        {
            gameEnds = threeInRow(grid, x, y);
        }
            /*   ↓ If he finds a 3 in a row, the game is done ↓   */
        if(gameEnds==1)
        {
            break;
        }
        if(gameEnds==-1)
        {
            printf("Invalid coordinates!!\n");
        }
        if(counter == 8) 
        {
            /*   ↓ If the number of moves is 8, then no one wins - Draw ↓   */
            draw = 1; 
            break;
        }
        counter++;
    }

    /*   ↓ End of the game ↓   */
    printf("\n");

    for(n=0; n<65; n++)
    {
        printf("*");
    }

    printf("\n");

    for(n=0; n<21; n++)
    {
        printf(" ");
    }

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

    /*   ↓ The program ends ↓   */
    for(n=0; n<65; n++)
    {
        printf("*");
    }
    printf("\n");
    printf("\n");
    for(n=0; n<21; n++)
    {
        printf(" ");
    }
    printf("See you later!\n");
    printf("\n");
    return 0;
}
