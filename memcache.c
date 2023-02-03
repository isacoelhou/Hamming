#include <stdio.h> 
 #include <stdlib.h> 
 #include <time.h> 
 #include<string.h> 
  
 void createmat(int linhas, int colunas, double matriz[linhas][colunas]) { 
   srand(time(0)); //garante a aleatoriedade do codigo 
    
   for (int i = 0; i < linhas; i++) { 
     for (int j = 0; j < colunas; j++) { 
       matriz[i][j] = rand(); //chama o random 
 }}} 
  
 void mostramat(int l, int c, double matriz[l][c]) 
 { 
   for (int i = 0; i < l; i++) { 
     printf("|"); 
     for (int j = 0; j < c; j++) { 
       printf("%10d ", matriz[i][j]); 
 } 
 printf("|\n"); 
  
 } 
 } 
  
  
 int main(/* colocar os parametros l1,c1,c2,l2 e transposta ou normal*/ int argc, char *argv[]) 
 { 
     int l1, c1, l2, c2, met_normal, met_transposta; 
     char *met, *normal; 
     normal = "Normal"; 
     double time_spent = 0.0; 
          
  
     // printf("Quantas linhas terá sua matriz 1?\n"); //essa parte tem que por nos parametros do main 
     // scanf("%d", &l1); 
     // printf("E a matriz 2?\n"); 
     // scanf("%d", &l2); 
     // printf("Quantas colunas terá sua matriz 1?\n");     
     // scanf("%d", &c1); 
     // printf("E a matriz 2?\n"); 
     // scanf("%d", &c2); 
     // printf("Qual será o metodo da multiplicação?\ndigite: \n[1] para tradicional [2] para transposta\n"); 
     // scanf("%d", &met); 
     if(argc == 6)//atribuicao dos valores passador nos parametros para suas respectivas variaveis 
     { 
       l1 = atoi(argv[1]); 
       c1 = atoi(argv[2]); 
       l2 = atoi(argv[3]); 
       c2 = atoi(argv[4]); 
       met = argv[5]; 
     } 
     else//caso nao seja compativel os paramtros com o desejado  
     { 
       printf("Erro de parametros, favor verificar!/n"); 
       return 0; 
     } 
      
     double M1[l1][c1]; //cria a matriz de acordo com o que leu 
     double M2[l2][c2]; 
     //printf("%d %d %d %d", l1, c1, l2, c2); 
      
     if (l2 != c1) //critério de multiplicação, se as linhas de uma mat n é igual a coluna de outra não tem como 
         printf("Não é possível multiplicar as matrizes\n"); 
     else{ 
         createmat(l1, c1, M1); //gera as matrizes aleatorias 
         createmat(l2, c2, M2); 
         met_normal = strcmp(met, normal); 
         if(met_normal == 0){ //metodo normal 
         clock_t begin = clock(); 
         double MR[c1][l2]; //gera a matriz resposta 
            
           for (int i = 0; i < l1; i++){ 
           for (int j = 0; j < c2; j++){ 
           for (int k = 0; k < c1; k++){ 
             MR[i][j] += M1[i][k]*M2[k][j]; //multiplicação 
            
         }}} 
         clock_t end = clock(); 
        //mostramat(l1, c2, MR); 
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //calcula o tempo e divide pela funcao persec para passar para segundos 
        printf("o tempo de execução foi de: %lf\n", time_spent); 
  
         } 
         else{ //metodo 2 
         double MR[c1][l2]; 
         clock_t begin = clock();    
         double MT[c2][l2]; //matriz transposta 
         for (int i = 0; i < l2; i++) { 
         for (int j = 0; j < c2; j++) { 
             MT[j][i] = M2[i][j];}} //troca linhas por colunas 
         //falta multiplicar a transposta com a normal 
         for (int i = 0; i < l1; i++){ 
           for (int j = 0; j < c2; j++){ 
           for (int k = 0; k < c1; k++){ 
             MR[i][j] += M1[i][k]*MT[k][j]; //multiplicação 
         //calcular o tempo de execução 
         }}} 
         clock_t end = clock(); 
         time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //calcula o tempo e divide pela funcao persec para passar para segundos 
         printf("o tempo de execução foi de: %lf\n", time_spent);    
     }} 
  
  
     return 0; 
 }