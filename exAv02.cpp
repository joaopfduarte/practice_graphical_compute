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
#include <cmath>

const float PI = 3.1415926535;

int raioCirculo = 8;
int totalDeVoltas = 0;
int totalDeRotacoes = 0;
int numEstrelas = rand() % 100 + 1;

float anguloOrbita = 0.0f;
float anguloRotacao = 0.0f;

bool orbitaEliptica = false;
bool mostradorDeEstrelas = true;
bool pause = false;
bool inverteSentido = false;

float xAzul = 0.0f, yAzul = 0.0f, anguloOrbitaPlaneta = PI / 2.0f;
float xLuaEsquerda = 0.0f, yLuaEsquerda = 0.0f;
float xLuaDireita = 0.0f, yLuaDireita = 0.0f;

float anguloOrbitaLuas = 0.0f;
float raioOrbitaLuas = 5.0f;

float zoom = 1.0f;
const float ZOOM_MIN = 0.3f;
const float ZOOM_MAX = 400.0f;

static void key(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }

    if ((key == 'T' || key == 't') && !pause) {
        orbitaEliptica = !orbitaEliptica;
        glutPostRedisplay();
    }

    if (key == 'E' || key == 'e') {
        mostradorDeEstrelas = !mostradorDeEstrelas;
    }

    if (key == 'P' || key == 'p') {
        pause = !pause;
        glutPostRedisplay();
    }

    if ((key == 'I' || key == 'i') && !pause) {
        inverteSentido = !inverteSentido;
        glutPostRedisplay();
    }
}

void atualizaProjecao() {
    float half = 40.0f / zoom;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-half, half, -half, half);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN)
        return;

    if (button == GLUT_LEFT_BUTTON) {
        zoom *= 1.1f;
        if (zoom > ZOOM_MAX) { zoom = ZOOM_MAX; }
    } else if (button == GLUT_RIGHT_BUTTON) {
        zoom /= 1.1f;
        if (zoom < ZOOM_MIN) { zoom = ZOOM_MIN; }
    }

    atualizaProjecao();
    glutPostRedisplay();
}

static void resize(int width, int height) {
    glViewport(0, 0, width, height);
    atualizaProjecao();
}

/*
 * EXP: Função de print fixo das estrelas na tela
 */
void desenhaPontosAleatorios() {
    if (!mostradorDeEstrelas) {
        return;
    }

    glPushMatrix();

    glScalef(1.0f / zoom, 1.0f / zoom, 1.0f);

    glPointSize(1.5f / zoom);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < numEstrelas; i++) {
        glVertex2f((rand() % 81) - 40, (rand() % 81) - 40);
    }
    glEnd();

    glPopMatrix();
}

/*
 * EXP: Função de print fixo dos dados na tela
 */
void desenhaTextoTela(float x, float y, const char *string) {
    // Salva o estado atual
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0, 100, 0, 100);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos2f(x, y);
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);

    // Restaura as matrizes
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void desenhaPlanetaAzul() {
    int raioPlaneta = 3;
    float angulo, incremento;
    incremento = (2 * M_PI) / 100;
    glBegin(GL_POLYGON);
    for (angulo = 0; angulo < 2 * M_PI; angulo += incremento) {
        glVertex2f(cos(angulo) * raioPlaneta, sin(angulo) * raioPlaneta);
    }
    glEnd();
}

