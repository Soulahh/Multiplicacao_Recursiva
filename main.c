#include <stdio.h>
#include <stdlib.h>


int liberar_matriz(int **matriz, int linhas){
    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int completar_matriz(int* matriz1, int* matriz2){}


int mult_matriz(int* matriz1, int* matriz2, int tam_matriz){}

int** alocar_matriz(int** matriz, int num_linhas, int num_colunas){
    matriz = malloc(num_linhas * sizeof(int*));
    if (!matriz){
        perror("Erro na alocacao de memoria para a matriz!");
        return NULL;
    }

    for(int l = 0; l < num_linhas; l++){
        matriz[l] = malloc(num_colunas * sizeof(int));
        if(!matriz[l]){
            perror("Erro na alocacao de memoria em matriz");
            return NULL;
        }

        for(int c = 0; c < num_colunas; c++){
            if (scanf("%d", &matriz[l][c]) != 1){
                perror("Erro na alocacao de memoria em matriz");
                return NULL;
            }
        }
    }
    return matriz;
}





//TODO: CRIAR MATRIZ ARBITRARIA E FAZER FUNCIONAR PELO METODO RECURSIVO BASICO



int main(void){
    int **matriz_a, **matriz_b;
    int linhas_a, colunas_a, linhas_b, colunas_b;
    int l, c;

    printf("Quantas linhas a matriz A deve possuir? ");
    if(scanf("%d", &linhas_a) != 1){
        perror("Erro na leitura das linhas!");
        exit(1);
    }

    printf("Quantas colunas a matriz A deve possuir? ");
    if(scanf("%d", &colunas_a) != 1){
        perror("Erro na leitura das colunas!");
        exit(1);
    }

        printf("Quantas linhas a matriz B deve possuir? ");
    if(scanf("%d", &linhas_b) != 1){
        perror("Erro na leitura das linhas!");
        exit(1);
    }

    printf("Quantas colunas a matriz B deve possuir? ");
    if(scanf("%d", &colunas_b) != 1){
        perror("Erro na leitura das colunas!");
        return 1;
    }

    if(colunas_a != linhas_b){
        printf("\nMultiplicacao somente possivel em matrizes cujo\nnumero de linhas de A e igual ao numero de colunas de B!\n");
        return 1;
    }
    matriz_a = alocar_matriz(matriz_a, linhas_a, colunas_a);
    matriz_b = alocar_matriz(matriz_b, linhas_b, colunas_b);
    if(matriz_a == NULL || matriz_b == NULL){
        exit(1);
    }





    return 0;
}