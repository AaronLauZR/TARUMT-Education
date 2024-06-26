#include <Windows.h>
#include <gl/GL.h>
#include <math.h>;

#define WINDOW_TITLE "OpenGL Window"

int qNo = 1;                  //question number
float x = -0.2, y = -0.22;    //origin of circle (x,y) (0,0)
float x3 = 0.2, y3 = -0.22;
float x2 = 0, y2 = 0;         //point on circle (x2,y2)
float r = 0.03;               //radius
float angle = 0;              //angle
float PI = 3.1429;            //PI
float noOfTri = 30;           //no of triangles

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
		else if (wParam == 0x31)
			qNo = 1;
		else if (wParam == 0x32)
			qNo = 2;
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

void enderdragonface() {
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);          //rightupper background
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(0.0, 0.0);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(1.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(1.0, 1.0);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 1.0);
	glEnd();

	glBegin(GL_POLYGON);          //leftupper background
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(0.0, 0.0);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(-1.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-1.0, 1.0);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 1.0);
	glEnd();

	glBegin(GL_POLYGON);          //leftlower background
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(0.0, 0.0);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(-1.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-1.0, -1.0);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -1.0);
	glEnd();

	glBegin(GL_POLYGON);          //rightlower background
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(0.0, 0.0);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(1.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(1.0, -1.0);
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, -1.0);
	glEnd();

	glBegin(GL_POLYGON);          //face
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.5, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(-0.5, -0.8);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(0.5, -0.8);
	glEnd();

	glBegin(GL_POLYGON);          //upper mouth
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, 0.0);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, 0.0);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, -0.44);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, -0.44);
	glEnd();

	glBegin(GL_POLYGON);          //lower mouth
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, -0.46);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, -0.46);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, -0.9);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, -0.9);
	glEnd();

	glBegin(GL_LINE_LOOP);        //upper mouth frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, -0.44);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, -0.44);
	glEnd();

	glBegin(GL_LINE_LOOP);        //lower mouth frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, -0.46);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, -0.46);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, -0.9);
	glEnd();

	glBegin(GL_POLYGON);          //tongue
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(0.1, -0.44);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(-0.1, -0.44);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(-0.1, -0.45);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(0.1, -0.45);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);     //left nostril
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(x, y);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);     //right nostril
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(x3, y3);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r * cos(angle);
		y2 = y3 + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);        //left nostril frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);        //right nostril frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r * cos(angle);
		y2 = y3 + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_POLYGON);          //left nose horn
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(-0.15, 0.05);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(-0.3, 0.05);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(-0.3, 0.0);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(-0.15, 0.0);
	glEnd();

	glBegin(GL_POLYGON);          //right nose horn
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(0.15, 0.05);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(0.3, 0.05);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(0.3, 0.0);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(0.15, 0.0);
	glEnd();

	glBegin(GL_POLYGON);          //left eye socket
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.2, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.35, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.35, 0.35);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.2, 0.35);
	glEnd();

	glBegin(GL_TRIANGLES);        //left eye socket triangle
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.05, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.2, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.2, 0.35);
	glEnd();

	glBegin(GL_POLYGON);         //right eye socket
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.2, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.35, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.35, 0.35);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.2, 0.35);
	glEnd();

	glBegin(GL_TRIANGLES);      //right eye socket triangle
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.05, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.2, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.2, 0.35);
	glEnd();

	glBegin(GL_POLYGON);         //left eye ball
	glColor3f(0.8, 0.0, 0.8);
	glVertex2f(-0.2, 0.15);
	glColor3f(0.8, 0.0, 0.8);
	glVertex2f(-0.3, 0.15);
	glColor3f(0.8, 0.0, 0.8);
	glVertex2f(-0.3, 0.35);
	glColor3f(0.8, 0.0, 0.8);
	glVertex2f(-0.2, 0.35);
	glEnd();

	glBegin(GL_POLYGON);         //right eye ball
	glColor3f(0.8, 0.0, 0.8);
	glVertex2f(0.2, 0.15);
	glColor3f(0.8, 0.0, 0.8);
	glVertex2f(0.3, 0.15);
	glColor3f(0.8, 0.0, 0.8);
	glVertex2f(0.3, 0.35);
	glColor3f(0.8, 0.0, 0.8);
	glVertex2f(0.2, 0.35);
	glEnd();

	glBegin(GL_LINE_LOOP);       //left eye ball frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, 0.15);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, 0.15);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.3, 0.36);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.2, 0.36);
	glEnd();

	glBegin(GL_LINE_LOOP);       //right eye ball frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, 0.15);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.3, 0.15);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.3, 0.36);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.2, 0.36);
	glEnd();

	glBegin(GL_POLYGON);         //left outter ear
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.25, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, 0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.25, 0.9);
	glEnd();

	glBegin(GL_POLYGON);         //right outter ear
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.25, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, 0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.25, 0.9);
	glEnd();

	glBegin(GL_POLYGON);         //left inner ear
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-0.2875, 0.7);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-0.3625, 0.7);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-0.3625, 0.85);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-0.2875, 0.85);
	glEnd();

	glBegin(GL_POLYGON);         //right inner ear
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.2875, 0.7);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.3625, 0.7);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.3625, 0.85);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.2875, 0.85);
	glEnd();
}

