#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mScene = new Scene;

	vpAux = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	camAux = new Camera(vpAux);
	sceneAux = new Scene;

	mCamera->set2D();
	mScene->init(1);

	activeCam = mCamera;
	activeScene = mScene;

	mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL()
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   

	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	glutIdleFunc(s_update);
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion); 
	glutMouseWheelFunc(s_mouseWheel);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free()
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;

	delete sceneAux; sceneAux = nullptr;
	delete camAux; camAux = nullptr;
	delete vpAux; vpAux = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display()
{  // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (m2Vistas) { 
		
		mScene->render(*mCamera);
		sceneAux->render(*camAux);
	}

	else mScene->render(*mCamera);;

	glutSwapBuffers();	// swaps the front and back buffer
}
//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	activeCam->setSize(mViewPort->width(), mViewPort->height());
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		activeCam->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		activeCam->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		activeCam->set3D();
		break;
	case 'o':
		activeCam->setCenital();
		break;
	case 'u':
		activeScene->update();;
		break;
	case 'U':
		updating = !updating;//Actualizar escena
		break;
	case 'f':
		mScene->capturaPantalla("save.bmp");//Guardar captura
		break;
	case 'p':
		activeCam->changePrj();
		break;
	case 'k':
		m2Vistas = !m2Vistas;
		if (!m2Vistas) display1V();
		else display2V();
		break;
	case '0':
		mScene->changeScene(0);//Cambia a la escena 0
		break;
	case '1':
		mScene->changeScene(1);//Cambia a la escena 1
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//activeCam->pitch(-1);   // rotates -1 on the X axis
			//activeCam->moveFB(1);
			activeCam->rollReal(1);
		else
			//activeCam->pitch(1);    // rotates 1 on the X axis
			//activeCam->moveLR(1);
			activeCam->pitchReal(1);
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//activeCam->yaw(1);      // rotates 1 on the Y axis 
			//activeCam->moveFB(-1);
			activeCam->rollReal(-1);
		else
			//activeCam->yaw(-1);     // rotate -1 on the Y axis 
			//activeCam->moveLR(-1);
			activeCam->pitchReal(-1);
			
		break;
	case GLUT_KEY_UP:
		//activeCam->roll(1);    // rotates 1 on the Z axis
		//activeCam->moveUD(1);
		activeCam->yawReal(1);
		break;
	case GLUT_KEY_DOWN:
		//activeCam->roll(-1);   // rotates -1 on the Z axis
		//activeCam->moveUD(-1);
		activeCam->yawReal(-1);
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::update() {
	//ms desde inicio

	if (updating) {
		if (glutGet(GLUT_ELAPSED_TIME) - mLastUpdateTime > (1000 / 60)) {
			activeScene->update();
			mLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
			glutPostRedisplay();
		}
	}
}

void IG1App::mouse(int button, int state, int x, int y)
{
	mMouseButt = button;

	y = glutGet(GLUT_WINDOW_HEIGHT) - y;

	mMouseCoord = glm::dvec2(x, y);
}

void IG1App::motion(int x, int y)
{
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;

	glm::dvec2 newPos = glm::dvec2(x, y);

	glm::dvec2 mp = mMouseCoord - newPos;

	mMouseCoord = glm::dvec2(x, y);

	if (m2Vistas) {
	
		int width = glutGet(GLUT_WINDOW_WIDTH);
		if (mMouseCoord.x < glutGet(GLUT_WINDOW_WIDTH) / 2) {

			activeCam = mCamera;
			activeScene = mScene;
		}
		else {

			activeCam = camAux;
			activeScene = sceneAux;
		}
	}

	if (mMouseButt == GLUT_LEFT_BUTTON) {
	
		activeCam->orbit(mp.x * 0.05, mp.y);
	}
	else if (mMouseButt == GLUT_RIGHT_BUTTON) {
	
		activeCam->moveUD(mp.y);
		activeCam->moveLR(mp.x);
	}

	glutPostRedisplay();
}

void IG1App::mouseWheel(int wheelButtonNumber, int direction, int x, int y)
{
	int tecla = glutGetModifiers();

	y = glutGet(GLUT_WINDOW_HEIGHT) - y;
	mMouseCoord = glm::dvec2(x, y);

	if (m2Vistas) {

		if (mMouseCoord.x < glutGet(GLUT_WINDOW_WIDTH) / 2) {

			activeCam = mCamera;
			activeScene = mScene;
		}
		else {

			activeCam = camAux;
			activeScene = sceneAux;
		}
	}

	if (!tecla) {
	
		activeCam->moveFB(direction*10);
	}
	else if (GLUT_ACTIVE_CTRL) {
	
		activeCam->setScale(0.1*direction);
	}

	glutPostRedisplay();
}

void IG1App::display2V()
{
	mViewPort->setSize(mWinW / 2, mWinH);
	vpAux->setSize(mWinW / 2, mWinH);

	mCamera->setSize(mViewPort->width(), mViewPort->height());

	//Viewport 1
	mViewPort->setPos(0, 0);
	mCamera->set3D();
	mScene->changeScene(1);
	mScene->render(*mCamera);

	camAux->setSize(vpAux->width(), vpAux->height());

	//Viewport 2
	vpAux->setPos(mWinW / 2, 0);
	camAux->set2D();
	sceneAux->changeScene(0);
	sceneAux->render(*camAux);
}

void IG1App::display1V()
{
	mViewPort->setSize(mWinW, mWinH);

	mCamera->setSize(mViewPort->width(), mViewPort->height());

	mViewPort->setPos(0, 0);
	mCamera->set3D();
	mScene->changeScene(1);
	mScene->render(*mCamera);

	activeCam = mCamera;
	activeScene = mScene;
}
