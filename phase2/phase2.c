#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include<stdlib.h>
#include <curses.h>
#include <dirent.h>

#include <sys/stat.h>

#include <sys/types.h>
#define NUM 10000;

char output[10000];
char command_str[10000];
int status = 0;
void command_mode(WINDOW * command);
void input_vim(char * a){
return ;
}

int main(){
    while(1){
   initscr();
   noecho();
   int b;
   cbreak();
   int maxx , maxy;
   getmaxyx(stdscr , maxy , maxx);
   WINDOW * mode = newwin(4 , 26 , maxy -10 , 1);
   refresh();
   box(mode , 0 , 0);
   if(status==0)
   mvwprintw(mode , 1 , 12 , "normal");
   else if(status==1)
    mvwprintw(mode , 1 , 12 , "visual");
    else if(status==2)
    mvwprintw(mode , 1 , 12 , "insert");

   wrefresh(mode);
   move(maxy - 4 , 2);
    WINDOW * mode1 = newwin(4 , 38 , maxy -10 , 26);
   refresh();
   box(mode1 , 0 , 0);
   wrefresh(mode1);

   WINDOW * win = newwin(maxy - 10 , 8 , 1 ,1);
   refresh();
   box(win , 0 , 0);
   for(int i =0 ; i<maxy-12 ; i++){
      mvwprintw(win , i+1 , 3 , "%d" , i+1);
   }
   wrefresh(win);

   WINDOW * input = newwin(maxy - 10 , maxx - 8 , 1 ,8);
   refresh();
   box(input , 0 , 0);
   wrefresh(input);

   WINDOW * command = newwin(5 , 130 , maxy -7 , 1);
   refresh();
   box(command , 0 , 0);
   wrefresh(command);
        while(1){
        b = wgetch(mode);
        if(b=='/' || b==':'){
        command_mode(command);
        break;
        }
    }

   getch();
   endwin();


    }

    return 0;
   
}

void command_mode(WINDOW * command){
    int b;
    int i = 2;
    memset(command_str , '\0' , )
    while (1)
    {
        b=wgetch(command);
        if(b=='\n')
        return;
        command_str[i-2]=(char)b;
        mvwprintw(command , 2 ,i ,"%c" , b);
        i++;
    }
    
}