#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>

void createfile(char *a);
char * find_name(char *path);
int nameis_core(char *name);

int main(){
    char a[300];
    mkdir("root" , 0777);
    printf("hey lets start\n");
    while(1){
    gets(a);
    
    if(!strncmp(a , "createfile--file" , strlen("createfile--file"))){
        createfile(a);
    }
    else if(!strncmp(a , "insertstr--file" , strlen("insertstr--file"))){

    }
    else if(!strcmp(a ,"exit")){
        printf("have a good time!\n");
        break;
    }
    else{
        printf("not correct command\n");
    }
    }
    return 0;
}

char * find_name(char *path){
    char *token , *last;
    last = token = strtok(path, "/");
    for (;(token = strtok(NULL, "/")) != NULL; last = token);
    return last;
}

int nameis_core(char *name){
int flag = 0;
if(name[0]=='"'){
while(flag!=strlen(name)){
    if(name[flag]==' ')
    return 1;
    flag++;
}
printf("you add double qoutation wrongly\n");
return 0;
}
else{

while(flag!=strlen(name)){
    if(name[flag]==' '){
        printf("you forget double qoutation\n");
        return 0;
    }
    flag++;
}
return 1;
}
}

void createfile(char *a){
int t;
char *path;
char *name;
path = strstr(a , "root");
name=find_name(path);
printf("name of file: %s\n" , name);
t=nameis_core(name);
}