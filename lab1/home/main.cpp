#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "cmath"
#include "unistd.h"
void sky(bool night)
{

    if (night)
        glColor3f(0,0,(float)110/255);
    else
        glColor3f(0,0,1);

    glBegin(GL_QUADS);
    glVertex2f(-1.0f,1.0f);
    glVertex2f(1.0f,1.0f);
    glVertex2f(1.0f,0.0f);
    glVertex2f(-1.0f,0.0f);
    glEnd();
}

void ground (bool night)
{
    if (night)
        glColor3f(0,(float)110/255,0);
    else
        glColor3f(0,1,0);

    glBegin(GL_QUADS);
    glVertex2f(-1.0f,0.0f);
    glVertex2f(1.0f,0.0f);
    glVertex2f(1.0f,-1.0f);
    glVertex2f(-1.0f,-1.0f);
    glEnd();
}

void house (bool night)
{
    if (night)
        glColor3f((float)110/255,(float)110/255,0);
    else
        glColor3f(1,1,0);

    glBegin(GL_QUADS);
    glVertex2f(-0.75f,-0.5f);
    glVertex2f(-0.25f,-0.5f);
    glVertex2f(-0.25f,-1.0f);
    glVertex2f(-0.75f,-1.0f);
    glEnd();

    if (night)
        glColor3f((float)110/255,0,0);
    else
        glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.8f,-0.5f);
    glVertex2f(-0.2f,-0.5f);
    glVertex2f(-0.5f,-0.0f);
    glEnd();
}

void sun (bool night)
{
    for (int j = 0; j < 250; j++) {
        if (night)
            glColor3f(1,1,1);
        else
            glColor3f(1,1,0);

        glBegin(GL_TRIANGLE_FAN);
        GLfloat rad = 0.1f;
        GLfloat cx = -1.0f - rad*2 + (float)j/100;
        GLfloat cy = 0.5f;
        glVertex2f(cx, cy);
        for (int i = 0; i < 360; i++) {
            GLfloat x = cx + rad * cos(i * 2.0f * M_PI / 360);
            GLfloat y = cy + rad * sin(i * 2.0f * M_PI / 360);
            glVertex2f(x, y);
        }
        usleep(10000);
        glEnd();
//        glutSwapBuffers();
        glFlush();
        sky(night);
    }
}

void draw() {
    while (1)
        for (int i = 0; i <= 1; i++) {
            glClear(GL_COLOR_BUFFER_BIT);
            sky(i);
            ground(i);
            house(i);
            sun(i);
            glutSwapBuffers();
        }
}


void init()
{
    glClearColor(1.0,1.0,0.0,1.0);
//    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
//    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}