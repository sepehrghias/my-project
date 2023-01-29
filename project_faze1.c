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
int ch_enter(char *string);
void find(char *a);
int check_featf(int a , int b , int c , int d);
void undo(char *a);
int FindSearch(FILE*file ,char * string);
int main(){
    char a[300];
    mkdir("root" , 0777);
    printf("hey lets start\n");
    while(1){
        gets(a);
        //barresi address dar qutation

        if(!strncmp(a , "createfile --file " , strlen("createfile --file "))){
            createfile(a);
        }
        else if(!strncmp(a , "insertstr --file " , strlen("insertstr --file "))){
            insertstr(a);
        }
        else if(!strncmp(a , "cat --file " , strlen("cat --file "))){
            cat(a);
        }
        else if(!strncmp(a ,"removetstr --file " , strlen("removetstr --file ")) ){
            removes(a);
        }
        else if(!strncmp(a , "copystr --file " , strlen("copystr --file "))){
            copy(a);
        }
        else if(!strncmp(a , "pastestr --file " , strlen("pastestr --file "))){
            paste(a);
        }
        else if(!strncmp(a , "cutstr --file " , strlen("cutstr --file "))){
            cut(a);
        }
        else if(!strncmp(a , "find --str " , strlen("find --str "))){
            find(a);
        }
        else if(!strncmp(a , "undo --file" , strlen("undo --file"))){
            undo(a);
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
        if((path[counter-4]=='.' && path[counter-3]=='t' && path[counter-1]=='t' && path[counter-2]=='x') || (path[counter-1]=='c' && path[counter-2]=='.')){
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
    int count = 0;
    char string[400]={'\0'};
    a = strstr(a , "--str ");
    while(1){
        if(( a[counter+6]==' ' && a[counter+7]=='-' && a[counter+8]=='-' && a[counter+9]=='p' && a[counter+10]=='o') || (a[counter+6]==' ' &&
        a[counter+7]=='-' && a[counter+8]=='-' && a[counter+9]=='f' && a[counter+10]=='i' && a[counter+11]=='l')){
            break;
        }
        if((a[counter+6]=='"' && a[counter+7]==' ' && a[counter+8]=='-' && a[counter+9]=='-' && a[counter+10]=='p' && a[counter+11]=='o') || ( a[counter+6]=='"' && a[counter+7]==' ' &&
        a[counter+8]=='-' && a[counter+9]=='-' && a[counter+10]=='f' && a[counter+11]=='i' && a[counter+12]=='l')){
            break;
        }
        if(a[counter]=='\0'){
            char * b = "FALSE RESULT";
            return b;
        }
        if(a[counter+6]=='"'){
            counter++;
            string[count]=a[counter+6];
            counter++;
            count++;
            continue;
        }
        if(a[counter+6]=='\\' && a[counter+7]=='"'){
            counter++;
            string[count]=a[counter+6];
            counter++;
            count++;
            continue;
        }
        string[count]=a[counter+6];
        counter++;
        count++;
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
       // printf("%s %d\n" ,string , strlen(string));
        fclose(fp);
        int ska =0 ;
        if(from>lots){
            printf("you enter wrong position\n");
            return;
        }
        FILE * file = fopen(path , "w");
        fputs(matn , file);
        while(1) {
            if(string[ska]=='\0')
                break;
            else if(string[ska]=='\\' && string[ska+1]=='\\' && string[ska+2]=='n'){
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
        int g = ch_enter(string);
        if(line-g>0){
            for(int i = line-g  ; i!=0 ; i--)
                fputc('\n' , file);
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
    char u;
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
                        u=fgetc(fp);
                        if(u==EOF)
                            break;
                        string[counter-chand]=u;
                    }
                    else if(flag=='f'){
                        if(h==0) {
                            for (int k = 0; k < chand-1; k++)
                                fgetc(fp);
                        }
                        h++;
                        //barresi qutation
                        u=fgetc(fp);
                        if(u==EOF)
                            break;
                        string[counter-1] = u;
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
                    //backward true
                    int i ,j;
                    string[counter]=fgetc(fp);
                    for(i = chand-1 ,j =0  ; i>=0 ; j++ ,  i--)
                        clipboard[j] = string[counter-i];
                        clipboard[j+1]='\0';
                    break;
                }
                else if(flag=='f'){
                    //forward true
                    for(int i = 0 ; i<chand ; i++)
                        clipboard[i]=fgetc(fp);
                    clipboard[chand] = '\0';
                    break;
                }

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
    printf("copy successfully\n");
}

void cut(char *a){
    copy(a);
    removes(a);
    printf("cut successfully\n");
}
char * tabdil(char *a){
    char path[NUM];
    char *t;
    char string[NUM] = " --str ";
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
    a = tabdil(a);
    if(a==NULL){
        printf("not correct command\n");
        return ;
    }
    insertstr(a);
}

int ch_enter(char *string){
    int counter = 0;
    for(int i = 0 ; i<strlen(string) ; i++){
        if(string[i]=='\n')
            counter++;
    }
}

int check_featf(int a , int b , int c , int d){
    if(a == 1 && b==0 && c==0 && d==0)
        return 1;
    else if(a == 0 && b==1 && c==0 && d==0)
        return 1;
    else if(a == 0 && b==0 && c==1 && d==0)
        return 1;
    else if(a == 0 && b==0 && c==0 && d==1)
        return 1;
    else if(a == 0 && b==0 && c==0 && d==0)
        return 2;
    else if(a == 0 && b==0 && c==1 && d==1)
        return 3;
    else{
        return 0;
    }
}

int FindSearch(FILE*file ,char * string){
    char c;
    int counter = 0;
    int flag = 1;
    int max = 0;
    int t = strlen(string);
    char * search = calloc(NUM , sizeof(char));
    if(string[t-1]=='*'){
        string[t-1]='\0';
        t = t -1 ;
    }
    while(1){
        if(feof(file)){
            break;
        }
        c=fgetc(file);
        if(c=='*'){
            search[counter]='\\';
            counter++;
        }
        search[counter] = c;
        flag = 1;
            int i , j;
            for(i=0 , j=t-1 ; i<t ; i++ , j--){
                if(search[counter-j] != string[i]) {
                    flag =0;
                    break;
                }
            }
            if(flag==1 ){
                return counter - t + 1;
            }

        counter++;
    }
    return -1;
}

void find(char *a){
    char *path = get_path(a);
    int count = 0 ,  at = 0 , all = 0 , byword = 0;
    char string[NUM];
    char * b;
    int check;
    int counter = 0;
    strcpy(string , getstring(a));
    char *token;
    b = strstr(a , "file");
    token = strtok(b , "-");
    while(token!=NULL){
        if((!strncmp(token , "at " , 4)) || (!strncmp(token , "at" , 4)))
            at++;
        else if(!(strncmp(token , "all " , 5)) || (!strncmp ( token , "all" , 4)))
            all++;
        else if((!strncmp(token , "count " , 7)) || (!strncmp(token , "count" , 6)))
            count++;
        else if((!strncmp(token , "byword " , 8)) || (!strncmp(token , "byword" , 7)))
            byword++;
        token = strtok(NULL , "-");
    }
    printf("at : %d , all : %d , count : %d , byword : %d\n" ,at , all , count , byword);
    check = check_featf(count , at , byword , all);
    if(check==0)
        return;
    if(check==2){  //simple find
        FILE * fp = fopen(path , "r");
        if(fp==NULL){
            printf("it's not correct address or file name\n");
            return;
        }
        counter = FindSearch(fp , string);
        fclose(fp);
        printf("%d\n" ,counter);
    }
}

void undo(char *a){

}

//handle \* in find
