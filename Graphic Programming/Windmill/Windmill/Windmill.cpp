#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

float x = 1.0, y = 1.0, x3 = 0.0, y3 = 0.0, x4 = 0.0, y4 = 0.8;
float r = 0.3, r2 = 0.05, r3 = 0.5;
float angle = 0;
float PI = 3.1429;
float x2 = 0, y2 = 0;
float noOfTri = 30;

float tspeed = 0.0, speed = 0.0;
float cspeed = 0.0;

int qNo = 1;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == VK_RIGHT)
			speed += 0.01;
		else if (wParam == VK_LEFT)
			speed -= 0.01;
		else if (wParam == VK_SPACE) {
			speed = 0.0;
		}
		else if (wParam == VK_UP) {
			qNo += 1;
			if (qNo > 4) {
				qNo = 4;
			}
		}
		else if (wParam == VK_DOWN) {
			qNo -= 1;
			if (qNo < 1) {
				qNo = 1;
			}
		}
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void windmillfan() {
	glBegin(GL_QUADS);                //windmill fan
	glColor3f(0.75, 0.7, 0.55);
	glVertex2f(0.04, 0.0);
	glColor3f(0.75, 0.7, 0.55);
	glVertex2f(-0.04, 0.0);
	glColor3f(0.75, 0.7, 0.55);
	glVertex2f(-0.04, 0.6);
	glColor3f(0.75, 0.7, 0.55);
	glVertex2f(0.04, 0.6);
	glEnd();

	glBegin(GL_LINE_LOOP);            //windmill fan frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.04, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.04, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.04, 0.6);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.04, 0.6);
	glEnd();

	glBegin(GL_QUADS);                //windmill fan shadow
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.04, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.02, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.02, 0.6);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2f(0.04, 0.6);
	glEnd();

	glBegin(GL_LINE_LOOP);            //windmill fan shadow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.04, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.02, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.02, 0.6);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.04, 0.6);
	glEnd();
}

void grass() {
	glBegin(GL_LINES);
	glColor3f(0, 0.5, 0.25);
	glVertex2f(-0.7, -0.7);
	glVertex2f(-0.65, -0.65);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0.5, 0.25);
	glVertex2f(-0.65, -0.65);
	glVertex2f(-0.6, -0.7);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0.5, 0.25);
	glVertex2f(-0.6, -0.7);
	glVertex2f(-0.55, -0.65);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0.5, 0.25);
	glVertex2f(-0.55, -0.65);
	glVertex2f(-0.5, -0.7);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0.5, 0.25);
	glVertex2f(-0.5, -0.7);
	glVertex2f(-0.45, -0.65);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0.5, 0.25);
	glVertex2f(-0.45, -0.65);
	glVertex2f(-0.4, -0.7);
	glEnd();
}

void cloud() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9, 1.0, 1.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x4 + r2 * cos(angle);
		y2 = y4 + r2 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 1.0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.07, 0.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9, 1.0, 1.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x4 + r2 * cos(angle);
		y2 = y4 + r2 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 1.0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.07, 0.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9, 1.0, 1.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x4 + r2 * cos(angle);
		y2 = y4 + r2 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 1.0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.035, 0.075, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9, 1.0, 1.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x4 + r2 * cos(angle);
		y2 = y4 + r2 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 1.0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.035, 0.075, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.9, 1.0, 1.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x4 + r2 * cos(angle);
		y2 = y4 + r2 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 1.0);
	}
	glEnd();
	glPopMatrix();
}

