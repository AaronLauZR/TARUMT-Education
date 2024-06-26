
#include <Windows.h>
#include <gl/GL.h>
#include <math.h> //math 
#include <gl/GLU.h>

//#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Assignment Robot"

//--------------- Initialized ---------------

boolean reset = false;

//********** Projection **********
// 
//Step 1: Variable declaration
GLuint textureArr[10];
BITMAP BMP; //Bitmap structure
HBITMAP hBMP = NULL; //bitmap handle

//**********************


//********** Projection **********

float tx = 0, tz = 0, tSpeed = 1.0; //translate for modelview
boolean isOrtho = true; //is ortho view
float ONear = -10, OFar = 10; //Ortho near far
float PNear = 1, PFar = 21; //Perspective near far
float ptx = 0, pty = 0, ptSpeed = 1.0; //translate for projection
float pry = 0, prSpeed = 1.5; //rotate ry for projection


//With Projection
float scaleX = 1, scaleY = 1, scaleZ = 1;
//Without Projection
//float scaleX = 0.2, scaleY = 0.2, scaleZ = 0.2;

//**********************


//********** Light **********

float posX = 0, posY = 1, posZ = 0;

//Ambient Light
float amb[3] = { 0, 0, 1 }; //Ambient Light - Blue
float posA[3] = { posX , posY, posZ }; //Ambient light Position

//Ambient Light - Material
float ambM[3] = { 0, 0, 1 }; //Ambient light Material - Blue
float ambM2[3] = { 1, 0, 0 }; //Ambient light 2 Material - Red
float ambM3[3] = { 1, 1, 0 }; //Ambient light 2 Material - Yellow

//Diffuse Light
float dif[3] = { 1, 1, 1 }; //Diffuse light - Red
float posD[3] = { posX , posY, posZ }; //Diffuse light Position

//Diffuse Light - Material
float difM[3] = { 1, 0, 0 }; //Diffuse light material - Red
float difM2[3] = { 0, 0, 1 }; //Ambient light 2 Material - Blue
float difM3[3] = { 1, 1, 0 }; //Ambient light 2 Material - Yello


bool isLightOn = false; //is light on?

//**********************


//********** Animation **********

//Robot Arm/Hand
float left_lowerArmDeg = 0;
float left_upperArmDeg = 0;

float right_lowerArmDeg = 0;
float right_upperArmDeg = 0;

int left_hand_x = 0, left_hand_y = 0, left_hand_z = 0;
int right_hand_x = 0, right_hand_y = 0, right_hand_z = 0;

float left_finger = 0, right_finger = 0;
double fingerMovementSpeed = 2;

double handMovementSpeed = 2;

double attackDeg = 0;

//Is walking
boolean isWalking = false;

//Switching Upper Hand
boolean handMove = false;
boolean handMoveSwitchSide = false;

//Switching Lower Hand
boolean left_lowerHandMove = false;
boolean right_lowerHandMove = false;

//Hand is moving
boolean isLeftHandMoving = false;
boolean isRightHandMoving = false;
int handMovementOption = 0;

//Use Weapon
boolean useSword = false;
boolean useGun = false;

//Appear Weapon
boolean appearSword = false;
boolean appearGun = false;

//Weapon Motion
boolean swingSword = false;
boolean fireGun = false;

//Feet
float movefleft = 0, movefright = 0;

//**********************

//Option
int qNo = 1;

//View shape angle
float angle_view = 0;

//Circle - 2D
float circle_x = 0.0, circle_y = 0.0;
float circle_x2 = 0.0, circle_y2 = 0.0;
float angle = 0; //angle
float PI = 3.1429; //PI 
float noOfTri = 250; //no of triangles

//weapon animation
int weapon = 0;
double shootX = 0.0, shootY = 0.0, shootZ = 0.0;
double shootSpeed = 0.15;
boolean shoot = false;

//texture changing
int change = 0;

