#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

    char mode = 't';
    char chamada[100];
    char ordem[5];
    int status;

    for (int i = 200; i <= 2000; i += 200){
        for (int j = 0; j < 20; j++)
        {
            if (j >= 10)
                mode = 'o';

            sprintf(ordem, "%d", i);
            sprintf(chamada, "./aloc %s %s %s %s %c", ordem, ordem, ordem, ordem, mode);

            system(chamada);
            wait(&status);
        }
    mode = 't';
    }

    return 0;
}