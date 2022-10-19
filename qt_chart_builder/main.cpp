#include "stdafx.h"
#include "qt_chart_builder.h"
#include <QtWidgets/QApplication>
#include "chartManager.h"
#include <thread>
#include <GL/freeglut.h>

chartManager cMgr;

void glutThrFunc(int argc, char *argv[]);
void cbIdle();
void cbDisplay();

int main(int argc, char *argv[])
{
	std::thread glutThr(glutThrFunc,argc,argv);
	glutThr.detach();
	
	QApplication a(argc, argv);
    qt_chart_builder w;
	w.cMgrPtr = &cMgr;
    w.show();	

	return a.exec();
}

void glutThrFunc(int argc, char *argv[])
{
	glutInit(&argc, argv); //initializing GLUT

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);

	glutCreateWindow("GLUT WINDOW");

	//OpenGL setup block
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//GLUT launch block
	glutIdleFunc(cbIdle);
	glutDisplayFunc(cbDisplay);

	glutMainLoop();
}

void cbIdle()
{
	if (cMgr.getCallRefresh())
	{
		cbDisplay();
		cMgr.setCallRefresh(false);
	}
}

void cbDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	cMgr.calcExtremes();
	gluOrtho2D(cMgr.getL(), cMgr.getR(), cMgr.getB(), cMgr.getT());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (cMgr.getChartSize() > 1)
	{
		glBegin(GL_LINE_STRIP);

		glColor3f(1, 0, 0);

		for (int i = 0; i < cMgr.getChartSize(); i++)
		{
			glVertex2f(cMgr.getPointX(i), cMgr.getPointY(i));
		}
	}

	glEnd();

	glutSwapBuffers();
}