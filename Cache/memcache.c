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
    for (int i = 0; i < linhas; i++) {
       for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand() %10 + 1; //chama o random
        }
    }
}

void mostramat(int l, int c, double **matriz) {
    for (int i = 0; i < l; i++) {
        printf("|");
        for (int j = 0; j < c; j++) {
            printf("%.10lf ", matriz[i][j]); }
            printf("|\n");}
            printf("\n");
}


int main(/* colocar os parametros l1,c1,c2,l2 e transposta ou normal*/ int argc, char *argv[])
{
    int l1, c1, l2, c2, met_normal, met_transposta;
    char *met, normal = 111;
    double time_spent = 0.0;

    if(argc == 6)//atribuicao dos valores passador nos parametros para suas respectivas variaveis
    {
      l1 = atoi(argv[1]);
      c1 = atoi(argv[2]);
      l2 = atoi(argv[3]);
      c2 = atoi(argv[4]);
      met = argv[5];
    }

    else{
        printf("Erro de parametros, favor verificar!/n");
        return 0;
        }

    if (l2 != c1) {
        printf("Não é possível multiplicar as matrizes\n");}
    else {
        srand(time(NULL));
        MatrizDinamica* M1 = criar_matriz(l1, c1);
        MatrizDinamica* M2 = criar_matriz(l2, c2);
        createmat(l1, c1, M1->matriz);
        createmat(l2, c2, M2->matriz);
        
        if(met[0] == normal)
        { //metodo normal
            clock_t begin = clock();
            MatrizDinamica* MR= criar_matriz(l1,c2);
          
            for (int i = 0; i < l1; i++){
            for (int j = 0; j < c2; j++){
            for (int k = 0; k < c1; k++){
            MR->matriz[i][j] += M1->matriz[i][k]*M2->matriz[k][j]; //multiplicação
        }}}
        clock_t end = clock();
        
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //calcula o tempo e divide pela funcao persec para passar para segundos
        FILE *pont_arq;
        pont_arq = fopen("temponormal.txt", "a+"); 
        if(pont_arq == NULL)
        {
            printf("Erro na abertura do arquivo!");
            return 1;
        }
        fseek(pont_arq, 0, SEEK_END);
        fprintf(pont_arq, "%lf \n", time_spent);
        }
        else{ //metodo 2
            MatrizDinamica* MR = criar_matriz(c1, l2);
            clock_t begin = clock();   
            MatrizDinamica* MT = criar_matriz(c2, l2);
            for (int i = 0; i < l2; i++) {
                for (int j = 0; j < c2; j++) {
                    MT->matriz[j][i] = M2->matriz[i][j];}}
                    //printf("Transposta:\n");
            for (int i = 0; i < l1; i++){
                for (int k = 0; k < c1; k++){
                    for (int l = 0; l < c2; l++){
                        MR->matriz[k][i] += M1->matriz[k][l]*MT->matriz[i][l];
            }}}
            clock_t end = clock();
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //calcula o tempo e divide pela funcao persec para passar para segundos
            FILE *pont_arq;
            pont_arq = fopen("tempotransp.txt", "a+"); 
        if(pont_arq == NULL)
        {
            printf("Erro na abertura do arquivo!");
            return 1;
        }
        fseek(pont_arq, 0, SEEK_END);
        fprintf(pont_arq, "\n%lf", time_spent);
    }
}

return 0;

}