//background
boolean bg = false;

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

		//----- Projection Control -----
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
			bg = false;
		}
		else if (wParam == 'P') {			//Change to Perspective Projection
			isOrtho = false;
			tz = 2;
			bg = true;
		}
		else if (wParam == 'Z') {			//Translate Projection along the x (left)
			ptx -= ptSpeed;
		}
		else if (wParam == 'X') {			//Translate Projection along the x (right)
			ptx += ptSpeed;
		}
		else if (wParam == VK_LEFT) {		//Translate Projection to left hand side
			tx -= tSpeed;
		}
		else if (wParam == VK_RIGHT) {		//Translate Projection to right hand side
			tx += tSpeed;
		}
		else if (wParam == 'L') {			//Rotate Projection at y axis (anti-clockwise)
			pry += prSpeed;
		}
		else if (wParam == 'R') {			//Rotate Projection at y axis (clockwise)
			pry -= prSpeed;
		}

		//----- Robot Arm Control -----
		else if (wParam == 0x31) {			//KEY 1 - Left Hand Move Front
			//Set Movement Option
			handMovementOption = 1;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			isWalking = false;
			handMove = false;

			swingSword = false;
			fireGun = false;
		}
		else if (wParam == 0x32) {			//KEY 2 - Left Hand Move Behind
			//Set Movement Option
			handMovementOption = 2;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			isWalking = false;
			handMove = false;

			swingSword = false;
			fireGun = false;
		}
		else if (wParam == 0x33) {			//KEY 3 - Left Hand Move Up
			//Set Movement Option
			handMovementOption = 3;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			isWalking = false;
			handMove = false;

			swingSword = false;
			fireGun = false;
		}
		else if (wParam == 0x34) {			//KEY 4 - Right Hand Move Front
			//Set Movement Option
			handMovementOption = 4;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			isWalking = false;
			handMove = false;

			swingSword = false;
			fireGun = false;
		}
		else if (wParam == 0x35) {			//KEY 5 - Right Hand Move Behind
			//Set Movement Option
			handMovementOption = 5;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			isWalking = false;
			handMove = false;

			swingSword = false;
			fireGun = false;
		}
		else if (wParam == 0x36) {			//KEY 6 - Right Hand Move Up
			//Set Movement Option
			handMovementOption = 6;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			isWalking = false;
			handMove = false;

			swingSword = false;
			fireGun = false;
		}

		else if (wParam == 0x37) {			//KEY 7 - Robot Walking
			//Reset Movement Option
			handMovementOption = 0;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			isWalking = true;
			handMove = true;

			swingSword = false;
			fireGun = false;

		}
		else if (wParam == 0x38) {			//KEY 8 - Use Weapon (Sickle)
			//Reset Movement Option
			handMovementOption = 8;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			//Reset Attack
			attackDeg = 0;

			isWalking = false;
			handMove = false;

			useSword = true;
			useGun = false;

			fireGun = false;

			weapon = 1;
		}
		else if (wParam == 0x39) {			//KEY 9 - Use Weapon (Pistol)
			//Reset Movement Option
			handMovementOption = 9;

			//Reset Arm Rotation
			right_upperArmDeg = 0;
			right_lowerArmDeg = 0;
			left_upperArmDeg = 0;
			left_lowerArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			//Reset Attack
			attackDeg = 0;

			isWalking = false;
			handMove = false;

			useSword = false;
			useGun = true;

			swingSword = false;

			weapon = 2;
		}

		else if (wParam == VK_SPACE) {		//Reset Everything

			//--------------- Hand Animation ---------------
			reset = true;

			//Reset Movement Option
			handMovementOption = 0;

			//Right Robot Arm Reset
			right_lowerArmDeg = 0;
			right_upperArmDeg = 0;

			//Left Robot Arm Reset
			left_lowerArmDeg = 0;
			left_upperArmDeg = 0;

			//Reset Robot Finger
			left_finger = 0;
			right_finger = 0;

			isLeftHandMoving = false;
			isRightHandMoving = false;

			isWalking = false;
			handMove = false;

			useSword = false;
			useGun = false;

			swingSword = false;
			fireGun = false;

			//--------------- Hand Animation ---------------

			movefleft = 0;
			movefright = 0;

			shootX = 0.0;
			shootY = 0.0;
			shootZ = 0.0;
		}

		//----- Robot View Rotation -----
		else if (wParam == 'H')			//Rotate whole Robot (Gonna Remove)
			angle_view += 2;

		else if (wParam == 'J')			//Rotate whole Robot (Gonna Remove)
			angle_view -= 2;

		//else if (wParam == 'M') {		//Leg walk to the front
		//	if (movef >= 10) {
		//		movef = 10;
		//	}
		//	movef += handMovementSpeed;

		//}
		//else if (wParam == 'N') {		//Leg walk to the back
		//	if (movef <= 0) {
		//		movef = 0;
		//	}
		//	movef -= handMovementSpeed;

		//}


		//----- Ligthing Control -----
		else if (wParam == 'W') {
			posD[1] += 3.0, posA[1] += 3.0, posY += 3.0;		//Lighting at Up
		}
		else if (wParam == 'S') {
			posD[1] -= 3.0, posA[1] -= 3.0, posY -= 3.0;		//Lighting at Down
		}
		else if (wParam == 'A') {
			posD[0] -= 3.0, posA[0] -= 3.0, posX -= 3.0;		//Lighting at Left
		}
		else if (wParam == 'D') {
			posD[0] += 3.0, posA[0] += 3.0, posX += 3.0;		//Lighting at Right
		}
		else if (wParam == 'E') {
			posD[2] += 3.0, posA[2] += 3.0, posZ += 3.0;		//Lighting at Near
		}
		else if (wParam == 'Q') {
			posD[2] -= 3.0, posA[2] -= 3.0, posZ -= 3.0;		//Lighting at Far
		}
		else if (wParam == VK_SHIFT) {						    //Lighting mode (on/off)
			isLightOn = !isLightOn;                             //If off, then on
		}
		else if (wParam == 'F') {                               //pistol shoot
			if (weapon == 2) {
				shootX = 0;
				shootY = 0;
				shootZ = 0;
				shoot = true;
			}
		}
		else if (wParam == 'T') {
			change = change + 1;
			if (change > 2) {
				change = 0;
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

//Texture
GLuint loadTexture(LPCSTR filename) {

	//Take from Step 1
	GLuint texture = 0; //Texture name

	//Step 3: INitialize texture info
	//Unpack pixel data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	//Load a bitmap file to WINAPI BITMAP handle
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	//Create bmp structure
	GetObject(hBMP, sizeof(BMP), &BMP); //Create bmp

	//Step 4: Assing texutre to polygon
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Take from Step 5
	DeleteObject(hBMP);
	return texture;
}

//Projection
void projection() {

	//--------------------------------
	//	Camera Projection
	//--------------------------------
	glMatrixMode(GL_PROJECTION); //refer to projection matrix
	glLoadIdentity(); //reset projection matrix

	if (isOrtho)
	{
		glRotatef(180, 0, 1, 0);
		//----- Orthographic view -----
		glOrtho(-8, 8, -6, 6, ONear, OFar); //left, right, bottom, top, near, far
	}
	else
	{
		glRotatef(180, 0, 1, 0);
		//----- Perspective view -----
		gluPerspective(20, 1, -1, 1); //fovy, aspect, near, far
		glFrustum(-10, 10, -10, 10, PNear, PFar); //xmin, xmax, ymin, ymax, -zmin(need to start from positive), -zmax

	}

	glRotatef(pry, 0, 1, 0); //Rotate projection y
	glTranslatef(ptx, pty, 0.0); //Translate projection x & y

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //Reset modelview matrix
	glTranslatef(tx, 0, tz); //Translate along the x & z axis (Translate for modelview) ***

}

void lighting()
{

	//--------------------------------
	//	Lighting
	//--------------------------------

	if (isLightOn)
	{
		//enable lighting for the whole scene
		glEnable(GL_LIGHTING);
	}
	else {
		//disable lighting for the whole scene
		glDisable(GL_LIGHTING);
	}


	//*** Default no lighting, so the output can't see anything ***

	//Light 0: Red color ambient light at pos(0, 6, 0) above
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb); //Meaning = bottom dark to top light
	glLightfv(GL_LIGHT0, GL_POSITION, posA);
	glEnable(GL_LIGHT0);

	//Blue Color Ambient Material
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambM2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambM3);


	////Light 1: Green color diffuse light at pos(6, 0, 0) right
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
	//glLightfv(GL_LIGHT1, GL_POSITION, posD);
	//glEnable(GL_LIGHT1);

	////White Color Diffuse Material
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, difM2);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, difM3);


	//Ligthing Movement
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glPopMatrix();

}

//Shapes
void drawFillSphere(double r, double sli, double sta) {

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, r, sli, sta); //Shape Variable, Radius, Slices, Stacks

	gluDeleteQuadric(sphere); //To remain the process memory performance, if not it will increment and crashed

}

void drawLineSphere(float r, double sli, double sta) {

	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_LINE);
	gluSphere(sphere, r, sli, sta); //Shape Variable, Radius, Slices, Stacks
	gluDeleteQuadric(sphere); //To remain the process memory performance, if not it will increment and crashed

}

void drawFillCylinder(float tr, float br, double h, double sli, double sta) {

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL); //GLU_LINE, GLU_FILL, GLU_POINT, GLU_SILHOUETTE
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, tr, br, h, sli, sta); //Shape Variable, Top Radius, Base Radius, Height, Slices, Stacks

	gluDeleteQuadric(cylinder); //To remain the process memory performance, if not it will increment and crashed

}

void drawLineCylinder(float tr, float br, double h, double sli, double sta) {

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE); //GLU_LINE, GLU_FILL, GLU_POINT, GLU_SILHOUETTE
	gluCylinder(cylinder, tr, br, h, sli, sta); //Shape Variable, Top Radius, Base Radius, Height, Slices, Stacks
	gluDeleteQuadric(cylinder); //To remain the process memory performance, if not it will increment and crashed

}

void drawFillPyramid(float sz) {

	//Pyramid
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

void drawLinePyramid(float sz) {

	//Pyramid
	glBegin(GL_LINE_LOOP);

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

void drawLineCube(float sx, float sy, float sz) {

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, sy, 0.0);
	glVertex3f(0.0, sy, sz);
	glVertex3f(0.0, 0.0, sz);

	glVertex3f(0.0, 0.0, sz);
	glVertex3f(sx, 0.0, sz);
	glVertex3f(sx, sy, sz);
	glVertex3f(0.0, sy, sz);

	glVertex3f(0.0, sy, sz);
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, sy, 0.0);
	glVertex3f(0.0, sy, 0.0);

	glVertex3f(0.0, sy, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(sx, 0.0, 0.0);
	glVertex3f(sx, sy, 0.0);

	glVertex3f(sx, sy, 0.0f);
	glVertex3f(sx, sy, sz);
	glVertex3f(sx, 0.0, sz);
	glVertex3f(sx, 0.0, 0.0);

	glVertex3f(sx, 0.0, 0.0);
	glVertex3f(sx, 0.0, sz);
	glVertex3f(0.0, 0.0, sz);
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glEnd();

}

void drawFillCube(float sx, float sy, float sz) {

	glBegin(GL_QUADS);

	//Face 1: Bottom
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, sz);

	glTexCoord2f(1, 1);
	glVertex3f(sx, 0, sz);

	glTexCoord2f(1, 0);
	glVertex3f(sx, 0, 0);

	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);


	//Face 2: Left
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(0, sy, 0);

	glTexCoord2f(1, 0);
	glVertex3f(0, sy, sz);

	glTexCoord2f(0, 0);
	glVertex3f(0, 0, sz);


	//Face 3: Front
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, sz);

	glTexCoord2f(1, 1);
	glVertex3f(0.0f, sy, sz);

	glTexCoord2f(1, 0);
	glVertex3f(sx, sy, sz);

	glTexCoord2f(0, 0);
	glVertex3f(sx, 0.0f, sz);


	//Face 4: Right
	glTexCoord2f(0, 1);
	glVertex3f(sx, 0, sz);

	glTexCoord2f(1, 1);
	glVertex3f(sx, sy, sz);

	glTexCoord2f(1, 0);
	glVertex3f(sx, sz, 0.);

	glTexCoord2f(0, 0);
	glVertex3f(sx, 0, 0);


	//Face 5: Back
	glTexCoord2f(0, 1);
	glVertex3f(sx, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(0, sy, 0);

	glTexCoord2f(0, 0);
	glVertex3f(sx, sy, 0);


	//Face 6: Top
	glTexCoord2f(0.0, 1.0);
	glVertex3f(sx, sy, 0.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0f, sy, 0.0f);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0f, sy, sz);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(sx, sy, sz);

	glEnd();

}

