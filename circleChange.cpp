//
// Created by joaop on 9/27/2025.
//

#include "header/circleChange.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>

//Variáveis globais
int raioCirculo = 3;
int tamanhoQuadrado = 3;
float angulo = 0;

std::vector<float> quadOne = {1.0f, 1.0f, 0.0f};
std::vector<float> quadTwo = {0.0f, 1.0f, 0.0f};
std::vector<float> quadThree = {0.0f, 1.0f, 1.0f};
std::vector<float> quadFour = {1.0f, 0.0f, 0.0f};

std::vector<float> quadPosOne = {-20.0f, 20.0f, 0.0f};
std::vector<float> quadPosTwo = {20.0f, 20.0f, 0.0f};
std::vector<float> quadPosThree = {-20.0f, -20.0f, 0.0f};
std::vector<float> quadPosFour = {20.0f, -20.0f, 0.0f};


void transladaQuadrado(char tipo) {
    switch (tipo) {
        case 'l':
            quadPosOne[0] = quadPosOne[0] - 1.0f;
            quadPosTwo[0] = quadPosTwo[0] - 1.0f;
            quadPosThree[0] = quadPosThree[0] - 1.0f;
            quadPosFour[0] = quadPosFour[0] - 1.0f;
            break;
        case 'r':
            quadPosOne[0] = quadPosOne[0] + 1.0f;
            quadPosTwo[0] = quadPosTwo[0] + 1.0f;
            quadPosThree[0] = quadPosThree[0] + 1.0f;
            quadPosFour[0] = quadPosFour[0] + 1.0f;
            break;
        case 'd':
            quadPosOne[1] = quadPosOne[1] - 1.0f;
            quadPosTwo[1] = quadPosTwo[1] - 1.0f;
            quadPosThree[1] = quadPosThree[1] - 1.0f;
            quadPosFour[1] = quadPosFour[1] - 1.0f;
            break;
        case 'u':
            quadPosOne[1] = quadPosOne[1] + 1.0f;
            quadPosTwo[1] = quadPosTwo[1] + 1.0f;
            quadPosThree[1] = quadPosThree[1] + 1.0f;
            quadPosFour[1] = quadPosFour[1] + 1.0f;
            break;
    }
}


static void key(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            angulo += 10;
            transladaQuadrado('l');
            break;
        case GLUT_KEY_RIGHT:
            angulo -= 10;
            transladaQuadrado('r');
            break;
        case GLUT_KEY_UP:
            angulo += 10;
            transladaQuadrado('u');
            break;
        case GLUT_KEY_DOWN:
            angulo -= 10;
            transladaQuadrado('d');
            break;
        case GLUT_KEY_PAGE_UP:
            raioCirculo += 1;
            break;
        case GLUT_KEY_PAGE_DOWN:
            raioCirculo -= 1;
            break;
        case GLUT_KEY_HOME:
            tamanhoQuadrado += 1;
            break;
        case GLUT_KEY_END:
            tamanhoQuadrado -= 1;
            break;
    }
    glutPostRedisplay();
}

// Fun  o de callback chamada sempre que a janela é redimensionada.
static void resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void desenhaEixoCoordenado() {
    glBegin(GL_LINES);
    glColor3f(1, 1, 0);
    glVertex2f(-40.0f, 0.0f);
    glVertex2f(40.0f, 0.0f);
    glVertex2f(0.0f, -40.0f);
    glVertex2f(0.0f, 40.0f);
    glEnd();
}

void desenhaCirculo(float raio) {
    float angulo, incremento;
    incremento = (2 * M_PI) / 10;
    glBegin(GL_POLYGON);
    for (angulo = 0; angulo < 2 * M_PI; angulo += incremento) {
        glVertex2f(cos(angulo) * raio, sin(angulo) * raio);
    }
    glEnd();
}

void desenhaQuadrado() {
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();
}


void rotacionaCirculo() {
    // deve aplicar a translação para origem :: rotação :: traslação inversa
    glPushMatrix();
    //glTranslatef(10.0f, 0.0f, 0.0f);
    glRotatef(angulo, 0.0f, 0.0f, 1.0f);
    //glTranslatef(-10.0f, 0.0f, 0.0f);
    glScalef((float)raioCirculo, (float)raioCirculo, 1.0f);
    desenhaCirculo(raioCirculo);
    glPopMatrix();
}

void PosicionaQuadrado() {
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        switch (i) {
            case 0:
                glTranslatef(quadPosOne[0], quadPosOne[1], quadPosOne[2]);
                glColor3f(quadOne[0], quadOne[1], quadOne[2]);
                break;
            case 1:
                glTranslatef(quadPosTwo[0], quadPosTwo[1], quadPosTwo[2]);
                glColor3f(quadTwo[0], quadTwo[1], quadTwo[2]);
                break;
            case 2:
                glTranslatef(quadPosThree[0], quadPosThree[1], quadPosThree[2]);
                glColor3f(quadThree[0], quadThree[1], quadThree[2]);
                break;
            case 3:
                glTranslatef(quadPosFour[0], quadPosFour[1], quadPosFour[2]);
                glColor3f(quadFour[0], quadFour[1], quadFour[2]);
                break;
        }
        glScalef((float)tamanhoQuadrado, (float)tamanhoQuadrado, 1.0f);
        desenhaQuadrado();
        glPopMatrix();
    }
}

void mudaEscala() {
    // deve aplicar a translação para origem :: ampliação/redução :: translação inversa
    //glScalef(x,y,z);
}

static void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    desenhaEixoCoordenado();

    glColor3f(1.0f, 0.0f, 1.0f);
    rotacionaCirculo();

    PosicionaQuadrado();

    glFlush();
}

void setup(void) {
    glViewport(0, 0, 400, 400);
    gluOrtho2D(-40.0f, 40.0f, -40.0f, 40.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(400, 400);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Pratica 04 - Exemplo 02");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKeys);
    glutReshapeFunc(resize);

    setup();

    glutMainLoop();

    return 0;
}
