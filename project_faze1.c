#include <stdio.h>

#include <string.h>

#include <dirent.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

#define NUM 1000000
void createfile(char *a);
char * find_name(char *path);
int nameis_core(char *name);
void insertstr(char *a);
char* get_path(char* a);
void cat(char* a);
int check_file(char *a);
char *getstring(char *a);

int main(){
    char a[300];
    mkdir("root" , 0777);
    printf("hey lets start\n");
    while(1){
        gets(a);

        if(!strncmp(a , "createfile--file " , strlen("createfile--file "))){
            createfile(a);
        }
        else if(!strncmp(a , "insertstr--file " , strlen("insertstr--file "))){
            insertstr(a);
        }
        else if(!strncmp(a , "cat--file " , strlen("cat--file "))){
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
            if(name[flag]==' '){

                return 1;
            }
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

int check_file(char*path){
    if(!access(path , F_OK))
    {
        printf("this file is exist\n");
        return 0;
    }
    return 1;
}

char* get_path(char* a){
    char*path;
    char *path1;
    path1 = (char*)malloc(300 * sizeof(char));
    // if("creatfile--file /root"!=)
    path = strstr(a , "root");
    int counter = 0;
    while(1){
        if(path[counter-4]=='.' && path[counter-3]=='t' && path[counter-1]=='t' && path[counter-2]=='x'){
            break;
        }
        path1[counter]=path[counter];
        counter++;
    }
    return path1;
}
void makedir(char *path){
    char *string ;
    string = (char *) calloc(100 , sizeof(char));
    int i = 0;
    string[0]='\0';
            while(1){
                if(i==strlen(path))
                break;
                if(path[i]=='/'){
                    mkdir(string , 0777);
                }
                string[i]=path[i];

                i++;
            }

    }
void createfile(char *a){
    int t;
    char *path1;
    char path[300];
    char *name;
    path1=get_path(a);
    strcpy(path , path1);
    name=find_name(path);
    t=nameis_core(name);
    if(t==1){
        if(name[0]=='"'){
            path1[strlen(path1)-1]='\0';
            for(int i ; i<strlen(path1)-2 ; i++){
                if(path1[i]=='"'){
                    for(int j = i ; j <= i+1 + strlen(name) - 2 ; j++){
                        path1[j]=path1[j+1];
                    }
                    break;
                }
            }
        }
        makedir(path1);
        if(check_file(path1)==1){

            FILE *sep = fopen(path1 , "w");

            fclose(sep);
            printf("success\n");

        }
    }
}

char *getstring(char*a){
    int counter = 0;
    char string[400]={'\0'};
    a = strstr(a , "--str ");
    while(1){
        if( a[counter+6]==' ' && a[counter+7]=='-' && a[counter+8]=='-' && a[counter+9]=='p' && a[counter+10]=='o'){
            string[counter+6]=='\0';
            break;
        }
         string[counter]=a[counter+6];
         counter++;
    }
    return string;
}
void insertstr(char *a) {
    char path[100] ,stri[400];
    char *string;
    string = (char*)malloc(400 * sizeof(char));
    int from, to;
    strcpy(path , get_path(a));
    strcpy(string,getstring(a));
    a = strstr(a , "--pos");
    sscanf(a , "--pos %d:%d" ,& from ,& to);
    int line = to - from;
    char matn[NUM], matn2[NUM];
    int lots = 1, counter = 0;
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("it's not correct address or file name\n");
        fclose(fp);
    } else {
        while (1) {
            if (lots < from) {
                matn[counter] = fgetc(fp);
                if (matn[counter]  == NULL) {
                    break;
                }
                if (matn[counter ] == '\n') {
                    lots++;
                }
                counter++;
            } else {

                if (fgets(stri, 40, fp) == NULL) {
                    break;
                }
                strcat(matn2 , stri);
            }

        }
        printf("%s %d\n" ,string , strlen(string));
        fclose(fp);
        int ska =0 ;
        FILE * file = fopen(path , "w");
        fputs(matn , file);
        while(1) {
            if(string[ska]=='\0')
                break;
            else if(string[ska]=='\n')
                fputc('\n' , file);
            else
                fputc(string[ska] , file);
            ska++;
        }
        fputc('\n' , file);
        fputs(matn2 , file);

        printf("added succesfully\n");
        fclose(file);
    }
}

void cat(char* a){
    char * path;
    path = get_path(a);
    char string[100];
    FILE * myfile = fopen(path , "r");
    while(1){
        if(myfile==NULL) {
            printf("it's not correct address or file name");
            break;
        }
        if( fgets(string , 20 , myfile) == NULL)
            break;
        printf("%s" , string);
    }
    fclose(myfile);
    printf("\n");
}