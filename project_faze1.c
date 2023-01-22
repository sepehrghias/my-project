#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

void createfile(char *a);
char * find_name(char *path);
int nameis_core(char *name);
void insertstr(char *a);
char* get_path(char* a);
void cat(char* a);
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
            insertstr(a);
        }
        else if(!strncmp(a , "cat--file" , strlen("cat--file"))){
            cat(a);
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

char* get_path(char* a){
    char*path;
    path = strstr(a , "root");
    return path;
}

void createfile(char *a){
    int t;
    char *path1;
    char path[100];
    char *name;
    path1=get_path(a);
    printf("%s",path1);
    strcpy(path , path1);
    name=find_name(path);
    printf("name of file: %s\n" , name);
    t=nameis_core(name);
    if(t==0)
        return;
    printf("path : %s\n" , path1);
    FILE * sep = fopen("root/se.txt" , "w");
    fclose(sep);
}

void insertstr(char *a){

}

void cat(char* a){
    char * path;
    path = get_path(a);
    char string[100];
    FILE * myfile = fopen(path , "r");
    while(1){
        if( fgets(string , 20 , myfile) == NULL)
            break;
        printf("%s" , string);
    }
    fclose(myfile);
}