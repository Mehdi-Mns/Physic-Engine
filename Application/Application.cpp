// Physics-engine.cpp : définit le point d'entrée pour l'application console.
// Demonstrates the Quantum physics engine with OpenGL rendering.

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <ctime>
#include <string>

#include "Quantum.h"
#include "GxWorld.h"
#include "GxParticle.h"
#include "HalfSpace.h"
#include "GxUpdater.h"

using namespace std;
using namespace Quantum;

// ------------------- Worlds -------------------

GxWorld gxWorld;
QmWorld pxWorld;

glm::vec3* mousePointer;
QmParticle* mousP;

int scene = 0;


// ------------------- OpenGL/GLUT Variables -------------------
// Global variables

int SCREEN_X = 800;
int SCREEN_Y = 800;
int VIEWPORT_X = 5; int VIEWPORT_Y = 5; int VIEWPORT_Z = 200;

GLuint DrawListSphere;

int buttons = 0;
float camRotate = 90.f;
float camDist = 30.f;
float camHeight = 0.f;
float mx = 0.f;
float my = 0.f;

// Framerate calculation variables
int timeold = 0;
int frame = 0;
float accTime = 0.0;
bool paused = false;
bool g = false;
bool uDel = false;
bool euler = true;
bool col = false;
int K = 8;
int charge = 0;
float damping = 1.0f;


GLfloat light_pos[] = { 0.0, 6.0, 1.0, 1.0 };


// ------------------- Utility Functions -------------------

/**
 * @brief Generates a random 3D vector with each component in the range [min, max].
 * @param min Minimum value for each component
 * @param max Maximum value for each component
 * @return glm::vec3 Random vector
 */
glm::vec3 randomVector(float min, float max)
{
	float x = min + (max - min)*((rand() % 100) / 100.f);
	float y = min + (max - min)*((rand() % 100) / 100.f);
	float z = min + (max - min)*((rand() % 100) / 100.f);
	return glm::vec3(x, y, z);

}

/**
 * @brief Creates a physics particle with a matching graphics particle.
 * @return QmParticle* Pointer to the created physics particle
 */
QmParticle* createParticle()
{
	glm::vec3 pos = randomVector(-5, 5);
	float rad = 0.1f + 0.2f*((rand() % 100) / 100.f);
	GxParticle* g = new GxParticle(randomVector(1, 0), rad, pos);
	QmParticle* p = new QmParticle(pos, randomVector(-1, 1), randomVector(-1, 1), 1, 0, rad, 1);
	p->setUpdater(new GxUpdater(g));
	gxWorld.addParticle(g);
	pxWorld.addBody(p);
	return p;
}

/**
 * @brief Creates a particle for the fountain scene.
 *
 * Spawns the particle at the mouse pointer location with initial upward velocity and gravity acting on it.
 * Also creates a corresponding graphics particle and attaches a GxUpdater.
 */
QmParticle* createParticleFontaine()
{
	glm::vec3 pos = *mousePointer;
	float rad = 0.1f + 0.2f*((rand() % 100) / 100.f);
	GxParticle* g = new GxParticle(randomVector(1, 0), rad, pos);
	QmParticle* p = new QmParticle(pos, glm::vec3(-5 + 10 * ((rand() % 100) / 100.f), 15, 0), glm::vec3(0, -9.81, 0), 1, 0, rad, 1);
	p->setUpdater(new GxUpdater(g));
	gxWorld.addParticle(g);
	pxWorld.addBody(p);
	return p;
}

/**
 * @brief Creates a particle with drag force applied.
 *
 * The particle is spawned at the mouse pointer location. A QmDrag force generator
 * is registered to apply drag in the physics world.
 */
QmParticle* createParticleDrag()
{
	glm::vec3 pos = *mousePointer;
	float rad = 0.1f + 0.2f*((rand() % 100) / 100.f);
	GxParticle* g = new GxParticle(randomVector(1, 0), rad, pos);
	QmParticle* p = new QmParticle(pos, glm::vec3(-3 + 6 * ((rand() % 100) / 100.f), 10, 0), glm::vec3(0, 0, 0), 2, 0, rad, 1);
	QmDrag* drag = new QmDrag(4 * ((rand() % 100) / 100.f), 0.7 * ((rand() % 100) / 100.f));
	QmForceGenerator* fg = (QmForceGenerator*)drag;
	QmForceRegistry* fr = new QmForceRegistry(p, fg);
	pxWorld.AddForceRegistry(fr);
	p->setUpdater(new GxUpdater(g));
	gxWorld.addParticle(g);
	pxWorld.addBody(p);
	return p;
}