void drawFillTrapezium() {

	glBegin(GL_POLYGON);

	//Right
	glTexCoord2f(0, 1);
	glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, 1, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.0, 1);

	//Top
	glTexCoord2f(0, 1);
	glVertex3f(0.3, 0.0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0.7, 0.0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, 1);


	//Behind
	glTexCoord2f(0, 1);
	glVertex3f(0, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, 0.0);


	//Bottom
	glTexCoord2f(0, 1);
	glVertex3f(0.0, 1, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.7, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, 0.0);


	//Left
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.7, 0.0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0.7, 0.0, 0.0);


	//front
	glTexCoord2f(0, 1);
	glVertex3f(0.7, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.7, 0.0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.0, 0.0);

	glEnd();

}

void drawLineTrapezium() {

	glBegin(GL_LINE_LOOP);

	//Right
	glVertex3f(0.3, 0.0, 0.0);
	glVertex3f(0.0, 1, 0.0);
	glVertex3f(0.0, 1, 1);
	glVertex3f(0.3, 0.0, 1);

	//Top
	glVertex3f(0.3, 0.0, 1);
	glVertex3f(0.7, 0.0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	//Behind
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0.0);
	glVertex3f(0, 1, 0.0);

	//Bottom
	glVertex3f(0.0, 1, 0.0);
	glVertex3f(0.3, 0.0, 0.0);
	glVertex3f(0.7, 0.0, 0.0);
	glVertex3f(1, 1, 0.0);

	//Left
	glVertex3f(1, 1, 0.0);
	glVertex3f(1, 1, 1);
	glVertex3f(0.7, 0.0, 1);
	glVertex3f(0.7, 0.0, 0.0);

	//front
	glVertex3f(0.7, 0.0, 0.0);
	glVertex3f(0.7, 0.0, 1);
	glVertex3f(0.3, 0.0, 1);
	glVertex3f(0.3, 0.0, 0.0);

	glEnd();

}

void drawFillRightTrapezium(float size) {

	glBegin(GL_POLYGON);

	//Right
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.0, 1, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.0, 1);

	//Top
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, 1);

	//Behind
	glTexCoord2f(0, 1);
	glVertex3f(0, 1, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, 0.0);

	//Bottom
	glTexCoord2f(0, 1);
	glVertex3f(0.0, 1, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, 0.0);

	//Left
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(size, 0.0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(size, 0.0, 0.0);

	//front
	glTexCoord2f(0, 1);
	glVertex3f(size, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(size, 0.0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0.0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.0, 0.0);

	glEnd();

}

void drawLineRightTrapezium(float size) {

	glBegin(GL_LINE_LOOP);

	//Right
	glVertex3f(0, 0.0, 0.0);
	glVertex3f(0.0, 1, 0.0);
	glVertex3f(0.0, 1, 1);
	glVertex3f(0, 0.0, 1);

	//Top
	glVertex3f(0, 0.0, 1);
	glVertex3f(size, 0.0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);

	//Behind
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0.0);
	glVertex3f(0, 1, 0.0);

	//Bottom
	glVertex3f(0.0, 1, 0.0);
	glVertex3f(0, 0.0, 0.0);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(1, 1, 0.0);

	//Left
	glVertex3f(1, 1, 0.0);
	glVertex3f(1, 1, 1);
	glVertex3f(size, 0.0, 1);
	glVertex3f(size, 0.0, 0.0);

	//front
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size, 0.0, 1);
	glVertex3f(0, 0.0, 1);
	glVertex3f(0, 0.0, 0.0);

	glEnd();

}

void drawFillHexagon() {

	glBegin(GL_POLYGON);

	//Front
	glTexCoord2f(0, 1);
	glVertex3f(0.9, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.9, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0, 0);

	//Right 1
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0.2, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.2, 0);

	//Right 2
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.2, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, 0.4, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0.1, 0.4, 0);

	//Behind
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 0.4, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, 0.4, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.9, 0.4, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0.9, 0.4, 0);


	//Left 1
	glTexCoord2f(0, 1);
	glVertex3f(0.9, 0.4, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1.0, 0.2, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1.0, 0.2, 1);
	glTexCoord2f(0, 0);
	glVertex3f(0.9, 0.4, 1);


	//Top
	glTexCoord2f(0.3, 1);
	glVertex3f(0.9, 0.4, 1);
	glTexCoord2f(0.7, 1);
	glVertex3f(0.1, 0.4, 1);
	glTexCoord2f(1, 0.5);
	glVertex3f(0, 0.2, 1);
	glTexCoord2f(0.7, 0);
	glVertex3f(0.1, 0, 1);
	glTexCoord2f(0.3, 0);
	glVertex3f(0.9, 0, 1);
	glTexCoord2f(0, 0.5);
	glVertex3f(1.0, 0.2, 1);


	//Left 2
	glTexCoord2f(0, 1);
	glVertex3f(1.0, 0.2, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0.9, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0.9, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1.0, 0.2, 0);


	//Bottom
	glTexCoord2f(0.3, 1);
	glVertex3f(1.0, 0.2, 0);
	glTexCoord2f(0.7, 1);
	glVertex3f(0.9, 0.4, 0);
	glTexCoord2f(1, 0.5);
	glVertex3f(0.1, 0.4, 0);
	glTexCoord2f(0.7, 0);
	glVertex3f(0.0, 0.2, 0.0);
	glTexCoord2f(0.3, 0);
	glVertex3f(0.1, 0.0, 0.0);
	glTexCoord2f(0, 0.5);
	glVertex3f(0.9, 0, 0);


	glEnd();

}

void drawLineHexagon() {

	glBegin(GL_LINE_LOOP);

	//Front
	glVertex3f(0.9, 0, 0);
	glVertex3f(0.9, 0, 1);
	glVertex3f(0.1, 0, 1);
	glVertex3f(0.1, 0, 0);

	//Right 1
	glVertex3f(0.1, 0, 0);
	glVertex3f(0.1, 0, 1);
	glVertex3f(0, 0.2, 1);
	glVertex3f(0, 0.2, 0);

	//Right 2
	glVertex3f(0, 0.2, 0);
	glVertex3f(0, 0.2, 1);
	glVertex3f(0.1, 0.4, 1);
	glVertex3f(0.1, 0.4, 0);

	//Behind
	glVertex3f(0.1, 0.4, 0);
	glVertex3f(0.1, 0.4, 1);
	glVertex3f(0.9, 0.4, 1);
	glVertex3f(0.9, 0.4, 0);

	//Left 1
	glVertex3f(0.9, 0.4, 0);
	glVertex3f(1.0, 0.2, 0);
	glVertex3f(1.0, 0.2, 1);
	glVertex3f(0.9, 0.4, 1);

	//Top
	glVertex3f(0.9, 0.4, 1);
	glVertex3f(0.1, 0.4, 1);
	glVertex3f(0, 0.2, 1);
	glVertex3f(0.1, 0, 1);
	glVertex3f(0.9, 0, 1);
	glVertex3f(1.0, 0.2, 1);

	//Left 2
	glVertex3f(1.0, 0.2, 1);
	glVertex3f(0.9, 0, 1);
	glVertex3f(0.9, 0, 0);
	glVertex3f(1.0, 0.2, 0);

	//Bottom
	glVertex3f(1.0, 0.2, 0);
	glVertex3f(0.9, 0.4, 0);
	glVertex3f(0.1, 0.4, 0);
	glVertex3f(0.0, 0.2, 0.0);
	glVertex3f(0.1, 0.0, 0.0);
	glVertex3f(0.9, 0, 0);

	glEnd();

}

