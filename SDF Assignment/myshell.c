#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

int main(){
pid_t pid;
pid=fork();
if(pid==0){
char* user=getenv("USER");
char command[200];
char* c2;
char hostname[100];
char cwd[50];
gethostname(hostname,100);
getcwd(cwd,50);
while(1){

sprintf(command,"%s@%s:~%s$",user,hostname,cwd);

c2=readline(command);
if(strlen(c2)>0){
system(c2);
add_history(c2);

}
if(strcmp(c2,"exit")==0){
break;
}
else if(strcmp(c2,"help")==0){
system("bash -c help");
}
}
}
else{
wait(NULL);
}
return 0;
}