/**
 * @brief Creates two magnetic particles that interact with each other and optionally with a fixed mouse particle.
 *
 * Particles are assigned positive and negative charges, and QmMagnetism/QmFixedMagnetism forces are registered.
 */
QmParticle* createParticleMagnet()
{
	glm::vec3 posp = randomVector(-6, 6);
	GxParticle* gp = new GxParticle(glm::vec3(1, 0, 0), 0.4f, posp);
	QmParticle* pp = new QmParticle(posp, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.1, 3, 0.2f, 1);
	glm::vec3 posn = randomVector(-6, 6);
	GxParticle* gn = new GxParticle(glm::vec3(0, 0, 1), 0.4f, posn);
	QmParticle* pn = new QmParticle(posn, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.1, -3, 0.2f, 1);

	QmMagnetism* mag1 = new QmMagnetism(0.2, pn);
	QmForceGenerator* fg1 = (QmForceGenerator*)mag1;
	QmForceRegistry* fr1 = new QmForceRegistry(pp, fg1);
	pxWorld.AddForceRegistry(fr1);
	QmMagnetism* mag2 = new QmMagnetism(0.2, pp);
	QmForceGenerator* fg2 = (QmForceGenerator*)mag2;
	QmForceRegistry* fr2 = new QmForceRegistry(pn, fg2);
	pxWorld.AddForceRegistry(fr2);

	QmFixedMagnetism* magfix1 = new QmFixedMagnetism(0.4,mousP);
	QmForceGenerator* fgf1 = (QmForceGenerator*)magfix1;
	QmForceRegistry* frf1 = new QmForceRegistry(pp, fgf1);
	pxWorld.AddForceRegistry(frf1);
	QmFixedMagnetism* magfix2 = new QmFixedMagnetism(0.4, mousP);
	QmForceGenerator* fgf2 = (QmForceGenerator*)magfix2;
	QmForceRegistry* frf2 = new QmForceRegistry(pn, fgf2);
	pxWorld.AddForceRegistry(frf2);

	pp->setUpdater(new GxUpdater(gp));
	gxWorld.addParticle(gp);
	pxWorld.addBody(pp);
	pn->setUpdater(new GxUpdater(gn));
	gxWorld.addParticle(gn);
	pxWorld.addBody(pn);
	return pp;
}

/**
 * @brief Creates a particle connected to another particle with a spring.
 * @param part The particle to which the new particle is attached
 * @param lo Rest length of the spring
 * @return QmParticle* Pointer to the newly created particle
 *
 * The function creates a graphics particle, a physics particle, and a QmSpring force connecting them.
 * The force is registered in the physics world, and the particle is added to both worlds.
 */
