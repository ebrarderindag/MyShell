#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char** envp){

    if(argv[1][0] < 48 || argv[1][0]>57){ //number kontrolü yapılır
        printf("'%s' is not defined, you need to enter a number.\n",argv[1]);
        return 0;
    }
    if(strcmp("-t",argv[0]) != 0){ //-t kontrolü yapılır
        printf("'%s' is not defined, you need to enter -t.\n",argv[0]);
        return 0;
    }

    int ln = atoi(argv[1]);
    char* new_argv[3];

    for(int i=0; i<ln; i++){ //döngü içinde terminalden alınan komutları bir arraye atıp kontrollerini sağlıyorum.

          if(strcmp("writef",argv[2]) == 0){
            int sts, pid;

            pid = fork();

            if (pid > 0) {
                wait(&sts);
            } else {
                new_argv[0]=argv[3];
                new_argv[1]=argv[4];
                new_argv[2]=NULL;
                sts=execve("writef", new_argv, envp);
                perror("error\n");
                exit(1); 
            }
    }
   }
}
