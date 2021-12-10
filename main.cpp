#include <GL\glew.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

#include"shader.hpp"

int h=790,w=790;
float points[6];
float fc[7][4]=
{
	{1.0,0.0,0.0,0.0},//red
	{0.0,1.0,0.0,0.0},//green
	{0.0,0.0,1.0,0.0},//bule
	{1.0,0.0,1.0,0.0},//purple
	{1.0,1.0,0.0,0.0},//yellow
	{0.8,0.4,0.0,0.0},//brouwn
	{0.0,0.0,0.0,0.0} //black
};

int f=0;

void changeViewPort(int w1, int h1)
{
	w=w1; h=h1;
	glViewport(0, 0, w, h);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

void init(void)
{
	GLuint p=LoadShaders("vs.hpp", "fs.hpp");
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*6, points, GL_STATIC_DRAW);
	
	glUseProgram(p);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,(void*)0);

	GLuint buffer1;
	glGenBuffers(1, &buffer1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer1);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*4, fc[f], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0,(void*)0);
}

void display(void)
{
	//glClear (GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_LINES,0,2);
	glFlush ( );
}

int i=1;
float xi,yi,xf,yf;
bool b=true;

void mouse(int button, int state, int x, int y)
{
	//if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) { exit(0); }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(b)
        {       
            b=false;
           xi=(float) x / (w/2) - 1.0;
           yi=(float) (h-y) / (h/2) - 1.0; 
        }
        else
        {
			xf=(float) x / (w/2) - 1.0; 
			yf=(float) (h-y) / (h/2) - 1.0; 

			points[0]=xi;
			points[1]=yi;
			points[3]=xf;
			points[4]=yf;
			points[2]=0.0;
			points[5]=0.0;

			cout<<"Line "<<i++<<" : \n";
			cout<<xi<<","<<yi<<"_"<<xf<<","<<yf<<"\n";
			init();
			display();
			cout<<"------------------------------------------------------------------\n";
            b=true;
        }   

    }
}

void output(void)
{
	glutMouseFunc(mouse);
    glFlush(); 
}

void demo_menu(int id) 
{
	switch(id)
	{ 
	case 1:{f=0; break;}
	case 2:{f=1; break;}
	case 3:{f=2; break;}
	case 4:{f=3; break;}
	case 5:{f=4; break;}
	case 6:{f=5; break;}
	case 7:{f=6; break;}
	case 8:{ exit(0); break;}
	}
	glutPostRedisplay();
}

void main(int argc, char* args[]) 
{
	cout<<"click **** RIGHT_BUTTON ***** \n for EXIT \n***************************************\n\n";

glutInit (&argc, args); 
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (790,790);
glutInitWindowPosition (0, 0); 
unsigned int ID= glutCreateWindow ("Program");
glClearColor (1.0, 1.0, 1.0, 0.0);
glMatrixMode (GL_PROJECTION); 
gluOrtho2D (0.0, 790.0, 0.0, 790.0);
glutSetWindow(ID);

glClear (GL_COLOR_BUFFER_BIT);

glutReshapeFunc(changeViewPort);

glutDisplayFunc(render);

GLenum err = glewInit();
if (GLEW_OK != err) { fprintf(stderr, "GLEW error"); return; }
fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

glutCreateMenu(demo_menu);
glutAddMenuEntry("1- red line", 1);
glutAddMenuEntry("2- green line", 2);
glutAddMenuEntry("3- blue line", 3);
glutAddMenuEntry("4- purple line", 4);
glutAddMenuEntry("5- yellow line", 5);
glutAddMenuEntry("6- brouwn line", 6);
glutAddMenuEntry("7- black line", 7);
glutAddMenuEntry("quit", 8); 
glutAttachMenu(GLUT_RIGHT_BUTTON);

glutDisplayFunc(output);

glutMainLoop();

}