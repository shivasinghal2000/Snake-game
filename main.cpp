#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<cstdlib>
#include<unistd.h>
#include<conio.h>
using namespace std;

bool gameover; // to check game is over or not
int tailx[50],taily[50]; // to maintain tali position
int ntail; // to maintain length of tail
const int width = 20; // to set width of game
const int height = 20; // to set height of game
int x,y; // to show current location (x and y coordinates) of a player
int fruitx,fruity; //to show current position (x and y coordinates) of fruit
int score; // to maintain score of player

// function to clear the screen since system("cls") was not working
void cls()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

// to initialize all variables in beginning of game
void settings()
{
    gameover=false;
    // player will start from center
    x= width/2;
    y=height/2;
    // to place fruit at any random position
    fruitx= rand()%width;
    fruity= rand()%height;
    score=0;
}

// to set up the border of the game
void visual()
{
    cls();
    cout<<"CONTROLS KEY ARE : \n";
    cout<<" < for LEFT \n";
    cout<<" > for RIGHT \n";
    cout<<" ^ for UP \n";
    cout<<" \\/ for DOWN \n";
    cout<<endl;
    for(int i=0;i<width+1;i++){
        cout<<"#";
    }
    cout<<endl;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0 || j==width-1)
                cout<<"#";
            if(i==y && j==x) //to display our snake
                cout<<"0";
            else if(i==fruity && j==fruitx)
                cout<<"*";
            else{
                bool printtail=false;
                for(int k=0;k<ntail;k++){
                    if(tailx[k]==j && taily[k]==i){
                        cout<<"O";
                        printtail=true;
                    }
                }
                if(!printtail)
                cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<width+1;i++){
        cout<<"#";
    }
    cout<<endl;
    cout<<"SCORE: "<<score<<endl;
}

void logic()
{
    int prevx=tailx[0];
    int prevy=taily[0];
    int prev2x,prev2y;
    tailx[0]=x;
    taily[0]=y;
    for(int i=1;i<ntail;i++){
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]=prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
    }
    if (GetAsyncKeyState(VK_LEFT)){
            if(x<0)
            x=width-3;
            else
            x--;
            visual();
    }
    else if (GetAsyncKeyState(VK_RIGHT)){
            if(x>=width-2)
            x=0;
            else
            x++;
            visual();
    }
    else if (GetAsyncKeyState(VK_UP)){
        y--;
        visual();
    }
    else if (GetAsyncKeyState(VK_DOWN)){
        y++;
        visual();
    }
    else
    {
        visual();
    }
    if(x>width-2)
        x=0;
    else if(x<0)
        x=width-2;
    if(y>height)
        y=0;
    else if(y<0)
        y=height;
    for(int i=0;i<ntail;i++){
        if(tailx[i]==x && taily[i]==y)
            gameover=true;
    }
    if(x==fruitx && y==fruity)
    {
        score++;
        fruitx= rand()%width;
        fruity= rand()%height;
        ntail++;
    }
}
int main()
{
    settings();
    while(!gameover)
    { //while game is not not over
        visual();
        logic();
        Sleep(700);
    }
    return 0;
}
