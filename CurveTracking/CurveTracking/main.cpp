/*
 * main.cpp
 * Xue Cui
 * Desc:
 * The code is used for demostrating curve tracking animation
 */
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <assert.h>
#include <GL\glut.h>
#include "ANI_CurveTracking.h"

using namespace std;

typedef struct _mouse
{
	int x;
	int y;
	int state;
}Mouse;

typedef struct _missile
{
	VFXEpoch::Vector2Df vel;
	VFXEpoch::Vector2Df pos;
	float fuel;
}Missile;

static Mouse g_mousePos;
static Mouse g_mousePosChange;

static void Init()
{
	bool result;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1280.0, 0.0, 720.0);
}

void Draw()
{
	glPointSize(10.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(.0f, 1.0f, .0f, 1.0f);
	glBegin(GL_POINTS);

	// TODO: Animate the points

	glEnd();
	glFlush();

	glutPostRedisplay();
	glutSwapBuffers();
}

void KeyboardEvent(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		break;
	default:
		break;
	}
}

static void MouseEvent(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
	{
		if (state == GLUT_DOWN)
		{
			g_mousePos.x = x;
			g_mousePos.y = y;
			g_mousePos.state = 1;
		}
	}
}

static void MouseMotionFunc(GLint x, GLint y)
{
	if (0 == g_mousePos.state) return;
	g_mousePosChange.x = x;
	g_mousePosChange.y = y;
	g_mousePos.x = g_mousePosChange.x;
	g_mousePos.y = g_mousePosChange.y;
	cout << "Mouse at <" << g_mousePos.x << "," << g_mousePos.y << ">" << endl;
}

void Resize(int width, int height)
{
	glutReshapeWindow(1280, 720);
}

void Shutdown()
{
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Test");
	glutReshapeFunc(Resize);
	Init();
	glutDisplayFunc(Draw);
	glutSpecialFunc(KeyboardEvent);
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMotionFunc);
	glutMainLoop();
	Shutdown();

	::system("Pause");
	return 0;
}