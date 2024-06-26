#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

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

void mainHead() {
	glBegin(GL_POLYGON);
	//Front
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.8, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.8, 0.0, 1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.2, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.2, 0.0, 0.0);

	//Right 1
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.2, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.2, 0.0, 1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.5, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);

	//Right 2
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.5, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.5, 1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.2, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.2, 1.0, 0.0);

	//Behind
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.2, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.2, 1.0, 1.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.8, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.8, 1.0, 0.0);

	//Left 1
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.8, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.8, 1.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, 0.5, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, 0.5, 0.0);

	//Top
	glTexCoord2f(0.3, 1);
	glVertex3f(1.0, 0.5, 1);
	glTexCoord2f(0.7, 1);
	glVertex3f(0.8, 0, 1);
	glTexCoord2f(1, 0.5);
	glVertex3f(0.2, 0, 1);
	glTexCoord2f(0.7, 0);
	glVertex3f(0, 0.5, 1);
	glTexCoord2f(0.3, 0);
	glVertex3f(0.2, 1.0, 1);
	glTexCoord2f(0, 0.5);
	glVertex3f(0.8, 1.0, 1);

	//Left 2
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 0.5, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.8, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.8, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, 0.5, 1.0);

	//Bottom
	glTexCoord2f(0.3, 1.0);
	glVertex3f(0.2, 0.0, 0.0);
	glTexCoord2f(0.7, 1.0);
	glVertex3f(0.0, 0.5, 0.0);
	glTexCoord2f(1.0, 0.5);
	glVertex3f(0.2, 1.0, 0.0);
	glTexCoord2f(0.7, 0.0);
	glVertex3f(0.8, 1.0, 0.0);
	glTexCoord2f(0.3, 0.0);
	glVertex3f(1.0, 0.5, 0.0);
	glTexCoord2f(0.0, 0.5);
	glVertex3f(0.8, 0.0, 0.0);
	glEnd();
}

void Horn(float sizeX, float sizeY, float sizeZ) {
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, sizeY, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, sizeY, sizeZ);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, 0.0, sizeZ);

	glTexCoord2f(0, 1);
	glVertex3f(0.0, 0.0, sizeZ);
	glTexCoord2f(1, 1);
	glVertex3f(sizeX, 0.0, sizeZ);
	glTexCoord2f(1, 0);
	glVertex3f(sizeX, sizeY, sizeZ);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, sizeY, sizeZ);

	glTexCoord2f(0, 1);
	glVertex3f(0.0, sizeY, sizeZ);
	glTexCoord2f(1, 1);
	glVertex3f(sizeX, sizeY, sizeZ);
	glTexCoord2f(1, 0);
	glVertex3f(sizeX, sizeY, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, sizeY, 0.0);

	glTexCoord2f(0, 1);
	glVertex3f(0.0, sizeY, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(sizeX, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(sizeX, sizeY, 0.0);

	glTexCoord2f(0, 1);
	glVertex3f(sizeX, sizeY, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(sizeX, sizeY, sizeZ);
	glTexCoord2f(1, 0);
	glVertex3f(sizeX, 0.0, sizeZ);
	glTexCoord2f(0, 0);
	glVertex3f(sizeX, 0.0, 0.0);

	glTexCoord2f(0, 1);
	glVertex3f(sizeX, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(sizeX, 0.0, sizeZ);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 0.0, sizeZ);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void Eye() {
	glColor3f(0.53, 0.81, 0.92);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(0.05, 0.05);
	glTexCoord2f(1, 1);
	glVertex2f(0.25, 0.05);
	glTexCoord2f(1, 0);
	glVertex2f(0.25, 0.2);
	glTexCoord2f(0, 0);
	glVertex2f(0.05, 0.2);
	glEnd();

	glColor3f(0.53, 0.81, 0.92);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(-0.05, 0.05);
	glTexCoord2f(1, 1);
	glVertex2f(-0.25, 0.05);
	glTexCoord2f(1, 0);
	glVertex2f(-0.25, 0.2);
	glTexCoord2f(0, 0);
	glVertex2f(-0.05, 0.2);
	glEnd();
}

void Mouth() {
	glColor3f(0.69, 0.7, 0.72);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.7);             
	glVertex2f(-0.3, 0.0);
	glTexCoord2f(0.5, 1.0);
	glVertex2f(0.3, 0.0);
	glTexCoord2f(1.0, 0.7);
	glVertex2f(0.3, 0.3);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(0.0, 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-0.3, 0.3);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.3, 0.0);
	glVertex2f(0.3, 0.0);
	glVertex2f(0.3, 0.3);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.3, 0.3);
	glEnd();
}

void mouthLine() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-0.3, 0.3);
	glVertex2f(-0.2, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.0, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.3, 0.3);
	glVertex2f(0.2, 0.0);
	glEnd();
}

void foreHead() {
	glColor3f(0.69, 0.7, 0.72);
	glBegin(GL_QUADS);
	glTexCoord2f(0.2, 1.0);
	glVertex2f(-0.2, 0.25);
	glTexCoord2f(0.8, 1.0);
	glVertex2f(0.2, 0.25);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(0.3, 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-0.3, 0.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2, 0.25);
	glVertex2f(0.2, 0.25);
	glVertex2f(0.3, 0.5);
	glVertex2f(-0.3, 0.5);
	glEnd();
}

