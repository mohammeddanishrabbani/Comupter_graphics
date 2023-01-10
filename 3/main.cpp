#include<stdlib.h>
#include<GL/glut.h>
GLfloat vertices[] = { -1, -1, -1,
1, -1, -1,
1, 1, -1,
-1, 1, -1,
-1, -1, 1,
1, -1, 1,
1, 1, 1,
-1, 1, 1
};


GLfloat colors[] =
{ 0, 0, 0,
1, 0, 0,
1, 1, 0,
0, 1, 0,
0, 0, 1,
1, 0, 1,
1, 1, 1,
0, 1, 1
};


GLubyte cubeIndices[]={0,3,2,1,
                       2,3,7,6,
                       0,4,7,3,
                       1,2,6,5,
                       4,5,6,7,
                       0,1,5,4,
                        };


static GLfloat theta[]= {0, 0, 0}; // initial angles
static GLint axis=2;
// let us assume the right mouse button has been clicked initially
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef (theta[0], 1, 0, 0);// first angle rotation via x axis
    glRotatef (theta[1], 0, 1, 0);// second angle rotation via y axis
    glRotatef (theta[2], 0, 0, 1);// third angle rotation via z axis



    glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,cubeIndices); // draw the cube
    glutSwapBuffers();
    // show the output
}


void spinCube()
{
    theta[axis] += 2;
    // rotate every 2 degrees
    if (theta[axis] > 360)
        theta[axis] -= 360;
    glutPostRedisplay();
    // it the rotation angle crosses 360 degrees, make it 0 degree
    // call display again
}
void mouse(int btn, int state, int x, int y)
{
    if (btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        axis=0;
// x axis rotation
    if (btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
        axis=1;
// y axis rotation
    if (btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
        axis=2;
// z axis rotation
}


void myReshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
            glOrtho (-2, 2, -2*(GLfloat)h/(GLfloat)w, 2*(GLfloat)h / (GLfloat)w, -10, 10);
    else
        glOrtho (-2*(GLfloat)w/(GLfloat)h, 2*(GLfloat)w / (GLfloat)h, -2, 2, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Spin a color cube");
    glutReshapeFunc(myReshape); // calls myReshape whenever we change the window size
        glutDisplayFunc(display); // call display function
    glutIdleFunc(spinCube); // whenever we are idle, calls spinCube function
    glutMouseFunc(mouse); // calls mouse function whenever we interact with mouse
    glEnable(GL_DEPTH_TEST); // enables depth – for 3D
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    // enables colour and vertex properties
    glVertexPointer(3, GL_FLOAT, 0, vertices); // glVertexPointer(size,type,stride,pointer)
    glColorPointer(3, GL_FLOAT, 0, colors);
    // glColorPointer(size,type,stride,pointer)
    glColor3f(1, 1, 1);
    glutMainLoop();
}
