#include "header.h"

void grep(int argc, char *argv[]);
void grep_n(int argc, char *argv[]);
void grep_c(int argc, char *argv[]);
void grep_i(int argc, char *argv[]);
void mygrep(int argc,char *argv[]);
void grep_l(int argc, char *argv[]);


void grep(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\nInvalid ::Enter the file names\n");
        return;
    }

    char *word = argv[1];

    for (int i = 2; i < argc; i++) {
        char *filename = argv[i];
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Error opening file %s.\n", filename);
            return;
        }

        char line[100];
        
        while (fgets(line, sizeof(line), fp)) {
            

            if (strstr(line, word)) {
                printf("%s: %s\n", filename,line);
                
            }
        }

        fclose(fp);
    }

  
}

void grep_n(int argc, char *argv[]) {
    if (argc < 3) {
        printf("\nInvalid ::Enter the file names\n");
        return;
    }

   char *word = argv[2];

    for (int i = 3; i < argc; i++) {
        char *filename = argv[i];
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Error opening file %s.\n", filename);
            return;
        }
    
    char line[100];
    int line_no = 0;
    while (fgets(line, sizeof(line), fp)) {
        line_no++;

        if (strstr(line, word)) {
            printf("%d: %s\n", line_no, line);
        }
    }

    fclose(fp);
    }
  
}

void grep_c(int argc, char *argv[]) {
int count=0;
    if (argc < 3) {
        printf("\nInvalid ::Enter the file names\n");
        return;
    }

   char *word = argv[2];

    for (int i = 3; i < argc; i++) {
        char *filename = argv[i];
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Error opening file %s.\n", filename);
            return;
        }
    
    char line[100];
    int line_no = 0;
    while (fgets(line, sizeof(line), fp)) {
        line_no++;

        if (strstr(line, word)) {
           count++;
        }
    }
printf("%d\n",count);
    fclose(fp);
    }
  
}

void grep_i(int argc, char *argv[]) {
int count=0;
    if (argc < 3) {
        printf("\nInvalid ::Enter the file names\n");
        return;
    }

   char *word = argv[2];

    for (int i = 3; i < argc; i++) {
        char *filename = argv[i];
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Error opening file %s.\n", filename);
            return;
        }
    
    char line[100];
    int line_no = 0;
    while (fgets(line, sizeof(line), fp)) {
        line_no++;

char *lower = strdup(line);
            char *plower = strdup(word);
            for (int j = 0; lower[j]; j++) {
                lower[j] = tolower(lower[j]);
            }
            for (int j = 0; plower[j]; j++) {
                plower[j] = tolower(plower[j]);
            }

            if (strstr(lower, plower)) {
                printf("%s:%d: %s", filename, line_no, line);
            }

            free(lower);
            free(plower);
 
        }
        fclose(fp);
    }

    }
 

void grep_l(int argc, char *argv[]) {
    if (argc < 3) {
        printf("\nInvalid ::Enter the file names\n");
        return;
    }

    char *word = argv[2];

    for (int i = 3; i < argc; i++) {
        char *filename = argv[i];
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("Error opening file %s.\n", filename);
            return;
        }

        char line[100];
        int flag=0;
        while (fgets(line, sizeof(line), fp)) {
            

            if (strstr(line, word)) {
                
                flag=1;
                
            }
        }
  if(flag==1){
printf("%s\n",filename);}
        fclose(fp);
    }

  
}




void mygrep(int argc,char *argv[]){

char opt;
optind=1;
int flag=1;
while((opt=getopt(argc,argv,":ncli"))!=-1){

switch(opt)
{
case 'n':  grep_n( argc,argv); 
           break;
case 'c':  grep_c(argc,argv);
           break;
case 'l':  grep_l(argc,argv);
           break;
case 'i':  grep_i(argc,argv);
           break;
case '?': flag=0;
printf(" \nSorry Invalid command \n")  ;
           break;

}
}
}