QmParticle* createParticleSpring(QmParticle* part, int lo)
{
	GxParticle* g = new GxParticle(randomVector(1, 0), 0.3f, part->getPos() - glm::vec3(0,3,0));
	QmParticle* p = new QmParticle(part->getPos() - glm::vec3(-3 + 6 * (rand() % 100) / 100.f, 3, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 2, 0, 0.3f, 1);
	
	QmSpring* spring = new QmSpring(K, lo, part);
	QmForceGenerator* fg = (QmForceGenerator*)spring;
	QmForceRegistry* fr = new QmForceRegistry(p, fg);
	pxWorld.AddForceRegistry(fr);
	p->setUpdater(new GxUpdater(g));
	gxWorld.addParticle(g);
	pxWorld.addBody(p);
	return p;
}

/**
 * @brief Creates a particle connected to a fixed point with a spring.
 * @param pos The fixed point in space
 * @param lo Rest length of the spring
 * @return QmParticle* Pointer to the newly created particle
 *
 * Similar to createParticleSpring but uses a QmFixedSpring attached to a fixed position.
 * Used for creating anchored spring structures.
 */
QmParticle* createParticleFixedSpring(glm::vec3 pos, int lo)
{
	GxParticle* g = new GxParticle(randomVector(1, 0), 0.3f, pos - glm::vec3(0, 3, 0));
	QmParticle* p = new QmParticle(pos - glm::vec3(-3 + 6 * (rand() % 100) / 100.f, 3, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 2, 0, 0.3f, 1);

	QmFixedSpring* fixspring = new QmFixedSpring(K, lo, pos);
	QmForceGenerator* fg = (QmForceGenerator*)fixspring;
	QmForceRegistry* fr = new QmForceRegistry(p, fg);
	pxWorld.AddForceRegistry(fr);
	p->setUpdater(new GxUpdater(g));
	gxWorld.addParticle(g);
	pxWorld.addBody(p);
	return p;
}

/**
 * @brief Creates a tetrahedral particle structure attached to a base particle.
 * @param part The base particle
 * @param lo Spring rest length
 * @return QmParticle* Pointer to the last created particle in the tetrahedron
 *
 * This function spawns 3 particles connected to the base particle with springs, then creates
 * additional springs between them to form a tetrahedron. Useful for soft-body simulations.
 */
QmParticle* createTethra(QmParticle* part, int lo) 
{
	QmParticle* p1 = createParticleSpring(part, 2);
	QmParticle* p2 = createParticleSpring(part, 2);
	QmParticle* p3 = createParticleSpring(part, 2);

	QmSpring* spring11 = new QmSpring(K, 1, p2);
	QmForceGenerator* fg11 = (QmForceGenerator*)spring11;
	QmForceRegistry* fr11 = new QmForceRegistry(p1, fg11);
	pxWorld.AddForceRegistry(fr11);

	QmSpring* spring21 = new QmSpring(K, 1, p3);
	QmForceGenerator* fg21 = (QmForceGenerator*)spring21;
	QmForceRegistry* fr21 = new QmForceRegistry(p2, fg21);
	pxWorld.AddForceRegistry(fr21);

	QmSpring* spring31 = new QmSpring(K, 1, p1);
	QmForceGenerator* fg31 = (QmForceGenerator*)spring31;
	QmForceRegistry* fr31 = new QmForceRegistry(p3, fg31);
	pxWorld.AddForceRegistry(fr31);

	QmParticle* p4 = createParticleSpring(p1, 2);
	QmSpring* spring22 = new QmSpring(K, 1, p2);
	QmForceGenerator* fg22 = (QmForceGenerator*)spring22;
	QmForceRegistry* fr22 = new QmForceRegistry(p4, fg22);
	pxWorld.AddForceRegistry(fr22);
	QmSpring* spring32 = new QmSpring(K, 1, p3);
	QmForceGenerator* fg32 = (QmForceGenerator*)spring32;
	QmForceRegistry* fr32 = new QmForceRegistry(p4, fg32);
	pxWorld.AddForceRegistry(fr32);

	return p4;
}

/**
 * @brief Creates a box particle for collision demonstration.
 * @return QmParticle* Pointer to the created particle
 *
 * Particles are spawned randomly and can collide with static boxes in the scene.
 * Both graphics and physics representations are created.
 */
QmParticle* createParticleBox()
{
	glm::vec3 pos = randomVector(-5, 5);
	GxParticle* g = new GxParticle(randomVector(1, 0), 0.3f, pos);
	QmParticle* p = new QmParticle(pos, randomVector(-4, 4), randomVector(1, 2), 1, 0, 0.3f, 1);
	p->setUpdater(new GxUpdater(g));
	gxWorld.addParticle(g);
	pxWorld.addBody(p);
	return p;
}


// ------------------- Scene Initialization -------------------

/**
 * @brief Initializes scene 1: random free particles
 */
void initScene1()
{
	printf("Scene 1: Random particles.\n");
	printf("Type space to pause.\n");
	printf("Type g to toggle gravity.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	for (int i = 0; i < 100; i++)
		createParticle();
}

/**
 * @brief Initializes scene 2: magnetism
 */
void initScene2()
{
	printf("Scene 2.\n");
	printf("Magnetism.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	mousP = new QmParticle(*mousePointer, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.1, 0, 0.2f, 0);
	pxWorld.addBody(mousP);
	for (int i = 0; i < 50; i++)
		createParticleMagnet();
}

/**
 * @brief Initializes scene 3: springs / tethers
 */
void initScene3()
{
	printf("Scene 3.\n");
	printf("Ressort.\n");
	mousePointer = new glm::vec3(0, 4.5, 0);
	mousP = new QmParticle(*mousePointer, glm::vec3(0, 0, 0), glm::vec3(0, 0, 9.81), 0.1, 0, 0.2f, 0);
	pxWorld.addBody(mousP);
	//QmParticle* begin = createParticleFixedSpring(*mousePointer, 1);
	QmParticle* n1 = createTethra(mousP, 2);
	QmParticle* n2 = createTethra(n1, 3);

}

/**
 * @brief Initializes scene 4: box collisions
 */
void initScene4()
{
	printf("Scene 4.\n");
	printf("Colision Box");
	mousePointer = new glm::vec3(0, 4.5, 0);
	pxWorld.CreateBox();
	for (int i = 0; i < 100; i++)
		createParticleBox();
}


// ------------------- GLUT Callbacks -------------------

void resetView()
{
	camRotate = 90.f;
	camDist = 30.f;
	camHeight = 0.f;
	mx = 0.f;
	my = 0.f;
	if (mousePointer) {
		delete mousePointer;
		mousePointer = NULL;
	}
}

void createDisplayListSphere()
{
	DrawListSphere = glGenLists(1);
	glNewList(DrawListSphere, GL_COMPILE);
	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, 1, 12, 8);
	glEndList();
}

void initLight()
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);

	GLfloat ambient_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuse_light[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
}

void calculateFPS(float dt)
{
	accTime += dt;

	if (accTime > 0.5)
	{
		char t[200];
		sprintf_s(t, "Quantum Physics Engine: Scene %d, %.2f FPS", scene, frame / accTime);
		glutSetWindowTitle(t);
		accTime = 0.0;
		frame = 0;
	}
}

/**
 * @brief Idle function for GLUT: advances simulation
 */
void idleFunc()
{
	int timer = glutGet(GLUT_ELAPSED_TIME);
	float dt = (float)(timer - timeold) / 1000.f;
	timeold = timer;

	calculateFPS(dt);
	if (!paused) pxWorld.simulate(dt, g, uDel, damping, euler, col);

	glutPostRedisplay();
}

/**
 * @brief Draw function for GLUT: renders all particles
 */
void drawFunc()
{
	frame++;
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camDist * cos(camRotate), camHeight, camDist * sin(camRotate), 0, camHeight, 0, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	if(scene == 3)
		for (QmForceRegistry* fr : pxWorld.getForces())
		{
			/*if ((QmFixedSpring*)(fr->getForceGen()))
			{
				glm::vec3 pos1 = fr->getPart()->getPos();
				glm::vec3 pos2 = ((QmFixedSpring*)fr->getForceGen())->fix;
				glBegin(GL_LINES);
				glColor3f(1.f, 0.5f, 0.5f);
				glVertex3f(pos1.x, pos1.y, pos1.z);
				glVertex3f(pos2.x, pos2.y, pos2.z);
				glEnd();
			}*/
			if ((QmSpring*)(fr->getForceGen()))
			{
				glm::vec3 pos1 = fr->getPart()->getPos();
				glm::vec3 pos2 = ((QmSpring*)fr->getForceGen())->part->getPos();
				glBegin(GL_LINES);
				glColor3f(1.f, 1.f, 1.f);
				glVertex3f(pos1.x, pos1.y, pos1.z);
				glVertex3f(pos2.x, pos2.y, pos2.z);
				glEnd();
			}
		}

	if (scene == 4)
	{
		glBegin(GL_LINES);
		glColor3f(1.f, 1.f, 1.f);
		glVertex3f(-6, -6, -6);
		glVertex3f(6, -6, -6);
		glVertex3f(-6, 6, -6);
		glVertex3f(6, 6, -6);
		glVertex3f(-6, -6, 6);
		glVertex3f(6, -6, 6);
		glVertex3f(-6, 6, 6);
		glVertex3f(6, 6, 6);

		glVertex3f(-6, -6, -6);
		glVertex3f(-6, -6, 6);
		glVertex3f(-6, 6, -6);
		glVertex3f(-6, 6, 6);
		glVertex3f(6, -6, -6);
		glVertex3f(6, -6, 6);
		glVertex3f(6, 6, -6);
		glVertex3f(6, 6, 6);

		glVertex3f(6, 6, -6);
		glVertex3f(6, -6, -6);
		glVertex3f(6, 6, 6);
		glVertex3f(6, -6, 6);
		glVertex3f(6, 6, -6);
		glVertex3f(6, -6, -6);
		glVertex3f(6, 6, 6);
		glVertex3f(6, -6, 6);

		glVertex3f(-6, 6, -6);
		glVertex3f(-6, -6, -6);
		glVertex3f(-6, 6, 6);
		glVertex3f(-6, -6, 6);
		glVertex3f(-6, 6, -6);
		glVertex3f(-6, -6, -6);
		glVertex3f(-6, 6, 6);
		glVertex3f(-6, -6, 6);
		glEnd();
	}

	for (GxParticle* p : gxWorld.getParticles())
	{
		glPushMatrix();
		glm::vec3 color = p->getColor();
		glColor3f(color.x, color.y, color.z);
		glTranslatef(p->getPos().x, p->getPos().y, p->getPos().z);
		glScaled(p->getRadius(), p->getRadius(), p->getRadius());
		glCallList(DrawListSphere);
		glPopMatrix();
	}
	if (mousePointer) {
		glPushMatrix();
		glColor3f(1.f, 1.f, 1.f);
		glTranslatef(mousePointer->x, mousePointer->y, mousePointer->z);
		glScaled(0.1f, 0.1f, 0.1f);
		glCallList(DrawListSphere);
		glPopMatrix();
	}
	glutSwapBuffers();
}


// ------------------- Input Handling -------------------

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) buttons = 1;
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) buttons = 2;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) buttons = 3;
	if (button == 3) camDist /= 1.07f;
	if (button == 4) camDist *= 1.07f;
	if (state == GLUT_UP) buttons = 0;

	mx = (float)x;
	my = (float)y;
}