void windmill3()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);                //ground
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	grass();

	glPushMatrix();
	glTranslatef(1.0, -0.2, 1.0);
	grass();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -0.25, 1.0);
	grass();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.3, 0.1, 1.0);
	grass();
	glPopMatrix();

	glBegin(GL_QUADS);                //sky
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.8, 1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glColor3f(0.8, 1.0, 1.0);
	glVertex2f(1.0, 1.0);
	glEnd();

	glBegin(GL_TRIANGLES);            //left mountain
	glColor3f(0.35, 0.2, 0.0);
	glVertex2f(0.0, -0.5);
	glColor3f(0.29, 0.14, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.8, 0.6, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);             //left mountain frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);             //right mountain
	glColor3f(0.39, 0.24, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(0.45, 0.3, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.9, 0.7, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);             //right mountain frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);             //left mountain snow
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(-0.375, 0.4);
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(-0.625, 0.4);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);             //left mountain snow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.375, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.625, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);             //right mountain snow
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(0.1875, 0.25);
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(0.5125, 0.25);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);             //right mountain snow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1875, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.5125, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);          //sun shine
	glColor3f(1.0, 1.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r3 * cos(angle);
		y2 = y + r3 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(0.8, 1.0, 1.0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);          //sun
	glColor3f(1.0, 0.5, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 0.0);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);             //sun frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_TRIANGLES);             //windmill roof
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.3, -0.2);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-0.3, -0.2);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.0, 0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill roof frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.3, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, 0.2);
	glEnd();

	glBegin(GL_QUADS);                 //windmill house
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(0.2, -0.9);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(-0.2, -0.9);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill house frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();

	glBegin(GL_QUADS);                   //door
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(0.1, -0.9);
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(-0.1, -0.9);
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(-0.1, -0.5);
	glColor3f(1.0, 0.75, 0.0);
	glVertex2f(0.1, -0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);                //door frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.1, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.1, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1, -0.5);
	glEnd();

	glBegin(GL_LINES);                    //door line
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.9);
	glVertex2f(0.0, -0.5);
	glEnd();

	glBegin(GL_QUADS);                    //window
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(0.075, -0.4);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-0.075, -0.4);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-0.075, -0.2);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.075, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);                //window frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.075, -0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.075, -0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.075, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.075, -0.2);
	glEnd();


	glPushMatrix();                       //windmill fan
	tspeed = tspeed + speed;
	glRotatef(tspeed, 0.0, 0.0, 1.0);

	glPushMatrix();
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(120, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(240, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPopMatrix();

	glBegin(GL_TRIANGLE_FAN);          //windmill center
	glColor3f(0.3, 0.3, 0.3);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r2 * cos(angle);
		y2 = y3 + r2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill center frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r2 * cos(angle);
		y2 = y3 + r2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glPushMatrix();
	cspeed = cspeed + 0.02;
	glRotatef(cspeed, 0.0, 1.0, 0.0);
	cloud();
	glPopMatrix();
};

void windmill4()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);                //ground
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	grass();

	glPushMatrix();
	glTranslatef(1.0, -0.2, 1.0);
	grass();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -0.25, 1.0);
	grass();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.3, 0.1, 1.0);
	grass();
	glPopMatrix();

	glBegin(GL_QUADS);                //sky
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.8, 1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glColor3f(0.8, 1.0, 1.0);
	glVertex2f(1.0, 1.0);
	glEnd();

	glBegin(GL_TRIANGLES);            //left mountain
	glColor3f(0.35, 0.2, 0.0);
	glVertex2f(0.0, -0.5);
	glColor3f(0.29, 0.14, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.8, 0.6, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);             //left mountain frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);             //right mountain
	glColor3f(0.39, 0.24, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(0.45, 0.3, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.9, 0.7, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);             //right mountain frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);             //left mountain snow
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(-0.375, 0.4);
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(-0.625, 0.4);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);             //left mountain snow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.375, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.625, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);             //right mountain snow
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(0.1875, 0.25);
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(0.5125, 0.25);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);             //right mountain snow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1875, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.5125, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);          //sun shine
	glColor3f(1.0, 1.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r3 * cos(angle);
		y2 = y + r3 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(0.8, 1.0, 1.0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);          //sun
	glColor3f(1.0, 0.5, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 0.0);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);             //sun frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_TRIANGLES);             //windmill roof
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.3, -0.2);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-0.3, -0.2);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.0, 0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill roof frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.3, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, 0.2);
	glEnd();

	glBegin(GL_QUADS);                 //windmill house
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(0.2, -0.9);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(-0.2, -0.9);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill house frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();

	glBegin(GL_QUADS);                   //door
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(0.1, -0.9);
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(-0.1, -0.9);
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(-0.1, -0.5);
	glColor3f(1.0, 0.75, 0.0);
	glVertex2f(0.1, -0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);                //door frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.1, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.1, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1, -0.5);
	glEnd();

	glBegin(GL_LINES);                    //door line
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.9);
	glVertex2f(0.0, -0.5);
	glEnd();

	glBegin(GL_QUADS);                    //window
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(0.075, -0.4);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-0.075, -0.4);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-0.075, -0.2);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.075, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);                //window frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.075, -0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.075, -0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.075, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.075, -0.2);
	glEnd();


	glPushMatrix();                       //windmill fan
	tspeed = tspeed + speed;
	glRotatef(tspeed, 0.0, 0.0, 1.0);

	glPushMatrix();
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(270, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPopMatrix();

	glBegin(GL_TRIANGLE_FAN);          //windmill center
	glColor3f(0.3, 0.3, 0.3);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r2 * cos(angle);
		y2 = y3 + r2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill center frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r2 * cos(angle);
		y2 = y3 + r2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glPushMatrix();
	cspeed = cspeed + 0.02;
	glRotatef(cspeed, 0.0, 1.0, 0.0);
	cloud();
	glPopMatrix();
};

