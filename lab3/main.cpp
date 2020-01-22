#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/glut.h>
#include <math.h>
//#include "SOIL.h"
#define WIN_HEIGHT 750
#define WIN_WIDTH 750

GLfloat ox_rotation = 0;  //  for oct rotation
GLfloat dx_rotation = 0.5;
GLfloat oy_rotation = 0;
GLfloat dy_rotation = 0;
GLuint cube;
GLfloat light_pos [] = {0, 0, 0, 1};
bool light_on = true;
GLfloat sun_rotation = 1;
GLfloat dx_sun_rotation = 1;
int sun_mode = 1;
bool visibility = true;
bool cube_flag = false;

GLint opened = 0;

void Draw () {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if (!visibility)
			{
				glEnable(GL_BLEND);
				glDepthMask(GL_FALSE);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else
			{
				glDepthMask(GL_TRUE);
				glDisable(GL_BLEND);
			}
    if (cube_flag)
        glCallList(cube);        
    //  Light and sphere
    glLoadIdentity();
    glTranslatef (0, 0, -12);
    glRotatef((sun_rotation), 0, 1, 0);
    glTranslatef (0, 0, -10);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric();
    glColor3d(1,1,0);
    gluQuadricDrawStyle(quadObj, GLU_LINE);
    gluSphere(quadObj, 1, 10, 10);

    //  Oct
    glLoadIdentity();
    glTranslatef (0, 0, -5);
    glRotatef((ox_rotation), 0, 1, 0);
    glRotatef((oy_rotation), 1, 0, 0);
	
    glBegin(GL_TRIANGLES);
    glColor4f(0.0, 1.0, 0.0, 0.5);  /// 123 - green
    glNormal3d(-1, -1, 1);
    //  (1, 1, -1)
	glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0+opened, 2+opened, 0-opened);
	glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0+opened, 0+opened, -2-opened);
	glTexCoord2f(1.0f, 1.0f);
    glVertex3f(2+opened, 0+opened, 0-opened);

    glColor4f(1.0, 0.0, 0.0,0.5);  ///134 - red
    glNormal3d(-1, -1, -1);
    //  (1, 1, 1)
    glVertex3f(0+opened, 2+opened, 0+opened);
    glVertex3f(2+opened, 0+opened, 0+opened);
    glVertex3f(0+opened, 0+opened, 2+opened);

    glColor4f(0.0, 0.0, 1.0, 0.5);  /// 145 - blue
    glNormal3d(1, -1, -1);
    //  (-1, 1, 1)
    glVertex3f(0-opened, 2+opened, 0+opened);
    glVertex3f(0-opened, 0+opened, 2+opened);
    glVertex3f(-2-opened, 0+opened, 0+opened);

    glColor4f(0.0, 1.0, 1.0, 0.5);  /// 236 - light blue
    glNormal3d(1, -1, -1);
    //  (1, -1, -1)
    glVertex3f(0+opened, 0-opened, -2-opened);
    glVertex3f(2+opened, 0-opened, 0-opened);
    glVertex3f(0+opened, -2-opened, 0-opened);

    glColor4f(1.0, 1.0, 0.0, 0.5);  /// 346 - yellow
    glNormal3d(-1, 1, -1);
    // (1, -1, 1)
    glVertex3f(0+opened, 0-opened, 2+opened);
    glVertex3f(2+opened, 0-opened, 0+opened);
    glVertex3f(0+opened, -2-opened, 0+opened);

    glColor4f(1.0, 0.0, 1.0, 0.5);  /// 456 - purple
    glNormal3d(-1, -1, 1);
    //  (-1, -1, 1)
    glVertex3f(0-opened, 0-opened, 2+opened);
    glVertex3f(-2-opened, 0-opened, 0+opened);
    glVertex3f(0-opened, -2-opened, 0+opened);

    glColor4f(1.0, 0.5, 0.0, 0.5);  /// 125 - orange
    glNormal3d(-1, 1, -1);
    //  (-1, 1, -1)
    glVertex3f(0-opened, 2+opened, 0-opened);
    glVertex3f(0-opened, 0+opened, -2-opened);
    glVertex3f(-2-opened, 0+opened, 0-opened);

    glColor4f(1.0, 0.0, 0.0, 0.5);  /// 256 - rgb
    glNormal3d(1, 1, 1);
    //  (-1, -1, -1)
    glVertex3f(0-opened, 0-opened, -2-opened);
    glColor4f(0.0, 1.0, 0.0, 0.5);
    glVertex3f(-2-opened, 0-opened, 0-opened);
    glColor4f(0.0, 0.0, 1.0, 0.5);
    glVertex3f(0-opened, -2-opened, 0-opened);

    glEnd();
    glutSwapBuffers();
}

