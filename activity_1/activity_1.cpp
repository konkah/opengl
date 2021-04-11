#include <GL/glut.h>
#include <stdlib.h>

// prototipos das funcoes
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

// funcao principal
int main(int argc, char** argv) {
	glutInit(&argc, argv);                         // inicializa o glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // especifica uso de cores e buffers
	glutInitWindowSize(256, 256);                 // especifica as dimensoes da janela
	glutInitWindowPosition(100, 100);       // especifica aonde a janela aparece na tela
	glutCreateWindow("Desenhando uma linha");              // cria a janela
	init();
	glutDisplayFunc(display);               // funcao que sera redesenhada pelo GLUT
	glutKeyboardFunc(keyboard);                    // funcoes de teclado
	glutMainLoop();                               // mostra todas as janelas criadas
	return 0;
}

// definicao de cada funcao

void init(void) {
	glClearColor(0.0, 0.0, 1.0, 1.0);    // cor de fundo
	glOrtho(0, 256, 0, 256, -1, 1);     // modo de projecao ortogonal
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);               // limpa a janela
	glColor3f(1.0, 0.0, 0.0);                  // cor da linha
	glLineWidth(4.0);
	glBegin(GL_QUADS);
	glVertex2i(40, 40);
	glVertex2i(40, 100);
	glVertex2i(100, 100);
	glVertex2i(100, 40);
	glEnd();
	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 69:
		exit(0);
		break;
	case 101:
		exit(0);
		break;
	}
}
