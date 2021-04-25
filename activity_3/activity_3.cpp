#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

// prototipos das funcoes
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

// funcao principal
int main(int argc, char** argv) {
	glutInit(&argc, argv);                         // inicializa o glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // especifica uso de cores e buffers
	glutInitWindowSize(256, 256);                 // especifica as dimensoes da janela
	glutInitWindowPosition(100, 100);       // especifica aonde a janela aparece na tela
	glutCreateWindow("Malha Triangular");              // cria a janela
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(display);               // funcao que sera redesenhada pelo GLUT
	glutKeyboardFunc(keyboard);                    // funcoes de teclado
	glutMainLoop();                               // mostra todas as janelas criadas
	return 0;
}

// definicao de cada funcao

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);    // cor de fundo
	glOrtho(0, 256, 0, 256, -1, 1);     // modo de projecao ortogonal
}

int mode = GL_LINE;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(1.0);

	glPolygonMode(GL_FRONT, mode);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3d(1, 1, 1);

	glVertex2i(96, 96);
	glVertex2i(128, 96);
	glVertex2i(96, 128);
	glVertex2i(128, 160);
	glVertex2i(128, 160);
	glVertex2i(96, 160);
	glVertex2i(96, 128);
	glVertex2i(96, 128);
	glVertex2i(64, 128);
	glVertex2i(96, 160);
	glVertex2i(96, 160);

	glVertex2i(32, 224);
	glVertex2i(96, 160);
	glVertex2i(32, 160);
	glVertex2i(64, 128);
	glVertex2i(32, 96);
	glVertex2i(96, 96);
	glVertex2i(96, 32);
	glVertex2i(128, 64);
	glVertex2i(160, 32);
	glVertex2i(160, 96);
	glVertex2i(224, 96);
	glVertex2i(192, 128);
	glVertex2i(224, 160);
	glVertex2i(160, 160);
	glVertex2i(224, 224);

	glVertex2i(160, 160);
	glVertex2i(160, 160);
	glVertex2i(192, 128);
	glVertex2i(160, 128);
	glVertex2i(160, 128);
	glVertex2i(160, 160);
	glVertex2i(128, 160);
	glVertex2i(128, 160);
	glVertex2i(160, 128);
	glVertex2i(128, 96);
	glVertex2i(160, 96);

	glEnd();

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

void mouse(int button, int state, int x, int y) {
	if (state != GLUT_UP) {
		return;
	}

	if (mode == GL_LINE) {
		mode = GL_FILL;
	} else {
		mode = GL_LINE;
	}

	display();
}
