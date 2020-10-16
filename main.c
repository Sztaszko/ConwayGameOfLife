#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>

#define ARR 22
#define COL 22

enum state{DEAD,ALIVE};
unsigned char board[ARR][COL];

unsigned int down(unsigned int y)
{
    return (y+1)%COL;
}
unsigned int up(unsigned int y)
{
    return(y+(COL-1))%COL;
}
unsigned int left(unsigned int x)
{
    return (x+1)%ARR;
}
unsigned int right(unsigned int x)
{
    return (x+(ARR-1))%ARR;
}
unsigned char liczenie_zywych_sasiadow( unsigned char board[ARR][COL],
                                       unsigned int i, unsigned int j)
{
    return board[i][down(j)]
        +board[i][up(j)]
        +board[left(i)][j]
        +board[right(i)][j]
        +board[right(i)][down(j)]
        +board[right(i)][up(j)]
        +board[left(i)][down(j)]
        +board[left(i)][up(j)];
}
void nastepny_krok(unsigned char board[ARR][COL])
{
    static unsigned char swap[ARR][COL];
    int i,j;
    for(i=0;i<ARR;i++)
        for(j=0;j<COL;j++){
            unsigned char state = board[i][j];
            unsigned char zywi_sasiedzi = liczenie_zywych_sasiadow(board,i,j);
            if (state == ALIVE && zywi_sasiedzi<2)
                swap[i][j]=DEAD;
            if (state==ALIVE && zywi_sasiedzi>3)
                swap[i][j]=DEAD;
            if (state==ALIVE && (zywi_sasiedzi==2 || zywi_sasiedzi==3))
                swap[i][j]=ALIVE;
            if (state==DEAD && zywi_sasiedzi==3)
                swap[i][j]=ALIVE;
        }
    memcpy(board,swap,ARR*COL);
}

void my_random(char board[ARR][COL])
{
    int i,j,k;
    srand(time(NULL));
    for(k=0;k<50;k++){
        i=rand()%10;
        j=rand()%10;
        board[i][j]=ALIVE;
        int choice = rand()%8;
        switch(choice){
        case 0 :
        board[i][up(j)]=ALIVE;
        case 1:
        board[i][down(j)]=ALIVE;
        case 2:
        board[left(i)][j]=ALIVE;
        case 3:
        board[right(i)][j]=ALIVE;
        case 4:
        board[right(i)][down(j)]= ALIVE;
        case 5:
        board[right(i)][up(j)]=ALIVE;
        case 6:
        board[left(i)][down(j)]=ALIVE;
        case 7:
        board[left(i)][up(j)]=ALIVE;
        case 8:
        board[i+2][j-2]=ALIVE;
        case 9:
        board[i-2][j+2]=ALIVE;
        }
    }
}



/*void premade_start(unsigned char board[ARR][COL]){
int x,y,b=1;

while(b>0){
printf("Wpisz komorki ktore chcesz ozywic. By zakonczyc wpisz q:");
x=getchar();
printf("\n2ga wspolrzedna:");
y=getchar();
board[x][y]=ALIVE;

}

}
*/


void create_ten_in_row(unsigned char board[ARR][COL]){
memset(( void*)&board[ARR/2-1][COL/2-6],ALIVE,10);
}


void create_blinker( unsigned char board[ARR][COL])
{ board[ARR/2-1][COL/2-1] = board[ARR/2][COL/2-1]= board[ARR/2+1][COL/2-1] = ALIVE;
}


void seed_board(unsigned char board[ARR][COL])
{
    int i,j,k;
    srand(time(NULL));
    for (k=0;k<8;k++){
        i=rand()%8;
        j=rand()%8;
        board[i][j]=ALIVE;
        int choice = rand()%8;
        switch(choice){
        case 0 :
        board[i][up(j)]=ALIVE;
        case 1:
        board[i][down(j)]=ALIVE;
        case 2:
        board[left(i)][j]=ALIVE;
        case 3:
        board[right(i)][j]=ALIVE;
        case 4:
        board[right(i)][down(j)]= ALIVE;
        case 5:
        board[right(i)][up(j)]=ALIVE;
        case 6:
        board[left(i)][down(j)]=ALIVE;
        case 7:
        board[left(i)][up(j)]=ALIVE;
        }
    }
}

void print_board(unsigned char board[ARR][COL])
{
    int i,j;
    for(i=0;i<ARR;i++){
        printf("\n");
        for(j=0;j<COL;j++){
            printf("%2d",board[i][j]);
        }
    }
    printf("\n");
}

int main()
{   int a=1;
    //seed_board(board);
    //create_ten_in_row(board);
    //create_blinker(board);
    my_random(board);
    //premade_start(board);
    while(a>0) {
        print_board(board);
        Sleep(200);
        nastepny_krok(board);
        if( kbhit() )
             if( getch() == 'k' || getch()=='K') return 0;

        system("cls");
        //while(getchar()=='k'||getchar()=='K') return 0;
    }
}
