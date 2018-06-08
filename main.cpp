#include <GL/gl.h>
#include<stdio.h>
#include <GL/glut.h>
#include "game.h"
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <iostream>
//elmoshkla kant fe 2ny 2shel el glut.h mlooosh lazma
#define COLUMNS 40
#define ROWS 40


void frontsreen();
void setFont();
void *currentfont;
void drawstring();
void display();
extern int FPS;
extern int score;
extern short sDirection;
bool gameOver=false;
extern bool Help ;
int score=0,flag=0;;
void timer_callback(int);
void display_callback();
void keyboard_callback(int,int,int);
void ToggleHelp();

GLfloat red=0,blue=1,green=.3;


const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18 ;
const int font3=(int)GLUT_BITMAP_8_BY_13;


char s[30];
void renderBitmapString(float x, float y, void *font,const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}
void setFont(void *font)
{
    currentfont=font;
}




void drawstring(float x,float y,char *string) //writing function
{
    char *c;
    glRasterPos2i(x,y);

    for(c=string; *c!='\0'; c++)
    {
        glColor3f(0.0,0.0,0.0);
        glutBitmapCharacter(currentfont,*c);
    }
    glutSwapBuffers();
}



//score display
void scoredisp()
{
    // glColor3f(1,1,1);
    glRasterPos2i(15,38);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'S');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'C');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'O');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'R');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'E');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,' ');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,':');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,' ');
    char _score[4];
    itoa(score,_score,10);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,_score[0]);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,_score[1]);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,_score[2]);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,_score[3]);

}


void frontscreen()
{
    // Backgound
    glColor3f(1.00, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(0,500);
    glVertex2f(500,500);
    glColor3f(.4,.6,0);
    glVertex2f(500,0);
    glVertex2f(0,0);
    glEnd();



    //Menu Place Holder

    glColor3f(.8,.6,.1);
    glBegin(GL_POLYGON);
    glVertex2f(7,5);
    glVertex2f(7,13);
    glVertex2f(35,13);
    glVertex2f(35,5);
    glEnd();


    //Text Information in Frist Page
    if(gameOver)
    {
         glColor3f(.9,.9,0);
        glBegin(GL_POLYGON);
        glVertex2f(7,24);
        glVertex2f(7,31);
        glVertex2f(30,31);
        glVertex2f(30,24);
        glEnd();
        glColor3f(1.000, 0.000, 0.000);
        renderBitmapString(10,28,(void *)font1,"GAME OVER");
        glColor3f(1.000, 0.000, 0.000);
        char buffer2 [50];
        sprintf (buffer2, "Your Score is : %d", score);
        renderBitmapString(10,26,(void *)font1,buffer2);
        //   exit(0);


    }


    glColor3f(0.0, 0.000, 0.00);
    renderBitmapString(10,32,(void *)font2,"SNAKE GAME ");

    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(10,22,(void *)font2,"Hint: Desperate ? \n ");
    renderBitmapString(10,17,(void *)font1,"Press X :') ");
    glColor3f(0.000, 0.000, 1.000);
    renderBitmapString(10,10,(void *)font3,"Use Arrows to Move ");
    renderBitmapString(10,7,(void *)font3,"Don't hit the Side boarder");

}




void init()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(50.0,600.0,0.0,600.0,-600,600);
    glClearColor(0.2,0.7,0,1.0);
    initGrid(COLUMNS,ROWS-3);

}

void reshape_callback(int h, int w)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0); //coordinates of the window at reshaping
    glMatrixMode(GL_MODELVIEW);




}



void processKeys(unsigned char key, int x, int y)
{

    switch (key)
    {
    case ' ':

             if(flag==0){
                flag = 1;
                init_game();
        break;

    case 27:
        exit(0);
        break;
    case 'x':
        ToggleHelp();
        break;
    default:
        break;
    }
}
}

void startGame()
{
     drawGrid();
    drawSnake();
    drawFood();
    scoredisp();

}

int main(int argc,char **argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(600,600);
    glutCreateWindow("SNAKE ");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    glutKeyboardFunc(processKeys );
    init();
    glutMainLoop();
    return 0;

}


void display_callback()
{


   glClear(GL_COLOR_BUFFER_BIT);

if(flag==1){

        startGame();
    }
    else{
        frontscreen();


    }
    glFlush();
    glutSwapBuffers();



}



void timer_callback(int)
{
    if(blue!=0&&green!=0&&red!=0)
    {
        blue-=.004;
        green-=.004;
        red-=0.005;
    }
    else
    {
        blue+=.004;
        green+=.004;
        red+=0.005;
    }

    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}

void keyboard_callback(int key,int,int)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)
            sDirection=UP;
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;
    }

}

void ToggleHelp()
{
    if (Help)
        Help = false;
    if(!Help)
        Help = true;
}

