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
    * Objetivo: Imprimir grelha de tamanho N, com os 'símbolos' nas respetivas coordenadas
    * 
    * grid: nome da grelha que pretendemos imprimir 
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
    * Objetivo: Colocar o símbolo do jogador, nas coordenadas por ele pretendidas, na grelha de tamanho N
    * 
    * grid: nome da grelha em que pretendemos inserir a jogada
    * x: número da linha (0, 1 ou 2)
    * y: número da coluna (0, 1 ou 2)
    * jogador: número do jogador que está a a fazer a jogada
    * 
    * returns:
    *       0: Se a jogada for fazível, ou seja, se as coordenadas estiverem vazias 
    *       1: Se as coordenadas pretendidas estiverem fora de alcance (não existirem)
    *       2: Se as coordenadas pretendidas já estiverem ocupadas
    */
    char sym;

        /*   ↓ Atribui o simbolo ao jogador ↓   */
    if(jogador == 0)
    {
        sym = 'O';
    }
    else
    {   
        sym = 'X';
    }

    /*   ↓ Criam-se condições para os returns ↓   */
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
    * Objetivo: Verificar se existem três símbolos em linha, na grelha de tamanho N, relativamente à posição pretendida
    * 
    * grid: nome da grelha em que pretendemos inserir a jogada
    * x: número da linha (0, 1 ou 2)
    * y: número da coluna (0, 1 ou 2)
    * 
    * returns:
    *       -1: Se as coordenadas digitadas estiverem vazias 
    *       0: Caso não haja três em linha e as coordenadas sejam válidas 
    *       1: Se houver um três em linha
    */

    int linha, coluna;
    char elementosLinha[N], elementosColuna[N], elementosDiaPri[N] = {' ', ' ', ' '}, elementosDiaSec[N] = {' ', ' ', ' '};


    /*   ↓ Coleta todos os elementos da linha da jogada ↓   */
    for(coluna=0; coluna<N; coluna++)
    {
        elementosLinha[coluna] = grid[x][coluna];
    }

    /*   ↓ Coleta todos os elementos da coluna da jogada ↓   */
    for(linha=0; linha<N; linha++)
    {
        elementosColuna[linha] = grid[linha][y];
    }

    /*   ↓ Coleta todos os elementos da diagonal principal, caso (x,y) lhe pertença ↓   */
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
    /*   ↓ Coleta todos os elementos da diagonal secundária, caso (x,y) lhe pertença ↓   */
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

    /*   ↓ Criam-se as condições para obter os return values ↓   */
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

    /*   ↓ Começo do jogo ↓   */
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
    /*   ↓ Ordem dos jogadores ↓   */
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

        /*   ↓ Começo da jogada ↓   */
        do
        {
            /*   ↓ Caso o input seja inválido, volta a pedir as cordenadas ↓   */
            if(jogadaInvalida == 1 || jogadaInvalida == 2 || coordenadaLetra == 1)
            {
                printf("\n");
                printf("-> Erro!! Digite coordenadas (0 a 2) válidas. <-\n");
                printf("-> Por favor, certifique-se que a célula pretendida está vazia. <-\n");
                printf("\n");
            }
            printf("COORDENADAS PARA COLOCAR O '%c':\n", sym);
            printf(" --> Número da linha (0 a 2): ");

            /*   ↓ Analisa se o input é uma letra ↓   */
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
            /*   ↓ Analisa se o input é uma letra ↓   */
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

        /*   ↓ Verifica se a cordenada está inserida num "três em linha", caso já se tenham feito mais de 4 jogadas ↓   */
        if(contador>3)
        {
            jogoTermina = tresEmLinha(grelha, x, y);
        }
            /*   ↓ Caso esteja, o jogo termina ↓   */
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
            /*   ↓ Se forem feitas 8 jogadas  e o jogo ainda não tiver terminado, há um empate ↓   */
            empate = 1; 
            break;
        }
        contador++;
    }

    /*   ↓ Fim do jogo ↓   */
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