void Ear() {
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0, 1);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.0, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.0, 1.3);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, 0.0, 1.0);

	//left
	glTexCoord2f(0, 1);
	glVertex3f(0.0, 0.0, 1.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 1.2, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, 1.2, 1.0);
	
	//back
	glTexCoord2f(0, 1);
	glVertex3f(0.0, 1.2, 1.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, 1.2, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 1.2, 0.3);
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 1.2, 1.3);

	//top
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 1.2, 1.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, 1.2, 1.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.0, 1.3);

	//right
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.0, 1.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 1.2, 1.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 1.2, 0.3);
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.0, 0.3);

	//bottom
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.0, 0.3);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 1.2, 0.3);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 1.2, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void earLine() {
	glBegin(GL_LINE_LOOP);
	//front
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.15, 0.0, 0.3);
	glVertex3f(0.15, 0.0, 1.3);
	glVertex3f(0.0, 0.0, 1.0);

	//left
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 1.2, 0.0);
	glVertex3f(0.0, 1.2, 1.0);

	//back
	glVertex3f(0.0, 1.2, 1.0);
	glVertex3f(0.0, 1.2, 0.0);
	glVertex3f(0.15, 1.2, 0.3);
	glVertex3f(0.15, 1.2, 1.3);

	//top
	glVertex3f(0.15, 1.2, 1.3);
	glVertex3f(0.0, 1.2, 1.0);
	glVertex3f(0.0, 0.0, 1.0);
	glVertex3f(0.15, 0.0, 1.3);

	//right
	glVertex3f(0.15, 0.0, 1.3);
	glVertex3f(0.15, 1.2, 1.3);
	glVertex3f(0.15, 1.2, 0.3);
	glVertex3f(0.15, 0.0, 0.3);

	//bottom
	glVertex3f(0.15, 0.0, 0.3);
	glVertex3f(0.15, 1.2, 0.3);
	glVertex3f(0.0, 1.2, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void backHead() {
	glColor3f(0.69, 0.7, 0.72);
	glBegin(GL_QUADS);
	glTexCoord2f(0.2, 1.0);
	glVertex2f(-0.2, 0.25);
	glTexCoord2f(0.8, 1.0);
	glVertex2f(0.2, 0.25);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(0.3, 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-0.3, 0.5);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2, 0.25);
	glVertex2f(0.2, 0.25);
	glVertex2f(0.3, 0.5);
	glVertex2f(-0.3, 0.5);
	glEnd();

	glColor3f(0.69, 0.7, 0.72);
	glBegin(GL_QUADS);
	glTexCoord2f(0.2, 1.0);
	glVertex2f(-0.3, -0.5);
	glTexCoord2f(0.8, 1.0);
	glVertex2f(0.3, -0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(0.15, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(-0.15, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.3, -0.5);
	glVertex2f(0.3, -0.5);
	glVertex2f(0.15, 0.0);
	glVertex2f(-0.15, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-0.2, 0.25);
	glVertex2f(-0.15, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.2, 0.25);
	glVertex2f(0.15, 0.0);
	glEnd();
}

void backCover() {
	glBegin(GL_POLYGON);
	glTexCoord2f(0.8, 0.0);
	glVertex2f(0.8, 0.0);
	glTexCoord2f(1.0, 0.5);
	glVertex2f(1.0, 0.5);
	glTexCoord2f(0.8, 1.0);
	glVertex2f(0.8, 1.0);
	glTexCoord2f(0.2, 1.0);
	glVertex2f(0.2, 1.0);
	glTexCoord2f(0.0, 0.5);
	glVertex2f(0.0, 0.5);
	glTexCoord2f(0.2, 0.0);
	glVertex2f(0.2, 0.0);
	glEnd();
}

void robotHead() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	GLuint textureArr[5];                                          

	glPushMatrix();
	textureArr[2] = loadTexture("dark_grey.bmp");
	glTranslatef(-0.5, -0.5, 0.0);
	glColor3f(0.48, 0.5, 0.5);
	mainHead();
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glPushMatrix();
	textureArr[1] = loadTexture("eye.bmp");
	glTranslatef(0.0, 0.0, -0.001);
	Eye();
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	textureArr[4] = loadTexture("steel.bmp");
	glTranslatef(0.0, -0.5, -0.001);
	Mouth();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.5, -0.002);
	mouthLine();
	glPopMatrix();

	glPushMatrix();
	textureArr[4] = loadTexture("steel.bmp");
	glTranslatef(0.0, 0.0, -0.001);
	foreHead();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	glPushMatrix();
	textureArr[3] = loadTexture("tire.bmp");
	glTranslatef(0.1, 0.3, -0.05);
	glRotatef(90, 0.0, 0.0, 1.0);
	glColor3f(0.14, 0.15, 0.15);
	Horn(0.4, 0.2, 0.5);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	glPushMatrix();
	textureArr[0] = loadTexture("blue.bmp");
	glRotatef(270, 1.0, 0.0, 0.0);
	glTranslatef(0.35, -1.05, -0.5);
	glColor3f(0.0, 0.0, 1.0);
	Ear();
	glColor3f(0.0, 0.0, 0.0);
	earLine();
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	textureArr[0] = loadTexture("blue.bmp");
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-0.5, -0.15, -0.8);
	glColor3f(0.0, 0.0, 1.0);
	Ear();
	glColor3f(0.0, 0.0, 0.0);
	earLine();
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	textureArr[4] = loadTexture("steel.bmp");
	glTranslatef(0.0, 0.0, 1.001);
	backHead();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	glPushMatrix();
	textureArr[2] = loadTexture("dark_grey.bmp");
	glTranslatef(-0.5, -0.5, 1.0);
	glColor3f(0.48, 0.5, 0.5);
	backCover();
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void display() {
	glRotatef(0.1, 0.0, 1.0, 0.0);
	glPushMatrix();
	glScalef(0.7, 0.7, 0.5);
	robotHead();
	glPopMatrix();
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