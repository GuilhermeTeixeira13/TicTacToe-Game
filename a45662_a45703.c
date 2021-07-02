#include <stdio.h>
#define N 3

void inicializaGrelha(char grid[N][N])
{
    /*
    * Goal: Inicialize empy grid, with the size of NxN
    * 
    * grid: Name of the grid that we want to inicialize
    */
    int linha, coluna;

    for(linha=0; linha<N; linha++)
    {
        for(coluna=0; coluna<N; coluna++)
        {
            grid[linha][coluna] = ' '; 
        }
    }
}


void imprimeGrelha(char grid[N][N])
{
    /*
    * Goal: Print Nxn grid, with the 'symbols' in the respective coordinates
    * 
    * grid: Name of the grid that we want to print
    */
    int linha, coluna, bloco;

    for(linha=0; linha<N; linha++)
    {
        for(coluna=0; coluna<N; coluna++)
        {
            if(coluna<N-1)
            {
                printf(" %c |", grid[linha][coluna]);
            }
            else
            {
                printf(" %c \n", grid[linha][coluna]);
            }
        }
        for(bloco=0; bloco<N; bloco++)
        {
            if(linha<(N-1))
            {
                printf("--- ");
            }
        }
        if(linha<(N-1))
        {
            printf("\n");
        }
    }
}


int jogada(char grid[N][N], int x, int y, int jogador)
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
    if(jogador == 0)
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


