#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int wordCount(char*, char);
int control(char**, int,char**);
char** splitWord(char*,char*,int);


int main(int argc, char *argv[], char** envp){
    
    printf("MyShell>> ");
    int xexit;
    char word[40];

    while(scanf("%[^\n]",word)==1){ 
             
        int word_count=wordCount(word,' ')+1;
        char **words=splitWord(word," ",word_count);
        
        xexit=control(words, word_count, envp);
       
        if(xexit){
           break;        
        }

        printf("MyShell>> ");
        scanf("%[^\n]",word);
        getchar();
        
    }
    return 0;
}


char** splitWord(char* word, char* x, int wordCount){
    int count = 0;
    char **words = (char**) malloc(wordCount* sizeof(char *));
    char *stoken = strtok(word, x);

    while (stoken != NULL){   
        *(words+count++) = stoken;
        stoken = strtok(NULL, x);
    }
    return words;
}

int control(char** word_array, int wordCount, char** envp){
    	char* new_argv[5];
    	if(strcmp("exit",*(word_array)) == 0){
            
            return 1;

        }else if(strcmp("ls",*(word_array)) == 0){
            
            system("ls");

        }else if(strcmp("clear",*(word_array)) == 0){
           
            system("clear");

        }else if(strcmp("cat",*(word_array)) == 0){
            printf("cat: ");

            for(int i=1;i<wordCount;i++){

                printf("%s ", word_array[i]);

            }
            printf("\n");
        
        }else if(strcmp("bash",*(word_array)) == 0){
            int sts, pid;

            pid = fork();

            if (pid > 0) {
                wait(&sts);
            } else {
                new_argv[0]="bash>>";
                new_argv[1]=NULL;
                sts=execve("/bin/bash", new_argv, envp);
                perror("error\n");
                exit(1);
            }
        }else if(strcmp("execx",*(word_array)) == 0){
            int pid;

            pid = fork();
            if (pid == 0) {
            
            for(int i=1 ; i<wordCount ; i++){
		new_argv[i-1]=*(word_array+i);
	    }
                new_argv[wordCount-1]=NULL;
                int i=execve("execx", new_argv, envp);
                perror("error\n");
                exit(1);
            }
        }else if(strcmp("writef", *(word_array)) == 0){
            int sts, pid ;

            pid = fork();

            if (pid > 0) {
                wait(&sts);
            } else {
                new_argv[0]=*(word_array+1);
                new_argv[1]=*(word_array+2);
                new_argv[2]=NULL;
                sts=execve("writef", new_argv, envp);
                perror("error\n");
                exit(1);
            }
        }else{
            printf("The command you entered is incorrect...\n");
        }
        return 0;
}

int wordCount(char* word,char x){
    int count = 0;
    int word_length;

    word_length = strlen(word);
    for(int i=0;i<word_length;i++){
        if(*(word+i) == x){
            count +=1;
        }
    }
    return count;
}


