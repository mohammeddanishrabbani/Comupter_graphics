#include <GL/glut.h>
//#include <windows.h>
float x1,x2,x3,x4,y2,y3,y4;
float y1;
int fillFlag=0;void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
	float mx,x,temp;
	int i;
	if((y2-y1)<0)
	{
		temp=y1;y1=y2;y2=temp;
		temp=x1;x1=x2;x2=temp;
	}
	if((y2-y1)!=0)
		mx=(x2-x1)/(y2-y1);
	else
		mx=x2-x1;
	x=x1;
	for(i=y1;i<=y2;i++)
	{
		if(x<(float)le[i])
		le[i]=(int)x;
		if(x>(float)re[i])
		re[i]=(int)x;
		x+=mx;
	}
}
void draw_pixel(int x,int y)
{
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void scanfill (float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
int left_edge[500], right_edge[500];
int i, y;
for (i = 0; i <= 500; i++)
{
left_edge [i] = 500;
// fill all the left_edge values as 500 initially
right_edge [i] = 0;
// fill all the right_edge values as 0 initially
}
edgedetect (x1, y1, x2, y2, left_edge, right_edge); // first line
edgedetect (x2, y2, x3, y3, left_edge, right_edge); // second line
edgedetect (x3, y3, x4, y4, left_edge, right_edge); // third line
edgedetect (x4, y4, x1, y1, left_edge, right_edge); // fourth line
for (y = 0; y <= 500; y++)
// now that you have calculated all values, start filling
{
//from left edge to right edge row by row pixel by pixel
if (left_edge[y] <= right_edge[y])
{
for (i = left_edge[y]; i <= right_edge[y]; i++)
{
draw_pixel (i, y);
glFlush ();
}
}
}
}
void display()
{
	x1=200.0;y1=200.0;x2=100.0;y2=300.0;x3=200.0;y3=400.0;x4=300.0;y4=300.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glEnd();
	if(fillFlag==1)
	scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
	glFlush();
}
void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
void fillMenu(int option)
{
	if(option==1)fillFlag=1;
	if(option==2)fillFlag=2;
	display();
}
int main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Filling a Polygon using Scan-line Algorithm");
	init();
	glutDisplayFunc(display);
	glutCreateMenu(fillMenu);
	glutAddMenuEntry("Fill Polygon",1);
	glutAddMenuEntry("Empty Polygon",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}
