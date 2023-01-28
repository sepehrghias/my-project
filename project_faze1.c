#include <stdio.h>

#include <string.h>

#include <dirent.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <stdlib.h>

#include <errno.h>

#include <unistd.h>

#define NUM 1000000

char clipboard[NUM];

void createfile(char *a);
char * find_name(char *path);
int nameis_core(char *name);
void insertstr(char *a);
char* get_path(char* a);
void cat(char* a);
int check_file(char *a);
char *getstring(char *a);
char* tabdil(char *a);
void removes(char *a);
void copy(char *a);
void cut(char *a);
void paste(char *a);
int main(){
    char a[300];
    mkdir("root" , 0777);
    printf("hey lets start\n");
    while(1){
        gets(a);
        //barresi address dar qutation

        if(!strncmp(a , "createfile--file " , strlen("createfile--file "))){
            createfile(a);
        }
        else if(!strncmp(a , "insertstr--file " , strlen("insertstr--file "))){
            insertstr(a);
        }
        else if(!strncmp(a , "cat--file " , strlen("cat--file "))){
            cat(a);
        }
        else if(!strncmp(a ,"removetstr--file " , strlen("removetstr--file ")) ){
            removes(a);
        }
        else if(!strncmp(a , "copystr--file " , strlen("copystr--file "))){
            copy(a);
        }
        else if(!strncmp(a , "pastestr--file " , strlen("pastestr--file "))){
            paste(a);
        }
        else if(!strncmp(a , "cutstr--file " , strlen("cutstr--file "))){
            cut(a);
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
    //check
    //kataha ra az ham joda kon
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
        if(a[counter]=='\0'){
            char * b = "FALSE RESULT";
            return b;
        }
        string[counter]=a[counter+6];
        counter++;
    }
    return string;
}

void insertstr(char *a) {
    //back to insert to corect it
    // string age space dare joda kon
    //hale //n
    //talash bara hazf namad moshkel dar
    char path[100] ,stri[400];
    char *string;
    string = (char*)malloc(400 * sizeof(char));
    int from, to;
    strcpy(path , get_path(a));
    strcpy(string,getstring(a));
    if(!strcmp(string , "FALSE RESULT")){
        printf("not correct command\n");
        return ;
    }
    a = strstr(a , "--pos");
    sscanf(a , "--pos %d:%d" ,& from ,& to);
    int line = to - from;
    char *matn =(char*) calloc(NUM , sizeof(char));
    char *matn2 =(char*) calloc(NUM , sizeof(char));
    int lots = 1, counter = 0;
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("it's not correct address or file name\n");
        fclose(fp);
    } else {
        while (1) {
            if (lots < from) {

                if (feof(fp)) {
                    break;
                }
                matn[counter]=fgetc(fp);
                if (matn[counter] == '\n') {
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
        if(lots<from){
            for(int i=0 ; i<from-lots ; i++)
                fputc('\n' , file);
        }
        while(1) {
            if(string[ska]=='\0')
                break;
            else if(string[ska]=='\\' && string[ska+1]=='\\' && string[ska]=='n'){
                fputc('\\' , file);
                fputc('n' , file);
                ska += 2 ;
            }
            else if(string[ska]=='\\' && string[ska+1]=='n'){
                fputc('\n' , file);
                ska ++;
            }

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

void cat(char* a) {
    //check
    //qutation
    char *path;
    path = get_path(a);

    char string[100];
    FILE *myfile = fopen(path, "r");
    while (1) {
        if (myfile == NULL) {
            printf("it's not correct address or file name");
            break;
        }
        if (fgets(string, 20, myfile) == NULL)
            break;
        printf("%s", string);
    }
    fclose(myfile);
    printf("\n");
}
void removes(char *a){
    //talash bara hazf on namade
    char *path = get_path(a);
    char *string = (char*)calloc(NUM , sizeof(char));
    char * t;
    char flag='\0';
    int l = 1;
    int line=0 , word=0 , chand;
    t= strstr(a , "--pos");
    if(t==NULL){
        printf("not correct command\n");
        return;
    }
    sscanf(t,"--pos %d:%d --size %d -%c" , &line , &word , &chand , &flag);
    if(line==1 || word==0 || flag=='\0'){
        printf("not correct command\n");
        return;
    }
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("it's not correct address or file name\n");
        fclose(fp);
        return;
    }
    int counter = 0 , enter=1;
    int h = 0;
    while(1){
        if(feof(fp))
            break;
        if(enter!=line) {
            string[counter] = fgetc(fp);
            if (string[counter]=='\n')
                enter++;
        }
        else{
                if(l<word+1){
                    string[counter]=fgetc(fp);
                    l++;
            }
                else{
                    if(flag=='b'){
                        string[counter-chand]=fgetc(fp);
                    }
                    else if(flag=='f'){
                        if(h==0) {
                            for (int k = 0; k < chand-1; k++)
                                fgetc(fp);
                        }
                        h++;
                        //barresi qutation
                        string[counter-1]=fgetc(fp);
                    }
                    //barresi word age \n dare ya na
                    else{
                        printf("not correct command\n");
                        return;
                    }
                }
        }

        counter++;
    }
    if(enter!=line){
        printf("you insert incorrect position\n");
        return;
    }
    printf("removed succesfully\n");
    fclose(fp);
    FILE *file = fopen(path , "w");
    fputs(string , file);
    fclose(file);
}

void copy(char *a){
    char *path = get_path(a);
    char * t = (char *)calloc(NUM , sizeof(char));
    char *string = (char*)calloc(NUM , sizeof(char));
    int l =1 ;
    int line = 0 , word = 0 , chand;
    char flag;
    t= strstr(a , "--pos");
    if(t==NULL){
        printf("not correct command\n");
        return;
    }
    sscanf(t,"--pos %d:%d --size %d -%c" , &line , &word , &chand , &flag);
    if(line==1 || word==0 || flag=='\0'){
        printf("not correct command\n");
        return;
    }
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("it's not correct address or file name\n");
        fclose(fp);
        return;
    }
    int counter = 0 , enter = 1 ;
    while(1){
        if(feof(fp))
        break;
        if(enter!=line){
            string[counter]=fgetc(fp);
            if(string[counter]=='\n')
                enter++;
        }
        else{
            if(l<word) {
                string[counter] = fgetc(fp);
                l++;
            }
            else{
                if(flag=='b'){
                    int i ,j;
                    for(i = chand-1 ,j =0  ; i>-1 ; j++ ,  i--)
                        clipboard[j] = string[counter-i];
                        clipboard[j+1]='\0';
                    break;
                }
                else if(flag=='f'){
                    for(int i = 0 ; i<chand ; i++)
                        clipboard[i]=fgetc(fp);
                    clipboard[chand] = '\0';
                    break;
                }
                    //barresi word age \n dare ya na
                else{
                    printf("not correct command\n");
                    return;
                }
            }

        }
        counter++;
    }
    if(enter!=line){
        printf("not correct command\n");
        return;
    }
    fclose(fp);
    printf("%s\n" , clipboard);
    printf("copy successfully\n");
}

void cut(char *a){
    copy(a);
    removes(a);
    printf("cut successfully");
}
char * tabdil(char *a){
    char path[NUM];
    char *t;
    char string[NUM] = " --str";
    strcpy(path , get_path(a));
    strcat(string , clipboard);
    t = strstr(a , " --pos");
    if(t==NULL){
        return NULL;
    }
    strcat(path , string);
    strcat(path , t);
    return path;
}

void paste(char *a){
    //its not okay yet
    //first handle it insert
    printf("%s\n" , clipboard);
    a = tabdil(a);
    if(a==NULL){
        printf("not correct command\n");
        return ;
    }
    insertstr(a);
}