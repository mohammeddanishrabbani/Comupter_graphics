#include <GL/glut.h>
#include <math.h>
#include <iostream>
void init()
{
        glClearColor(0, 0, 0, 0);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0, 640, 0, 480);
}




void setPixel(GLint x, GLint y)
{
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
}



void lines(int x1, int y1, int x2, int y2)
{
        int dx, dy, i, e;
        int incx, incy, inc1, inc2;
        int x,y;
        dx = x2-x1;
        dy = y2-y1;
        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        incx = 1;
        if (x2 < x1) incx = -1;
        incy = 1;
        if (y2 < y1) incy = -1;
        x = x1; y = y1;
        if (dx > dy)
        {
            setPixel(x, y);
            e = 2 * dy-dx;
            inc1 = 2*(dy-dx);
            inc2 = 2*dy;
            for (i=0; i<dx; i++)
            {
                if (e >= 0)
                {
                        y += incy;
                        e += inc1;
                }
                else
                e += inc2;
            x += incx;
            setPixel(x, y);
            }
        }

        else
        {
            setPixel(x, y);
            e = 2*dx-dy;
            inc1 = 2*(dx-dy);
            inc2 = 2*dx;
            for (i=0; i<dy; i++)
            {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
            e += inc2;
            y += incy;
            setPixel(x, y);
            }
        }
}







void axes()
{
        int x1 = 0, x2 = 640, y1 = 0, y2 = 480;
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);
    int x = x1, y = y1;
//drawing x axis
    while (x <= x2)
    {
        setPixel(x, 240);
        x++;
    }
//drawing y axis
    while (y <= y2)
    {
        setPixel(320, y);
        y++;
    }
// drawing lines

        lines(320,240,640,480);
        lines(0,480,320,240);
        lines(0,0,320,240);
        lines(640,0,320,240);
        glFlush();
}





int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(0, 0);
glutInitWindowSize(640, 480);
glutCreateWindow("Bresenham line drawing");
init();
glutDisplayFunc(axes);
glutMainLoop();
return 0;
}