void drawFillCoverCylinder(double radius, double length, double sli, double sta) {

	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(circle_x, circle_y); //origin of circle (x, y)
	glTexCoord2f(circle_x, circle_y);

	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri)
	{
		circle_x2 = circle_x + radius * cos(angle);
		circle_y2 = circle_y + radius * sin(angle);
		glVertex2f(circle_x2, circle_y2);
		glTexCoord2f(circle_x2, circle_y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	drawFillCylinder(radius, radius, length, sli, sta);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, (length - (length * 2)));

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(circle_x, circle_y); //origin of circle (x, y)
	glTexCoord2f(circle_x, circle_y);

	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri)
	{
		circle_x2 = circle_x + radius * cos(angle);
		circle_y2 = circle_y + radius * sin(angle);
		glVertex2f(circle_x2, circle_y2);
		glTexCoord2f(circle_x2, circle_y2);
	}
	glEnd();
	glPopMatrix();

}

void drawLineCoverCylinder(double radius, double length, double sli, double sta) {

	glPushMatrix();
	glBegin(GL_LINE_LOOP);

	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri)
	{
		circle_x2 = circle_x + radius * cos(angle);
		circle_y2 = circle_y + radius * sin(angle);
		glVertex2f(circle_x2, circle_y2);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	drawLineCylinder(radius, radius, length, sli, sta);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, (length - (length * 2)));

	glBegin(GL_LINE_LOOP);

	for (angle = 0; angle <= (2 * PI); angle += (2 * PI) / noOfTri)
	{
		circle_x2 = circle_x + radius * cos(angle);
		circle_y2 = circle_y + radius * sin(angle);
		glVertex2f(circle_x2, circle_y2);
	}
	glEnd();
	glPopMatrix();
}

void draw2DTriangle() {
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex2f(1, 0);
	glTexCoord2f(0, 0.5);
	glVertex2f(0, 0.5);
	glEnd();
}

void draw2DSquare() {
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 1);
	glVertex2f(0, 1);
	glEnd();
}


//************************************************************************************************

									//Head

//************************************************************************************************
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
	glTexCoord2f(1, 1);
	glVertex2f(0.05, 0.05);
	glTexCoord2f(1, 0);
	glVertex2f(0.25, 0.05);
	glTexCoord2f(0, 0);
	glVertex2f(0.25, 0.2);
	glTexCoord2f(0, 1);
	glVertex2f(0.05, 0.2);
	glEnd();

	glColor3f(0.53, 0.81, 0.92);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex2f(-0.05, 0.05);
	glTexCoord2f(1, 0);
	glVertex2f(-0.25, 0.05);
	glTexCoord2f(0, 0);
	glVertex2f(-0.25, 0.2);
	glTexCoord2f(0, 1);
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
	
	GLuint textureArr[5];

	glPushMatrix();
	textureArr[2] = loadTexture("dark_grey.bmp");
	glTranslatef(-0.5, -0.5, 0.0);
	glColor3f(0.48, 0.5, 0.5);
	mainHead();
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glPushMatrix();
	if (change == 0) {
		textureArr[1] = loadTexture("blueeye.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("purpleeye.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("greeneye.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
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
	if (change == 0) {
		textureArr[0] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("purplesteel.bmp");
	}
	glRotatef(270, 1.0, 0.0, 0.0);
	glTranslatef(0.35, -1.05, -0.5);
	glColor3f(1.0, 1.0, 1.0);
	Ear();
	glColor3f(0.0, 0.0, 0.0);
	earLine();
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();
	if (change == 0) {
		textureArr[0] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("purplesteel.bmp");
	}
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-0.5, -0.15, -0.8);
	glColor3f(1.0, 1.0, 1.0);
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

//************************************************************************************************

									//Robot Weapons

//************************************************************************************************

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
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 0.1);
	sickleStick(0.01, 0.01, 0.05);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.1, 0.0);
	sickleCorn(0.01, 0.0, 0.05);
	glPopMatrix();
}

void sickle() {
	glRotatef(-90, 1.0, 0.0, 0.0);
	glRotatef(-90, 0.0, 1.0, 0.0);
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
	glRotatef(180, 1.0, 0.0, 0.0);
	glRotatef(-90, 0.0, 0.0, 1.0);
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
	if (shootY > 100) {
		shootY = 100.01;
	}
	else {
		shootY = shootY + shootSpeed;
	}

	glTranslatef(shootX, shootY, shootZ);

	glPushMatrix();
	GLuint textureArr[1];
	textureArr[0] = loadTexture("bullet.bmp");
	glTranslatef(0.05, 0.2, -0.05);
	glScalef(2.0, 2.0, 2.0);
	glColor3f(1.0, 1.0, 1.0);
	bullet();
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();
}

void shootingPistol() {
	glPushMatrix();
	pistol();
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	if (shoot == true) {
		glPushMatrix();
		bulletShoot();
		glPopMatrix();
	}
}

//************************************************************************************************

									//Robot Hands

//************************************************************************************************

