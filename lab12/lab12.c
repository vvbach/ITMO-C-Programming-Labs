#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]){
    unsigned char *fileName;
    strcpy(fileName, argv[1]);
    FILE *f = fopen(fileName, "w");

    time_t rtime;

    time(&rtime);
    
    for (int i = 0; i < 10; i++){
        fprintf(f, "%s\n", asctime(localtime(&rtime)));
        rtime += 86400;
    }
    fclose(f);
    return 0;
}