void desenhaLuaPlanetaAzul() {
    float raioPlaneta = 0.5f;
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
        incremento = (2 * M_PI) / 200;
        glBegin(GL_LINE_LOOP);
        for (anguloOrbita = 0; anguloOrbita < 2 * M_PI; anguloOrbita += incremento) {
            glVertex2f(cos(anguloOrbita) * raioOrbita, sin(anguloOrbita) * raioOrbita);
            anguloRotacao += 0.05f;
        }
        glEnd();
    } else {
        float segmentos, x, y;
        glBegin(GL_LINE_STRIP);
        segmentos = 200.f;
        for (float angle = 0.0f; angle <= (2.0f * PI); angle += (2.0f * PI / segmentos)) {
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
    if (!pause) {
        static float anguloAnteriorOrbitaPlaneta = anguloOrbitaPlaneta;

        if (!inverteSentido) {
            anguloOrbitaPlaneta += 0.09f;

            if (anguloOrbitaPlaneta > 2 * PI) {
                anguloOrbitaPlaneta -= 2 * PI;
            }

            if (anguloAnteriorOrbitaPlaneta < PI / 2.0f && anguloOrbitaPlaneta >= PI / 2.0f) {
                totalDeVoltas++;
            }

            anguloAnteriorOrbitaPlaneta = anguloOrbitaPlaneta;

            if (!orbitaEliptica) {
                xAzul = -cos(anguloOrbitaPlaneta) * 25;
                yAzul = sin(anguloOrbitaPlaneta) * 25;
            } else {
                xAzul = -cos(anguloOrbitaPlaneta) * 25;
                yAzul = sin(anguloOrbitaPlaneta) * 15;
            }
        } else {
            anguloOrbitaPlaneta += 0.09f;

            if (anguloOrbitaPlaneta > 2 * PI) {
                anguloOrbitaPlaneta -= 2 * PI;
            }

            if (anguloAnteriorOrbitaPlaneta < PI / 2.0f && anguloOrbitaPlaneta >= PI / 2.0f) {
                totalDeVoltas--;
            }

            anguloAnteriorOrbitaPlaneta = anguloOrbitaPlaneta;

            if (!orbitaEliptica) {
                xAzul = -cos(anguloOrbitaPlaneta) * 25;
                yAzul = -sin(anguloOrbitaPlaneta) * 25;
            } else {
                xAzul = -cos(anguloOrbitaPlaneta) * 25;
                yAzul = -sin(anguloOrbitaPlaneta) * 15;
            }
        }
        if (!inverteSentido) {
            anguloOrbitaLuas += 0.15f;
        } else {
            anguloOrbitaLuas -= 0.15f;
        }

        if (anguloOrbitaLuas > 2 * PI) {
            anguloOrbitaLuas -= 2 * PI;
            totalDeRotacoes++;
        } else if (anguloOrbitaLuas < 0) {
            anguloOrbitaLuas += 2 * PI;
            totalDeRotacoes--;
        }

        glutPostRedisplay();
    }
    glutTimerFunc(100, atualizaCena, 0);
}

static void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    desenhaPontosAleatorios();

    std::string mensagemContador = std::format("Translacao orbital: {}", totalDeVoltas);
    glColor3f(1.0f, 0.0f, 0.0f);
    desenhaTextoTela(5, 5, mensagemContador.c_str()); // canto inferior esquerdo

    std::string mensagemContadorRotacoes = std::format("Rotacoes: {}", totalDeRotacoes);
    glColor3f(1.0f, 0.0f, 0.0f);
    desenhaTextoTela(5, 8, mensagemContadorRotacoes.c_str()); // canto inferior esquerdo

    if (pause) {
        std::string mensagemPause = "*** PAUSE ***";
        glColor3f(1.0f, 0.0f, 0.0f);
        desenhaTextoTela(42, 95, mensagemPause.c_str()); // topo central
    }

    glColor3f(0.8f, 0.8f, 0.8f);
    desenhaOrbita();
    
    //planeta azul
    glPushMatrix();
    glTranslatef(xAzul, yAzul, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    desenhaPlanetaAzul();

    // Lua direita
    glPushMatrix();
    glRotatef(anguloOrbitaLuas * (180.0f / PI), 0, 0, 1);
    glTranslatef(raioOrbitaLuas, 0, 0);
    glColor3f(1.0f, 0.0f, 1.0f);
    desenhaLuaPlanetaAzul();
    glPopMatrix();

    // Lua esquerda
    glPushMatrix();
    glRotatef((anguloOrbitaLuas * (180.0f / PI)) - 180.0f, 0, 0, 1);
    glTranslatef(raioOrbitaLuas, 0, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    desenhaLuaPlanetaAzul();
    glPopMatrix();

    glPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f);
    desenhaSol(raioCirculo);

    glFlush();
}

void setup(void) {
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
    glutMouseFunc(mouse);
    glutReshapeFunc(resize);

    setup();
    glutTimerFunc(100, atualizaCena, 0);

    glutMainLoop();

    return 0;
}
