#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void liberar_matriz(int **matriz, int linhas){
    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void dividir_matriz(int** matriz, int** A11, int** A12, int** A21, int** A22, int n){
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            A11[i][j] = matriz[i][j];
            A12[i][j] = matriz[i][j + n/2];
            A21[i][j] = matriz[i + n/2][j];
            A22[i][j] = matriz[i + n/2][j + n/2];
        }
    }
}

void reunir_matriz(int** matriz, int** A11, int** A12, int** A21, int** A22, int n){
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n/2; j++){
            matriz[i][j] = A11[i][j];
            matriz[i][j + n/2] = A12[i][j];
            matriz[i + n/2][j] = A21[i][j];
            matriz[i + n/2][j + n/2] = A22[i][j];
        }
    }
}

int** somar_matrizes(int** matriz_a, int** matriz_b, int tam){
    int** matriz_c = alocar_matriz(tam);
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            matriz_c[i][j] = matriz_a[i][j] + matriz_b[i][j]; 
        }
    }
    return matriz_c;
}

int ler_inteiro_positivo(const char* prompt){
    int valor, c;
    do{
        printf("%s", prompt);
        if (scanf("%d", &valor) != 1 || valor <= 0){
            printf("Entrada invalida. Tente novamente!\n");
            valor = 0;
        }
        while ((c = getchar()) != '\n' && c != EOF);
    } while (valor <= 0);
    return valor;
}

void imprimir_resultado(int** matriz, int linhas, int colunas){
    printf("Matriz resultante da multiplicacao:\n\n");
    for (int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}

int** multiplicar_matriz(int** A, int** B, int tam){
    int** C = alocar_matriz(tam);

    if (tam == 1){
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    int** A11 = alocar_matriz(tam/2);
    int** A12 = alocar_matriz(tam/2);
    int** A21 = alocar_matriz(tam/2);
    int** A22 = alocar_matriz(tam/2);
    int** B11 = alocar_matriz(tam/2);
    int** B12 = alocar_matriz(tam/2);
    int** B21 = alocar_matriz(tam/2);
    int** B22 = alocar_matriz(tam/2);

    dividir_matriz(A,A11,A12,A21,A22,tam);
    dividir_matriz(B,B11,B12,B21,B22,tam);

    int** P1 = multiplicar_matriz(A11, B11, tam/2);
    int** P2 = multiplicar_matriz(A12, B21, tam/2);
    int** P3 = multiplicar_matriz(A11, B12, tam/2);
    int** P4 = multiplicar_matriz(A12, B22, tam/2);
    int** P5 = multiplicar_matriz(A21, B11, tam/2);
    int** P6 = multiplicar_matriz(A22, B21, tam/2);
    int** P7 = multiplicar_matriz(A21, B12, tam/2);
    int** P8 = multiplicar_matriz(A22, B22, tam/2);

    int** C11 = somar_matrizes(P1,P2,tam/2);
    int** C12 = somar_matrizes(P3, P4, tam/2);
    int** C21 = somar_matrizes(P5, P6, tam/2);
    int** C22 = somar_matrizes(P7, P8, tam/2);

    reunir_matriz(C,C11,C12,C21,C22,tam);

    liberar_matriz(A11, tam/2);
    liberar_matriz(A12, tam/2);
    liberar_matriz(A21, tam/2);
    liberar_matriz(A22, tam/2);
    liberar_matriz(B11, tam/2);
    liberar_matriz(B12, tam/2);
    liberar_matriz(B21, tam/2);
    liberar_matriz(B22, tam/2);
    liberar_matriz(P1, tam/2);
    liberar_matriz(P2, tam/2);
    liberar_matriz(P3, tam/2);
    liberar_matriz(P4, tam/2);
    liberar_matriz(P5, tam/2);
    liberar_matriz(P6, tam/2);
    liberar_matriz(P7, tam/2);
    liberar_matriz(P8, tam/2);
    liberar_matriz(C11, tam/2);
    liberar_matriz(C12, tam/2);
    liberar_matriz(C21, tam/2);
    liberar_matriz(C22, tam/2);

    return C;
}

int** alocar_matriz(int tamanho){
    int l, c;
    int **matriz = calloc(tamanho, sizeof(int*));
    if (!matriz){
        perror("Erro na alocacao de memoria para a matriz!");
        return NULL;
    }
    for(l = 0; l < tamanho; l++){
        matriz[l] = calloc(tamanho, sizeof(int));
        if(!matriz[l]){
            perror("Erro na alocacao de memoria em matriz");
            return NULL;
        }        
    }
    return matriz;
}

int preencher_matriz_user(int** matriz, int linhas, int colunas){
    int l, c;
    for(l = 0; l < linhas; l++){
        for(c = 0; c < colunas; c++){
            if (scanf("%d", &matriz[l][c]) != 1){
                perror("Erro na alocacao de memoria em matriz");
                return 1;
            }
        }
    }
    return 0;
}

int preencher_matriz_random(int** matriz, int linhas, int colunas){
        int l, c;
    for(l = 0; l < linhas; l++){
        for(c = 0; c < colunas; c++){
            matriz[l][c] = rand() % 10;
        }
    }
    return 0;
}

int proxima_potencia_de_2(int x) { if (x <= 1) return 1; return pow(2, ceil(log2(x))); }

int maior_valor(int a, int b, int c, int d){
    return fmax(fmax(fmax(a,b),c),d); 
}

int main(void){
    srand(time(NULL));
    int **matriz_a, **matriz_b;
    int linhas_a, colunas_a, linhas_b, colunas_b;
    int l, c;

    linhas_a = ler_inteiro_positivo("Quantas linhas a matriz A deve possuir? ");
    colunas_a = ler_inteiro_positivo("Quantas colunas a matriz A deve possuir? ");
    linhas_b = ler_inteiro_positivo("Quantas linhas a matriz B deve possuir? ");
    colunas_b = ler_inteiro_positivo("Quantas colunas a matriz B deve possuir? ");

    if(colunas_a != linhas_b){
        printf("\nMultiplicacao somente possivel em matrizes cujo\nnumero de linhas de A e igual ao numero de colunas de B!\n");
        return 1;
    }
    int escolher_random = ler_inteiro_positivo("Deseja que o aplicativo escolha os valores da matriz aleatoriamente? (1 para SIM, 0 para NÃO): ");
    int maior = maior_valor(linhas_a,colunas_a, linhas_b, colunas_b);
    int tam_padding = proxima_potencia_de_2(maior);
    matriz_a = alocar_matriz(tam_padding);
    matriz_b = alocar_matriz(tam_padding);
    if(matriz_a == NULL || matriz_b == NULL){
        exit(1);
    }
    if (escolher_random){
        preencher_matriz_random(matriz_a, linhas_a, colunas_a);
        preencher_matriz_random(matriz_b, linhas_b, colunas_b);
    } else{
        preencher_matriz_user(matriz_a, linhas_a, colunas_a);
        preencher_matriz_user(matriz_b, linhas_b, colunas_b);
    }
    int** resultado = multiplicar_matriz(matriz_a,matriz_b,tam_padding);
    imprimir_resultado(resultado, linhas_b, colunas_a);
    liberar_matriz(matriz_a,tam_padding);
    liberar_matriz(matriz_b,tam_padding); 
    liberar_matriz(resultado,tam_padding);

    return 0;
}