void motionFunc(int x, int y)
{
	if (buttons == 1)
	{
		camRotate += (x - mx) / 100.f;
		camHeight += (y - my) * camDist / 1000.f;
	}
	if (buttons == 3)
	{
		if (mousePointer)
		*mousePointer += glm::vec3(x - mx, my - y, 0.f) / 15.f;
		if (scene==3 || scene ==2)
			mousP->setPos(*mousePointer);
	}

	mx = (float)x;
	my = (float)y;
}

void clearWorld()
{
	gxWorld.clear();
	pxWorld.clear();

}

void toggleScene(int s)
{
	clearWorld();
	scene = s;
	resetView();

	switch (scene)
	{
	case 1: initScene1(); break;
	case 2: initScene2(); break;
	case 3: initScene3(); break;
	case 4: initScene4(); break;
	}
}

/**
 * @brief Keyboard input handler: toggles scenes, pause, gravity, damping, etc.
 */
void keyFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': case 'Q': case 27:
		clearWorld();
		glDeleteLists(DrawListSphere, 1);
		exit(0);
		break;
	case '1':
		clearWorld();
		toggleScene(1);
		break;
	case '2':
		clearWorld();
		toggleScene(2);
		break;
	case '3':
		clearWorld();
		toggleScene(3);
		break;
	case '4':
		clearWorld();
		toggleScene(4);
		break;
	case ' ': 
		paused = !paused; 
		break;
	case 'g':
		g = !g;
		break;
	case 'u':
		uDel = !uDel;
		break;
	case 'f':
		if (scene == 1)
			for (int i = 0; i < 10; i++)
				createParticleFontaine();
		break;
	case 'p':
		if (scene == 1)
			for (int i = 0; i < 10; i++)
				createParticleDrag();
		break;
	case 'm':
		if (scene == 2) {
			//delete mousP;
			charge = (charge++) % 3;
			if (charge == 0) {
				mousP = new QmParticle(*mousePointer, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 0.1, 0, 0.2f, 0);
				pxWorld.addBody(mousP);
			}
			else if (charge == 1)
				mousP->setCharge(15);
			else if (charge == 2)
				mousP->setCharge(-15);
		}
		break;
	case 'a':
		if (damping == 1.0f)
			damping = 0.995f;
		else
			damping = 1.0f;
		break;
	case 'd':
		damping -= 0.005f;
		break;
	case 'D':
		damping += 0.005f;
		break;
	case 'k':
		if(K > 2)
			if (scene == 3)
			{
				K--;
				pxWorld.ChangeRaideur(K);
			} 
		break;
	case 'K':
		if (K < 15)
			if (scene == 3)
			{
				K++;
				pxWorld.ChangeRaideur(K);
			}
		break;
	case 'e':
		euler = !euler;
		break;
	case 'c':
		col = !col;
		break;
	default:
		break;
	}
}

// ------------------- Graphics Initialization -------------------

/**
 * @brief Sets up OpenGL/GLUT, lighting, projection, and display list
 */
void initGraphics(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutCreateWindow("Quantum Demo");

	glutIdleFunc(idleFunc);
	glutDisplayFunc(drawFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutKeyboardFunc(keyFunc);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_PROGRAM_POINT_SIZE);
	//glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = SCREEN_X / (float)SCREEN_Y;
	gluPerspective(45.0, aspect, 1.0, VIEWPORT_Z);
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	createDisplayListSphere();
	initLight();
}


// ------------------- Main -------------------

int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	initGraphics(argc, argv);

	toggleScene(1);

	glutMainLoop();
	return 0;
}