void enderdragonblink() {
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);        //rightupper background
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(1.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(1.0, 1.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.0, 1.0);
	glEnd();

	glBegin(GL_POLYGON);        //leftupper background
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-1.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(-1.0, 1.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.0, 1.0);
	glEnd();

	glBegin(GL_POLYGON);        //leftlower background
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(-1.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(-1.0, -1.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.0, -1.0);
	glEnd();

	glBegin(GL_POLYGON);        //rightlower background
	glColor3f(0.3, 0.3, 0.3);
	glVertex2f(0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(1.0, 0.0);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(1.0, -1.0);
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(0.0, -1.0);
	glEnd();

	glBegin(GL_POLYGON);        //face
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.5, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.5, 0.7);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(-0.5, -0.8);
	glColor3f(0.1, 0.1, 0.1);
	glVertex2f(0.5, -0.8);
	glEnd();

	glBegin(GL_POLYGON);        //upper mouth
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, 0.0);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, 0.0);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, -0.44);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, -0.44);
	glEnd();

	glBegin(GL_POLYGON);         //lower mouth
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, -0.46);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, -0.46);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, -0.9);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, -0.9);
	glEnd();

	glBegin(GL_LINE_LOOP);       //upper mouth frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, -0.44);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, -0.44);
	glEnd();

	glBegin(GL_LINE_LOOP);       //lower mouth frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, -0.46);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, -0.46);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, -0.9);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, -0.9);
	glEnd();

	glBegin(GL_POLYGON);         //tongue
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(0.1, -0.44);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(-0.1, -0.44);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(-0.1, -0.45);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(0.1, -0.45);
	glEnd();
	 
	glBegin(GL_TRIANGLE_FAN);    //left nostril
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(x, y);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);    //right nostril
	glColor3f(0.2, 0.2, 0.2);
	glVertex2f(x3, y3);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r * cos(angle);
		y2 = y3 + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);       //left nostril frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);       //right nostril frame
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x3 + r * cos(angle);
		y2 = y3 + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glBegin(GL_POLYGON);          //left nose horn
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(-0.15, 0.05);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(-0.3, 0.05);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(-0.3, 0.0);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(-0.15, 0.0);
	glEnd();

	glBegin(GL_POLYGON);          //right nose horn
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(0.15, 0.05);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(0.3, 0.05);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(0.3, 0.0);
	glColor3f(0.13, 0.13, 0.13);
	glVertex2f(0.15, 0.0);
	glEnd();
	 
	glBegin(GL_POLYGON);          //left eye blink
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.05, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.35, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.35, 0.2);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(-0.05, 0.2);
	glEnd();

	glBegin(GL_POLYGON);          //right eye blink
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.05, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.35, 0.15);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.35, 0.2);
	glColor3f(1.0, 0.5, 1.0);
	glVertex2f(0.05, 0.2);
	glEnd();

	glBegin(GL_POLYGON);          //left ear down
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.25, 0.7);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, 0.7);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.4, 0.52);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(-0.25, 0.52);
	glEnd();

	glBegin(GL_POLYGON);          //right ear down
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.25, 0.7);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, 0.7);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.4, 0.52);
	glColor3f(0.15, 0.15, 0.15);
	glVertex2f(0.25, 0.52);
	glEnd();

	glBegin(GL_LINE_LOOP);        //left ear down frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.25, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.4, 0.52);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.25, 0.52);
	glEnd();

	glBegin(GL_LINE_LOOP);        //right ear down frame
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.25, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, 0.7);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.4, 0.52);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.25, 0.52);
	glEnd();
}

void display()
{
	switch (qNo) {
	case 1:
		enderdragonface();
		break;
	case 2:
		enderdragonblink();
		break;
	default:
		enderdragonface();
		break;
	}
}

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
//--------------------------------------------------------------------