void robot_rightHand() {

	boolean attack = false;

	//-------------------- ROBOT HAND MOVEMENT --------------------
	switch (handMovementOption)
	{
		//Move Front
	case 1:
		right_hand_x = -1;
		right_hand_y = 0;
		right_hand_z = 0;

		if (right_upperArmDeg >= 35)
		{
			right_upperArmDeg = 35;
		}
		right_upperArmDeg = right_upperArmDeg + handMovementSpeed;
		break;

		//Move Behind
	case 2:
		right_hand_x = 1;
		right_hand_y = 0;
		right_hand_z = 0;

		if (right_upperArmDeg >= 35)
		{
			right_upperArmDeg = 35;
		}

		right_upperArmDeg = right_upperArmDeg + handMovementSpeed;
		break;

		//Move Up 
	case 3:
		right_hand_x = 0;
		right_hand_y = 0;
		right_hand_z = 1;

		//Upper Hand Rotation
		if (right_upperArmDeg <= -30)
		{
			right_upperArmDeg = -30;
		}

		right_upperArmDeg = right_upperArmDeg - handMovementSpeed;
		break;

		//Use Sword
	case 8:

		right_lowerArmDeg = right_lowerArmDeg - handMovementSpeed;

		if (right_lowerArmDeg <= -90)
		{
			right_lowerArmDeg = -90;

			//Finger Rotation
			right_finger = right_finger + fingerMovementSpeed;

			if (right_finger >= 70)
			{
				appearSword = true;
			}
			if (right_finger >= 90)
			{
				right_finger = 90;

				swingSword = true;
				right_lowerArmDeg = -90;
			}
			if (right_finger <= 0)
			{
				right_finger = 0;
			}

		}

		if (swingSword)
		{
			right_hand_x = -1;
			right_hand_y = 1;
			right_hand_z = 0;

			//Upper Hand Rotation
			if (right_upperArmDeg >= 40)
			{
				right_upperArmDeg = 40;

				attack = true;

			}

			right_upperArmDeg = right_upperArmDeg + handMovementSpeed;
		}

		//Attack with sword
		if (attack)
		{
			attackDeg = attackDeg - 4;

			if (attackDeg <= -60)
			{
				attackDeg = -60;

			}

		}
		break;

		//Use Gun
	case 9:

		right_lowerArmDeg = right_lowerArmDeg - handMovementSpeed;

		if (right_lowerArmDeg <= -90)
		{
			right_lowerArmDeg = -90;

			//Finger Rotation
			right_finger = right_finger + fingerMovementSpeed;

			if (right_finger >= 70)
			{
				appearGun = true;
			}
			if (right_finger >= 90)
			{
				right_finger = 90;
			}
			if (right_finger <= 0)
			{
				right_finger = 0;
			}

		}
		break;

		break;
	}


	//-------------------- ROBOT WALKING --------------------
	if (isWalking == true)
	{
		handMovementSpeed = 1;
		right_hand_x = -1;
		right_hand_y = 0;
		right_hand_z = 0;
		float movefspeed = 0.5;

		if (handMove)
		{
			//Move Upper Hand
			right_upperArmDeg = right_upperArmDeg - handMovementSpeed;
			movefright += movefspeed;
			if (right_upperArmDeg <= -35)
			{
				right_upperArmDeg = -35;

				handMove = false;
				handMoveSwitchSide = true;

			}
			if (movefright >= 10) {
				movefright = 10;
			}


			//Move Lower Hand 
			if (right_lowerHandMove)
			{
				right_lowerArmDeg = right_lowerArmDeg + handMovementSpeed;

				if (right_lowerArmDeg >= 0)
				{
					right_lowerArmDeg = 0;
					right_lowerHandMove = false;
				}

			}

		}

		else if (handMoveSwitchSide)
		{

			//Move Upper Hand
			right_upperArmDeg = right_upperArmDeg + handMovementSpeed;

			movefright -= movefspeed;
			if (right_upperArmDeg >= 35)
			{
				right_upperArmDeg = 35;

				handMove = true;
				handMoveSwitchSide = false;

			}
			if (movefright <= -5) {
				movefright = -5;
			}
			//Move Lower Hand
			right_lowerArmDeg = right_lowerArmDeg - handMovementSpeed;

			if (right_lowerArmDeg <= -60)
			{
				right_lowerArmDeg = -60;
				right_lowerHandMove = true;
			}

		}

		//Finger Rotation
		right_finger = right_finger + fingerMovementSpeed;
		left_finger = left_finger + fingerMovementSpeed;

		if (right_finger >= 90)
		{
			right_finger = 90;
			left_finger = 90;
		}
		if (right_finger <= 0)
		{
			right_finger = 0;
			left_finger = 0;
		}


	}


	glPushMatrix();

	//Scale
	glScalef(scaleX, scaleY, scaleZ);
	//Translate
	glTranslatef(-2.7, 0, 0);

	glPushMatrix();

	glRotatef(right_upperArmDeg, right_hand_x, right_hand_y, right_hand_z);

	if (attack)
	{
		glRotatef(attackDeg, -1, 1, 0);
	}

	glTranslatef(-0.5, 0, 0);

	//---------------------------- Robot Hand - Shoulder ---------------------------------
	glPushMatrix();

	//Robot Shoulder - Cube
	glPushMatrix();

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(-1, 1, 1);
	glDeleteTextures(1, &textureArr[0]);

	glPopMatrix();

	//Robot Shoulder - Cylinder
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1.1, 0.5, -1.5);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0.15, 0.15, 1.5, 10, 10);
	glDeleteTextures(1, &textureArr[1]);

	glPopMatrix();

	//Robot Shoulder - Cone
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1.1, 0.5, -2);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0, 0.15, 0.5, 10, 10);
	glDeleteTextures(1, &textureArr[1]);

	glPopMatrix();

	//Robot Shoulder - Pyramid 1
	glPushMatrix();
	glTranslatef(-0.3, 1, 0.4);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillPyramid(0.2);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot Shoulder - Pyramid 2
	glPushMatrix();
	glTranslatef(-0.6, 1, 0.4);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillPyramid(0.2);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();
	
	//Robot Shoulder - Pyramid 3
	glPushMatrix();
	glTranslatef(-0.9, 1, 0.4);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillPyramid(0.2);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPopMatrix();
	//---------------------------- Robot Hand - Shoulder ---------------------------------


	//---------------------------- Robot Hand - Arm ---------------------------------
	glPushMatrix();
	glTranslatef(0, 0, 0.2);

	//Robot Hand - upper arm cube
	glPushMatrix();
	glTranslatef(-0.8, -0.8, 0);

	glColor3f(1, 1, 1);
	textureArr[2] = loadTexture("light_grey.bmp");
	drawFillCube(0.6, 0.8, 0.6);
	glDeleteTextures(1, &textureArr[2]);

	glPopMatrix();

	//Robot Joint
	glPushMatrix();
	glTranslatef(-0.5, -1.1, 0.3);

	glColor3f(1, 1, 1);
	textureArr[3] = loadTexture("dark_grey.bmp");
	drawFillSphere(0.25, 30, 30);
	glDeleteTextures(1, &textureArr[3]);

	glPopMatrix();

	//Robot Hand - lower arm
	glPushMatrix();
	glTranslatef(-0.8, -0.8, 0.6);
	glRotatef(right_lowerArmDeg, 1, 0, 0);
	glRotatef(180, 1, 0, 0);

	//Robot Hand - lower arm cube
	glPushMatrix();
	glTranslatef(0, 0, 0);

	glColor3f(1, 1, 1);
	textureArr[2] = loadTexture("light_grey.bmp");
	drawFillCube(0.6, 0.8, 0.6);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	//Robot Hand - lower arm cylinder
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0.3, -0.3, 0.6);

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0.65, 0.5, 1.2, 10, 10);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	//---------------------------- Robot Hand & Finger ---------------------------------
	glPushMatrix();

	glTranslatef(0, 1.8, 0);

	glPushMatrix();
	glScalef(0.65, 0.65, 0.65);
	glRotatef(180, 1, 0, 0);
	glTranslatef(-0.1, -0.6, -1);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillTrapezium();
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot Thumbnail
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.4, 0, 0);
	glRotatef(right_finger, 0, 0, 1);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.3, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();


	//--------------- Weapon ---------------
	//Add Sicker Weapon
	if (appearSword)
	{
		glPushMatrix();
		glTranslatef(0.55, 0.2, -3.0);
		glScalef(8.0, 8.0, 8.0);
		sickle();
		glPopMatrix();
	}

	//Add Pistol Weapon
	if (appearGun)
	{
		glPushMatrix();
		glTranslatef(0.15, 0.0, -0.1);
		glScalef(4.0, 4.0, 4.0);
		shootingPistol();
		glPopMatrix();
	}

	//--------------- Robot Finger ---------------
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.3, 0.4, -0.6);
	glRotatef(right_finger, 0, 0, 1);

	//Robot 1 Finger
	glPushMatrix();
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.4, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot 2 Finger
	glPushMatrix();
	glTranslatef(0, 0, 0.17);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.4, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot 3 Finger
	glPushMatrix();
	glTranslatef(0, 0, 0.32);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.4, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot 4 Finger
	glPushMatrix();
	glTranslatef(0, 0, 0.47);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.4, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	//---------------------------- Robot Hand - Hand ---------------------------------

	glPopMatrix();

	glPopMatrix();
	//---------------------------- Robot Hand - Shoulder ---------------------------------

	glPopMatrix();

	glPopMatrix();

}

