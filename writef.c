#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[], char** envp){
    
    if(strcmp("-f",argv[0]) != 0){
         printf("'%s' it is not a defined operation. \n",argv[0]);
        return 0;
    }

    time_t rtime;
    struct tm * info;
    time ( &rtime );
    info = localtime ( &rtime );

    char *word = (char*)malloc(50 * sizeof(char));
    sprintf(word, "pid:%d, ppid:%d, time: %s",getpid(),getppid(),asctime(info));
    FILE *f;

    if (access(argv[1], F_OK) == 0) {
     f = fopen(argv[1],"a");
    } else {
     f = fopen(argv[1],"w");
    }

    fputs(word,f);
    fclose(f);
  
    return 0;
}
