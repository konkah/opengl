#include <cstdlib>
#include <GL/glut.h>

static int rot = 0;
static int pos = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void asa(int x)
{
	glPushMatrix();
	glTranslatef(x * 0.3, 1.8, -0.3);
	glScalef(0.3, 0.2, 0.9);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x * 0.9, 1.8, -0.3);
	glScalef(0.3, 0.2, 0.9);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x * 0.6, 2.0, 0);
	glScalef(0.9, 0.2, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x * 0.6, 2.0, -0.6);
	glScalef(0.9, 0.2, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();
}

void cauda()
{
	glPushMatrix();
	glTranslatef(0, 1.8, -1.5);
	glScalef(0.9, 0.2, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2.0, -1.5);
	glScalef(0.9, 0.2, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2.2, -1.5);
	glScalef(0.9, 0.2, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();
}

void corpo()
{
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(0.3, 0.2, 0.9);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.8, 0);
	glScalef(0.3, 0.2, 0.9);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.8, -0.9);
	glScalef(0.3, 0.2, 0.9);
	glutSolidCube(1.0);
	glPopMatrix();
}

void aviao()
{
	glColor3f(0, 0, 1);

	corpo();
	cauda();
	asa(1);
	asa(-1);
}

void chao()
{
	glColor3f(0.4, 0.4, 0.4);
	glPushMatrix();
	glScalef(10.0, 0.1, 10.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glColor3f(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glScalef(3.0, 0.1, 10.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void frente(float y)
{
	glColor3f(0.0, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(-3.5, 0.5 + y, 0);
	glScalef(0.1, 0.9, 3.3);
	glutSolidCube(1.0);
	glPopMatrix();
}

void fundo(float y)
{
	glColor3f(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(-4.5, 0.5 + y, 0);
	glScalef(0.1, 0.9, 3.3);
	glutSolidCube(1.0);
	glPopMatrix();
}

void parede(float z, float y)
{
	glPushMatrix();
	glTranslatef(-4.0, 0.5 + y, z);
	glScalef(0.9, 0.9, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
}

void paredes(float y)
{
	glColor3f(0.6, 0.6, 0.6);

	parede(-1.6, y);
	parede(-0.8, y);
	parede(0, y);
	parede(0.8, y);
	parede(1.6, y);
}

void teto(float y)
{
	glColor3f(0.6, 0.6, 0.6);
	glPushMatrix();
	glTranslatef(-4.0, 1.0 + y, 0);
	glScalef(1.1, 0.1, 3.3);
	glutSolidCube(1.0);
	glPopMatrix();
}

void andar(float y)
{
	fundo(y);
	paredes(y);
	frente(y);
	teto(y);
}

void predio()
{
	andar(0);
	andar(1);
	andar(2);
}

void torre_controle()
{
	glColor3f(0.8, 0.8, 0.8);
	glPushMatrix();
	glTranslatef(3, 1, -3);
	glScalef(0.5, 2, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.2, 0, 0);
	glPushMatrix();
	glTranslatef(3, 2, -3);
	glScalef(0.5, 2, 0.5);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1, 1, 8, 8);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(3, 4, -3);
	glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

	glTranslatef(0, 0, (GLfloat)pos);
	glRotatef((GLfloat)rot, 0.0, 1.0, 0.0);

    chao();
    predio();
    aviao();
	torre_controle();

	glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
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
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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
