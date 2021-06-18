#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>

char TEXTURA_DO_PLANO[13] = "chao.rgb";
GLuint  textura_plano;

void material(float r, float g, float b, float a, float s)
{
	GLfloat ambiente[] = { r/2, g/2, b/2, a };
	GLfloat difusa[] = { r, g, b, a };
	GLfloat especular[] = { s, s, s, a };
	GLfloat brilho[] = { 50 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

GLfloat posicao_luz[] = { 0.0, 3.0, 0.0, 1.0 };
GLfloat cor_luz[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat cor_luz_amb[] = { 0.7, 0.7, 0.7, 1.0 };

static int rot = 0;
static int pos = 0;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
	int light = GL_LIGHT0;
	
	glLightfv(light, GL_DIFFUSE, cor_luz);
	glLightfv(light, GL_SPECULAR, cor_luz);
	glLightfv(light, GL_AMBIENT, cor_luz_amb);
	glLightfv(light, GL_POSITION, posicao_luz);

	glEnable(GL_LIGHTING);
	glEnable(light);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
}

float toSee = 50;

void chao()
{
	material(1, 1, 0, 1, 1);

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(500 / toSee, 2 / toSee, 300 / toSee);
	glutSolidCube(1.0);
	glPopMatrix();
}

void rodinha(float x, float z)
{
	glPushMatrix();
	glTranslatef(x, 6 / toSee, z);
	glutSolidSphere(5 / toSee, 20, 20);
	glPopMatrix();
}

void rodinhas()
{
	float y = 1;
	material(1, 0, 0, 1, 1);

	float position = 45 / toSee;
	rodinha(position, position);
	rodinha(-position, position);
	rodinha(position, -position);
	rodinha(-position, -position);
}

void maquina()
{
	material(0, 0, 1, 1, 1);

	glPushMatrix();
	glTranslatef(0, 71 / toSee, 0);
	glScalef(100 / toSee, 120 / toSee, 100 / toSee);
	glutSolidCube(1.0);
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
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
	gluPerspective(65.0, w * 1.0 / h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, -3.0, -10.0);
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
	        pos++;
	        glutPostRedisplay();
	        break;
	    case 's':
	        pos--;
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
