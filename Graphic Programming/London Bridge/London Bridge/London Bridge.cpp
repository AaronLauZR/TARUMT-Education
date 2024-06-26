#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

//bridge controller
float speed = 0.0, bspeed = 0.0;

//texture
BITMAP BMP;
HBITMAP hBMP = NULL;

//projection
float tx = 0, tz = 0, tSpeed = 0.05; //translate for modelview
boolean isOrtho = true;              //is ortho view
float ONear = -20, OFar = 20;        //Ortho near far
float PNear = 1, PFar = 30;          //Perspective near far
float ptx = 0, pty = 0;              //translate for projection
float pry = 0, prSpeed = 1.0;        //rotate ry for projection

//cloud controller
boolean cloudMain = false;
float cloudX = 0.0, cloudY = 0.0, cloudZ = 0.0;
float cloudSpeed = 0.01;

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
		else if (wParam == 'W') {
			speed = +0.1;
		}
		else if (wParam == 'S') {
			speed = -0.1;
		}
		else if (wParam == VK_UP) {			//Zoom In Projection
			if (isOrtho) {
				if (tz > ONear)
				{
					//Ortho view - zoom in
					tz -= tSpeed;
				}
			}
			else
			{
				if (tz > PNear + 1)
				{
					//perspective view - zoom in
					tz -= tSpeed;
				}
			}
		}
		else if (wParam == VK_DOWN) {		//Zoom Out Projection
			if (isOrtho)
			{
				if (tz < OFar)
				{
					//Ortho view - zoom out
					tz += tSpeed;
				}
			}
			else
			{
				//perspective view - zoom out
				if (tz < PFar / 2)
				{
					tz += tSpeed;
				}
			}
		}
		else if (wParam == 'O') {			//Change to Orthographic Projection
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P') {			//Change to Perspective Projection
			isOrtho = false;
			tz = 2;
		}
		else if (wParam == VK_RIGHT) {		//Translate Projection to left hand side
			tx -= tSpeed;
		}
		else if (wParam == VK_LEFT) {		//Translate Projection to right hand side
			tx += tSpeed;
		}
		else if (wParam == 'L') {			//Rotate Projection at y axis (anti-clockwise)
			pry += prSpeed;
		}
		else if (wParam == 'R') {			//Rotate Projection at y axis (clockwise)
			pry -= prSpeed;
		}
		else if (wParam == 'C') {
			cloudMain = true;
			cloudX = 0;
			cloudY = 0;
			cloudZ = 0;
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

	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

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

void projection() {
	glMatrixMode(GL_PROJECTION); //refer to projection matrix
	glLoadIdentity(); //reset projection matrix

	if (isOrtho) //----- Orthographic view -----
	{
		glRotatef(180, 0, 1, 0);
		glOrtho(0, 0, 0, 0, ONear, OFar); //left, right, bottom, top, near, far
	}
	else //----- Perspective view -----
	{
		glRotatef(180, 0, 1, 0);
		gluPerspective(20, 1, -1, 1); //fovy, aspect, near, far
		glFrustum(-1, 1, -1, 1, PNear, PFar); //xmin, xmax, ymin, ymax, -zmin(need to start from positive), -zmax
	}

	glRotatef(pry, 0, 1, 0); //Rotate projection y
	glTranslatef(ptx, pty, 0.0); //Translate projection x & y

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //Reset modelview matrix
	glTranslatef(tx, 0, tz); //Translate along the x & z axis (Translate for modelview) ***

}

void drawCube(float sx, float sy, float sz) {
	glBegin(GL_QUADS);
	//Face 1: Front 
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sx, 0.0, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sx, 0.0, 0.0);

	//Face 2: Right
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sx, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sx, sy, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sx, sy, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sx, 0.0, sz);

	//Face 3: Top
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sx, 0.0, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, sy, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sx, sy, sz);

	//Face 4: Behind
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sx, sy, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sx, sy, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, sy, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, sy, sz);

	//Face 5: Left
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, sy, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, sy, 0.0);

	//Face 6: Bottom
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, sy, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sx, sy, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sx, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawCube2(float sx, float sy, float sz) {
	glBegin(GL_QUADS);
	//Face 1: Front 
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sx, 0.0, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sx, 0.0, 0.0);

	//Face 2: Right
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sx, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sx, sy, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sx, sy, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sx, 0.0, sz);

	//Face 3: Top
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sx, 0.0, sz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, 0.0, sz);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, sy, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(sx, sy, sz);

	//Face 4: Behind
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sx, sy, sz);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sx, sy, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, sy, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, sy, sz);

	//Face 5: Left
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.0, sy, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, 0.0, sz);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, sy, 0.0);

	//Face 6: Bottom
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.0, sy, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sx, sy, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(sx, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void drawPyramid(float sz) {
	glBegin(GL_QUADS);
	// Face 1 : Bottom
	glTexCoord2f(0, 1);
	glVertex3f(0.0, 0.0, sz);
	glTexCoord2f(1, 1);
	glVertex3f(sz, 0.0, sz);
	glTexCoord2f(1, 0);
	glVertex3f(sz, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0.0, 0.0, 0.0);

	// Face 2 & 3 & 4 & 5 : go up to centre point and down to another point to create triange face
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0.0f, 0.0f, sz);
	glTexCoord2f(1.0, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0);
	glVertex3f(sz, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(sz, 0.0, 0.0);
	glTexCoord2f(1.0, 0);
	glVertex3f(sz, 0.0, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);
	glTexCoord2f(0.5, 1.0);
	glVertex3f(sz, 0.0, sz);
	glTexCoord2f(1.0, 0);
	glVertex3f(0.0, 0.0, sz);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(sz / 2, sz, sz / 2);
	glEnd();
}

void drawSphere(double radius, double slices, double stacks) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, radius, slices, stacks); 
	gluDeleteQuadric(sphere); 
}

