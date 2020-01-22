#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "cmath"
#include "unistd.h"
#include "iostream"

void sky(bool night)
{

    if (night)
        glColor3f(0,0,(float)110/255);
    else
        glColor3f(0,0,1);

    GLfloat verts[8];
    verts[0] = -1.0f;
    verts[1] = 1.0f;
    verts[2] =1.0f;
    verts[3] =1.0f;
    verts[4] =1.0f;
    verts[5] =0.0f;
    verts[6] =-1.0f;
    verts[7] =0.0f;
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, verts );
    glDrawArrays( GL_QUADS, 0, 4);
    glDisableClientState( GL_VERTEX_ARRAY );
}


void ground (bool night)
{
    if (night)
        glColor3f(0,(float)110/255,0);
    else
        glColor3f(0,1,0);

    GLfloat verts[8];
    verts[0] = -1.0f;
    verts[1] = 0.0f;
    verts[2] =1.0f;
    verts[3] =0.0f;
    verts[4] =1.0f;
    verts[5] =-1.0f;
    verts[6] =-1.0f;
    verts[7] =-1.0f;
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, verts );
    glDrawArrays( GL_QUADS, 0, 4);
    glDisableClientState( GL_VERTEX_ARRAY );

}


void house (bool night)
{
    if (night)
        glColor3f((float)110/255,(float)110/255,0);
    else
        glColor3f(1,1,0);

    GLfloat verts[8];
    verts[0] = -0.75f;
    verts[1] = -0.5f;
    verts[2] = -0.25f;
    verts[3] =-0.5f;
    verts[4] =-0.25f;
    verts[5] =-1.0f;
    verts[6] =-0.75f;
    verts[7] =-1.0f;

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, verts );
    glDrawArrays( GL_QUADS, 0, 4);
    glDisableClientState( GL_VERTEX_ARRAY );

    if (night)
        glColor3f((float)110/255,0,0);
    else
        glColor3f(1,0,0);
    GLfloat verts1[6];
    verts1[0] = -0.8f;
    verts1[1] = -0.5f;
    verts1[2] =-0.2f;
    verts1[3] =-0.5f;
    verts1[4] =-0.5f;
    verts1[5] =-0.0f;

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, verts1);
    glDrawArrays( GL_TRIANGLES, 0, 3);
    glDisableClientState( GL_VERTEX_ARRAY );

}


void sun (bool night)
{
    for (int j = 0; j < 250; j++)
    {
        if (night)
            glColor3f(1,1,1);
        else
            glColor3f(1,1,0);

        GLfloat verts[360*2];
        GLfloat rad = 0.1f;
        GLfloat cx = -1.0f - rad*2 + (float)j/100;
        GLfloat cy = 0.5f;
        verts[0] = cx;
        verts[1] = cy;
        for (int i = 1; i < 360; i++)
        {
            GLfloat x = cx + rad * cos(i * 2.0f * M_PI / 360);
            GLfloat y = cy + rad * sin(i * 2.0f * M_PI / 360);
            verts[i*2] = x;
            verts[(i*2) + 1] = y;
        }
        glEnableClientState( GL_VERTEX_ARRAY );
        glVertexPointer( 2, GL_FLOAT, 0, verts);
        glDrawArrays( GL_TRIANGLE_FAN, 0, 360);
        glDisableClientState( GL_VERTEX_ARRAY );
        usleep(10000);
        glutSwapBuffers();
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