void robot_leftHand() {


	//-------------------- ROBOT HAND MOVEMENT --------------------

	switch (handMovementOption)
	{
	case 4: //Move Front
		left_hand_x = -1;
		left_hand_y = 0;
		left_hand_z = 0;

		if (left_upperArmDeg <= -35)
		{
			left_upperArmDeg = -35;
		}
		left_upperArmDeg = left_upperArmDeg - handMovementSpeed;
		break;

	case 5: //Move Behind
		left_hand_x = 1;
		left_hand_y = 0;
		left_hand_z = 0;

		if (left_upperArmDeg <= -35)
		{
			left_upperArmDeg = -35;
		}
		left_upperArmDeg = left_upperArmDeg - handMovementSpeed;
		break;

	case 6: //Move Up 
		left_hand_x = 0;
		left_hand_y = 0;
		left_hand_z = 1;

		if (left_upperArmDeg <= -30)
		{
			left_upperArmDeg = -30;
		}
		left_upperArmDeg = left_upperArmDeg - handMovementSpeed;
		break;

	default:
		break;
	}


	//-------------------- ROBOT WALKING --------------------
	if (isWalking == true)
	{
		handMovementSpeed = 1;
		left_hand_x = 1;
		left_hand_y = 0;
		left_hand_z = 0;
		float movefspeed = 0.5;

		if (handMove)
		{
			//Move Upper Hand 
			left_upperArmDeg = left_upperArmDeg + 1;
			movefleft -= movefspeed;


			if (left_upperArmDeg >= 35)
			{
				left_upperArmDeg = 35;

				handMove = false;
				handMoveSwitchSide = true;
			}
			if (movefleft <= -5) {
				movefleft = -5;
			}
			//Move Lower Hand 
			if (left_lowerHandMove)
			{
				left_lowerArmDeg = left_lowerArmDeg - 1;

				if (left_lowerArmDeg <= -60)
				{
					left_lowerArmDeg = -60;
					left_lowerHandMove = false;
				}
			}

		}

		else if (handMoveSwitchSide)
		{
			//Move Upper Hand
			left_upperArmDeg = left_upperArmDeg - 1;
			movefleft += movefspeed;
			if (left_upperArmDeg <= -35)
			{
				left_upperArmDeg = -35;

				handMove = true;
				handMoveSwitchSide = false;
			}
			if (movefleft >= 10) {
				movefleft = 10;
			}
			//Move Lower Hand
			left_lowerArmDeg = left_lowerArmDeg + 1;

			if (left_lowerArmDeg >= 0)
			{
				left_lowerArmDeg = 0;
				left_lowerHandMove = true;
			}

		}

	}


	glPushMatrix();

	//Translate
	glTranslatef(2.7, 0, 0);
	//Scale
	glScalef(scaleX, scaleY, scaleZ);

	glPushMatrix();

	glRotatef(180, 0, 1, 0);
	glTranslatef(0.5, 0, -1);

	//Animation Rotation
	glRotatef(left_upperArmDeg, left_hand_x, left_hand_y, left_hand_z);

	//---------------------------- Robot Hand - Shoulder ---------------------------------
	glPushMatrix();

	//Robot Shoulder - Cube
	glPushMatrix();
	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(-1, 1, 1);
	glDeleteTextures(1, &textureArr[0]);

	glPopMatrix();

	//Robot Shoulder - Cylinder
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1.1, 0.5, -1.5);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0.15, 0.15, 1.5, 10, 10);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot Shoulder - Cone
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(-1.1, 0.5, -2);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0, 0.15, 0.5, 10, 10);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot Shoulder - Pyramid 1
	glPushMatrix();
	glTranslatef(-0.3, 1, 0.4);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillPyramid(0.2);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot Shoulder - Pyramid 2
	glPushMatrix();
	glTranslatef(-0.6, 1, 0.4);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillPyramid(0.2);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot Shoulder - Pyramid 3
	glPushMatrix();
	glTranslatef(-0.9, 1, 0.4);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillPyramid(0.2);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPopMatrix();
	//---------------------------- Robot Hand - Shoulder ---------------------------------

	//---------------------------- Robot Hand - Arm ---------------------------------
	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	glRotatef(180, 0, 1, 0);
	glTranslatef(1, 0, -1);

	//Robot Hand - upper arm cube
	glPushMatrix();
	glTranslatef(-0.8, -0.8, 0);
	textureArr[2] = loadTexture("light_grey.bmp");
	drawFillCube(0.6, 0.8, 0.6);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	//Robot Joint
	glPushMatrix();
	glTranslatef(-0.5, -1.1, 0.3);
	textureArr[3] = loadTexture("dark_grey.bmp");
	drawFillSphere(0.25, 30, 30);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	//Robot Hand - lower arm
	glPushMatrix();
	glTranslatef(-0.8, -0.8, 0.6);
	glRotatef(left_lowerArmDeg, 1, 0, 0);
	glRotatef(180, 1, 0, 0);

	//Robot Hand - lower arm cube
	glPushMatrix();
	glTranslatef(0, 0, 0);
	textureArr[2] = loadTexture("light_grey.bmp");
	drawFillCube(0.6, 0.8, 0.6);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	//Robot Hand - lower arm cylinder
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0.3, -0.3, 0.6);
	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0.65, 0.5, 1.2, 10, 10);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	//---------------------------- Robot Hand & Finger ---------------------------------
	glPushMatrix();

	glTranslatef(0, 1.8, 0);

	glPushMatrix();
	glScalef(0.65, 0.65, 0.65);
	glRotatef(180, 1, 0, 0);
	glTranslatef(-0.1, -0.6, -1);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillTrapezium();
	glDeleteTextures(1, &textureArr[1]);

	glPopMatrix();

	//Robot Thumbnail
	glPushMatrix();

	glTranslatef(0.1, 0, -0.1);
	glRotatef(left_finger, 0, 0, 1);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.3, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//--------------- Robot Finger ---------------
	glPushMatrix();

	glTranslatef(0.2, 0.4, 0);

	glRotatef(left_finger, 0, 0, 1);

	//Robot 1 Finger
	glPushMatrix();
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.4, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot 2 Finger
	glPushMatrix();
	glTranslatef(0, 0, 0.17);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.4, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot 3 Finger
	glPushMatrix();
	glTranslatef(0, 0, 0.32);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.4, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	//Robot 4 Finger
	glPushMatrix();
	glTranslatef(0, 0, 0.47);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(0.15, 0.4, 0.1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	//---------------------------- Robot Hand - Hand ---------------------------------

	glPopMatrix();

	glPopMatrix();
	//---------------------------- Robot Hand - Arm ---------------------------------

	glPopMatrix();

	glPopMatrix();

}

//************************************************************************************************

									//Robot Body

//************************************************************************************************

void mini_hood() {

	glScalef(0.8, 0.2, 1.4);

	glPushMatrix();
	glTranslatef(1.5, 0, 0);
	glColor3f(0.91, 0.91, 0.91);
	drawFillCube(0.99, 0.99, 0.99);
	glColor3f(0, 0, 0);
	drawLineCube(1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5, 0, 0);
	glColor3f(0.91, 0.91, 0.91);
	drawFillCube(0.99, 0.99, 0.99);
	glColor3f(0, 0, 0);
	drawLineCube(1, 1, 1);
	glPopMatrix();
}

