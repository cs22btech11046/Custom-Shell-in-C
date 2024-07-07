#include "header.h"
void mylscmd(int argc,char *argv[]);
void myls(char*dir_name);
void printmodevalue(mode_t m);
void myls_l(char*dir_name);
void myls_a(char*dir_name);
void myls_R(char*dir_name);
void myls_t(char*dir_name);
struct array{
struct stat c;
char a[100];
};
void printlscommand(struct array myn);
   
int mils_l(const void*a,const void*b){
struct array*x=(struct array*)a;
struct array*y=(struct array*)b;
return strcasecmp(x->a,y->a);
}

int mils_t(const void*a,const void*b){
struct array*x=(struct array*)a;
struct array*y=(struct array*)b;
return(y->c.st_mtime)-(x->c.st_mtime);
}



void printlscommand(struct array myn){
struct stat fstat=myn.c;
struct passwd *own= getpwuid(fstat.st_uid);
struct group *grp= getgrgid(fstat.st_gid);

printmodevalue(fstat.st_mode);
printf("%ld ",fstat.st_nlink);
printf("%s ",own->pw_name);
printf("%s ",grp->gr_name);
printf("%7ld ",fstat.st_size);
time_t t =time(000);
struct tm tm = *localtime(&(fstat.st_mtime));
printf("%5d-%2d-%2d %2d:%2d:%2d  ",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
printf("%s",myn.a);
}


void printmodevalue(mode_t m){
if(S_ISDIR(m)){printf("d");}
else{printf("-");}
printf((m & S_IRUSR) ? "r":"-");
printf((m & S_IWUSR) ? "w":"-");
printf((m & S_IXUSR) ? "x":"-");
printf((m & S_IRGRP) ? "r":"-");
printf((m & S_IWGRP) ? "w":"-");
printf((m & S_IXGRP) ? "x":"-");
printf((m & S_IROTH) ? "r":"-");
printf((m & S_IWUSR) ? "w":"-");
printf((m & S_IXUSR) ? "x":"-");

}

void myls(char*dir_name){                                                                                                          
DIR* dir;
int i=0,count=0;
struct dirent*de;
struct array lsarr[MAXLIMIT];
dir=opendir(dir_name);
if(dir==0){
printf("\ncannot open the current directory");
}

while((de=readdir(dir))!=0){

if(strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0||(*de->d_name)=='.'){continue;}

struct array m;
struct stat fstat;
stat(de->d_name,&fstat);
m.c=fstat;
strcpy(m.a,de->d_name);
lsarr[i++]=m;
count++;
}
qsort(lsarr,count,sizeof(struct array),mils_l);
for(int j=0;j<i;j++){
printf("%s",lsarr[j].a);
printf("\n");
}

closedir(dir);
}



void myls_l(char*dir_name){                                                                                                          
DIR* dir;
int i=0,count=0;
struct dirent*de;
struct array lsarr[MAXLIMIT];
dir=opendir(dir_name);
if(dir==0){
printf("\ncannot open the current directory");
}

while((de=readdir(dir))!=0){

if(strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0||(*de->d_name)=='.'){continue;}

struct array m;
struct stat fstat;
stat(de->d_name,&fstat);
m.c=fstat;
strcpy(m.a,de->d_name);
lsarr[i++]=m;
count++;
}
qsort(lsarr,count,sizeof(struct array),mils_l);
for(int j=0;j<i;j++){
printlscommand(lsarr[j]);
printf("\n");
}

closedir(dir);
}



void myls_a(char*dir_name){                                                                                                          
DIR* dir;
int i=0,count=0;
struct dirent*de;
struct array lsarr[MAXLIMIT];
dir=opendir(dir_name);
if(dir==0){
printf("\ncannot open the current directory");
}

while((de=readdir(dir))!=0){
struct array m;
struct stat fstat;
stat(de->d_name,&fstat);
m.c=fstat;
strcpy(m.a,de->d_name);
lsarr[i++]=m;
count++;
}
qsort(lsarr,count,sizeof(struct array),mils_l);
for(int j=0;j<i;j++){
printlscommand(lsarr[j]);
printf("\n");
}

closedir(dir);
}

void myls_R(char*dir_name){                                                                                                          
DIR* dir;
int i=0,count=0;
struct dirent*de;
struct array lsarr[MAXLIMIT];
dir=opendir(dir_name);
if(dir==0){
printf("\ncannot open the current directory");
}

while((de=readdir(dir))!=0){

if(strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0||(*de->d_name)=='.'){continue;}

struct array m;
struct stat fstat;
stat(de->d_name,&fstat);
m.c=fstat;
strcpy(m.a,de->d_name);
lsarr[i++]=m;
count++;
}
qsort(lsarr,count,sizeof(struct array),mils_l);
for(int j=i;j>0;j--){
printlscommand(lsarr[j]);
printf("\n");
}

closedir(dir);
}

void myls_t(char*dir_name){                                                                                                          
DIR* dir;
int i=0,count=0;
struct dirent*de;
struct array lsarr[MAXLIMIT];
dir=opendir(dir_name);
if(dir==0){
printf("\ncannot open the current directory");
}

while((de=readdir(dir))!=0){

if(strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0||(*de->d_name)=='.'){continue;}

struct array m;
struct stat fstat;
stat(de->d_name,&fstat);
m.c=fstat;
strcpy(m.a,de->d_name);
lsarr[i++]=m;
count++;
}
qsort(lsarr,count,sizeof(struct array),mils_t);
for(int j=0;j<i;j++){
printlscommand(lsarr[j]);
printf("\n");
}

closedir(dir);
}


void mylscmd(int argc,char *argv[]){

char opt;
optind=1;
int flag=1;
while((opt=getopt(argc,argv,":latR"))!=-1){

switch(opt)
{
case 'l':  myls_l(".");
           break;
case 'a':  myls_a(".");
           break;
case 'R': 
           myls_R("."); 
           break;
case 't':  myls_t(".");
           break;
case '?': flag=0;
printf(" \nSorry Invalid command \n")  ;
           break;

}

}
}




