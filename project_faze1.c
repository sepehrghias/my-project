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
void ReplaceAt(char *string , int at , char *str1 , char *str2);
void cat(char* a);
int check_file(char *a);
char *getstring(char *a);
char* tabdil(char *a);
void removes(char *a);
void copy(char *a);
void cut(char *a);
void paste(char *a);
int ch_enter(char *string);
void GetStringR (char *a , char *str1  , char * str2);
void replace(char *a);
void find(char *a);
int check_featf(int a , int b , int c , int d);
void undo(char *a);
int FindSearch(FILE*file ,char * string , int word[] , int charc[]);
int SpecialFind(char *string , FILE *file);
int chand_space(char * string);
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
        else if(!strncmp(a , "replace --str1 "  , strlen("replace --str1"))){
            replace(a);
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

char *getstring(char*a) {
    int counter = 0;
    int count = 0;
    char string[400] = {'\0'};
    a = strstr(a, "--str");
        while (1) {
            if ((a[counter + 6] == ' ' && a[counter + 7] == '-' && a[counter + 8] == '-' && a[counter + 9] == 'p' &&a[counter + 10] == 'o')
                || (a[counter + 6] == ' ' &&a[counter + 7] == '-' && a[counter + 8] == '-' && a[counter + 9] == 'f' &&a[counter + 10] == 'i' && a[counter + 11] == 'l')
                ||(a[counter + 6] == ' ' &&a[counter + 7] == '-' && a[counter + 8] == '-' && a[counter+9]=='s' && a[counter+10]=='t' && a[counter+11]=='r'
                && a[counter+12]=='2')) {
                break;
            }
            if ((a[counter + 6] == '"' && a[counter + 7] == ' ' && a[counter + 8] == '-' && a[counter + 9] == '-' &&
                 a[counter + 10] == 'p' && a[counter + 11] == 'o') || (a[counter + 6] == '"' && a[counter + 7] == ' ' &&
                 a[counter + 8] == '-' && a[counter + 9] == '-' &&a[counter + 10] == 'f' &&
                 a[counter + 11] == 'i' &&a[counter + 12] == 'l') ||( a[counter+6]=='"' && a[counter + 7] == ' ' &&a[counter + 8] == '-' && a[counter + 9] == '-' &&
                 a[counter+10]=='s' && a[counter+11]=='t' && a[counter+12]=='r'&& a[counter+13]=='2')) {
                break;
            }
            if (a[counter] == '\0') {
                char *b = "FALSE RESULT";
                return b;
            }
            if(a[counter+5]=='1' || a[counter+5]=='2')
                counter++;

            if (a[counter + 6] == '"') {
                counter++;
                string[count] = a[counter + 6];
                counter++;
                count++;
                continue;
            }
            if (a[counter + 6] == '\\' && a[counter + 7] == '"') {
                counter++;
                string[count] = a[counter + 6];
                counter++;
                count++;
                continue;
            }
            string[count] = a[counter + 6];
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
    if(line==0 || word==0 || flag=='\0'){
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

/*void find_evethi(int word[] , int l[] ,char * string , FILE * fp){
    char c;
    char * search = calloc(NUM , sizeof(char));
    int counter=0 , counterw = 0;
    while(1){
        if(feof(fp))
            break;
        c=fgetc(fp);

    }
}*/

int SpecialFind (char * string , FILE * file){
    char * search = calloc(NUM , sizeof(char));
    char c;
    int counter = 0 , max = -1 , flag = 1 , l=1;
    int t = strlen(string);
    while(1){
        if(feof(file)){
            break;
        }
        l=1;
        c = fgetc(file);
        if(c=='*'){
            search[counter]='\\';
            counter++;
        }
        search[counter] = c;
        flag =1;
        int i , j;
        for(i =1 , j = t-2 ; i<t ; i++ , j--) {
            if (search[counter - j] != string[i]) {
                flag = 0;
                break;
            }
        }
            if(flag==1){
                while ((search[counter-t+2 - l]!=' ') && ( counter-t+2-l!=-1))
                    l++;
                max = counter - t + 3 -l;
            }
        counter++;
    }
    return max;
}

int chand_space(char * string){
    int space = 0;
    for(int i = 0 ; i<strlen(string) ; i++){
        if(string[i]==' ')
        space++;
    }
    return space;
}

int FindSearch(FILE*file ,char * string , int word[] , int l[]){
    char c;
    int space;
    int counter = 0 , counterw = 0;
    int flag = 1 , max = -1 , h = 0;
    int t = strlen(string);
    char * search = calloc(NUM , sizeof(char));
    if(string[t-1]=='*'){
        string[t-1]='\0';
        t = t -1 ;
    }
    if(string[0]=='*'){
        counter = SpecialFind(string , file);
        return counter;
    }
    space = chand_space(string);
    while(1){
        if(feof(file)){
            break;
        }
        c=fgetc(file);
        if(c=='*'){
            search[counter]='\\';
            counter++;
        }
        if(c==' '){
            counterw++;
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
                word[h]=counterw - space;
                l[h]=counter - t + 1;
                h++;
                if(h==1) {
                    max = counter - t + 1;
                }
            }

        counter++;
    }
    word[h]=-10;
    l[h]=-10;
    return max;
}

void find(char *a){
    char *path = get_path(a);
    int count = 0 ,  at = 0 , all = 0 , byword = 0;
    char string[NUM];
    char * b;
    int  ate;
    int   word[100]  ={-10};
    int  charc[100]={-10};
    int check;
    int counter = 0;
    strcpy(string , getstring(a));
    char *token;
    b = strstr(a , "file");
    token = strtok(b , "-");
    while(token!=NULL){
        if((!strncmp(token , "at " , 3)) || (!strncmp(token , "at" , 2))) {
            at++;
            sscanf(token , "at %d" , &ate);
        }
        else if(!(strncmp(token , "all " , 4)) || (!strncmp ( token , "all" , 3)))
            all++;
        else if((!strncmp(token , "count " , 6)) || (!strncmp(token , "count" , 5)))
            count++;
        else if((!strncmp(token , "byword " , 7)) || (!strncmp(token , "byword" , 6)))
            byword++;
        token = strtok(NULL , "-");
    }
    printf("at : %d , all : %d , count : %d , byword : %d\n" ,at , all , count , byword);
    check = check_featf(count , at , byword , all);
    if(check==0) {
        printf("these features is not come with together");
        return;
    }
    if(check==2){  //simple find
        FILE * fp = fopen(path , "r");
        if(fp==NULL){
            printf("it's not correct address or file name\n");
            return;
        }
        counter = FindSearch(fp , string ,word ,charc);
        fclose(fp);
        printf("%d\n" ,counter);
    }
    if(check==1){
        FILE * fp = fopen(path , "r");
        if(fp==NULL){
            printf("it's not correct address or file name\n");
            return;
        }
        FindSearch(fp , string , word , charc);
        fclose(fp);
        if(count ==1){
            int i = 0;
            while(charc[i]!=-10)
                i++;
            printf("counted : %d\n" , i);
            return;
        }
        else if(at==1){
            int i =0 ;
            while(charc[i]!=-10){
                if(i+1==ate) {
                    printf("this word repeated %d times\n" , ate);
                    return;
                }
                i++;
            }
            printf("this word not repeated %d times\n" , ate);
            return;
        }
        else if(byword){
            if(word[0]!=-10)
            printf("it starts at word : %d\n" , word[0]);
            else
                printf("not found this word in text\n");
            return;
        }
        else if(all){
            int i = 0;
            while(charc[i]!=-10){
                if(charc[i+1]!=-10)
                printf("%d , ",charc[i]);
                else
                    printf("%d\n" , charc[i]);
                i++;
            }

            return;
        }
    }
    if(check==3){
        FILE * fp = fopen(path , "r");
        if(fp==NULL){
            printf("it's not correct address or file name\n");
            return;
        }
        FindSearch(fp , string , word , charc);
        fclose(fp);
        int i=0;
        while(word[i]!=-10){
            if(i==0){
                printf("word is find in :\n");
            }
            if(i!=0 && (word[i]==word[i-1])){
                i++;
                continue;
            }
            printf("%d\n",word[i]);
            i++;
        }
    }
return;
}

/*void GetStringR(char *a , char * str1 , char * str2 ){
    char * c ;
    c= strstr(a , "--str");
    str1 = getstring(c);
    c = c+3;
    str2 = getstring(c);

}*/

void ReplaceAt(char * string , int at , char *str1 ,char *str2){
    int a = 1;
    char *pos , temp[NUM];
    int index = 0 ,  olen;
    int index1 = 0;
    olen = strlen(str1);
    strcpy(temp, string);
    while((pos=strstr(temp , str1))!=NULL){
        index = strlen(string)-strlen(pos);
        index1 = pos - temp;
        if(at==a || at==0) {
            string[index] = '\0';
            strcat(string, str2);
            strcat(string, temp + index1 + olen);
        }

        if(at==a)
            break;
        strcpy(temp , string + index + 1 );
        a++;
    }
}

void replace(char * a){
    char *path = get_path(a);
    int at=0 , all=0 , ate;
    char str1[100];
    char string[300];
    char str2[100];
    char *c;
    strcpy(str1 , getstring(a));
    c= strstr(a , "--str");
    c = c + 4;
    strcpy(str2 , getstring(c));
    if((!strcmp(str1 , "FALSE RESULT")) || (!strcmp(str2 , "FALSE RESULT"))){
        printf("not correct command\n");
        return;
    }
    printf("str 1 :%s , str 2 :%s\n" , str1 , str2);
    c = strtok(a ,"-");
    while(c!=NULL){
        if((!strncmp(c , "at " , 3)) || (!strncmp(c , "at" , 2))) {
            at++;
            sscanf(c , "at %d" , &ate);
        }
        else if(!(strncmp(c , "all " , 4)) || (!strncmp ( c , "all" , 3)))
            all++;
        c = strtok(NULL , "-");
    }
    printf("at : %d , all : %d\n" , at , all);
    FILE *fp = fopen(path , "r");
    while(fgets(string , 300 , fp));
    fclose(fp);
    if(at==1)
        ReplaceAt(string , ate , str1 ,str2);
    else if(all)
         ReplaceAt(string , 0 ,str1 , str2);
    else
        ReplaceAt(string , 1 , str1 , str2);
    FILE *file = fopen(path , "w");
    fputs(string , file);
    fclose(file);
    return;
}

void undo(char *a){

}

//handle \* in find
//handle *name to featrues