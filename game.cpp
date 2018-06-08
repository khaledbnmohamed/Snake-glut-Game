#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"
#include <windows.h>
#include <math.h>
#include <stdio.h>

//int posX[MAX+1]={4,3,2,1,0,-1,-1};
//int posY[MAX+1]={10,10,10,10,10,10,10};
extern int FPS=10;
bool seedflag = false;
int chance;
int gridX,gridY;
short sDirection=RIGHT;
extern bool gameOver;
extern bool food= true;
extern bool Badfood= false;
int foodX,foodY;
int BadfoodX1,BadfoodY1;
int BadfoodX2,BadfoodY2;
int BadfoodX3,BadfoodY3;
int posX[60]= {20,20,20,20,20},posY[60]= {20,19,18,17,16};
int snake_length=5;
extern int score,flag;
GLfloat red1=0,blue1=1,green1=.3;
void SnakeColor();
extern bool Help = false;


void initGrid(int x, int y)
{
    gridX=x;
    gridY=y;
}


void unit(int x,int y)
{
    glLoadIdentity();
    if(x==0 ||y==0 ||x==gridX-1 || y==gridY-1)
    {
        glLineWidth(3.0);
        glColor3f(0.2,0.6,00);
        glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1);
        glVertex2f(x,y+1);
        glEnd();
    }
    else
    {

        glColor3f(.4,.4,0);
        glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(gridX-1,y);
        glVertex2f(gridX-1,gridY-1);
        glVertex2f(x,gridY-1);
        glEnd();

    }


}

void drawGrid()
{
    for(int x=0; x<gridX; x++)
    {
        for(int y=0; y<gridY; y++)
        {
            unit(x,y);
        }
    }

}

void drawFood()
{
    if(Help)
    {
        food=false;
        // Help=false;
    }
    if(food)
        random(foodX,foodY);
        srand(time(NULL));

    food=true;  ///bt3'er mkan el akl kol shwia if true

    glColor3f(1.0,1.0,1.0);
    glRectf(foodX,foodY,foodX+1,foodY+1);

    ///////////////////////bad food drawing

    randomBad(BadfoodX1,BadfoodY1);

    Badfood=false;  ///bt3'er mkan el akl kol shwia if true

    glColor3f(1.0,0.0,0.0);
    glRectf(BadfoodX1,BadfoodY1,BadfoodX1+1,BadfoodY1+1);

        randomBad(BadfoodX3,BadfoodY3);

    glRectf(BadfoodX3,BadfoodY3,BadfoodX3+1,BadfoodY3+1);
        randomBad(BadfoodX2,BadfoodY2);

    glRectf(BadfoodX2,BadfoodY2,BadfoodX2+1,BadfoodY2+1);


}


void drawSnake()
{
    for(int i =snake_length-1; i>0; i--)
    {
        posX[i]=posX[i-1];
        posY[i]=posY[i-1];
    }
    for(int i=0; i<snake_length; i++)
    {
        glColor3f(red1,blue1,green1);
        if(i==0)
        {
            glColor3f(0.0,0.0,1.0);
            switch(sDirection)
            {
            case UP:
                posY[i]++;
                break;
            case DOWN:
                posY[i]--;
                break;
            case RIGHT:
                posX[i]++;
                break;
            case LEFT:
                posX[i]--;
                break;
            }
            if(posX[0]==0|| posX[0]==gridX-1||posY[0]==0||posY[0]==gridY-1)
            {
                gameOver=true;
                flag=0;
            }
            else if(posX[i]==foodX && posY[i]==foodY)
            {

                food=true;
                score++;
                snake_length++;
                SnakeColor();
                Help=false;
                //bnlon elt3ban kol mra yakol

                // if(snake_length%10==0)
                FPS+=3;
                if(FPS>=30)
                    FPS=30;



            } //badFood
            else if(posX[i]==BadfoodX1 && posY[i]==BadfoodY1|| posX[i]==BadfoodX2 && posY[i]==BadfoodY2 || posX[i]==BadfoodX3 && posY[i]==BadfoodY3)
            {

                Badfood=true;
                score--;
                snake_length--;
                SnakeColor();
                Help=false;
                //bnlon elt3ban kol mra yakol
                SnakeColorBlack();
                // if(snake_length%10==0)
                FPS-=5;
                if(FPS>=30)
                    FPS=30;



            }
            for(int j=1; j<snake_length; j++)
            {
                if(posX[j]==posX[0] && posY[j]==posY[0])
                    snake_length=j;
                score=j-4;

            }
        }
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);

    }

}


void random(int &x,int &y)
{

    int _maxX=gridX-2;
    int _maxY=gridY-2;
    int _min=1;
    x=_min+rand()%(_maxX-_min);
    y=_min+rand()%(_maxY-_min);


}
void randomBad(int &x,int &y)
{

    int _maxX=gridX-2;
    int _maxY=gridY-2;
    int _min=1;
    x=_min+rand()%(_maxX-_min);
    y=_min+rand()%(_maxY-_min);


}

void init_game()
{
    posX[0]=20;
    posX[1]=20;
    posX[2]=20;
    posX[3]=20;
    posX[4]=20;
    posY[0]=20;
    posY[1]=19;
    posY[2]=18;
    posY[3]=17;
    posY[4]=16;
    score=0;
    snake_length=5;
    sDirection=RIGHT;
    food= true;
    FPS=10;
    red1=0;
    blue1=1;
    green1=.3;
}

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

void SnakeColor()
{

    blue1 = float_rand(0.0,1.0);
    green1 = float_rand(0.0,1.0);
    red1 = float_rand(0.0,1.0);

}
void SnakeColorBlack()
{

    blue1 = 0.0;
    green1 = 0.0;
    red1 = 0.0;

}
void Togglefood()
{
    if (food)
        food = false;
    if(!food)
        food = true;
}
