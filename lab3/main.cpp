#include <iostream>
#include <time.h>
#include <cstdlib>
#include <GL/glut.h>
#include <math.h>
#include "SOIL.h"
#include "unistd.h"
#define WIN_HEIGHT 750
#define WIN_WIDTH 750

GLfloat ox_rotation = 0;
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
GLuint textures[8];
GLfloat opened = 0;
int texture_mode = 0;

void draw_colored_oct()
{
    glLoadIdentity();
    glTranslatef (0, 0, -5);
    glRotatef((ox_rotation), 0, 1, 0);
    glRotatef((oy_rotation), 1, 0, 0);

    GLfloat vertices[] = {-2-opened, 0.0+opened, 0.0+opened, //0 передняя грань
                          0.0-opened, 2+opened, 0.0+opened,  //1
                          0.0-opened, 0.0+opened, 2+opened,  //2
                          
                          0.0+opened, 0.0+opened, 2+opened,  //2 правая боковая
                          0.0+opened, 2+opened, 0.0+opened,  //1
                          2+opened, 0.0+opened, 0.0+opened,  //3
                          
                          2+opened, 0.0+opened, 0.0-opened,  //3 задняя грань
                          0.0+opened, 2+opened, 0.0-opened,  //1
                          0.0+opened, 0.0+opened, -2-opened, //4
                          
                          0.0-opened, 0.0+opened, -2-opened, //4 левая боковая
                          0.0-opened, 2+opened, 0.0-opened,  //1
                          -2-opened, 0.0+opened, 0.0-opened, //0
                          
                          -2-opened, 0.0-opened, 0.0+opened, //0 нижняя передняя грань
                          0.0-opened, -2-opened, 0.0+opened, //5
                          0.0-opened, 0.0-opened, 2+opened,  //2
                          
                          0.0+opened, 0.0-opened, 2+opened,  //2 нижняя правая грань
                          0.0+opened, -2-opened, 0.0+opened, //5
                          2+opened, 0.0-opened, 0.0+opened,  //3
                          
                          2+opened, 0.0-opened, 0.0-opened,  //3 нижняя задняя грань
                          0.0+opened, -2-opened, 0.0-opened, //5
                          0.0+opened, 0.0-opened, -2-opened, //4
                          
                          0.0-opened, 0.0-opened, -2-opened, //4 нижняя левая  грань
                          0.0-opened, -2-opened, 0.0-opened, //5
                          -2-opened, 0.0-opened, 0.0-opened, //0
                          };

   GLfloat normal[] = { //Нормали
                        1, -1, -1,
                        1, -1, -1,
                        1, -1, -1,

                        -1, -1, -1,
                        -1, -1, -1,
                        -1, -1, -1,

                        -1, -1, 1,
                        -1, -1, 1,
                        -1, -1, 1,

                        1, -1, 1,
                        1, -1, 1,
                        1, -1, 1,

                        -1, -1, 1,
                        -1, -1, 1,
                        -1, -1, 1,

                        1, -1, 1,
                        1, -1, 1,
                        1, -1, 1,

                        1, 1, -1,
                        1, 1, -1,
                        1, 1, -1,

                        -1, -1, -1,
                        -1, -1, -1,
                        -1, -1, -1,
                        };
    GLfloat texCoords[] = { 0.0, 0.0,  // Нижний левый угол
                            1.0, 0.0,  // Нижний правый угол
                            0.5, 1.0,  // верхняя центральная сторона
                            0.0, 0.0,
                            1.0, 0.0,
                            0.5, 1.0,
                            0.0, 0.0,
                            1.0, 0.0,
                            0.5, 1.0,
                            0.0, 0.0,
                            1.0, 0.0,
                            0.5, 1.0,
                            0.0, 0.0,
                            1.0, 0.0,
                            0.5, 1.0,
                            0.0, 0.0,
                            1.0, 0.0,
                            0.5, 1.0,
                            0.0, 0.0,
                            1.0, 0.0,
                            0.5, 1.0,
                            0.0, 0.0,
                            1.0, 0.0,
                            0.5, 1.0,};

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glVertexPointer(3,GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normal);

    GLubyte front_face[] = {0,1,2};             // передняя грань
    GLubyte right_side[] = {3,4,5};             // правая грань
    GLubyte back_face[] = {6,7,8};              // задняя грань
    GLubyte left_side[] = {9,10,11};            // левая грань
    GLubyte lower_front[] = {12,13,14};         // нижняя передняя грань
    GLubyte bottom_right_side[] = {15,16,17};   // нижняя правая грань
    GLubyte lower_back_face[] = {18,19,20};     // нижняя задняя грань
    GLubyte bottom_left_side[] = {21,22,23};    // нижняя левая грань

    if(texture_mode == 0) // цвета
    {
        glEnable(GL_COLOR_MATERIAL);
        glColor4f(0.00, 0.32, 0.48, 0.5);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,lower_back_face);
        glColor4f(0.18, 0.4, 0.32, 0.5);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,bottom_left_side);
        glColor4f(0.32, 0.16, 0.36, 0.5);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, bottom_right_side);
        glColor4f(0.82, 0.21, 0.0, 0.5);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, lower_front);
        glColor4f(1.0, 1.0, 1.0, 0.5);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, back_face);
        glColor4f(1.0, 0.0, 0.0, 0.5);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, front_face);
        glColor4f(1.0, 0.0, 1.0, 0.5);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, right_side);
        glColor4f(0.0, 1.0, 0.0, 0.5);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, left_side);
    }
    if(texture_mode == 2) // одна текстура
        {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,lower_back_face);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,bottom_left_side);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,bottom_right_side);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,lower_front);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,back_face);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,front_face);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,right_side);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,left_side);
        glDisable(GL_TEXTURE_2D);
    }
    if(texture_mode == 1) // несколько текстур
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,lower_back_face);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,bottom_left_side);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,bottom_right_side);
        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,lower_front);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,back_face);
        glBindTexture(GL_TEXTURE_2D, textures[5]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,front_face);
        glBindTexture(GL_TEXTURE_2D, textures[6]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,right_side);
        glBindTexture(GL_TEXTURE_2D, textures[7]);
        glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,left_side);
        glDisable(GL_TEXTURE_2D);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void Draw () {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if (!visibility)// прозрачность
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
   
    //  Oct
    glColor4f(1,1,1,0.5);
    draw_colored_oct();
   
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
    gluSphere(quadObj, 0.5, 10, 10);
   
    glutSwapBuffers();
}

