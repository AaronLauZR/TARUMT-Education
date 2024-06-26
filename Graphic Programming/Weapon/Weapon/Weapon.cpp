#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int weapon = 1;
float x = 0.0, y = 0.0, z = 0.0;
float speed = 0.01;

BITMAP BMP;
HBITMAP hBMP = NULL;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == 0x31) {
			weapon = 1;
		}
		else if (wParam == 0x32) {
			weapon = 2;
		}
		else if (wParam == 0x33) {
			if (weapon == 2) {
				x = 0;
				y = 0;
				z = 0;
			}
		}
		break;
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

GLuint loadTexture(LPCSTR filename) {
	GLuint texture = 0; 

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	DeleteObject(hBMP);

	return texture;
}

void sickleStick(double tr, double br, double h) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, tr, br, h, 20, 20);
	gluDeleteQuadric(cylinder);
}

void sickleCorn(double tr, double br, double h) {
	glRotatef(90, 1.0, 0.0, 0.0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, tr, br, h, 10, 10);
	gluDeleteQuadric(cylinder);
}

void sickleBlade(float sz, float sh) {
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, sh);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.15, 0.0, sh);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.15, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.15 / 2, sz, sh / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, sh);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.15 / 2, sz, sh / 2);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.15 / 2, sz, sh / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.15, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.15 / 2, sz, sh / 2);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.15 / 2, sz, sh / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.15, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.15, 0.0, sh);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.15 / 2, sz, sh / 2);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.15 / 2, sz, sh / 2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.15, 0.0, sh);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.0, sh);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.15 / 2, sz, sh / 2);
	glEnd();
}

void pistolCube(float sizeX, float sizeY, float sizeZ) {
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, sizeY, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, sizeY, sizeZ);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, sizeZ);

	//top
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, sizeZ);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeX, 0.0, sizeZ);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeX, sizeY, sizeZ);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, sizeY, sizeZ);

	//back
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, sizeY, sizeZ);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeX, sizeY, sizeZ);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeX, sizeY, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, sizeY, 0.0);

	//bottom
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, sizeY, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeX, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeX, sizeY, 0.0);

	//right
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeX, sizeY, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeX, sizeY, sizeZ);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sizeX, 0.0, sizeZ);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sizeX, 0.0, 0.0);

	//front
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sizeX, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sizeX, 0.0, sizeZ);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.0, sizeZ);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void pistolLine(float sizeX, float sizeY, float sizeZ) {
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sizeY, 0.0);
	glVertex3f(0.0, sizeY, sizeZ);
	glVertex3f(0.0, 0.0, sizeZ);

	glVertex3f(0.0, 0.0, sizeZ);
	glVertex3f(sizeX, 0.0, sizeZ);
	glVertex3f(sizeX, sizeY, sizeZ);
	glVertex3f(0.0, sizeY, sizeZ);

	glVertex3f(0.0, sizeY, sizeZ);
	glVertex3f(sizeX, sizeY, sizeZ);
	glVertex3f(sizeX, sizeY, 0.0);
	glVertex3f(0.0, sizeY, 0.0);

	glVertex3f(0.0, sizeY, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(sizeX, 0.0, 0.0);
	glVertex3f(sizeX, sizeY, 0.0);

	glVertex3f(sizeX, sizeY, 0.0f);
	glVertex3f(sizeX, sizeY, sizeZ);
	glVertex3f(sizeX, 0.0, sizeZ);
	glVertex3f(sizeX, 0.0, 0.0);

	glVertex3f(sizeX, 0.0, 0.0);
	glVertex3f(sizeX, 0.0, sizeZ);
	glVertex3f(0.0, 0.0, sizeZ);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void pistolHole() {
	float x = 0.0, y = 0.0, x2 = 0, y2 = 0, r = 0.02, angle = 0, PI = 3.1429, noOfTri = 60;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 0.0, 0.0);
	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri) {
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
		glColor3f(0.35, 0.35, 0.33);
	}
	glEnd();
}

void bullet() {
	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.1);
	sickleStick(0.01, 0.01, 0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -0.15, 0.0);
	sickleCorn(0.01, 0.0, 0.05);
	glPopMatrix();
}

