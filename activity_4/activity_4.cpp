#include<stdlib.h>
#include<GL/glut.h>

static int rot = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glRotatef((GLfloat)rot, 0.0, 1.0, 0.0);

    /* chao */
    glPushMatrix();
    glScalef(4.0, 0.2, 6.0);
    glutWireCube(1.0);
    glPopMatrix();

    /* parede esquerda */
    glPushMatrix();
    glTranslatef(-1.9, 1.6, 0.0);
    glScalef(0.2, 3.0, 6.0);
    glutWireCube(1.0);
    glPopMatrix();

    /*  parede fundo */
    glPushMatrix();
    glTranslatef(0.0, 1.6, -2.9);
    glScalef(4.0, 3.0, 0.2);
    glutWireCube(1.0);
    glPopMatrix();

    /* cama */
    glPushMatrix();
    glTranslatef(-1.3, 0.6, -1.6);
    glScalef(1.0, 0.2, 2.0);
    glutWireCube(1.0);
    glPopMatrix();

    /* pe cama frente esquerdo*/
    glPushMatrix();
    glTranslatef(-1.7, 0.3, -0.7);
    glScalef(0.2, 0.4, 0.2);
    glutWireCube(1.0);
    glPopMatrix();

    /* pe cama frente direito*/
    glPushMatrix();
    glTranslatef(-0.9, 0.3, -0.7);
    glScalef(0.2, 0.4, 0.2);
    glutWireCube(1.0);
    glPopMatrix();

    /* pe cama cabeceira esquerdo*/
    glPushMatrix();
    glTranslatef(-1.7, 0.6, -2.7);
    glScalef(0.2, 1.0, 0.2);
    glutWireCube(1.0);
    glPopMatrix();

    /* pe cama cabeceira esquerdo*/
    glPushMatrix();
    glTranslatef(-0.9, 0.6, -2.7);
    glScalef(0.2, 1.0, 0.2);
    glutWireCube(1.0);
    glPopMatrix();

    // tampo
    glPushMatrix();
    glTranslatef(0, 1.05, -2.5);
    glScalef(0.8, 0.1, 0.6);
    glutWireCube(1.0);
    glPopMatrix();

    // primeira gaveta
    glPushMatrix();
    glTranslatef(0, 0.55, -2.5);
    glScalef(0.8, 0.3, 0.6);
    glutWireCube(1.0);
    glPopMatrix();

    // puxador primeira gaveta
    glPushMatrix();
    glTranslatef(0, 0.55, -2.15);
    glScalef(0.2, 0.1, 0.1);
    glutWireCube(1.0);
    glPopMatrix();

    // segunda gaveta
    glPushMatrix();
    glTranslatef(0, 0.25, -2.5);
    glScalef(0.8, 0.3, 0.6);
    glutWireCube(1.0);
    glPopMatrix();

    // puxador segunda gaveta
    glPushMatrix();
    glTranslatef(0, 0.25, -2.15);
    glScalef(0.2, 0.1, 0.1);
    glutWireCube(1.0);
    glPopMatrix();

    // lateral direita
    glPushMatrix();
    glTranslatef(-0.35, 0.85, -2.5);
    glScalef(0.1, 0.3, 0.6);
    glutWireCube(1.0);
    glPopMatrix();

	// lateral esquerda
    glPushMatrix();
    glTranslatef(0.35, 0.85, -2.5);
    glScalef(0.1, 0.3, 0.6);
    glutWireCube(1.0);
    glPopMatrix();

	// fundo
    glPushMatrix();
    glTranslatef(0, 0.85, -2.75);
    glScalef(0.6, 0.3, 0.1);
    glutWireCube(1.0);
    glPopMatrix();

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
    case 'r':
        rot = (rot + 5) % 360;
        glutPostRedisplay();
        break;
    case 'R':
        rot = (rot - 5) % 360;
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