void draw_cube() {
   
    glLoadIdentity();
	
    glNewList(cube, GL_COMPILE);
		glTranslatef(0,0,10); 
        glColor4f(1.0, 0.0, 0.0, 1.0);
        for(int i = 0; i < 31; i++) {
                glBegin(GL_LINE_LOOP);
                    glVertex3f(-30, 30 - i * 2, 30);
                    glVertex3f(30, 30 - i * 2, 30);
                    glVertex3f(30, 30 - i * 2, -30);
                    glVertex3f(-30, 30 - i * 2, -30);
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glVertex3f(30 - i * 2, 30, 30);
                    glVertex3f(30 - i * 2, -30, 30);
                    glVertex3f(30 - i * 2, -30, -30);
                    glVertex3f(30 - i * 2, 30, -30);
                glEnd();
                glBegin(GL_LINE_LOOP);
                    glVertex3f(-30, 30, 30 - i * 2);
                    glVertex3f(30, 30, 30 - i * 2);
                    glVertex3f(30, -30, 30 - i * 2);
                    glVertex3f(-30, -30, 30 - i * 2);
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
    if (sun_mode != 0)
        sun_rotation += dx_sun_rotation;    
}


void glutNormalKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 't':
            if (texture_mode == 2)
            {
                //glDisable(GL_TEXTURE_2D);
                texture_mode = 0;
            }
            else
            {
                //glEnable(GL_TEXTURE_2D); 
                texture_mode++;
            }
            std::cout << texture_mode <<std::endl;
            break;
        case 'c':
            cube_flag = !cube_flag;
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
                opened = 0.2;
            else
                opened = 0;
            break;
        case 'r':
            if (sun_mode>=0)
            {
                sun_mode--;
                dx_sun_rotation--;
                std::cout << sun_mode << dx_sun_rotation << std::endl;
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


void processSpecialKeys (int key, int x, int y)
{
    switch(key){
    case GLUT_KEY_LEFT:
        if(sun_mode != 0)
        {
          sun_mode = 0;// sun_rotation = 0; 
        }
         sun_rotation==360?sun_rotation=5:sun_rotation-=5;
        break;
    case GLUT_KEY_RIGHT:
       if(sun_mode != 0)
        {
            sun_mode = 0;//sun_rotation = 0;
        }
         sun_rotation==360?sun_rotation=5:sun_rotation+=5;
        break;
  
    }
    glutPostRedisplay();
}


int main(int argc,char** argv) {
    std::cout << "w - turn up\ns - turn down\na - turn left\nd - turn right\nq - stop rotation\ne - open octahedron\nf - invert the light\nr - change sun mode\nx - visibility mode\nz - exit\nt - texture mode\nc - cube mode" << std::endl;
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
    glutSpecialFunc(processSpecialKeys);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    // Texture mode
    int width[8];
    int height[8];
    unsigned char* image[8];
    if (!image)
        std::cout<<"Error: SOIL_load_image";
    glGenTextures(8, textures);

    unsigned char* image0 = SOIL_load_image("txt1.bmp", &width[0], &height[0], 0,SOIL_LOAD_RGB);
    unsigned char* image1 = SOIL_load_image("txt2.bmp", &width[1], &height[1], 0,SOIL_LOAD_RGB);
	unsigned char* image2 = SOIL_load_image("txt3.bmp", &width[2], &height[2], 0,SOIL_LOAD_RGB);
    unsigned char* image3 = SOIL_load_image("txt4.bmp", &width[3], &height[3], 0,SOIL_LOAD_RGB);
	unsigned char* image4 = SOIL_load_image("txt5.bmp", &width[4], &height[4], 0,SOIL_LOAD_RGB);
	unsigned char* image5 = SOIL_load_image("txt6.bmp", &width[5], &height[5], 0,SOIL_LOAD_RGB);
	unsigned char* image6 = SOIL_load_image("txt7.bmp", &width[6], &height[6], 0,SOIL_LOAD_RGB);
	unsigned char* image7 = SOIL_load_image("txt8.bmp", &width[7], &height[7], 0,SOIL_LOAD_RGB);
    unsigned char* images[8] = {image0, image1, image2, image3, image4, image5, image6, image7};

    for(int i=0; i<8; i++){
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[i], height[i], 0, GL_RGB, GL_UNSIGNED_BYTE, images[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    for(int i=0; i<8; i++)
    {
        SOIL_free_image_data(images[i]);
    }
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
    return 0;
}
