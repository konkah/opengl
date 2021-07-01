#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>

extern "C" {
	#include "image.h"
}

char TEXTURA_DO_PLANO[13] = "chao.rgb";
GLuint  textura_plano;

float inicial_aviao_y = -1.7;
float posicao_aviao_y = inicial_aviao_y;
float inicial_aviao_z = -2;
float posicao_aviao_z = inicial_aviao_z;
int rotacao_aviao_y = 0;

GLfloat posicao_luz[] = { 0.0, 3.0, 0.0, 1.0 };
GLfloat cor_luz[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat cor_luz_amb[] = { 0.7, 0.7, 0.7, 1.0 };

static int rot = 305;
static int pos = 0;

void material(float r, float g, float b, float a, float s)
{
	GLfloat ambiente[] = { r / 2, g / 2, b / 2, a };
	GLfloat difusa[] = { r, g, b, a };
	GLfloat especular[] = { s, s, s, a };
	GLfloat brilho[] = { 50 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difusa);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brilho);
}

//spot no avião
// difusa no chão e na torre
// distante da lua
void carregar_texturas() {
	IMAGE* img;

	// textura do plano
	glGenTextures(1, &textura_plano);
	glBindTexture(GL_TEXTURE_2D, textura_plano);

	if (!((img = ImageLoad(TEXTURA_DO_PLANO)))) {
		fprintf(stderr, "Error reading a texture.\n");
		exit(-1);
	}

	const GLenum gluerr = gluBuild2DMipmaps(
		GL_TEXTURE_2D, 3,
	    img->sizeX, img->sizeY,
        GL_RGB, GL_UNSIGNED_BYTE,
        img->data
	);

	if (gluerr) {
		fprintf(stderr, "GLULib%s\n", gluErrorString(gluerr));
		exit(-1);
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

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

	carregar_texturas();
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
	glPushMatrix();
	glTranslatef(0, posicao_aviao_y, posicao_aviao_z);
	glRotatef(rotacao_aviao_y, 0, 1, 0);
	
	material(0, 0, 1, 1, 1);

	corpo();
	cauda();
	asa(1);
	asa(-1);

	glPopMatrix();
}

void chao()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, textura_plano);

	GLfloat planotext[4][2] = {
	  {0,0},
	  {+1,0},
	  {+1,+1},
	  {0,+1}
	};

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2fv(planotext[0]);  glVertex3f(-5,  0,  5);
	glTexCoord2fv(planotext[1]);  glVertex3f( 5,  0,  5);
	glTexCoord2fv(planotext[2]);  glVertex3f( 5,  0, -5);
	glTexCoord2fv(planotext[3]);  glVertex3f(-5,  0, -5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void frente(float y)
{
	material(0.0, 0.8, 1, 0.6, 1);
	glPushMatrix();
	glTranslatef(-3.5, 0.5 + y, 0);
	glScalef(0.1, 0.9, 3.3);
	glutSolidCube(1.0);
	glPopMatrix();
}

void fundo(float y)
{
	material(0.6, 0.6, 0.6, 1, 0);
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
	material(0.6, 0.6, 0.6, 1, 0);

	parede(-1.6, y);
	parede(-0.8, y);
	parede(0, y);
	parede(0.8, y);
	parede(1.6, y);
}

void teto(float y)
{
	material(0.6, 0.6, 0.6, 1, 0);
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
	material(0.8, 0.8, 0.8, 1, 0);
	glPushMatrix();
	glTranslatef(3, 1, -3);
	glScalef(0.5, 2, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	material(0.5, 0, 0, 1, 0);
	glPushMatrix();
	glTranslatef(3, 2, -3);
	glScalef(0.5, 2, 0.5);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1, 1, 8, 8);
	glPopMatrix();

	material(1, 1, 0, 1, 1);
	glPushMatrix();
	glTranslatef(3, 4, -3);
	glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glPushMatrix();

	glTranslatef(0, 0, pos);
	glRotatef(rot, 0.0, 1.0, 0.0);

    chao();
    predio();
    aviao();
	torre_controle();

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

int timer = 33;
int variacao = 1;

void anima(int value)
{
	if (value >= 100)
	{
		rotacao_aviao_y = (value - 100) * 9;

		if (variacao == -1)
		{
			rotacao_aviao_y = 180 - rotacao_aviao_y;
		}
	}
	else if (value <= 0)
	{
		rotacao_aviao_y = value * 9 * variacao;

		if (variacao == -1)
		{
			rotacao_aviao_y = 180 + rotacao_aviao_y;
		}
	}
	else
	{
		float factor = value / 20.0;

		posicao_aviao_y = inicial_aviao_y + pow(factor, 2);
		posicao_aviao_z = inicial_aviao_z + 6 * factor;
	}
	
	if (value > 110)
	{
		variacao = -1;
	}

	if (value < -10)
	{
		variacao = 1;
	}

	// Redesenha o quadrado com as novas coordenadas 
	glutPostRedisplay();
	glutTimerFunc(timer, anima, value + variacao);
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
	glutTimerFunc(timer, anima, 1);
	glutMainLoop();
	return 0;
}
