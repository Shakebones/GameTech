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
Missile g_missile;
VFXEpoch::Vector2Df target(220, 360);

CANICurveTracking* g_pAnimation;
float timeElapsed;

void Timer(int p)
{
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 0);
}

static void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1280.0, 0.0, 720.0);

	// Initialize missile parameters
	g_missile.pos = VFXEpoch::Vector2Df(640, 360);
	g_missile.vel = VFXEpoch::Vector2Df(1.0f, 1.0f);
	g_missile.fuel = 100.0f;

	g_pAnimation = new CANICurveTracking;
	if (!g_pAnimation)
		exit(-1);
}

void Draw()
{
	clock_t begin = GetTickCount();
	glPointSize(10.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	g_missile.fuel -= timeElapsed;
	float fuleScalingdown = g_missile.fuel / 100.0f;
	g_missile.fuel <= 0.0f ? glColor3f(1.0f, 0.2f, 0.1f) : glColor3f(0.0f, fuleScalingdown, 0.0f);
	
	glBegin(GL_POINTS);

	// TODO: Animate the points
	VFXEpoch::Vector2Df tarVec = target;
	if (g_pAnimation->_isHit(g_missile.pos, tarVec, 5.0f))
	{
		cout << "Destroyed" << endl;
		g_missile.pos = VFXEpoch::Vector2Df(640, 360);
		g_missile.vel = VFXEpoch::Vector2Df(1.0, 1.0f);
		g_missile.fuel = 100.0f;
	}

	else
	{
		bool result;
		result = g_pAnimation->_isCollinear_same_direction(g_missile.vel, g_missile.pos, tarVec);
		if (!result)
		{
			g_pAnimation->_tracking(tarVec - g_missile.pos, g_missile.vel, 1.0f);
		}
		g_pAnimation->_move(g_missile.pos, g_missile.vel, 3.0f);
	}
	glVertex3f(g_missile.pos.m_x, g_missile.pos.m_y, 0);

	glColor3f(1.0f, 0.0f, 0.0f);
	target = VFXEpoch::Vector2Df(g_mousePos.x, 720 - g_mousePos.y);
	glVertex3f(target.m_x, target.m_y, 0);

	glEnd();
	glFlush();

	glutPostRedisplay();
	glutSwapBuffers();
	clock_t end = GetTickCount();
	timeElapsed = (end - begin) / 1000.0f;

	float fpsControl = 1000 / 60 - timeElapsed;
	Sleep(fpsControl);
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
	if (0 == g_mousePos.state) 
		return;
	else
	{
		g_mousePosChange.x = x;
		g_mousePosChange.y = y;
		g_mousePos.x = g_mousePosChange.x;
		g_mousePos.y = g_mousePosChange.y;
		cout << "Mouse at <" << g_mousePos.x << "," << g_mousePos.y << ">" << endl;
	}
}

void Resize(int width, int height)
{
	glutReshapeWindow(1280, 720);
}

void Shutdown()
{
	if (g_pAnimation)
	{
		delete g_pAnimation;
		g_pAnimation = NULL;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Homing missile");
	glutReshapeFunc(Resize);
	Init();
	glutTimerFunc(20, Timer, 0);
	glutDisplayFunc(Draw);
	glutSpecialFunc(KeyboardEvent);
	glutMouseFunc(MouseEvent);
	glutMotionFunc(MouseMotionFunc);
	glutMainLoop();
	Shutdown();

	::system("Pause");
	return 0;
}