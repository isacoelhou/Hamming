#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

typedef struct {
double** matriz;
int linhas;
int colunas;
} MatrizDinamica;

double** alocar_matriz(int linhas, int colunas) {
    double** matriz = (double**) calloc(linhas, sizeof(double*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (double*) calloc(colunas, sizeof(double));
        if(matriz[i] == NULL){
          printf("Error: Falha na alocacao de memoria");
          return NULL;}
        }
    return matriz; }

MatrizDinamica* criar_matriz(int linhas, int colunas) {
    MatrizDinamica* mat = (MatrizDinamica*) malloc(sizeof(MatrizDinamica));
    mat->matriz = alocar_matriz(linhas, colunas);
    mat->linhas = linhas;
    mat->colunas = colunas;
    return mat;
}

void createmat(int linhas, int colunas, double **matriz) {
    srand(time(0)); //garante a aleatoriedade do codigo

    for (int i = 0; i < linhas; i++) {
       for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand(); //chama o random
        }
    }
}

void mostramat(int l, int c, double **matriz) {
    for (int i = 0; i < l; i++) {
        printf("|");
        for (int j = 0; j < c; j++) {
            printf("%.10lf ", matriz[i][j]); }
            printf("|\n");}
}


int main(/* colocar os parametros l1,c1,c2,l2 e transposta ou normal*/ int argc, char *argv[]) {
    int l1, c1, l2, c2, met_normal;
    double time_spent = 0.0;

    if(argc == 5) {
        met_normal = atoi(argv[0]);
        l1 = atoi(argv[1]);
        c1 = atoi(argv[2]);
        l2 = atoi(argv[3]);
        c2 = atoi(argv[4]);
        }

    else{
        printf("Erro de parametros, favor verificar!/n");
        return 0;
        }

    if (l2 != c1) {
        printf("Não é possível multiplicar as matrizes\n");}
    else {
        MatrizDinamica* M1 = criar_matriz(l1, c1);
        MatrizDinamica* M2 = criar_matriz(l2, c2);
        createmat(l1, c1, M1->matriz);
        createmat(l2, c2, M2->matriz);
        mostramat(l1, c1, M1->matriz);
        mostramat(l2, c2, M2->matriz);
 
            
        if(met_normal == 0){ //metodo normal
            clock_t begin = clock();
            MatrizDinamica* MR= criar_matriz(l1,c2);
          
            for (int i = 0; i < l1; i++){
            for (int j = 0; j < c2; j++){
            for (int k = 0; k < c1; k++){
                MR->matriz[i][j] += M1->matriz[i][k]*M2->matriz[k][j]; //multiplicação
        }}}
        clock_t end = clock();
        
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //calcula o tempo e divide pela funcao persec para passar para segundos
        printf("o tempo de execução foi de: %lf\n", time_spent);
        }
        else{ //metodo 2
            MatrizDinamica* MR = criar_matriz(c1, l2);
            clock_t begin = clock();   
            MatrizDinamica* MT = criar_matriz(c2, l2);
            for (int i = 0; i < l2; i++) {
                for (int j = 0; j < c2; j++) {
                    MT->matriz[j][i] = M2->matriz[i][j];}}
            for (int i = 0; i < l1; i++){
                for (int j = 0; j < c2; j++){
                    for (int k = 0; k < c1; k++){
                          MR->matriz[i][j] += M1->matriz[i][k]*MT->matriz[k][j];
        }}}
            clock_t end = clock();
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //calcula o tempo e divide pela funcao persec para passar para segundos
            printf("o tempo de execução foi de: %lf\n", time_spent);
    }
}

return 0;

}