void robot_body() {

	glPushMatrix();
	//Scale
	glScalef(scaleX, scaleY, scaleZ);

	//---------------------------- Robot Arm Joint ---------------------------------
	glPushMatrix();

	//--------------- Robot Arm Joint - Left ---------------
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-0.5, 0.5, -2.8);

	//Robot Shoulder Joint - Cylinder
	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0.4, 0.5, 0.3, 10, 10);
	glDeleteTextures(1, &textureArr[0]);

	//Robot Shoulder Joint - Sphere
	glPushMatrix();
	glTranslatef(0, 0, -0.1);

	glColor3f(1, 1, 1);
	textureArr[3] = loadTexture("dark_grey.bmp");
	drawFillSphere(0.35, 30, 30);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	glPopMatrix();

	//--------------- Robot Arm Joint - Right ---------------
	glPushMatrix();

	glRotatef(-90, 0, 1, 0);
	glTranslatef(0.5, 0.5, -1.8);

	//Robot Shoulder Joint - Cylinder
	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0.4, 0.5, 0.3, 10, 10);
	glDeleteTextures(1, &textureArr[0]);

	//Robot Shoulder Joint - Sphere
	glPushMatrix();
	glTranslatef(0, 0, -0.1);

	glColor3f(1, 1, 1);
	textureArr[3] = loadTexture("dark_grey.bmp");
	drawFillSphere(0.35, 30, 30);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
	//---------------------------- Robot Arm Joint ---------------------------------


	//---------------------------- Robot Body ---------------------------------
	glPushMatrix();

	glTranslatef(-2.5, 0, -0.5);

	//Body Cube
	glPushMatrix();
	glScalef(4, 1.5, 2);
	glTranslatef(0, -0.3, 0);

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	//Body Hexagon
	glPushMatrix();
	glScalef(5, 1, 2.3);
	glTranslatef(-0.1, 1.051, -0.05);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillHexagon();
	glDeleteTextures(1, &textureArr[1]);

	glPopMatrix();

	//--------------- Cube Window - Left ---------------
	glPushMatrix();
	glScalef(1.8, 1, 0.2);
	glTranslatef(0.08, -0.15, 10);

	textureArr[5] = loadTexture("window.bmp");
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[5]);

	//Viper - Left
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 1, 0);
	glColor3f(0, 0, 0);

	glPushMatrix();
	glRotatef(-70, 0, 1, 0);
	drawFillCoverCylinder(0.03, 1, 10, 10);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();

	//--------------- Cube Window - Right ---------------
	glPushMatrix();
	glScalef(1.8, 1, 0.2);
	glTranslatef(1.15, -0.15, 10);

	glColor3f(1, 1, 1);
	textureArr[5] = loadTexture("window.bmp");
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[5]);

	//Viper - Right
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 1, 0);
	glColor3f(0, 0, 0);

	glPushMatrix();
	glRotatef(-70, 0, 1, 0);
	drawFillCoverCylinder(0.03, 1, 10, 10);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	//--------------- Led Light ---------------
	//Led Light 1
	glPushMatrix();
	glTranslatef(0.5, 1.25, 2.2);

	glColor3f(1, 1, 1);
	textureArr[4] = loadTexture("light.bmp");
	drawFillCoverCylinder(0.12, 0.1, 10, 10);
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//Led Light 2
	glPushMatrix();
	glTranslatef(1, 1.25, 2.2);
	textureArr[4] = loadTexture("light.bmp");
	drawFillCoverCylinder(0.12, 0.1, 10, 10);
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//Led Light 3
	glPushMatrix();
	glTranslatef(3, 1.25, 2.2);
	textureArr[4] = loadTexture("light.bmp");
	drawFillCoverCylinder(0.12, 0.1, 10, 10);
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//Led Light 4
	glPushMatrix();
	glTranslatef(3.5, 1.25, 2.2);
	textureArr[4] = loadTexture("light.bmp");
	drawFillCoverCylinder(0.12, 0.1, 10, 10);
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//---------------------------- Robot Body ---------------------------------
	glPushMatrix();

	glTranslatef(0, 0.05, 0);

	//--------------- Robot Hood ---------------
	glPushMatrix();

	//Mini Hood
	glPushMatrix();
	glTranslatef(0, -0.9, 0.3);
	mini_hood();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1.1, 0.3);
	mini_hood();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1.3, 0.3);
	mini_hood();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1.5, 0.3);
	mini_hood();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1.7, 0.3);
	mini_hood();
	glPopMatrix();

	//Side Hood
	glPushMatrix();
	glTranslatef(1, -0.7, 0.2);
	glScalef(2, 0.2, 1.6);

	glColor3f(1, 1, 1);
	textureArr[2] = loadTexture("light_grey.bmp");
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -1.7, 0.2);
	glScalef(0.2, 1, 1.6);

	textureArr[2] = loadTexture("light_grey.bmp");
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.8, -1.7, 0.2);
	glScalef(0.2, 1, 1.6);

	textureArr[2] = loadTexture("light_grey.bmp");
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -1.9, 0.2);
	glScalef(2, 0.2, 1.6);

	textureArr[2] = loadTexture("light_grey.bmp");
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[2]);
	glPopMatrix();

	glPopMatrix();

	//Side Body
	glPushMatrix();
	glTranslatef(3.01, -1.1, 0);
	glScalef(0.8, 0.6, 2);

	textureArr[3] = loadTexture("dark_grey.bmp");
	drawFillRightTrapezium(0.7);
	glDeleteTextures(1, &textureArr[3]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.99, -1.1, 2);
	glRotatef(180, 0, 1, 0);
	glScalef(0.8, 0.6, 2);

	textureArr[3] = loadTexture("dark_grey.bmp");
	drawFillRightTrapezium(0.7);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.01, -1.11, 1.6);
	glRotatef(180, 1, 0, 0);
	glScalef(0.6, 0.6, 1.2);

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillRightTrapezium(0.7);
	glDeleteTextures(1, &textureArr[0]);

	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glRotatef(180, 1, 0, 0);
	glTranslatef(-0.99, 1.11, 0.4);
	glScalef(0.6, 0.6, 1.15);

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillRightTrapezium(0.7);
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.4, -1.9, 0);
	glScalef(0.6, 0.2, 2);

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[0]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, -1.9, 0);
	glScalef(0.6, 0.2, 2);

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[0]);

	glPopMatrix();

	//Pant
	glPushMatrix();
	glTranslatef(0.4, -2, 0);
	glScalef(3.2, 0.15, 2);

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[0]);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -3.2, -0.2);
	glScalef(1, 1.2, 2.4);

	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(1, 1, 1);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslatef(2, -4, -2);
	glScalef(0.7, 1.5, 2);

	textureArr[3] = loadTexture("dark_grey.bmp");
	drawFillRightTrapezium(0.8);
	glDeleteTextures(1, &textureArr[3]);

	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(2.001, 0, 0);
	glScalef(0.7, 1.5, 2);

	textureArr[3] = loadTexture("dark_grey.bmp");
	drawFillRightTrapezium(0.8);
	glDeleteTextures(1, &textureArr[3]);
	glPopMatrix();

	//Triangle Light - Front view
	glPushMatrix();
	glTranslatef(2.8, -2.1, 2.01);
	glRotatef(180, 1, 0, 0);
	glScalef(0.8, 0.8, 0.8);

	textureArr[4] = loadTexture("light.bmp");
	draw2DTriangle();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.2, -2.1, 2.01);
	glRotatef(180, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glScalef(0.8, 0.8, 0.8);

	textureArr[4] = loadTexture("light.bmp");
	draw2DTriangle();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//Triangle Light - Behind view
	glPushMatrix();
	glTranslatef(2.8, -2.1, -0.01);
	glRotatef(180, 1, 0, 0);
	glScalef(0.8, 0.8, 0.8);

	textureArr[4] = loadTexture("light.bmp");
	draw2DTriangle();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.2, -2.1, -0.01);
	glRotatef(180, 1, 0, 0);
	glRotatef(180, 0, 1, 0);
	glScalef(0.8, 0.8, 0.8);

	textureArr[4] = loadTexture("light.bmp");
	draw2DTriangle();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//Square Light - Front view
	glPushMatrix();
	glTranslatef(1.7, -3, 2.21);
	glScalef(0.6, 0.8, 0.8);

	textureArr[4] = loadTexture("light.bmp");
	draw2DSquare();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//Square Light - Behind view
	glPushMatrix();
	glTranslatef(1.7, -3, -0.21);
	glScalef(0.6, 0.8, 0.8);

	textureArr[4] = loadTexture("light.bmp");
	draw2DSquare();
	glDeleteTextures(1, &textureArr[4]);
	glPopMatrix();

	//Robot Joint
	glPushMatrix();
	glTranslatef(0.8, -2.8, 1);
	glColor3f(0.83, 0.83, 0.83);
	drawFillSphere(0.4, 30, 30);
	glColor3f(0, 0, 0);
	drawLineSphere(0.4, 30, 30);
	glPopMatrix();

	//Robot Joint
	glPushMatrix();
	glTranslatef(3.2, -2.8, 1);
	glColor3f(0.83, 0.83, 0.83);
	drawFillSphere(0.4, 30, 30);
	glColor3f(0, 0, 0);
	drawLineSphere(0.4, 30, 30);
	glPopMatrix();

	//Body Backpack
	glPushMatrix();
	glScalef(2.5, 2, 0.8);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.3, -1, -0.45);

	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillTrapezium();
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	//Body Tyre 1
	glPushMatrix();
	glRotatef(30, 0, -1, 0);
	glTranslatef(2.6, -0.4, -2);

	textureArr[6] = loadTexture("tire.bmp");
	drawFillCoverCylinder(0.6, 0.4, 10, 10);
	glDeleteTextures(1, &textureArr[6]);
	glPopMatrix();

	//Body Tyre 2
	glPushMatrix();
	glRotatef(30, 0, 1, 0);
	glTranslatef(1, -0.4, 0);

	textureArr[6] = loadTexture("tire.bmp");
	drawFillCoverCylinder(0.6, 0.4, 10, 10);
	glDeleteTextures(1, &textureArr[6]);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	//---------------------------- Robot Body ---------------------------------


	glPopMatrix();

}

//************************************************************************************************

									//Robot Legs

//************************************************************************************************