void sickle() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	GLuint textureArr[4];

	glPushMatrix();
	textureArr[0] = loadTexture("steel.bmp");
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.75, 0.76, 0.8);
	sickleStick(0.015, 0.015, 0.7);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	textureArr[1] = loadTexture("purple.bmp");
	glColor3f(0.44, 0.44, 0.43);
	glTranslatef(0.0, -0.7, 0.0);
	sickleCorn(0.03, 0.0, 0.15);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	textureArr[2] = loadTexture("black.bmp");
	glTranslatef(0.0, 0.2, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.44, 0.44, 0.43);
	sickleStick(0.02, 0.02, 0.2);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glPushMatrix();
	textureArr[1] = loadTexture("purple.bmp");
	glColor3f(0.44, 0.44, 0.43);
	glTranslatef(0.0, 0.2, 0.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	sickleCorn(0.03, 0.0, 0.15);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	textureArr[3] = loadTexture("blade.bmp");
	glColor3f(0.85, 0.85, 0.85);
	glTranslatef(0.0, 0.2, 0.0);
	glRotatef(-90, 0.0, 0.0, 1.0);
	sickleBlade(0.6, 0.01);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void pistol() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glRotatef(-90, 1.0, 0.0, 0.0);
	GLuint textureArr[2];
	
	//pistol body
	glPushMatrix();
	textureArr[0] = loadTexture("pistolsilver.bmp");
	glColor3f(0.83, 0.83, 0.83);
	pistolCube(0.35, 0.1, 0.1);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	pistolLine(0.35, 0.1, 0.1);
	glPopMatrix();

	//pistol handle
	glPushMatrix();
	textureArr[1] = loadTexture("brownleather.bmp");
	glTranslatef(0.05, 0.01, 0.05);
	glRotatef(110, 0.0, 1.0, 0.0);
	glColor3f(0.64, 0.66, 0.69);
	pistolCube(0.2, 0.08, 0.08);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.05, 0.01, 0.05);
	glRotatef(110, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	pistolLine(0.2, 0.08, 0.08);
	glPopMatrix();

	//pistol scope
	glPushMatrix();
	textureArr[0] = loadTexture("pistolsilver.bmp");
	glTranslatef(0.3, 0.04, 0.01);
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.64, 0.66, 0.69);
	pistolCube(0.12, 0.03, 0.03);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3, 0.04, 0.01);
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	pistolLine(0.12, 0.03, 0.03);
	glPopMatrix();

	//pistol shooting hole
	glPushMatrix();
	glTranslatef(0.355, 0.05, 0.05);
	glRotatef(90, 0.0, 1.0, 0.0);
	pistolHole();
	glPopMatrix();

	//pistol press space straight
	glPushMatrix();
	textureArr[0] = loadTexture("pistolsilver.bmp");
	glTranslatef(0.2, 0.03, -0.05);
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.64, 0.66, 0.69);
	pistolCube(0.12, 0.04, 0.02);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 0.03, -0.05);
	glRotatef(270, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	pistolLine(0.12, 0.04, 0.02);
	glPopMatrix();

	//pistol press space horizontal
	glPushMatrix();
	textureArr[0] = loadTexture("pistolsilver.bmp");
	glTranslatef(0.2, 0.03, -0.05);
	glRotatef(180, 0.0, 1.0, 0.0);
	glColor3f(0.64, 0.66, 0.69);
	pistolCube(0.12, 0.04, 0.02);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 0.03, -0.05);
	glRotatef(180, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	pistolLine(0.12, 0.04, 0.02);
	glPopMatrix();

	//pistol shooting button
	glPushMatrix();
	textureArr[0] = loadTexture("pistolsilver.bmp");
	glTranslatef(0.16, 0.043, -0.025);
	glRotatef(230, 0.0, 1.0, 0.0);
	glColor3f(0.85, 0.85, 0.85);
	pistolCube(0.08, 0.02, 0.02);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.16, 0.043, -0.025);
	glRotatef(230, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	pistolLine(0.08, 0.02, 0.02);
	glPopMatrix();
}

void bulletShoot() {
	if (x > 1.0) {
		x = 1.01;
	}
	else {
		x = x + speed;
	}

	glTranslatef(x, y, z);

	glPushMatrix();
	GLuint textureArr[1];
	textureArr[0] = loadTexture("bullet.bmp");
	glTranslatef(0.3, 0.05, 0.05);
	glColor3f(1.0, 1.0, 1.0);
	bullet();
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();
}

void shootingPistol() {
	glPushMatrix();
	pistol();
	glPopMatrix();

	glPushMatrix();
	bulletShoot();
	glPopMatrix();
}

void display() {
	switch (weapon) {
	case 1:
		bullet();
		break;
	case 2:
		shootingPistol();
		break;
	default: 
		sickle();
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
//--------------------------------------------------------------------