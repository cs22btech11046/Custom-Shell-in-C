#include "header.h"

void mymvcmd(int argc,char *argv[]);
void mycpcmd(int argc,char *argv[]);
void mylscmd(int argc,char *argv[]);
void myls(char*dir_name);
void mycp( char *sfile,char *dfile);
void grep(int argc, char *argv[]);
void mymv(char *sfile,char *dfile);
void mygrep(int argc,char *argv[]);

void parsing(int *argc,char*argv[],char *l);

void parsing(int *argc,char*argv[],char *l){
int k=0;
char *tok;
tok=strtok(l," ");
argv[k++]=tok;
while(tok){
argv[k++]=tok=strtok(NULL," ");
}

*argc=k-1;

}


int main(){

char* user=getenv("USER");
char command[200];
char* c2;
char hostname[100];
char cwd[50];
gethostname(hostname,100);
getcwd(cwd,50);

while(1){
int argc;
char *argv[30];
int m=0;
sprintf(command,"%s@%s:~%s$",user,hostname,cwd);

c2=readline(command);
if(strlen(c2)>0){
add_history(c2);
}
if(strcmp(c2,"exit")==0){
m=1;
break;
}
if(strcmp(c2,"help")==0){
m=1;
printf("ls : \n");
printf("ls -l  ls -a  ls -R  ls -t \n");
printf("cp : \n");
printf("cp -b  cp -i  cp -f  cp -p \n");
printf("mv : \n");
printf("mv -b  mv -i  mv -f  mv -p \n");
printf("grep : \n");
printf("grep -n  grep -c  grep -i  grep -l \n");
}

if(strcmp(c2,"ls")==0){
m=1;
myls(".");
}
//=================================//
 parsing(&argc,argv,c2);

if(strcmp(argv[0],"cp")==0){
if(argc==3){
 mycp(argv[1],argv[2]);
}
m=1;
mycpcmd( argc,argv);

} 

if(strcmp(argv[0],"ls")==0){
m=1;
mylscmd(argc,argv);

}

if(strcmp(argv[0],"mv")==0){
if(argc==3){
 mymv(argv[1],argv[2]);
}
m=1;
mymvcmd(argc,argv);
}
if(strcmp(argv[0],"grep")==0){
if(argc==3){
 grep(3,argv);
}
m=1;
mygrep(argc,argv);
}
if(m==0)
printf("\nInvalid command\n");
fflush(stdout);
}

return 0;
}