void ankle() {
	glBegin(GL_POLYGON);
	//front
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.3, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.6, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.6, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.3, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, 0.0);
	glEnd();

	glBegin(GL_QUADS);
	//left
	glPushMatrix();
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.6, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.6, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.3, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.3, 0.0);

	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.0, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.3, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.3, 0.0);

	//RIGHT
	glPushMatrix();
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.6, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.6, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.3, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.3, 0.0);

	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.0, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.3, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.3, 0.0);
	glPopMatrix();
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glPushMatrix();
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.0, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, 0.3, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.6, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.6, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, 0.3, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.0, 0.5);
	glPopMatrix();
	glEnd();
}

void toe() {

	//top
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.05, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.05, 0.45);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.05, 0.45);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.05, 0.15);
	glEnd();
	glPopMatrix();

	//front
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.05, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.05, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.6, -0.2, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, -0.2, 0.0);
	glEnd();
	glPopMatrix();

	//left    
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.05, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.05, 0.45);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, -0.2, 0.6);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, -0.2, 0.0);
	glEnd();
	glPopMatrix();

	//right
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.05, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.05, 0.45);
	glTexCoord2f(1, 1);
	glVertex3f(0.6, -0.2, 0.6);
	glTexCoord2f(1, 1);
	glVertex3f(0.6, -0.2, 0.0);
	glEnd();
	glPopMatrix();

	//back
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-0.3, 0.05, 0.45);
	glTexCoord2f(1, 1);
	glVertex3f(0.3, 0.05, 0.45);
	glTexCoord2f(1, 1);
	glVertex3f(0.6, -0.2, 0.6);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, -0.2, 0.6);
	glEnd();
	glPopMatrix();


	//bottom
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(0.6, -0.2, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.6, -0.2, 0.6);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, -0.2, 0.6);
	glTexCoord2f(1, 1);
	glVertex3f(-0.6, -0.2, 0.0);
	glEnd();
	glPopMatrix();

}

void robotLeg(float movef) {
	glPushMatrix();
	///////////////////////////////////////////////////////////////////////////

	glPushMatrix();
	glRotatef(-(movef), 1.0, 0.0, 0.0);

	glTranslatef(-1.2, 5.4, 0.0);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(2, 2, 1.5);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-(movef), 1.0, 0.0, 0.0);

	glTranslatef(-1.2, 3.4, 0.0);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(2, 2, 1.5);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();


	glRotatef((movef), 1.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(-0.2, 4.0, 0.7);
	textureArr[1] = loadTexture("steel.bmp");
	drawFillSphere(0.8, 30, 30);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -0.2);
	glRotatef((movef), 1.0, 0.0, 0.0);
	glRotatef((movef), 1.0, 0.0, 0.0);


	glPushMatrix();
	glScaled(1.8, 3.0, 3.0);
	glTranslatef(-0.1, 1.2, -0.05);
	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	toe();
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-0.3, 2, 0.0);
	textureArr[6] = loadTexture("tire.bmp");
	drawFillCoverCylinder(0.75, 1, 10, 10);
	glDeleteTextures(1, &textureArr[6]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3, -0.0, 0.0);
	textureArr[6] = loadTexture("tire.bmp");
	drawFillCoverCylinder(0.75, 1, 10, 10);
	glDeleteTextures(1, &textureArr[6]);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.2, -1.0, 0.0);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(2, 2, 1.5);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.2, 1.0, 0.0);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCube(2, 2, 1.5);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.8, -2.3, -0.2);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0.1, 0.1, 2, 15, 15);
	glDeleteTextures(1, &textureArr[1]);
	glTranslatef(-1.95, 0, 0);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	drawFillCylinder(0.1, 0.1, 2, 15, 15);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();

	glPushMatrix();
	glScaled(1.8, 3.0, 3.0);
	glRotatef(180.0, 1.0, 0.0, 0.0);
	glTranslatef(-0.10, 0.52, -0.55);
	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	toe();
	glDeleteTextures(1, &textureArr[0]);
	glScaled(2.0, 1.0, 1.0);
	glTranslatef(0.0, 0.0, 0.1);
	if (change == 0) {
		textureArr[1] = loadTexture("blue.bmp");
	}
	else if (change == 1) {
		textureArr[1] = loadTexture("orange.bmp");
	}
	else if (change == 2) {
		textureArr[1] = loadTexture("purplesteel.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	ankle();
	glDeleteTextures(1, &textureArr[1]);
	glTranslatef(0.3, 0.65, 0.25);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	if (change == 0) {
		textureArr[0] = loadTexture("red.bmp");
	}
	else if (change == 1) {
		textureArr[0] = loadTexture("yellow.bmp");
	}
	else if (change == 2) {
		textureArr[0] = loadTexture("green.bmp");
	}
	glColor3f(1.0, 1.0, 1.0);
	toe();
	glDeleteTextures(1, &textureArr[0]);
	glPopMatrix();

	glPopMatrix();


	glPopMatrix();




	///////////////////////////////////////////////////////////////////////////


}

//************************************************************************************************

									//Background

//************************************************************************************************

void bigbackground() {
	GLuint textureArr[1];
	textureArr[0] = loadTexture("sky.bmp");
	glColor3f(1.0, 1.0, 1.0);
	drawFillSphere(100, 30, 30);
	glDeleteTextures(1, &textureArr[0]);
	glDisable(GL_TEXTURE_2D);
}

void background() {
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex2f(-10, -10);
	glTexCoord2f(1, 1);
	glVertex2f(-10, 10);
	glTexCoord2f(1, 0);
	glVertex2f(10, 10);
	glTexCoord2f(0, 0);
	glVertex2f(10, -10);
	glEnd();
}

void flatbackground() {
	GLuint textureArr[1];
	textureArr[0] = loadTexture("sky.bmp");
	glColor3f(1.0, 1.0, 1.0);	
	glScalef(50.0, 50.0, 0.0);
	glTranslatef(0.0, 0.0, 50.0);
	background();
	glDeleteTextures(1, &textureArr[0]);
	glDisable(GL_TEXTURE_2D);
}

//************************************************************************************************

									//Display

//************************************************************************************************

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Apply depth to display every face of the cube
	glClearColor(0.8, 0.9, 0.75, 0.0f);
	glEnable(GL_DEPTH_TEST); //Test the depth

	if (bg == false) {
		flatbackground();
	}
	else if (bg == true) {
		bigbackground();
	}

	//--------------------------------
	//	Projection
	//--------------------------------
	projection();

	//--------------------------------
	//	Lighting
	//--------------------------------
	lighting();


	//--------------------------------
	//	OpenGL drawing Robot
	//--------------------------------
	glScalef(0.7, 0.7, 0.7);
	glRotatef(180, 0, 1, 0);


	glPushMatrix();
	glRotatef(angle_view, 1, 1, 1); //View Robot Rotation
	glTranslatef(0, 2, 0);

	//*********************************
	//	Robot Head
	//*********************************
	glPushMatrix();
	glTranslatef(-0.5, 1.9, 1.2);
	glRotatef(180, 0.0, 1.0, 0.0);
	glScalef(1.4, 1, 1.4);
	robotHead();
	glPopMatrix();

	//*********************************
	//	Robot Hands & Body
	//*********************************
	glPushMatrix();
	glTranslatef(0, 0, 0);
	robot_rightHand(); //Robot Right Hand
	robot_leftHand(); //Robot Left Hand
	robot_body(); //Robot Body
	glPopMatrix();


	//*********************************
	//	Robot Legs
	//*********************************
	//left leg
	glPushMatrix();
	glTranslatef(-1.7, -7, 0);
	glScalef(0.5, 0.5, 0.5);
	robotLeg(movefleft); //Robot leg
	glPopMatrix();

	//right leg
	glPushMatrix();
	glTranslatef(1, -7, 0);
	glScalef(0.5, 0.5, 0.5);
	robotLeg(movefright); //Robot leg
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 1);
	drawFillHexagon();
	drawLineSphere(0.25, 30, 30);
	glPopMatrix();


	glPopMatrix();

	//glDisable(GL_DEPTH_TEST);
	

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
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
		CW_USEDEFAULT, CW_USEDEFAULT, 900, 900,
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