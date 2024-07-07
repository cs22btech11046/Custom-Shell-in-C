#include "header.h"
void mymv(char *sfile,char *dfile);
void mymv_b(char *sfile,char *dfile);
void mymv_f(char *sfile,char *dfile);
void mymv_i(char *sfile,char *dfile);
void mymvcmd(int argc,char *argv[]);
void mymv_p(char *sfile, char *dfile);

void mymv(char *sfile,char *dfile){

    if (rename(sfile, dfile) != 0) {
        printf("\nError moving file\n");
       return;
    }
    
    
    return;
}

void mymv_b(char *sfile,char *dfile){
char newfile[MAXBITS];
if(strcmp(sfile,dfile)==0){
printf("\nboth files cannot have the same name\n");
return;}
 strcpy(newfile,dfile);

strcat(newfile,"~");
rename(dfile,newfile);
rename(sfile,dfile);
}

void mymv_f(char *sfile,char *dfile){
if(strcmp(sfile,dfile)==0){
printf("\nboth files cannot have the same name\n");
return;}
remove(dfile);
rename(sfile,dfile);
}

void mymv_i(char *sfile,char *dfile){

char newfile[MAXBITS];
int i=0;
if(strcmp(sfile,dfile)==0){
printf("\nboth files cannot have the same name\n");
return;}
int fdd=-1;
if((fdd=open(dfile,O_RDWR,0))>=0)
{

close(fdd);
char c='n';
printf("\n%s File already exist. do you want to Overwrite y/n",dfile);
scanf("%c",&c);
if(c=='n'){return;}

}
rename(sfile,dfile);
remove(sfile);

}

void mymv_p(char *sfile, char *dfile) {
    
int fd1= open(sfile, O_RDONLY);
if (fd1 == -1) {
 printf("\nError while opening %s\n",sfile);
        return;
    }

struct stat cpstat;
if (fstat(fd1, &cpstat) == -1) {
    printf("\nError while getting %s file stat\n",sfile);
        close(fd1);
        return;
    }

int fd2 = open(dfile, O_WRONLY | O_CREAT | O_TRUNC, cpstat.st_mode);
if (fd2 == -1) {
        printf("\nError while opening %s\n",dfile);
        close(fd2);
        return;
                }

ssize_t num;
char buffer[MAXBITS];
while ((num = read(fd1, buffer, MAXBITS)) > 0) {
 if (write(fd2, buffer, num) != num) {
 printf("\nError writing to destination file\n");
   close(fd1);
        close(fd2);
            return;
        }
    }

if (num == -1) {
        printf("\nError reading from source file\n");
        close(fd1);
        close(fd2);
        return;
    }

if (fchown(fd2, cpstat.st_uid, cpstat.st_gid) == -1) {
        printf("\nError setting ownership of destination file\n");
        close(fd1);
        close(fd2);
        return;
    }
    
     
struct timeval times[2];
times[0].tv_sec = cpstat.st_atime;
times[0].tv_usec = 0;
times[1].tv_sec = cpstat.st_mtime;
times[1].tv_usec = 0;
    
if (utimes(dfile, times) == -1) {
        printf("\nError setting time of destination file\n");
        close(fd1);
        close(fd2);
        return;
    }
    
        close(fd1);
        close(fd2);
 remove(sfile);   

    return;
}

void mymvcmd(int argc,char *argv[]){

char opt;
optind=1;
int flag=1;
while((opt=getopt(argc,argv,":bfip"))!=-1){

switch(opt)
{
case 'b':  if(argv[optind]!=NULL && argv[optind +1]!=NULL ){
           mymv_b(argv[optind],argv[optind +1]);}
           break;
case 'f': if(argv[optind]!=NULL && argv[optind +1]!=NULL ){
           mymv_f(argv[optind],argv[optind +1]);}
           break;
case 'i': if(argv[optind]!=NULL && argv[optind +1]!=NULL ){
           mymv_i(argv[optind],argv[optind +1]);}
       
           break;
case 'p':  if(argv[optind]!=NULL && argv[optind +1]!=NULL ){
           mymv_p(argv[optind],argv[optind +1]);}
           break;
case '?': flag=0;
printf(" \nSorry Invalid command \n")  ;
           break;

}
}
}