int tresEmLinha(char grid[N][N], int x, int y)
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

    int linha, coluna;
    char elementosLinha[N], elementosColuna[N], elementosDiaPri[N] = {' ', ' ', ' '}, elementosDiaSec[N] = {' ', ' ', ' '};


    /*   ↓ Collects all elements of the move line ↓   */
    for(coluna=0; coluna<N; coluna++)
    {
        elementosLinha[coluna] = grid[x][coluna];
    }

    /*   ↓ Collects all elements of the move collumn ↓   */
    for(linha=0; linha<N; linha++)
    {
        elementosColuna[linha] = grid[linha][y];
    }

    /*   ↓ Collects all elements of the main diagonal, if (x,y) belongs to it ↓   */
    int coordenada_na_dp = 0;
    if(x==y)
    {
        coordenada_na_dp = 1;
        for(linha=0; linha<N; linha++)
        {
            for(coluna=0; coluna<N; coluna++)
            {
                if(linha==coluna)
                {
                    elementosDiaPri[coluna] = grid[linha][coluna];
                }
            }
        }
    }

    /*   ↓ Collects all elements of the secundary diagonal, if (x,y) belongs to it ↓   */
    linha=0;
    int coordenada_na_ds = 0;
    for(coluna=(N-1);coluna>=0;coluna--)
    {
        if(linha==x && coluna==y)
        {
            coordenada_na_ds = 1;
        }
        linha++;
    }
    linha = 0;
    if(coordenada_na_ds == 1)
    {
        for(coluna=(N-1);coluna>=0;coluna--)
        {
            elementosDiaSec[coluna] = grid[linha][coluna];
            linha++;
        }
    }

    /*   ↓ Returns conditions ↓   */
    if(elementosColuna[0] == elementosColuna[1] && elementosColuna[0] == elementosColuna[2])
    {
        return 1;
    }
    else if(elementosLinha[0] == elementosLinha[1] && elementosLinha[0] == elementosLinha[2])
    {
        return 1;
    }
    else if(coordenada_na_dp==1 && (elementosDiaPri[0]==elementosDiaPri[1] && elementosDiaPri[0]==elementosDiaPri[2]))
    {
        return 1;
    }
    else if(coordenada_na_ds==1 && (elementosDiaSec[0]==elementosDiaSec[1] && elementosDiaSec[0]==elementosDiaSec[2]))
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
    char grelha[N][N], sym;
    int x, y, n, contador, jogador, recebeCoordenada, coordenadaLetra, empate, jogoTermina=0, jogadaInvalida;

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

    printf("Seja bem-vindo ao Jogo do Galo!!!\n");

    printf(" \n");
    for(n=0; n<65; n++)
    {
        printf("-");
    }
    printf("\n");

    printf("Aspetos IMPORTANTES:\n");
    printf(" . Jogador 0: Usa o símbolo 'O'.\n");
    printf(" . Jogador 1: Usa o símbolo 'X'.\n");
    printf(" . Na grelha 3x3, as linhas e colunas estão numeradas de 0 a 2.\n");

    for(n=0; n<65; n++)
    {
        printf("-");
    }
    printf("\n");

    printf("\t\t  |--  INICIALIZANDO JOGO  --|\n");
    printf("\n");
    inicializaGrelha(grelha);
    imprimeGrelha(grelha);
    contador=0;

    while(contador <=9 || jogoTermina != 1)
    {
    /*   ↓ Players order ↓   */
        if (contador % 2 == 0)
        {   
            sym = 'O';
            jogador = 0;
        }
        else if (contador % 2 != 0)
        {
            sym = 'X';
            jogador = 1;
        }

        for(n=0; n<65; n++)
        {
            printf("-");
        }
        printf("\n");
        printf("\t\t       |--  JOGADOR %d  --|\n", jogador);
        printf("\n");

        /*   ↓ Start of the move ↓   */
        do
        {
            /*   ↓ Asks for a valid input ↓   */
            if(jogadaInvalida == 1 || jogadaInvalida == 2 || coordenadaLetra == 1)
            {
                printf("\n");
                printf("-> Erro!! Digite coordenadas (0 a 2) válidas. <-\n");
                printf("-> Por favor, certifique-se que a célula pretendida está vazia. <-\n");
                printf("\n");
            }
            printf("COORDENADAS PARA COLOCAR O '%c':\n", sym);
            printf(" --> Número da linha (0 a 2): ");

            /*   ↓ Check if the input is a letter ↓   */
            recebeCoordenada = scanf("%d", &x);

            if(recebeCoordenada != 1) 
            {
                getchar();
                coordenadaLetra = 1;
            }
            else
            {
                coordenadaLetra = 0;
            }
            printf(" --> Número da coluna (0 a 2): ");

            /*   ↓ Check if the input is a letter ↓   */
            recebeCoordenada = scanf("%d", &y);

            if(recebeCoordenada != 1) 
            {
                getchar();
                coordenadaLetra = 1;
            }
            else
            {
                coordenadaLetra = 0;
            }

            jogadaInvalida = jogada(grelha, x, y, jogador);

        }while(jogadaInvalida == 1 || jogadaInvalida == 2 || coordenadaLetra == 1); 


        jogada(grelha, x, y, jogador);
        printf("\n");
        imprimeGrelha(grelha);

        /*   ↓ If the number of moves is above 3, checks if there is any 3 in a row ↓   */
        if(contador>3)
        {
            jogoTermina = tresEmLinha(grelha, x, y);
        }
            /*   ↓ If he finds a 3 in a row, the game is done ↓   */
        if(jogoTermina==1)
        {
            break;
        }
        if(jogoTermina==-1)
        {
            printf("Coordenadas inválidas!!\n");
        }
        if(contador == 8) 
        {
            /*   ↓ If the number of moves is 8, then no one wins - Draw ↓   */
            empate = 1; 
            break;
        }
        contador++;
    }

    /*   ↓ End of the game ↓   */
    printf("\n");

    for(n=0; n<65; n++)
    {
        printf("*");
    }

    printf("\n");

    for(n=0; n<19; n++)
    {
        printf(" ");
    }

    /*   ↓ Mensagem em caso de empate ↓   */
    if(empate == 1) 
    {
        printf("**  JOGO EMPATADO  **\n");
        printf("     Nenhum dos jogadores colocou 3 símbolos em linha: \n");
    }
    /*   ↓ Mensagem caso alguém vença ↓   */
    else 
    {
        printf("** JOGADOR %d VENCEU !! **\n", jogador);
        printf("\n");
        printf("   O JOGADOR %d colocou 3 símbolos em linha e ganhou o jogo: \n", jogador);
    }
    printf("\n");
    imprimeGrelha(grelha);
    printf("\n");

    /*   ↓ Fim do programa ↓   */
    for(n=0; n<65; n++)
        {
            printf("*");
        }
        printf("\n");
    printf("\n");
    for(n=0; n<19; n++)
    {
        printf(" ");
    }
    printf("Programa terminado!\n");
    printf("\n");
    return 0;
}
