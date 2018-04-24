#include <GL/gl.h>
#include <GL/glut.h>

void display_callback();
void reshape_callback();

void init()
{
glClearColor(1.0,1.0,0.0,1.0);

}

int main(int argc,char **argv)
{

    glutInit(&argc,argv); //initializing glut
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Snake");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    init();
    glutMainLoop();
    return 0;

}
void reshape_callback(int w , int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,40.0,0.0,40.0,-1.0,1.0); //coordinates of the window at reshaping
    glMatrixMode(GL_MODELVIEW);




}
void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers(); //swap buffer for double buffer

}