void windmill5()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);                //ground
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	grass();

	glPushMatrix();
	glTranslatef(1.0, -0.2, 1.0);
	grass();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -0.25, 1.0);
	grass();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.3, 0.1, 1.0);
	grass();
	glPopMatrix();

	glBegin(GL_QUADS);                //sky
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.8, 1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glColor3f(0.8, 1.0, 1.0);
	glVertex2f(1.0, 1.0);
	glEnd();

	glBegin(GL_TRIANGLES);            //left mountain
	glColor3f(0.35, 0.2, 0.0);
	glVertex2f(0.0, -0.5);
	glColor3f(0.29, 0.14, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.8, 0.6, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);             //left mountain frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);             //right mountain
	glColor3f(0.39, 0.24, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(0.45, 0.3, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.9, 0.7, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);             //right mountain frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);             //left mountain snow
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(-0.375, 0.4);
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(-0.625, 0.4);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);             //left mountain snow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.375, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.625, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);             //right mountain snow
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(0.1875, 0.25);
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(0.5125, 0.25);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);             //right mountain snow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1875, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.5125, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);          //sun shine
	glColor3f(1.0, 1.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r3 * cos(angle);
		y2 = y + r3 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(0.8, 1.0, 1.0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);          //sun
	glColor3f(1.0, 0.5, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 0.0);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);             //sun frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_TRIANGLES);             //windmill roof
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.3, -0.2);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-0.3, -0.2);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.0, 0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill roof frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.3, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, 0.2);
	glEnd();

	glBegin(GL_QUADS);                 //windmill house
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(0.2, -0.9);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(-0.2, -0.9);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill house frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();

	glBegin(GL_QUADS);                   //door
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(0.1, -0.9);
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(-0.1, -0.9);
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(-0.1, -0.5);
	glColor3f(1.0, 0.75, 0.0);
	glVertex2f(0.1, -0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);                //door frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.1, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.1, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1, -0.5);
	glEnd();

	glBegin(GL_LINES);                    //door line
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.9);
	glVertex2f(0.0, -0.5);
	glEnd();

	glBegin(GL_QUADS);                    //window
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(0.075, -0.4);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-0.075, -0.4);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-0.075, -0.2);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.075, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);                //window frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.075, -0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.075, -0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.075, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.075, -0.2);
	glEnd();


	glPushMatrix();                       //windmill fan
	tspeed = tspeed + speed;
	glRotatef(tspeed, 0.0, 0.0, 1.0);

	glPushMatrix();
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(72, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(144, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(216, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(288, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPopMatrix();

	glBegin(GL_TRIANGLE_FAN);          //windmill center
	glColor3f(0.3, 0.3, 0.3);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r2 * cos(angle);
		y2 = y3 + r2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill center frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r2 * cos(angle);
		y2 = y3 + r2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glPushMatrix();
	cspeed = cspeed + 0.02;
	glRotatef(cspeed, 0.0, 1.0, 0.0);
	cloud();
	glPopMatrix();
};

void windmill6()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);                //ground
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.5, 1.0, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-1.0, -1.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	grass();

	glPushMatrix();
	glTranslatef(1.0, -0.2, 1.0);
	grass();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.25, -0.25, 1.0);
	grass();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.3, 0.1, 1.0);
	grass();
	glPopMatrix();

	glBegin(GL_QUADS);                //sky
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.8, 1.0, 1.0);
	glVertex2f(-1.0, 1.0);
	glColor3f(0.8, 1.0, 1.0);
	glVertex2f(1.0, 1.0);
	glEnd();

	glBegin(GL_TRIANGLES);            //left mountain
	glColor3f(0.35, 0.2, 0.0);
	glVertex2f(0.0, -0.5);
	glColor3f(0.29, 0.14, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.8, 0.6, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);             //left mountain frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-1.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);             //right mountain
	glColor3f(0.39, 0.24, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(0.45, 0.3, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.9, 0.7, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);             //right mountain frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(1.0, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);             //left mountain snow
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(-0.375, 0.4);
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(-0.625, 0.4);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_LINE_LOOP);             //left mountain snow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.375, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.625, 0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glEnd();

	glBegin(GL_TRIANGLES);             //right mountain snow
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(0.1875, 0.25);
	glColor3f(0.7, 1.0, 1.0);
	glVertex2f(0.5125, 0.25);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);             //right mountain snow frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1875, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.5125, 0.25);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.35, 0.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);          //sun shine
	glColor3f(1.0, 1.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r3 * cos(angle);
		y2 = y + r3 * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(0.8, 1.0, 1.0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);          //sun
	glColor3f(1.0, 0.5, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(1.0, 1.0, 0.0);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);             //sun frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_TRIANGLES);             //windmill roof
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.3, -0.2);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-0.3, -0.2);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.0, 0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill roof frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.3, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, 0.2);
	glEnd();

	glBegin(GL_QUADS);                 //windmill house
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(0.2, -0.9);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(-0.2, -0.9);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.55, 0.0, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill house frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, -0.2);
	glEnd();

	glBegin(GL_QUADS);                   //door
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(0.1, -0.9);
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(-0.1, -0.9);
	glColor3f(0.5, 0.25, 0.0);
	glVertex2f(-0.1, -0.5);
	glColor3f(1.0, 0.75, 0.0);
	glVertex2f(0.1, -0.5);
	glEnd();

	glBegin(GL_LINE_LOOP);                //door frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.1, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.1, -0.5);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.1, -0.5);
	glEnd();

	glBegin(GL_LINES);                    //door line
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.0, -0.9);
	glVertex2f(0.0, -0.5);
	glEnd();

	glBegin(GL_QUADS);                    //window
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(0.075, -0.4);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-0.075, -0.4);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(-0.075, -0.2);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.075, -0.2);
	glEnd();

	glBegin(GL_LINE_LOOP);                //window frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.075, -0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.075, -0.4);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.075, -0.2);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.075, -0.2);
	glEnd();


	glPushMatrix();                       //windmill fan
	tspeed = tspeed + speed;
	glRotatef(tspeed, 0.0, 0.0, 1.0);

	glPushMatrix();
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(60, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(120, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(240, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPushMatrix();
	glRotatef(300, 0.0, 0.0, 1.0);
	windmillfan();
	glPopMatrix();

	glPopMatrix();

	glBegin(GL_TRIANGLE_FAN);          //windmill center
	glColor3f(0.3, 0.3, 0.3);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r2 * cos(angle);
		y2 = y3 + r2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);             //windmill center frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r2 * cos(angle);
		y2 = y3 + r2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glPushMatrix();
	cspeed = cspeed + 0.02;
	glRotatef(cspeed, 0.0, 1.0, 0.0);
	cloud();
	glPopMatrix();
};

void display() {
	switch (qNo) {
	case 1:
		windmill3();
		break;
	case 2:
		windmill4();
		break;
	case 3:
		windmill5();
		break;
	case 4:
		windmill6();
		break;
	dafault:
		windmill3();
		break;
	}
}

//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//---------------------------------