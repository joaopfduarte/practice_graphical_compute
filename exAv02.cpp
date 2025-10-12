#include "header/exAv02.h"
//
// Created by joaop on 9/27/2025.
//
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <random>
#include <format>

const double PI = 3.1415926535;

int raioCirculo = 8;
int totalDeVoltas = 0;
int numEstrelas = rand() % 100 + 1;

float angulo = 0;
float anguloOrbita = 0.0f;

bool orbitaEliptica = false;

float xAzul = 0.0f, yAzul = 0.0f, anguloOrbitaPlaneta = 0.0f;


static void key(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }

    if (key == 'T' || key == 't') {
        orbitaEliptica = !orbitaEliptica;
        glutPostRedisplay();
    }
}

void specialKeys(int key, int x, int y) {
    glutPostRedisplay();
}

// Fun  o de callback chamada sempre que a janela é redimensionada.
static void resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void desenhaPontosAleatorios() {
    glPointSize(2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < numEstrelas; i++) {
        glVertex2f((rand() % 81) - 40, (rand() % 81) - 40);
    }
    glEnd();
}

void desenhaTexto(const char *string) {
    glPushMatrix();
    // Posição no universo onde o texto será colocado
    glRasterPos2f(-35, -32 - (32 * 0.08));
    // Exibe caracter a caracter
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    glPopMatrix();
}

void desenhaPlanetaAzul() {
    int raioPlaneta = 4;
    float angulo, incremento;
    incremento = (2 * M_PI) / 100;
    glBegin(GL_POLYGON);
    for (angulo = 0; angulo < 2 * M_PI; angulo += incremento) {
        glVertex2f(cos(angulo) * raioPlaneta, sin(angulo) * raioPlaneta);
    }
    glEnd();
}

void desenhaOrbita() {
    if (!orbitaEliptica) {
        int raioOrbita = 25;
        float incremento;
        incremento = (2 * M_PI) / 100;
        glBegin(GL_LINE_LOOP);
        for (anguloOrbita = 0; anguloOrbita < 2 * M_PI; anguloOrbita += incremento) {
            glVertex2f(cos(anguloOrbita) * raioOrbita, sin(anguloOrbita) * raioOrbita);
        }
        glEnd();
    } else {
        float Segments, x, y;
        glBegin(GL_LINE_STRIP);
        Segments = 100.f;
        for (float angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI / Segments)) {
            x = cos(angle) * 25;
            y = sin(angle) * 15;
            glVertex3f(x, y, 0);
        }
        glEnd();
    }
}

void desenhaSol(float raio) {
    float angulo, incremento;
    incremento = (2 * M_PI) / 100;
    glBegin(GL_POLYGON);
    for (angulo = 0; angulo < 2 * M_PI; angulo += incremento) {
        glVertex2f(cos(angulo) * raio, sin(angulo) * raio);
    }
    glEnd();
}

void atualizaCena(int valor) {
    anguloOrbitaPlaneta += 0.02f; // Ajuste a velocidade conforme necessário
    if (anguloOrbitaPlaneta > 2 * PI) anguloOrbitaPlaneta -= 2 * PI;

    if (!orbitaEliptica) {
        xAzul = cos(anguloOrbitaPlaneta) * 25;
        yAzul = sin(anguloOrbitaPlaneta) * 25;
    } else {
        xAzul = cos(anguloOrbitaPlaneta) * 25;
        yAzul = sin(anguloOrbitaPlaneta) * 15;
    }

    glutPostRedisplay();
    glutTimerFunc(100, atualizaCena, 0);
}

static void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    desenhaPontosAleatorios();

    glColor3f(1.0f, 0.0f, 0.0f);
    std::string mensagem = std::format("Translacao orbital: {}", totalDeVoltas);
    desenhaTexto(mensagem.c_str());

    glColor3f(0.8f, 0.8f, 0.8f);
    desenhaOrbita();

    glPushMatrix();
    glTranslatef(xAzul, yAzul, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    desenhaPlanetaAzul();
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f);
    desenhaSol(raioCirculo);

    glFlush();
}

void setup(void) {
    glViewport(0, 0, 600, 600);
    gluOrtho2D(-40.0f, 40.0f, -40.0f, 40.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 800);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Avaliacao 2 - Ex01");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKeys);
    glutReshapeFunc(resize);

    setup();
    glutTimerFunc(100, atualizaCena, 0);

    glutMainLoop();

    return 0;
}