void draw_cube() {
    glColor4f(1.0, 0, 1.0, 1.0);
    glNewList(cube, GL_COMPILE);
        for(int i = 0; i < 31; i++) {
                glBegin(GL_LINE_LOOP);
                    glVertex3f(-20, 20 - i * 1.5, 20);
                    glVertex3f(20, 20 - i * 1.5, 20);
                    glVertex3f(20, 20 - i * 1.5, -20);
                    glVertex3f(-20, 20 - i * 1.5, -20);
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glVertex3f(20 - i * 1.5, 20, 20);
                    glVertex3f(20 - i * 1.5, -20, 20);
                    glVertex3f(20 - i * 1.5, -20, -20);
                    glVertex3f(20 - i * 1.5, 20, -20);
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glVertex3f(-20, 20, 20 - i * 1.5);
                    glVertex3f(20, 20, 20 - i * 1.5);
                    glVertex3f(20, -20, 20 - i * 1.5);
                    glVertex3f(-20, -20, 20 - i * 1.5);
                glEnd();

        }
    glEndList();
}
void ChangeSize(GLsizei w, GLsizei h) {
    if (h == 0)
        h = 1;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, (GLdouble)w/h, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, (GLdouble)w, (GLdouble)h);

    Draw ();
}

void TimerFunction (int value) {
    glutPostRedisplay();
    glutTimerFunc(10,TimerFunction,1);
    ox_rotation+=dx_rotation;
    oy_rotation+=dy_rotation;
    sun_rotation += dx_sun_rotation;
}

void glutNormalKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'c':
            cube_flag = !cube_flag;
            std::cout << cube_flag << std::endl;
            break;
		case 'x':
			visibility = !visibility;
			
			break;
        case 'a':
            dx_rotation = -0.5;
            break;
        case 'd':
            dx_rotation = 0.5;
            break;
        case 'w':
            dy_rotation = -0.5;
            break;
        case 's':
            dy_rotation = 0.5;
            break;
        case 'q':
            dy_rotation = 0;
            dx_rotation = 0;
            break;
        case 'e':
            if (!opened)
                opened = 1;
            else
                opened = 0;
            break;
        case 'r':
            if (sun_mode>=0)
            {
                sun_mode--;
                dx_sun_rotation--;
            }
            else
            {
                sun_mode = 1;
                dx_sun_rotation=1;
            }
            break;
        case 'z':
            exit(0);
            break;
        case 'f':
            if (light_on)
                glDisable(GL_LIGHT0);
            else
                glEnable(GL_LIGHT0);
            light_on = !light_on;
            break;
        default:
            break;
    }
}

int main(int argc,char** argv) {
    std::cout << "w - turn up\ns - turn down\na - turn left\nd - turn right\nq - stop rotation\ne - open octahedron\nf - invert the light\nr - change sun mode\nx - visibility mode\nz - exit\n" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("Octahedron");
    cube = glGenLists(1);
    draw_cube();
    std::cout << "cube"<< std::endl;
    glutDisplayFunc(Draw);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(5, TimerFunction, 0.5);
    glutKeyboardFunc(glutNormalKeys);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GEQUAL, 0.5);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}