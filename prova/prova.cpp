#include <cstdlib>
#include <GL/glut.h>

static int rot = 0;
static int pos = 0;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
}

void chao()
{
	glColor3f(1, 1, 0);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(500, 2, 300);
	glutSolidCube(1.0);
	glPopMatrix();
}

void rodinha(float x, float z)
{
	glPushMatrix();
	glTranslatef(x, 6, z);
	glutSolidSphere(5, 20, 20);
	glPopMatrix();
}

void rodinhas()
{
	glColor3f(1, 0, 0);

	float position = 45;
	rodinha(position, position);
	rodinha(-position, position);
	rodinha(position, -position);
	rodinha(-position, -position);
}

void maquina()
{
	glColor3f(0, 0, 1);

	glPushMatrix();
	glTranslatef(0, 71, 0);
	glScalef(100, 120, 100);
	glutSolidCube(1.0);
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glTranslatef(0, 0, pos);
	glRotatef(rot, 0.0, 1.0, 0.0);

    chao();
	maquina();
	rodinhas();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, w * 1.0 / h, 1.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, -66.0, -300.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
	    case 'a':
	        rot = (rot + 5) % 360;
	        glutPostRedisplay();
	        break;
	    case 'd':
	        rot = (rot - 5) % 360;
	        glutPostRedisplay();
	        break;
	    case 'w':
	        pos+=10;
	        glutPostRedisplay();
	        break;
	    case 's':
	        pos-=10;
	        glutPostRedisplay();
	        break;
	    case 27:                                         // tecla Esc (encerra o programa)
	        exit(0);
    }
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
