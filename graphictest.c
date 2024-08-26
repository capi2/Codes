#include <GL/glut.h>
#include <math.h>

#define pi 3.141592

float toRadians(int angle){
    return angle*(pi/180);
}

void display(){
    float a,b;
    float centerx = 0.1;
    float centery = 0.1;
    float radius = 0.5;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++){
        a = centerx + radius*cos(toRadians(i));
        b = centery + radius*sin(toRadians(i));
        glVertex2f(a,b);
    }
    glEnd();
    glFlush();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

//execute code: gcc graphictest.c -lGL -lGLU -lglut -o teste -lm

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}