void drawCylinder(float topRadius, float baseRadius, double height, double slices, double stacks) {
	glRotatef(90, 0.0, 1.0, 0.0);
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, topRadius, baseRadius, height, slices, stacks); 
	gluDeleteQuadric(cylinder); 
}

void display()
{
	glClearColor(0.53, 0.81, 0.98, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	GLuint textureArr[10];

	//Orthographic view & Perspective view
	projection(); 

	//background
	glPushMatrix();
	textureArr[0] = loadTexture("sky.bmp");
	drawSphere(35, 50, 50);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	//left tower base
	glPushMatrix();
	glTranslatef(-0.55, -0.5, -0.05);
	textureArr[1] = loadTexture("base.bmp");
	drawCube(0.3, 0.1, 0.3);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//right tower base
	glPushMatrix();
	glTranslatef(0.25, -0.5, -0.05);
	textureArr[1] = loadTexture("base.bmp");
	drawCube(0.3, 0.1, 0.3);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//left tower
	glPushMatrix();
	glTranslatef(-0.5, -0.4, 0.0);
	textureArr[2] = loadTexture("tower.bmp");
	drawCube(0.2, 0.7, 0.2);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	//right tower
	glPushMatrix();
	glTranslatef(0.3, -0.4, 0.0);
	textureArr[2] = loadTexture("tower.bmp");
	drawCube(0.2, 0.7, 0.2);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	//top left tower
	glPushMatrix();
	glTranslatef(-0.55, 0.3, -0.05);
	textureArr[3] = loadTexture("roof.bmp");
	drawPyramid(0.3);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	//top right tower
	glPushMatrix();
	glTranslatef(0.25, 0.3, -0.05);
	textureArr[3] = loadTexture("roof.bmp");
	drawPyramid(0.3);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	//left extra bridge
	glPushMatrix();
	glTranslatef(-1.0, -0.3, 0.0);
	textureArr[4] = loadTexture("road.bmp");
	drawCube(0.5, 0.05, 0.2);
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//right extra bridge
	glPushMatrix();
	glTranslatef(0.5, -0.3, 0.0);
	textureArr[4] = loadTexture("road.bmp");
	drawCube(0.5, 0.05, 0.2);
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//sky bridge
	glPushMatrix();
	glTranslatef(-0.3, 0.15, 0.02);
	textureArr[5] = loadTexture("iron.bmp");
	drawCube(0.6, 0.05, 0.16);
	glDeleteTextures(1, &textureArr[5]);
	glPopMatrix();

	//bridge controller
	glPushMatrix();
	bspeed = bspeed + speed;
	if (bspeed >= 50) {
		bspeed = 50;
	}
	else if (bspeed <= 0) {
		bspeed = 0;
	}

	//left control bridge
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.3, -0.3, 0.0);
	glRotatef(bspeed, 0.0, 0.0, 1.0);
	textureArr[4] = loadTexture("road.bmp");
	drawCube(0.3, 0.05, 0.2);
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//right control bridge
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.3, -0.3, 0.0);
	glRotatef(-bspeed, 0.0, 0.0, 1.0);
	textureArr[4] = loadTexture("road.bmp");
	drawCube(-0.3, 0.05, 0.2);
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();
	
	glPopMatrix();

	//sea
	glPushMatrix();
	glTranslatef(-1.0, -1.0, -1.0);
	textureArr[6] = loadTexture("sea.bmp");
	drawCube(2.0, 0.5, 2.0);
	glDeleteTextures(1, &textureArr[6]);
	glPopMatrix();

	//left bridge back holder
	glPushMatrix();
	glTranslatef(0.45, 0.15, 0.02);
	glRotatef(-45, 0.0, 0.0, 1.0);
	textureArr[7] = loadTexture("steelbar.bmp");
	drawCylinder(0.015, 0.015, 0.6, 20, 20);
	glDeleteTextures(1, &textureArr[7]);
	glPopMatrix();

	//left bridge front holder
	glPushMatrix();
	glTranslatef(0.45, 0.15, 0.18);
	glRotatef(-45, 0.0, 0.0, 1.0);
	textureArr[7] = loadTexture("steelbar.bmp");
	drawCylinder(0.015, 0.015, 0.6, 20, 20);
	glDeleteTextures(1, &textureArr[7]);
	glPopMatrix();

	//right bridge back holder
	glPushMatrix();
	glTranslatef(-0.9, -0.29, 0.02);
	glRotatef(45, 0.0, 0.0, 1.0);
	textureArr[7] = loadTexture("steelbar.bmp");
	drawCylinder(0.015, 0.015, 0.6, 20, 20);
	glDeleteTextures(1, &textureArr[7]);
	glPopMatrix();

	//right bridge front holder
	glPushMatrix();
	glTranslatef(-0.9, -0.29, 0.18);
	glRotatef(45, 0.0, 0.0, 1.0);
	textureArr[7] = loadTexture("steelbar.bmp");
	drawCylinder(0.015, 0.015, 0.6, 20, 20);
	glDeleteTextures(1, &textureArr[7]);
	glPopMatrix();

	//cloud controller
	glPushMatrix();
	if (cloudMain == true) {
		if (cloudX > 2.5) {
			cloudX = 35.1;
		}
		else {
			cloudX = cloudX + cloudSpeed;
		}
	}
	glTranslatef(cloudX, cloudY, cloudZ);

	//reset cloud position
	glPushMatrix();
	glTranslatef(-1.2, 0.75, 0.0);

	//center cloud
	glPushMatrix();
	textureArr[8] = loadTexture("cloud.bmp");
	drawSphere(0.05, 30, 30);
	glDeleteTextures(1, &textureArr[8]);
	glPopMatrix();

	//left bottom cloud
	glPushMatrix();
	glTranslatef(-0.07, 0.0, 0.0);
	textureArr[8] = loadTexture("cloud.bmp");
	drawSphere(0.05, 30, 30);
	glDeleteTextures(1, &textureArr[8]);
	glPopMatrix();

	//right bottom cloud
	glPushMatrix();
	glTranslatef(0.07, 0.0, 0.0);
	textureArr[8] = loadTexture("cloud.bmp");
	drawSphere(0.05, 30, 30);
	glDeleteTextures(1, &textureArr[8]);
	glPopMatrix();

	//left top cloud
	glPushMatrix();
	glTranslatef(0.035, 0.06, 0.0);
	textureArr[8] = loadTexture("cloud.bmp");
	drawSphere(0.05, 30, 30);
	glDeleteTextures(1, &textureArr[8]);
	glPopMatrix();

	//right top cloud
	glPushMatrix();
	glTranslatef(-0.035, 0.06, 0.0);
	textureArr[8] = loadTexture("cloud.bmp");
	drawSphere(0.05, 30, 30);
	glDeleteTextures(1, &textureArr[8]);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	//left tower hole
	glPushMatrix();
	glTranslatef(0.299, -0.3, 0.02);
	textureArr[9] = loadTexture("tunnel.bmp");
	drawCube2(0.202, 0.2, 0.16);
	glDeleteTextures(1, &textureArr[9]);
	glPopMatrix();

	//right tower hole
	glPushMatrix();
	glTranslatef(-0.501, -0.3, 0.02);
	textureArr[9] = loadTexture("tunnel.bmp");
	drawCube2(0.202, 0.2, 0.16);
	glDeleteTextures(1, &textureArr[9]);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
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